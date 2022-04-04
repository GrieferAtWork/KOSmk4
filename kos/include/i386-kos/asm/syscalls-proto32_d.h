/* HASH CRC-32:0xbfd0e64b */
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
#ifndef __NR32FEAT_DEFINED_SYSCALL_ATTR_NORETURN
#define __NR32FEAT_DEFINED_SYSCALL_ATTR_NORETURN
#define __NR32FEAT_HAVE_ATTR_NORETURN
#define __NR32NT_exit
#define __NR32NT_exit_group
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ATTR_NORETURN */
#endif /* __WANT_SYSCALL_ATTR_NORETURN */


/************************************************************************/
/* SYSCALL ARGUMENT COUNT                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_COUNT
#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#define __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT
#define __NR32AC_restart_syscall              0
#define __NR32AC_exit                         1
#define __NR32AC_fork                         0
#define __NR32AC_read                         3
#define __NR32AC_write                        3
#define __NR32AC_open                         3
#define __NR32AC_close                        1
#define __NR32AC_waitpid                      3
#define __NR32AC_creat                        2
#define __NR32AC_link                         2
#define __NR32AC_unlink                       1
#define __NR32AC_execve                       3
#define __NR32AC_chdir                        1
#define __NR32AC_time                         1
#define __NR32AC_mknod                        3
#define __NR32AC_chmod                        2
#define __NR32AC_lchown                       3
#define __NR32AC_break                        0
#define __NR32AC_oldstat                      2
#define __NR32AC_lseek                        3
#define __NR32AC_getpid                       0
#define __NR32AC_mount                        5
#define __NR32AC_umount                       1
#define __NR32AC_setuid                       1
#define __NR32AC_getuid                       0
#define __NR32AC_stime                        1
#define __NR32AC_ptrace                       4
#define __NR32AC_alarm                        1
#define __NR32AC_oldfstat                     2
#define __NR32AC_pause                        0
#define __NR32AC_utime                        2
#define __NR32AC_stty                         0
#define __NR32AC_gtty                         0
#define __NR32AC_access                       2
#define __NR32AC_nice                         1
#define __NR32AC_ftime                        1
#define __NR32AC_sync                         0
#define __NR32AC_kill                         2
#define __NR32AC_rename                       2
#define __NR32AC_mkdir                        2
#define __NR32AC_rmdir                        1
#define __NR32AC_dup                          1
#define __NR32AC_pipe                         1
#define __NR32AC_times                        1
#define __NR32AC_prof                         0
#define __NR32AC_brk                          1
#define __NR32AC_setgid                       1
#define __NR32AC_getgid                       0
#define __NR32AC_signal                       2
#define __NR32AC_geteuid                      0
#define __NR32AC_getegid                      0
#define __NR32AC_acct                         1
#define __NR32AC_umount2                      2
#define __NR32AC_lock                         0
#define __NR32AC_ioctl                        3
#define __NR32AC_fcntl                        3
#define __NR32AC_mpx                          0
#define __NR32AC_setpgid                      2
#define __NR32AC_ulimit                       0
#define __NR32AC_oldolduname                  1
#define __NR32AC_umask                        1
#define __NR32AC_chroot                       1
#define __NR32AC_ustat                        2
#define __NR32AC_dup2                         2
#define __NR32AC_getppid                      0
#define __NR32AC_getpgrp                      0
#define __NR32AC_setsid                       0
#define __NR32AC_sigaction                    3
#define __NR32AC_sgetmask                     0
#define __NR32AC_ssetmask                     1
#define __NR32AC_setreuid                     2
#define __NR32AC_setregid                     2
#define __NR32AC_sigsuspend                   1
#define __NR32AC_sigpending                   1
#define __NR32AC_sethostname                  2
#define __NR32AC_setrlimit                    2
#define __NR32AC_getrlimit                    2
#define __NR32AC_getrusage                    2
#define __NR32AC_gettimeofday                 2
#define __NR32AC_settimeofday                 2
#define __NR32AC_getgroups                    2
#define __NR32AC_setgroups                    2
#define __NR32AC_select                       1
#define __NR32AC_symlink                      2
#define __NR32AC_oldlstat                     2
#define __NR32AC_readlink                     3
#define __NR32AC_uselib                       1
#define __NR32AC_swapon                       2
#define __NR32AC_reboot                       1
#define __NR32AC_readdir                      2
#define __NR32AC_mmap                         6
#define __NR32AC_munmap                       2
#define __NR32AC_truncate                     2
#define __NR32AC_ftruncate                    2
#define __NR32AC_fchmod                       2
#define __NR32AC_fchown                       3
#define __NR32AC_getpriority                  2
#define __NR32AC_setpriority                  3
#define __NR32AC_profil                       0
#define __NR32AC_statfs                       2
#define __NR32AC_fstatfs                      2
#define __NR32AC_ioperm                       3
#define __NR32AC_socketcall                   2
#define __NR32AC_syslog                       3
#define __NR32AC_setitimer                    3
#define __NR32AC_getitimer                    2
#define __NR32AC_stat                         2
#define __NR32AC_lstat                        2
#define __NR32AC_fstat                        2
#define __NR32AC_olduname                     1
#define __NR32AC_iopl                         1
#define __NR32AC_vhangup                      0
#define __NR32AC_idle                         0
#define __NR32AC_vm86old                      1
#define __NR32AC_wait4                        4
#define __NR32AC_swapoff                      1
#define __NR32AC_sysinfo                      1
#define __NR32AC_ipc                          1
#define __NR32AC_fsync                        1
#define __NR32AC_sigreturn                    0
#define __NR32AC_clone                        5
#define __NR32AC_setdomainname                2
#define __NR32AC_uname                        1
#define __NR32AC_modify_ldt                   3
#define __NR32AC_adjtimex                     1
#define __NR32AC_mprotect                     3
#define __NR32AC_sigprocmask                  3
#define __NR32AC_create_module                0
#define __NR32AC_init_module                  3
#define __NR32AC_delete_module                2
#define __NR32AC_get_kernel_syms              0
#define __NR32AC_quotactl                     1
#define __NR32AC_getpgid                      1
#define __NR32AC_fchdir                       1
#define __NR32AC_bdflush                      1
#define __NR32AC_sysfs                        1
#define __NR32AC_personality                  1
#define __NR32AC_afs_syscall                  0
#define __NR32AC_setfsuid                     1
#define __NR32AC_setfsgid                     1
#define __NR32AC__llseek                      4
#define __NR32AC_getdents                     3
#define __NR32AC__newselect                   5
#define __NR32AC_flock                        2
#define __NR32AC_msync                        3
#define __NR32AC_readv                        3
#define __NR32AC_writev                       3
#define __NR32AC_getsid                       1
#define __NR32AC_fdatasync                    1
#define __NR32AC__sysctl                      1
#define __NR32AC_mlock                        2
#define __NR32AC_munlock                      2
#define __NR32AC_mlockall                     1
#define __NR32AC_munlockall                   0
#define __NR32AC_sched_setparam               2
#define __NR32AC_sched_getparam               2
#define __NR32AC_sched_setscheduler           3
#define __NR32AC_sched_getscheduler           1
#define __NR32AC_sched_yield                  0
#define __NR32AC_sched_get_priority_max       1
#define __NR32AC_sched_get_priority_min       1
#define __NR32AC_sched_rr_get_interval        2
#define __NR32AC_nanosleep                    2
#define __NR32AC_mremap                       5
#define __NR32AC_setresuid                    3
#define __NR32AC_getresuid                    3
#define __NR32AC_vm86                         1
#define __NR32AC_query_module                 0
#define __NR32AC_poll                         3
#define __NR32AC_nfsservctl                   1
#define __NR32AC_setresgid                    3
#define __NR32AC_getresgid                    3
#define __NR32AC_prctl                        5
#define __NR32AC_rt_sigreturn                 0
#define __NR32AC_rt_sigaction                 4
#define __NR32AC_rt_sigprocmask               4
#define __NR32AC_rt_sigpending                2
#define __NR32AC_rt_sigtimedwait              4
#define __NR32AC_rt_sigqueueinfo              3
#define __NR32AC_rt_sigsuspend                2
#define __NR32AC_pread64                      4
#define __NR32AC_pwrite64                     4
#define __NR32AC_chown                        3
#define __NR32AC_getcwd                       2
#define __NR32AC_capget                       1
#define __NR32AC_capset                       1
#define __NR32AC_sigaltstack                  2
#define __NR32AC_sendfile                     4
#define __NR32AC_getpmsg                      0
#define __NR32AC_putpmsg                      0
#define __NR32AC_vfork                        0
#define __NR32AC_ugetrlimit                   1
#define __NR32AC_mmap2                        6
#define __NR32AC_truncate64                   2
#define __NR32AC_ftruncate64                  2
#define __NR32AC_stat64                       2
#define __NR32AC_lstat64                      2
#define __NR32AC_fstat64                      2
#define __NR32AC_lchown32                     3
#define __NR32AC_getuid32                     0
#define __NR32AC_getgid32                     0
#define __NR32AC_geteuid32                    0
#define __NR32AC_getegid32                    0
#define __NR32AC_setreuid32                   2
#define __NR32AC_setregid32                   2
#define __NR32AC_getgroups32                  2
#define __NR32AC_setgroups32                  2
#define __NR32AC_fchown32                     3
#define __NR32AC_setresuid32                  3
#define __NR32AC_getresuid32                  3
#define __NR32AC_setresgid32                  3
#define __NR32AC_getresgid32                  3
#define __NR32AC_chown32                      3
#define __NR32AC_setuid32                     1
#define __NR32AC_setgid32                     1
#define __NR32AC_setfsuid32                   1
#define __NR32AC_setfsgid32                   1
#define __NR32AC_pivot_root                   1
#define __NR32AC_mincore                      3
#define __NR32AC_madvise                      3
#define __NR32AC_getdents64                   3
#define __NR32AC_fcntl64                      3
#define __NR32AC_gettid                       0
#define __NR32AC_readahead                    3
#define __NR32AC_setxattr                     5
#define __NR32AC_lsetxattr                    5
#define __NR32AC_fsetxattr                    5
#define __NR32AC_getxattr                     4
#define __NR32AC_lgetxattr                    4
#define __NR32AC_fgetxattr                    4
#define __NR32AC_listxattr                    3
#define __NR32AC_llistxattr                   3
#define __NR32AC_flistxattr                   3
#define __NR32AC_removexattr                  2
#define __NR32AC_lremovexattr                 2
#define __NR32AC_fremovexattr                 2
#define __NR32AC_tkill                        2
#define __NR32AC_sendfile64                   4
#define __NR32AC_futex                        6
#define __NR32AC_sched_setaffinity            3
#define __NR32AC_sched_getaffinity            3
#define __NR32AC_set_thread_area              1
#define __NR32AC_get_thread_area              1
#define __NR32AC_io_setup                     1
#define __NR32AC_io_destroy                   1
#define __NR32AC_io_getevents                 1
#define __NR32AC_io_submit                    1
#define __NR32AC_io_cancel                    1
#define __NR32AC_fadvise64                    1
#define __NR32AC_exit_group                   1
#define __NR32AC_lookup_dcookie               1
#define __NR32AC_epoll_create                 1
#define __NR32AC_epoll_ctl                    4
#define __NR32AC_epoll_wait                   4
#define __NR32AC_remap_file_pages             5
#define __NR32AC_set_tid_address              1
#define __NR32AC_timer_create                 3
#define __NR32AC_timer_settime                4
#define __NR32AC_timer_gettime                2
#define __NR32AC_timer_getoverrun             1
#define __NR32AC_timer_delete                 1
#define __NR32AC_clock_settime                2
#define __NR32AC_clock_gettime                2
#define __NR32AC_clock_getres                 2
#define __NR32AC_clock_nanosleep              4
#define __NR32AC_statfs64                     2
#define __NR32AC_fstatfs64                    2
#define __NR32AC_tgkill                       3
#define __NR32AC_utimes                       2
#define __NR32AC_fadvise64_64                 1
#define __NR32AC_vserver                      0
#define __NR32AC_mbind                        1
#define __NR32AC_get_mempolicy                1
#define __NR32AC_set_mempolicy                1
#define __NR32AC_mq_open                      3
#define __NR32AC_mq_unlink                    1
#define __NR32AC_mq_timedsend                 5
#define __NR32AC_mq_timedreceive              5
#define __NR32AC_mq_notify                    2
#define __NR32AC_mq_getsetattr                3
#define __NR32AC_kexec_load                   1
#define __NR32AC_waitid                       5
#define __NR32AC_add_key                      1
#define __NR32AC_request_key                  1
#define __NR32AC_keyctl                       1
#define __NR32AC_ioprio_set                   3
#define __NR32AC_ioprio_get                   2
#define __NR32AC_inotify_init                 0
#define __NR32AC_inotify_add_watch            3
#define __NR32AC_inotify_rm_watch             2
#define __NR32AC_migrate_pages                1
#define __NR32AC_openat                       4
#define __NR32AC_mkdirat                      3
#define __NR32AC_mknodat                      4
#define __NR32AC_fchownat                     5
#define __NR32AC_futimesat                    3
#define __NR32AC_fstatat64                    4
#define __NR32AC_unlinkat                     3
#define __NR32AC_renameat                     4
#define __NR32AC_linkat                       5
#define __NR32AC_symlinkat                    3
#define __NR32AC_readlinkat                   4
#define __NR32AC_fchmodat                     4
#define __NR32AC_faccessat                    3
#define __NR32AC_pselect6                     6
#define __NR32AC_ppoll                        5
#define __NR32AC_unshare                      1
#define __NR32AC_set_robust_list              1
#define __NR32AC_get_robust_list              1
#define __NR32AC_splice                       6
#define __NR32AC_sync_file_range              4
#define __NR32AC_tee                          4
#define __NR32AC_vmsplice                     4
#define __NR32AC_move_pages                   1
#define __NR32AC_getcpu                       3
#define __NR32AC_epoll_pwait                  6
#define __NR32AC_utimensat                    4
#define __NR32AC_signalfd                     3
#define __NR32AC_timerfd_create               2
#define __NR32AC_eventfd                      1
#define __NR32AC_fallocate                    4
#define __NR32AC_timerfd_settime              4
#define __NR32AC_timerfd_gettime              2
#define __NR32AC_signalfd4                    4
#define __NR32AC_eventfd2                     2
#define __NR32AC_epoll_create1                1
#define __NR32AC_dup3                         3
#define __NR32AC_pipe2                        2
#define __NR32AC_inotify_init1                1
#define __NR32AC_preadv                       4
#define __NR32AC_pwritev                      4
#define __NR32AC_rt_tgsigqueueinfo            4
#define __NR32AC_perf_event_open              1
#define __NR32AC_recvmmsg                     5
#define __NR32AC_fanotify_init                1
#define __NR32AC_fanotify_mark                1
#define __NR32AC_prlimit64                    4
#define __NR32AC_name_to_handle_at            5
#define __NR32AC_open_by_handle_at            3
#define __NR32AC_clock_adjtime                1
#define __NR32AC_syncfs                       1
#define __NR32AC_sendmmsg                     4
#define __NR32AC_setns                        2
#define __NR32AC_process_vm_readv             6
#define __NR32AC_process_vm_writev            6
#define __NR32AC_kcmp                         5
#define __NR32AC_finit_module                 3
#define __NR32AC_sched_setattr                1
#define __NR32AC_sched_getattr                1
#define __NR32AC_renameat2                    5
#define __NR32AC_seccomp                      1
#define __NR32AC_getrandom                    3
#define __NR32AC_memfd_create                 2
#define __NR32AC_bpf                          1
#define __NR32AC_execveat                     5
#define __NR32AC_socket                       3
#define __NR32AC_socketpair                   4
#define __NR32AC_bind                         3
#define __NR32AC_connect                      3
#define __NR32AC_listen                       2
#define __NR32AC_accept4                      4
#define __NR32AC_getsockopt                   5
#define __NR32AC_setsockopt                   5
#define __NR32AC_getsockname                  3
#define __NR32AC_getpeername                  3
#define __NR32AC_sendto                       6
#define __NR32AC_sendmsg                      3
#define __NR32AC_recvfrom                     6
#define __NR32AC_recvmsg                      3
#define __NR32AC_shutdown                     2
#define __NR32AC_userfaultfd                  1
#define __NR32AC_membarrier                   1
#define __NR32AC_mlock2                       3
#define __NR32AC_copy_file_range              1
#define __NR32AC_preadv2                      1
#define __NR32AC_pwritev2                     1
#define __NR32AC_pkey_mprotect                4
#define __NR32AC_pkey_alloc                   2
#define __NR32AC_pkey_free                    1
#define __NR32AC_statx                        1
#define __NR32AC_arch_prctl                   2
#define __NR32AC_io_pgetevents                1
#define __NR32AC_rseq                         1
#define __NR32AC_semget                       1
#define __NR32AC_semctl                       1
#define __NR32AC_shmget                       3
#define __NR32AC_shmctl                       3
#define __NR32AC_shmat                        3
#define __NR32AC_shmdt                        1
#define __NR32AC_msgget                       1
#define __NR32AC_msgsnd                       1
#define __NR32AC_msgrcv                       1
#define __NR32AC_msgctl                       1
#define __NR32AC_clock_gettime64              2
#define __NR32AC_clock_settime64              2
#define __NR32AC_clock_adjtime64              1
#define __NR32AC_clock_getres_time64          2
#define __NR32AC_clock_nanosleep_time64       4
#define __NR32AC_timer_gettime64              2
#define __NR32AC_timer_settime64              4
#define __NR32AC_timerfd_gettime64            2
#define __NR32AC_timerfd_settime64            4
#define __NR32AC_utimensat_time64             4
#define __NR32AC_pselect6_time64              6
#define __NR32AC_ppoll_time64                 5
#define __NR32AC_io_pgetevents_time64         1
#define __NR32AC_recvmmsg_time64              5
#define __NR32AC_mq_timedsend_time64          5
#define __NR32AC_mq_timedreceive_time64       5
#define __NR32AC_semtimedop_time64            1
#define __NR32AC_rt_sigtimedwait_time64       4
#define __NR32AC_futex_time64                 6
#define __NR32AC_sched_rr_get_interval_time64 2
#define __NR32AC_pidfd_send_signal            4
#define __NR32AC_io_uring_setup               1
#define __NR32AC_io_uring_enter               1
#define __NR32AC_io_uring_register            1
#define __NR32AC_open_tree                    1
#define __NR32AC_move_mount                   1
#define __NR32AC_fsopen                       1
#define __NR32AC_fsconfig                     1
#define __NR32AC_fsmount                      1
#define __NR32AC_fspick                       1
#define __NR32AC_pidfd_open                   2
#define __NR32AC_clone3                       2
#define __NR32AC_close_range                  3
#define __NR32AC_openat2                      1
#define __NR32AC_pidfd_getfd                  3
#define __NR32AC_faccessat2                   4
#define __NR32AC_pwritevf                     5
#define __NR32AC_preadvf                      5
#define __NR32AC_fallocate64                  4
#define __NR32AC_freadlinkat                  5
#define __NR32AC_fsymlinkat                   4
#define __NR32AC_kfstatat                     4
#define __NR32AC_futimesat64                  3
#define __NR32AC_fmknodat                     5
#define __NR32AC_fmkdirat                     4
#define __NR32AC_inotify_add_watch_at         5
#define __NR32AC_waitid64                     5
#define __NR32AC_utimes64                     2
#define __NR32AC_kreaddirf                    5
#define __NR32AC_kfstat                       2
#define __NR32AC_klstat                       2
#define __NR32AC_kstat                        2
#define __NR32AC_pwrite64f                    5
#define __NR32AC_pread64f                     5
#define __NR32AC_ksigreturn                   6
#define __NR32AC_nanosleep64                  2
#define __NR32AC_rpc_serve                    0
#define __NR32AC_ksysctl                      2
#define __NR32AC_writevf                      4
#define __NR32AC_readvf                       4
#define __NR32AC_kreaddir                     4
#define __NR32AC_wait4_64                     4
#define __NR32AC_getitimer64                  2
#define __NR32AC_setitimer64                  3
#define __NR32AC_maplibrary                   5
#define __NR32AC_select64                     5
#define __NR32AC_settimeofday64               2
#define __NR32AC_gettimeofday64               2
#define __NR32AC_getrusage64                  2
#define __NR32AC_fsmode                       1
#define __NR32AC_ioctlf                       4
#define __NR32AC_rtm_test                     0
#define __NR32AC_rtm_abort                    1
#define __NR32AC_rtm_end                      0
#define __NR32AC_rtm_begin                    0
#define __NR32AC_ftime64                      1
#define __NR32AC_rpc_serve_sysret             0
#define __NR32AC_set_userprocmask_address     1
#define __NR32AC_utime64                      2
#define __NR32AC_userviofd                    2
#define __NR32AC_stime64                      1
#define __NR32AC_coredump                     6
#define __NR32AC_mktty                        4
#define __NR32AC_lfutexexpr                   5
#define __NR32AC_lseek64                      3
#define __NR32AC_lfutex                       5
#define __NR32AC_debugtrap                    2
#define __NR32AC_get_exception_handler        3
#define __NR32AC_set_exception_handler        3
#define __NR32AC_time64                       1
#define __NR32AC_fchdirat                     3
#define __NR32AC_openpty                      5
#define __NR32AC_rpc_schedule                 5
#define __NR32AC_frealpathat                  5
#define __NR32AC_frealpath4                   4
#define __NR32AC_getdrives                    0
#define __NR32AC_detach                       1
#define __NR32AC_writef                       4
#define __NR32AC_readf                        4
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_COUNT */
#endif /* __WANT_SYSCALL_ARGUMENT_COUNT */


/************************************************************************/
/* SYSCALL RETURN TYPES                                                 */
/************************************************************************/
#ifdef __WANT_SYSCALL_RETURN_TYPES
#ifndef __NR32FEAT_DEFINED_SYSCALL_RETURN_TYPES
#define __NR32FEAT_DEFINED_SYSCALL_RETURN_TYPES
#define __NR32RT_restart_syscall              (errno_t, __errno_t)
#define __NR32RT_exit                         (void, void)
#define __NR32RT_fork                         (pid_t, __pid_t)
#define __NR32RT_read                         (ssize_t, __ssize_t)
#define __NR32RT_write                        (ssize_t, __ssize_t)
#define __NR32RT_open                         (fd_t, __fd_t)
#define __NR32RT_close                        (errno_t, __errno_t)
#define __NR32RT_waitpid                      (pid_t, __pid_t)
#define __NR32RT_creat                        (fd_t, __fd_t)
#define __NR32RT_link                         (errno_t, __errno_t)
#define __NR32RT_unlink                       (errno_t, __errno_t)
#define __NR32RT_execve                       (errno_t, __errno_t)
#define __NR32RT_chdir                        (errno_t, __errno_t)
#define __NR32RT_time                         (int32_t, __int32_t)
#define __NR32RT_mknod                        (errno_t, __errno_t)
#define __NR32RT_chmod                        (errno_t, __errno_t)
#define __NR32RT_lchown                       (errno_t, __errno_t)
#define __NR32RT_break                        (errno_t, __errno_t)
#define __NR32RT_oldstat                      (errno_t, __errno_t)
#define __NR32RT_lseek                        (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_getpid                       (pid_t, __pid_t)
#define __NR32RT_mount                        (errno_t, __errno_t)
#define __NR32RT_umount                       (errno_t, __errno_t)
#define __NR32RT_setuid                       (errno_t, __errno_t)
#define __NR32RT_getuid                       (uint16_t, __uint16_t)
#define __NR32RT_stime                        (errno_t, __errno_t)
#define __NR32RT_ptrace                       (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_alarm                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32RT_oldfstat                     (errno_t, __errno_t)
#define __NR32RT_pause                        (errno_t, __errno_t)
#define __NR32RT_utime                        (errno_t, __errno_t)
#define __NR32RT_stty                         (errno_t, __errno_t)
#define __NR32RT_gtty                         (errno_t, __errno_t)
#define __NR32RT_access                       (errno_t, __errno_t)
#define __NR32RT_nice                         (errno_t, __errno_t)
#define __NR32RT_ftime                        (errno_t, __errno_t)
#define __NR32RT_sync                         (errno_t, __errno_t)
#define __NR32RT_kill                         (errno_t, __errno_t)
#define __NR32RT_rename                       (errno_t, __errno_t)
#define __NR32RT_mkdir                        (errno_t, __errno_t)
#define __NR32RT_rmdir                        (errno_t, __errno_t)
#define __NR32RT_dup                          (fd_t, __fd_t)
#define __NR32RT_pipe                         (errno_t, __errno_t)
#define __NR32RT_times                        (clock_t, __clock_t)
#define __NR32RT_prof                         (errno_t, __errno_t)
#define __NR32RT_brk                          (errno_t, __errno_t)
#define __NR32RT_setgid                       (errno_t, __errno_t)
#define __NR32RT_getgid                       (uint16_t, __uint16_t)
#define __NR32RT_signal                       (__sigactionx32_sa_handler_t, __sigactionx32_sa_handler_t)
#define __NR32RT_geteuid                      (uint16_t, __uint16_t)
#define __NR32RT_getegid                      (uint16_t, __uint16_t)
#define __NR32RT_acct                         (errno_t, __errno_t)
#define __NR32RT_umount2                      (errno_t, __errno_t)
#define __NR32RT_lock                         (errno_t, __errno_t)
#define __NR32RT_ioctl                        (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_fcntl                        (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_mpx                          (errno_t, __errno_t)
#define __NR32RT_setpgid                      (errno_t, __errno_t)
#define __NR32RT_ulimit                       (errno_t, __errno_t)
#define __NR32RT_oldolduname                  (errno_t, __errno_t)
#define __NR32RT_umask                        (mode_t, __mode_t)
#define __NR32RT_chroot                       (errno_t, __errno_t)
#define __NR32RT_ustat                        (errno_t, __errno_t)
#define __NR32RT_dup2                         (fd_t, __fd_t)
#define __NR32RT_getppid                      (pid_t, __pid_t)
#define __NR32RT_getpgrp                      (pid_t, __pid_t)
#define __NR32RT_setsid                       (pid_t, __pid_t)
#define __NR32RT_sigaction                    (errno_t, __errno_t)
#define __NR32RT_sgetmask                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32RT_ssetmask                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32RT_setreuid                     (errno_t, __errno_t)
#define __NR32RT_setregid                     (errno_t, __errno_t)
#define __NR32RT_sigsuspend                   (errno_t, __errno_t)
#define __NR32RT_sigpending                   (errno_t, __errno_t)
#define __NR32RT_sethostname                  (errno_t, __errno_t)
#define __NR32RT_setrlimit                    (errno_t, __errno_t)
#define __NR32RT_getrlimit                    (errno_t, __errno_t)
#define __NR32RT_getrusage                    (errno_t, __errno_t)
#define __NR32RT_gettimeofday                 (errno_t, __errno_t)
#define __NR32RT_settimeofday                 (errno_t, __errno_t)
#define __NR32RT_getgroups                    (ssize_t, __ssize_t)
#define __NR32RT_setgroups                    (errno_t, __errno_t)
#define __NR32RT_select                       (ssize_t, __ssize_t)
#define __NR32RT_symlink                      (errno_t, __errno_t)
#define __NR32RT_oldlstat                     (errno_t, __errno_t)
#define __NR32RT_readlink                     (ssize_t, __ssize_t)
#define __NR32RT_uselib                       (errno_t, __errno_t)
#define __NR32RT_swapon                       (errno_t, __errno_t)
#define __NR32RT_reboot                       (errno_t, __errno_t)
#define __NR32RT_readdir                      (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_mmap                         (void *, void *)
#define __NR32RT_munmap                       (errno_t, __errno_t)
#define __NR32RT_truncate                     (errno_t, __errno_t)
#define __NR32RT_ftruncate                    (errno_t, __errno_t)
#define __NR32RT_fchmod                       (errno_t, __errno_t)
#define __NR32RT_fchown                       (errno_t, __errno_t)
#define __NR32RT_getpriority                  (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_setpriority                  (errno_t, __errno_t)
#define __NR32RT_profil                       (errno_t, __errno_t)
#define __NR32RT_statfs                       (errno_t, __errno_t)
#define __NR32RT_fstatfs                      (errno_t, __errno_t)
#define __NR32RT_ioperm                       (errno_t, __errno_t)
#define __NR32RT_socketcall                   (__LONG32_TYPE__, __LONG32_TYPE__)
#define __NR32RT_syslog                       (ssize_t, __ssize_t)
#define __NR32RT_setitimer                    (errno_t, __errno_t)
#define __NR32RT_getitimer                    (errno_t, __errno_t)
#define __NR32RT_stat                         (errno_t, __errno_t)
#define __NR32RT_lstat                        (errno_t, __errno_t)
#define __NR32RT_fstat                        (errno_t, __errno_t)
#define __NR32RT_olduname                     (errno_t, __errno_t)
#define __NR32RT_iopl                         (errno_t, __errno_t)
#define __NR32RT_vhangup                      (errno_t, __errno_t)
#define __NR32RT_idle                         (errno_t, __errno_t)
#define __NR32RT_vm86old                      (errno_t, __errno_t)
#define __NR32RT_wait4                        (pid_t, __pid_t)
#define __NR32RT_swapoff                      (errno_t, __errno_t)
#define __NR32RT_sysinfo                      (errno_t, __errno_t)
#define __NR32RT_ipc                          (errno_t, __errno_t)
#define __NR32RT_fsync                        (errno_t, __errno_t)
#define __NR32RT_sigreturn                    (void, void)
#define __NR32RT_clone                        (pid_t, __pid_t)
#define __NR32RT_setdomainname                (errno_t, __errno_t)
#define __NR32RT_uname                        (errno_t, __errno_t)
#define __NR32RT_modify_ldt                   (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_adjtimex                     (errno_t, __errno_t)
#define __NR32RT_mprotect                     (errno_t, __errno_t)
#define __NR32RT_sigprocmask                  (errno_t, __errno_t)
#define __NR32RT_create_module                (errno_t, __errno_t)
#define __NR32RT_init_module                  (errno_t, __errno_t)
#define __NR32RT_delete_module                (errno_t, __errno_t)
#define __NR32RT_get_kernel_syms              (errno_t, __errno_t)
#define __NR32RT_quotactl                     (errno_t, __errno_t)
#define __NR32RT_getpgid                      (pid_t, __pid_t)
#define __NR32RT_fchdir                       (errno_t, __errno_t)
#define __NR32RT_bdflush                      (errno_t, __errno_t)
#define __NR32RT_sysfs                        (errno_t, __errno_t)
#define __NR32RT_personality                  (errno_t, __errno_t)
#define __NR32RT_afs_syscall                  (errno_t, __errno_t)
#define __NR32RT_setfsuid                     (errno_t, __errno_t)
#define __NR32RT_setfsgid                     (errno_t, __errno_t)
#define __NR32RT__llseek                      (errno_t, __errno_t)
#define __NR32RT_getdents                     (ssize_t, __ssize_t)
#define __NR32RT__newselect                   (ssize_t, __ssize_t)
#define __NR32RT_flock                        (errno_t, __errno_t)
#define __NR32RT_msync                        (errno_t, __errno_t)
#define __NR32RT_readv                        (ssize_t, __ssize_t)
#define __NR32RT_writev                       (ssize_t, __ssize_t)
#define __NR32RT_getsid                       (pid_t, __pid_t)
#define __NR32RT_fdatasync                    (errno_t, __errno_t)
#define __NR32RT__sysctl                      (errno_t, __errno_t)
#define __NR32RT_mlock                        (errno_t, __errno_t)
#define __NR32RT_munlock                      (errno_t, __errno_t)
#define __NR32RT_mlockall                     (errno_t, __errno_t)
#define __NR32RT_munlockall                   (errno_t, __errno_t)
#define __NR32RT_sched_setparam               (errno_t, __errno_t)
#define __NR32RT_sched_getparam               (errno_t, __errno_t)
#define __NR32RT_sched_setscheduler           (errno_t, __errno_t)
#define __NR32RT_sched_getscheduler           (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_sched_yield                  (errno_t, __errno_t)
#define __NR32RT_sched_get_priority_max       (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_sched_get_priority_min       (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_sched_rr_get_interval        (errno_t, __errno_t)
#define __NR32RT_nanosleep                    (errno_t, __errno_t)
#define __NR32RT_mremap                       (void *, void *)
#define __NR32RT_setresuid                    (errno_t, __errno_t)
#define __NR32RT_getresuid                    (errno_t, __errno_t)
#define __NR32RT_vm86                         (errno_t, __errno_t)
#define __NR32RT_query_module                 (errno_t, __errno_t)
#define __NR32RT_poll                         (ssize_t, __ssize_t)
#define __NR32RT_nfsservctl                   (errno_t, __errno_t)
#define __NR32RT_setresgid                    (errno_t, __errno_t)
#define __NR32RT_getresgid                    (errno_t, __errno_t)
#define __NR32RT_prctl                        (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_rt_sigreturn                 (void, void)
#define __NR32RT_rt_sigaction                 (errno_t, __errno_t)
#define __NR32RT_rt_sigprocmask               (errno_t, __errno_t)
#define __NR32RT_rt_sigpending                (errno_t, __errno_t)
#define __NR32RT_rt_sigtimedwait              (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_rt_sigqueueinfo              (errno_t, __errno_t)
#define __NR32RT_rt_sigsuspend                (errno_t, __errno_t)
#define __NR32RT_pread64                      (ssize_t, __ssize_t)
#define __NR32RT_pwrite64                     (ssize_t, __ssize_t)
#define __NR32RT_chown                        (errno_t, __errno_t)
#define __NR32RT_getcwd                       (ssize_t, __ssize_t)
#define __NR32RT_capget                       (errno_t, __errno_t)
#define __NR32RT_capset                       (errno_t, __errno_t)
#define __NR32RT_sigaltstack                  (errno_t, __errno_t)
#define __NR32RT_sendfile                     (ssize_t, __ssize_t)
#define __NR32RT_getpmsg                      (errno_t, __errno_t)
#define __NR32RT_putpmsg                      (errno_t, __errno_t)
#define __NR32RT_vfork                        (pid_t, __pid_t)
#define __NR32RT_ugetrlimit                   (errno_t, __errno_t)
#define __NR32RT_mmap2                        (void *, void *)
#define __NR32RT_truncate64                   (errno_t, __errno_t)
#define __NR32RT_ftruncate64                  (errno_t, __errno_t)
#define __NR32RT_stat64                       (errno_t, __errno_t)
#define __NR32RT_lstat64                      (errno_t, __errno_t)
#define __NR32RT_fstat64                      (errno_t, __errno_t)
#define __NR32RT_lchown32                     (errno_t, __errno_t)
#define __NR32RT_getuid32                     (uint32_t, __uint32_t)
#define __NR32RT_getgid32                     (uint32_t, __uint32_t)
#define __NR32RT_geteuid32                    (uint32_t, __uint32_t)
#define __NR32RT_getegid32                    (uint32_t, __uint32_t)
#define __NR32RT_setreuid32                   (errno_t, __errno_t)
#define __NR32RT_setregid32                   (errno_t, __errno_t)
#define __NR32RT_getgroups32                  (ssize_t, __ssize_t)
#define __NR32RT_setgroups32                  (errno_t, __errno_t)
#define __NR32RT_fchown32                     (errno_t, __errno_t)
#define __NR32RT_setresuid32                  (errno_t, __errno_t)
#define __NR32RT_getresuid32                  (errno_t, __errno_t)
#define __NR32RT_setresgid32                  (errno_t, __errno_t)
#define __NR32RT_getresgid32                  (errno_t, __errno_t)
#define __NR32RT_chown32                      (errno_t, __errno_t)
#define __NR32RT_setuid32                     (errno_t, __errno_t)
#define __NR32RT_setgid32                     (errno_t, __errno_t)
#define __NR32RT_setfsuid32                   (errno_t, __errno_t)
#define __NR32RT_setfsgid32                   (errno_t, __errno_t)
#define __NR32RT_pivot_root                   (errno_t, __errno_t)
#define __NR32RT_mincore                      (errno_t, __errno_t)
#define __NR32RT_madvise                      (errno_t, __errno_t)
#define __NR32RT_getdents64                   (ssize_t, __ssize_t)
#define __NR32RT_fcntl64                      (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_gettid                       (pid_t, __pid_t)
#define __NR32RT_readahead                    (ssize_t, __ssize_t)
#define __NR32RT_setxattr                     (errno_t, __errno_t)
#define __NR32RT_lsetxattr                    (errno_t, __errno_t)
#define __NR32RT_fsetxattr                    (errno_t, __errno_t)
#define __NR32RT_getxattr                     (ssize_t, __ssize_t)
#define __NR32RT_lgetxattr                    (ssize_t, __ssize_t)
#define __NR32RT_fgetxattr                    (ssize_t, __ssize_t)
#define __NR32RT_listxattr                    (ssize_t, __ssize_t)
#define __NR32RT_llistxattr                   (ssize_t, __ssize_t)
#define __NR32RT_flistxattr                   (ssize_t, __ssize_t)
#define __NR32RT_removexattr                  (errno_t, __errno_t)
#define __NR32RT_lremovexattr                 (errno_t, __errno_t)
#define __NR32RT_fremovexattr                 (errno_t, __errno_t)
#define __NR32RT_tkill                        (errno_t, __errno_t)
#define __NR32RT_sendfile64                   (ssize_t, __ssize_t)
#define __NR32RT_futex                        (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_sched_setaffinity            (errno_t, __errno_t)
#define __NR32RT_sched_getaffinity            (errno_t, __errno_t)
#define __NR32RT_set_thread_area              (errno_t, __errno_t)
#define __NR32RT_get_thread_area              (errno_t, __errno_t)
#define __NR32RT_io_setup                     (errno_t, __errno_t)
#define __NR32RT_io_destroy                   (errno_t, __errno_t)
#define __NR32RT_io_getevents                 (errno_t, __errno_t)
#define __NR32RT_io_submit                    (errno_t, __errno_t)
#define __NR32RT_io_cancel                    (errno_t, __errno_t)
#define __NR32RT_fadvise64                    (errno_t, __errno_t)
#define __NR32RT_exit_group                   (void, void)
#define __NR32RT_lookup_dcookie               (errno_t, __errno_t)
#define __NR32RT_epoll_create                 (fd_t, __fd_t)
#define __NR32RT_epoll_ctl                    (errno_t, __errno_t)
#define __NR32RT_epoll_wait                   (ssize_t, __ssize_t)
#define __NR32RT_remap_file_pages             (errno_t, __errno_t)
#define __NR32RT_set_tid_address              (pid_t, __pid_t)
#define __NR32RT_timer_create                 (errno_t, __errno_t)
#define __NR32RT_timer_settime                (errno_t, __errno_t)
#define __NR32RT_timer_gettime                (errno_t, __errno_t)
#define __NR32RT_timer_getoverrun             (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_timer_delete                 (errno_t, __errno_t)
#define __NR32RT_clock_settime                (errno_t, __errno_t)
#define __NR32RT_clock_gettime                (errno_t, __errno_t)
#define __NR32RT_clock_getres                 (errno_t, __errno_t)
#define __NR32RT_clock_nanosleep              (errno_t, __errno_t)
#define __NR32RT_statfs64                     (errno_t, __errno_t)
#define __NR32RT_fstatfs64                    (errno_t, __errno_t)
#define __NR32RT_tgkill                       (errno_t, __errno_t)
#define __NR32RT_utimes                       (errno_t, __errno_t)
#define __NR32RT_fadvise64_64                 (errno_t, __errno_t)
#define __NR32RT_vserver                      (errno_t, __errno_t)
#define __NR32RT_mbind                        (errno_t, __errno_t)
#define __NR32RT_get_mempolicy                (errno_t, __errno_t)
#define __NR32RT_set_mempolicy                (errno_t, __errno_t)
#define __NR32RT_mq_open                      (fd_t, __fd_t)
#define __NR32RT_mq_unlink                    (errno_t, __errno_t)
#define __NR32RT_mq_timedsend                 (errno_t, __errno_t)
#define __NR32RT_mq_timedreceive              (ssize_t, __ssize_t)
#define __NR32RT_mq_notify                    (errno_t, __errno_t)
#define __NR32RT_mq_getsetattr                (errno_t, __errno_t)
#define __NR32RT_kexec_load                   (errno_t, __errno_t)
#define __NR32RT_waitid                       (errno_t, __errno_t)
#define __NR32RT_add_key                      (errno_t, __errno_t)
#define __NR32RT_request_key                  (errno_t, __errno_t)
#define __NR32RT_keyctl                       (errno_t, __errno_t)
#define __NR32RT_ioprio_set                   (errno_t, __errno_t)
#define __NR32RT_ioprio_get                   (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_inotify_init                 (fd_t, __fd_t)
#define __NR32RT_inotify_add_watch            (int, int)
#define __NR32RT_inotify_rm_watch             (errno_t, __errno_t)
#define __NR32RT_migrate_pages                (errno_t, __errno_t)
#define __NR32RT_openat                       (fd_t, __fd_t)
#define __NR32RT_mkdirat                      (errno_t, __errno_t)
#define __NR32RT_mknodat                      (errno_t, __errno_t)
#define __NR32RT_fchownat                     (errno_t, __errno_t)
#define __NR32RT_futimesat                    (errno_t, __errno_t)
#define __NR32RT_fstatat64                    (errno_t, __errno_t)
#define __NR32RT_unlinkat                     (errno_t, __errno_t)
#define __NR32RT_renameat                     (errno_t, __errno_t)
#define __NR32RT_linkat                       (errno_t, __errno_t)
#define __NR32RT_symlinkat                    (errno_t, __errno_t)
#define __NR32RT_readlinkat                   (ssize_t, __ssize_t)
#define __NR32RT_fchmodat                     (errno_t, __errno_t)
#define __NR32RT_faccessat                    (errno_t, __errno_t)
#define __NR32RT_pselect6                     (ssize_t, __ssize_t)
#define __NR32RT_ppoll                        (ssize_t, __ssize_t)
#define __NR32RT_unshare                      (errno_t, __errno_t)
#define __NR32RT_set_robust_list              (errno_t, __errno_t)
#define __NR32RT_get_robust_list              (errno_t, __errno_t)
#define __NR32RT_splice                       (ssize_t, __ssize_t)
#define __NR32RT_sync_file_range              (errno_t, __errno_t)
#define __NR32RT_tee                          (ssize_t, __ssize_t)
#define __NR32RT_vmsplice                     (ssize_t, __ssize_t)
#define __NR32RT_move_pages                   (errno_t, __errno_t)
#define __NR32RT_getcpu                       (errno_t, __errno_t)
#define __NR32RT_epoll_pwait                  (ssize_t, __ssize_t)
#define __NR32RT_utimensat                    (errno_t, __errno_t)
#define __NR32RT_signalfd                     (errno_t, __errno_t)
#define __NR32RT_timerfd_create               (fd_t, __fd_t)
#define __NR32RT_eventfd                      (fd_t, __fd_t)
#define __NR32RT_fallocate                    (errno_t, __errno_t)
#define __NR32RT_timerfd_settime              (errno_t, __errno_t)
#define __NR32RT_timerfd_gettime              (errno_t, __errno_t)
#define __NR32RT_signalfd4                    (errno_t, __errno_t)
#define __NR32RT_eventfd2                     (fd_t, __fd_t)
#define __NR32RT_epoll_create1                (fd_t, __fd_t)
#define __NR32RT_dup3                         (fd_t, __fd_t)
#define __NR32RT_pipe2                        (errno_t, __errno_t)
#define __NR32RT_inotify_init1                (fd_t, __fd_t)
#define __NR32RT_preadv                       (ssize_t, __ssize_t)
#define __NR32RT_pwritev                      (ssize_t, __ssize_t)
#define __NR32RT_rt_tgsigqueueinfo            (errno_t, __errno_t)
#define __NR32RT_perf_event_open              (errno_t, __errno_t)
#define __NR32RT_recvmmsg                     (ssize_t, __ssize_t)
#define __NR32RT_fanotify_init                (errno_t, __errno_t)
#define __NR32RT_fanotify_mark                (errno_t, __errno_t)
#define __NR32RT_prlimit64                    (errno_t, __errno_t)
#define __NR32RT_name_to_handle_at            (errno_t, __errno_t)
#define __NR32RT_open_by_handle_at            (fd_t, __fd_t)
#define __NR32RT_clock_adjtime                (errno_t, __errno_t)
#define __NR32RT_syncfs                       (errno_t, __errno_t)
#define __NR32RT_sendmmsg                     (ssize_t, __ssize_t)
#define __NR32RT_setns                        (errno_t, __errno_t)
#define __NR32RT_process_vm_readv             (ssize_t, __ssize_t)
#define __NR32RT_process_vm_writev            (ssize_t, __ssize_t)
#define __NR32RT_kcmp                         (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_finit_module                 (errno_t, __errno_t)
#define __NR32RT_sched_setattr                (errno_t, __errno_t)
#define __NR32RT_sched_getattr                (errno_t, __errno_t)
#define __NR32RT_renameat2                    (errno_t, __errno_t)
#define __NR32RT_seccomp                      (errno_t, __errno_t)
#define __NR32RT_getrandom                    (ssize_t, __ssize_t)
#define __NR32RT_memfd_create                 (fd_t, __fd_t)
#define __NR32RT_bpf                          (errno_t, __errno_t)
#define __NR32RT_execveat                     (errno_t, __errno_t)
#define __NR32RT_socket                       (fd_t, __fd_t)
#define __NR32RT_socketpair                   (errno_t, __errno_t)
#define __NR32RT_bind                         (errno_t, __errno_t)
#define __NR32RT_connect                      (errno_t, __errno_t)
#define __NR32RT_listen                       (errno_t, __errno_t)
#define __NR32RT_accept4                      (fd_t, __fd_t)
#define __NR32RT_getsockopt                   (errno_t, __errno_t)
#define __NR32RT_setsockopt                   (errno_t, __errno_t)
#define __NR32RT_getsockname                  (errno_t, __errno_t)
#define __NR32RT_getpeername                  (errno_t, __errno_t)
#define __NR32RT_sendto                       (ssize_t, __ssize_t)
#define __NR32RT_sendmsg                      (ssize_t, __ssize_t)
#define __NR32RT_recvfrom                     (ssize_t, __ssize_t)
#define __NR32RT_recvmsg                      (ssize_t, __ssize_t)
#define __NR32RT_shutdown                     (errno_t, __errno_t)
#define __NR32RT_userfaultfd                  (fd_t, __fd_t)
#define __NR32RT_membarrier                   (errno_t, __errno_t)
#define __NR32RT_mlock2                       (errno_t, __errno_t)
#define __NR32RT_copy_file_range              (errno_t, __errno_t)
#define __NR32RT_preadv2                      (errno_t, __errno_t)
#define __NR32RT_pwritev2                     (errno_t, __errno_t)
#define __NR32RT_pkey_mprotect                (errno_t, __errno_t)
#define __NR32RT_pkey_alloc                   (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_pkey_free                    (errno_t, __errno_t)
#define __NR32RT_statx                        (errno_t, __errno_t)
#define __NR32RT_arch_prctl                   (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_io_pgetevents                (errno_t, __errno_t)
#define __NR32RT_rseq                         (errno_t, __errno_t)
#define __NR32RT_semget                       (errno_t, __errno_t)
#define __NR32RT_semctl                       (errno_t, __errno_t)
#define __NR32RT_shmget                       (errno_t, __errno_t)
#define __NR32RT_shmctl                       (errno_t, __errno_t)
#define __NR32RT_shmat                        (errno_t, __errno_t)
#define __NR32RT_shmdt                        (errno_t, __errno_t)
#define __NR32RT_msgget                       (errno_t, __errno_t)
#define __NR32RT_msgsnd                       (errno_t, __errno_t)
#define __NR32RT_msgrcv                       (errno_t, __errno_t)
#define __NR32RT_msgctl                       (errno_t, __errno_t)
#define __NR32RT_clock_gettime64              (errno_t, __errno_t)
#define __NR32RT_clock_settime64              (errno_t, __errno_t)
#define __NR32RT_clock_adjtime64              (errno_t, __errno_t)
#define __NR32RT_clock_getres_time64          (errno_t, __errno_t)
#define __NR32RT_clock_nanosleep_time64       (errno_t, __errno_t)
#define __NR32RT_timer_gettime64              (errno_t, __errno_t)
#define __NR32RT_timer_settime64              (errno_t, __errno_t)
#define __NR32RT_timerfd_gettime64            (errno_t, __errno_t)
#define __NR32RT_timerfd_settime64            (errno_t, __errno_t)
#define __NR32RT_utimensat_time64             (errno_t, __errno_t)
#define __NR32RT_pselect6_time64              (ssize_t, __ssize_t)
#define __NR32RT_ppoll_time64                 (ssize_t, __ssize_t)
#define __NR32RT_io_pgetevents_time64         (errno_t, __errno_t)
#define __NR32RT_recvmmsg_time64              (ssize_t, __ssize_t)
#define __NR32RT_mq_timedsend_time64          (errno_t, __errno_t)
#define __NR32RT_mq_timedreceive_time64       (ssize_t, __ssize_t)
#define __NR32RT_semtimedop_time64            (errno_t, __errno_t)
#define __NR32RT_rt_sigtimedwait_time64       (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_futex_time64                 (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_sched_rr_get_interval_time64 (errno_t, __errno_t)
#define __NR32RT_pidfd_send_signal            (errno_t, __errno_t)
#define __NR32RT_io_uring_setup               (errno_t, __errno_t)
#define __NR32RT_io_uring_enter               (errno_t, __errno_t)
#define __NR32RT_io_uring_register            (errno_t, __errno_t)
#define __NR32RT_open_tree                    (errno_t, __errno_t)
#define __NR32RT_move_mount                   (errno_t, __errno_t)
#define __NR32RT_fsopen                       (errno_t, __errno_t)
#define __NR32RT_fsconfig                     (errno_t, __errno_t)
#define __NR32RT_fsmount                      (errno_t, __errno_t)
#define __NR32RT_fspick                       (errno_t, __errno_t)
#define __NR32RT_pidfd_open                   (fd_t, __fd_t)
#define __NR32RT_clone3                       (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_close_range                  (errno_t, __errno_t)
#define __NR32RT_openat2                      (errno_t, __errno_t)
#define __NR32RT_pidfd_getfd                  (fd_t, __fd_t)
#define __NR32RT_faccessat2                   (errno_t, __errno_t)
#define __NR32RT_pwritevf                     (ssize_t, __ssize_t)
#define __NR32RT_preadvf                      (ssize_t, __ssize_t)
#define __NR32RT_fallocate64                  (errno_t, __errno_t)
#define __NR32RT_freadlinkat                  (ssize_t, __ssize_t)
#define __NR32RT_fsymlinkat                   (errno_t, __errno_t)
#define __NR32RT_kfstatat                     (errno_t, __errno_t)
#define __NR32RT_futimesat64                  (errno_t, __errno_t)
#define __NR32RT_fmknodat                     (errno_t, __errno_t)
#define __NR32RT_fmkdirat                     (errno_t, __errno_t)
#define __NR32RT_inotify_add_watch_at         (int, int)
#define __NR32RT_waitid64                     (errno_t, __errno_t)
#define __NR32RT_utimes64                     (errno_t, __errno_t)
#define __NR32RT_kreaddirf                    (ssize_t, __ssize_t)
#define __NR32RT_kfstat                       (errno_t, __errno_t)
#define __NR32RT_klstat                       (errno_t, __errno_t)
#define __NR32RT_kstat                        (errno_t, __errno_t)
#define __NR32RT_pwrite64f                    (ssize_t, __ssize_t)
#define __NR32RT_pread64f                     (ssize_t, __ssize_t)
#define __NR32RT_ksigreturn                   (void, void)
#define __NR32RT_nanosleep64                  (errno_t, __errno_t)
#define __NR32RT_rpc_serve                    (errno_t, __errno_t)
#define __NR32RT_ksysctl                      (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_writevf                      (ssize_t, __ssize_t)
#define __NR32RT_readvf                       (ssize_t, __ssize_t)
#define __NR32RT_kreaddir                     (ssize_t, __ssize_t)
#define __NR32RT_wait4_64                     (pid_t, __pid_t)
#define __NR32RT_getitimer64                  (errno_t, __errno_t)
#define __NR32RT_setitimer64                  (errno_t, __errno_t)
#define __NR32RT_maplibrary                   (void *, void *)
#define __NR32RT_select64                     (ssize_t, __ssize_t)
#define __NR32RT_settimeofday64               (errno_t, __errno_t)
#define __NR32RT_gettimeofday64               (errno_t, __errno_t)
#define __NR32RT_getrusage64                  (errno_t, __errno_t)
#define __NR32RT_fsmode                       (uint64_t, __uint64_t)
#define __NR32RT_ioctlf                       (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_rtm_test                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32RT_rtm_abort                    (errno_t, __errno_t)
#define __NR32RT_rtm_end                      (errno_t, __errno_t)
#define __NR32RT_rtm_begin                    (rtm_status_t, __rtm_status_t)
#define __NR32RT_ftime64                      (errno_t, __errno_t)
#define __NR32RT_rpc_serve_sysret             (errno_t, __errno_t)
#define __NR32RT_set_userprocmask_address     (errno_t, __errno_t)
#define __NR32RT_utime64                      (errno_t, __errno_t)
#define __NR32RT_userviofd                    (fd_t, __fd_t)
#define __NR32RT_stime64                      (errno_t, __errno_t)
#define __NR32RT_coredump                     (errno_t, __errno_t)
#define __NR32RT_mktty                        (fd_t, __fd_t)
#define __NR32RT_lfutexexpr                   (errno_t, __errno_t)
#define __NR32RT_lseek64                      (int64_t, __int64_t)
#define __NR32RT_lfutex                       (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_debugtrap                    (errno_t, __errno_t)
#define __NR32RT_get_exception_handler        (errno_t, __errno_t)
#define __NR32RT_set_exception_handler        (errno_t, __errno_t)
#define __NR32RT_time64                       (int64_t, __int64_t)
#define __NR32RT_fchdirat                     (errno_t, __errno_t)
#define __NR32RT_openpty                      (errno_t, __errno_t)
#define __NR32RT_rpc_schedule                 (errno_t, __errno_t)
#define __NR32RT_frealpathat                  (ssize_t, __ssize_t)
#define __NR32RT_frealpath4                   (ssize_t, __ssize_t)
#define __NR32RT_getdrives                    (syscall_slong_t, __syscall_slong_t)
#define __NR32RT_detach                       (errno_t, __errno_t)
#define __NR32RT_writef                       (ssize_t, __ssize_t)
#define __NR32RT_readf                        (ssize_t, __ssize_t)
#endif /* !__NR32FEAT_DEFINED_SYSCALL_RETURN_TYPES */
#endif /* __WANT_SYSCALL_RETURN_TYPES */


/************************************************************************/
/* SYSCALL ARGUMENT TYPES                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_TYPES
#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_TYPES
#define __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_TYPES
#define __NR32AT0_exit                         (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_read                         (fd_t, __fd_t)
#define __NR32AT1_read                         (void *, void *)
#define __NR32AT2_read                         (size_t, __size_t)
#define __NR32AT0_write                        (fd_t, __fd_t)
#define __NR32AT1_write                        (void const *, void const *)
#define __NR32AT2_write                        (size_t, __size_t)
#define __NR32AT0_open                         (char const *, char const *)
#define __NR32AT1_open                         (oflag_t, __oflag_t)
#define __NR32AT2_open                         (mode_t, __mode_t)
#define __NR32AT0_close                        (fd_t, __fd_t)
#define __NR32AT0_waitpid                      (pid_t, __pid_t)
#define __NR32AT1_waitpid                      (int32_t *, __int32_t *)
#define __NR32AT2_waitpid                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_creat                        (char const *, char const *)
#define __NR32AT1_creat                        (mode_t, __mode_t)
#define __NR32AT0_link                         (char const *, char const *)
#define __NR32AT1_link                         (char const *, char const *)
#define __NR32AT0_unlink                       (char const *, char const *)
#define __NR32AT0_execve                       (char const *, char const *)
#define __NR32AT1_execve                       (__HYBRID_PTR32(char const) const *, __HYBRID_PTR32(char const) const *)
#define __NR32AT2_execve                       (__HYBRID_PTR32(char const) const *, __HYBRID_PTR32(char const) const *)
#define __NR32AT0_chdir                        (char const *, char const *)
#define __NR32AT0_time                         (int32_t *, __int32_t *)
#define __NR32AT0_mknod                        (char const *, char const *)
#define __NR32AT1_mknod                        (mode_t, __mode_t)
#define __NR32AT2_mknod                        (dev_t, __dev_t)
#define __NR32AT0_chmod                        (char const *, char const *)
#define __NR32AT1_chmod                        (mode_t, __mode_t)
#define __NR32AT0_lchown                       (char const *, char const *)
#define __NR32AT1_lchown                       (uint16_t, __uint16_t)
#define __NR32AT2_lchown                       (uint16_t, __uint16_t)
#define __NR32AT0_oldstat                      (char const *, char const *)
#define __NR32AT1_oldstat                      (struct linux_oldstat *, struct linux_oldstat *)
#define __NR32AT0_lseek                        (fd_t, __fd_t)
#define __NR32AT1_lseek                        (syscall_slong_t, __syscall_slong_t)
#define __NR32AT2_lseek                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_mount                        (char const *, char const *)
#define __NR32AT1_mount                        (char const *, char const *)
#define __NR32AT2_mount                        (char const *, char const *)
#define __NR32AT3_mount                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_mount                        (void const *, void const *)
#define __NR32AT0_umount                       (char const *, char const *)
#define __NR32AT0_setuid                       (uint16_t, __uint16_t)
#define __NR32AT0_stime                        (time32_t const *, __time32_t const *)
#define __NR32AT0_ptrace                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_ptrace                       (pid_t, __pid_t)
#define __NR32AT2_ptrace                       (void *, void *)
#define __NR32AT3_ptrace                       (void *, void *)
#define __NR32AT0_alarm                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_oldfstat                     (fd_t, __fd_t)
#define __NR32AT1_oldfstat                     (struct linux_oldstat *, struct linux_oldstat *)
#define __NR32AT0_utime                        (char const *, char const *)
#define __NR32AT1_utime                        (struct utimbufx32 const *, struct __utimbufx32 const *)
#define __NR32AT0_access                       (char const *, char const *)
#define __NR32AT1_access                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_nice                         (syscall_slong_t, __syscall_slong_t)
#define __NR32AT0_ftime                        (struct timebx32 *, struct __timebx32 *)
#define __NR32AT0_kill                         (pid_t, __pid_t)
#define __NR32AT1_kill                         (signo_t, __signo_t)
#define __NR32AT0_rename                       (char const *, char const *)
#define __NR32AT1_rename                       (char const *, char const *)
#define __NR32AT0_mkdir                        (char const *, char const *)
#define __NR32AT1_mkdir                        (mode_t, __mode_t)
#define __NR32AT0_rmdir                        (char const *, char const *)
#define __NR32AT0_dup                          (fd_t, __fd_t)
#define __NR32AT0_pipe                         (fd_t *, __fd_t *)
#define __NR32AT0_times                        (struct tmsx32 *, struct __tmsx32 *)
#define __NR32AT0_brk                          (void *, void *)
#define __NR32AT0_setgid                       (uint16_t, __uint16_t)
#define __NR32AT0_signal                       (signo_t, __signo_t)
#define __NR32AT1_signal                       (__sigactionx32_sa_handler_t, __sigactionx32_sa_handler_t)
#define __NR32AT0_acct                         (char const *, char const *)
#define __NR32AT0_umount2                      (char const *, char const *)
#define __NR32AT1_umount2                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_ioctl                        (fd_t, __fd_t)
#define __NR32AT1_ioctl                        (ioctl_t, __ioctl_t)
#define __NR32AT2_ioctl                        (void *, void *)
#define __NR32AT0_fcntl                        (fd_t, __fd_t)
#define __NR32AT1_fcntl                        (fcntl_t, __fcntl_t)
#define __NR32AT2_fcntl                        (void *, void *)
#define __NR32AT0_setpgid                      (pid_t, __pid_t)
#define __NR32AT1_setpgid                      (pid_t, __pid_t)
#define __NR32AT0_oldolduname                  (struct linux_oldolduname *, struct linux_oldolduname *)
#define __NR32AT0_umask                        (mode_t, __mode_t)
#define __NR32AT0_chroot                       (char const *, char const *)
#define __NR32AT0_ustat                        (dev_t, __dev_t)
#define __NR32AT1_ustat                        (struct ustat *, struct ustat *)
#define __NR32AT0_dup2                         (fd_t, __fd_t)
#define __NR32AT1_dup2                         (fd_t, __fd_t)
#define __NR32AT0_sigaction                    (signo_t, __signo_t)
#define __NR32AT1_sigaction                    (struct __old_kernel_sigactionx32 const *, struct __old_kernel_sigactionx32 const *)
#define __NR32AT2_sigaction                    (struct __old_kernel_sigactionx32 *, struct __old_kernel_sigactionx32 *)
#define __NR32AT0_ssetmask                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_setreuid                     (uint16_t, __uint16_t)
#define __NR32AT1_setreuid                     (uint16_t, __uint16_t)
#define __NR32AT0_setregid                     (uint16_t, __uint16_t)
#define __NR32AT1_setregid                     (uint16_t, __uint16_t)
#define __NR32AT0_sigsuspend                   (struct __old_sigset_struct const *, struct __old_sigset_struct const *)
#define __NR32AT0_sigpending                   (struct __old_sigset_struct *, struct __old_sigset_struct *)
#define __NR32AT0_sethostname                  (char const *, char const *)
#define __NR32AT1_sethostname                  (size_t, __size_t)
#define __NR32AT0_setrlimit                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_setrlimit                    (struct rlimitx32 const *, struct __rlimitx32 const *)
#define __NR32AT0_getrlimit                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_getrlimit                    (struct rlimitx32 *, struct __rlimitx32 *)
#define __NR32AT0_getrusage                    (syscall_slong_t, __syscall_slong_t)
#define __NR32AT1_getrusage                    (struct rusagex32 *, struct __rusagex32 *)
#define __NR32AT0_gettimeofday                 (struct timevalx32 *, struct __timevalx32 *)
#define __NR32AT1_gettimeofday                 (struct timezone *, struct timezone *)
#define __NR32AT0_settimeofday                 (struct timevalx32 const *, struct __timevalx32 const *)
#define __NR32AT1_settimeofday                 (struct timezone const *, struct timezone const *)
#define __NR32AT0_getgroups                    (size_t, __size_t)
#define __NR32AT1_getgroups                    (uint16_t *, __uint16_t *)
#define __NR32AT0_setgroups                    (size_t, __size_t)
#define __NR32AT1_setgroups                    (uint16_t const *, __uint16_t const *)
#define __NR32AT0_select                       (struct sel_arg_structx32 const *, struct sel_arg_structx32 const *)
#define __NR32AT0_symlink                      (char const *, char const *)
#define __NR32AT1_symlink                      (char const *, char const *)
#define __NR32AT0_oldlstat                     (char const *, char const *)
#define __NR32AT1_oldlstat                     (struct linux_oldstat *, struct linux_oldstat *)
#define __NR32AT0_readlink                     (char const *, char const *)
#define __NR32AT1_readlink                     (char *, char *)
#define __NR32AT2_readlink                     (size_t, __size_t)
#define __NR32AT0_uselib                       (char const *, char const *)
#define __NR32AT0_swapon                       (char const *, char const *)
#define __NR32AT1_swapon                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_reboot                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_readdir                      (fd_t, __fd_t)
#define __NR32AT1_readdir                      (struct old_linux_direntx32 *, struct old_linux_direntx32 *)
#define __NR32AT0_mmap                         (void *, void *)
#define __NR32AT1_mmap                         (size_t, __size_t)
#define __NR32AT2_mmap                         (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_mmap                         (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_mmap                         (fd_t, __fd_t)
#define __NR32AT5_mmap                         (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_munmap                       (void *, void *)
#define __NR32AT1_munmap                       (size_t, __size_t)
#define __NR32AT0_truncate                     (char const *, char const *)
#define __NR32AT1_truncate                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_ftruncate                    (fd_t, __fd_t)
#define __NR32AT1_ftruncate                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_fchmod                       (fd_t, __fd_t)
#define __NR32AT1_fchmod                       (mode_t, __mode_t)
#define __NR32AT0_fchown                       (fd_t, __fd_t)
#define __NR32AT1_fchown                       (uint16_t, __uint16_t)
#define __NR32AT2_fchown                       (uint16_t, __uint16_t)
#define __NR32AT0_getpriority                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_getpriority                  (id_t, __id_t)
#define __NR32AT0_setpriority                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_setpriority                  (id_t, __id_t)
#define __NR32AT2_setpriority                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_statfs                       (char const *, char const *)
#define __NR32AT1_statfs                       (struct __statfsx32 *, struct __statfsx32 *)
#define __NR32AT0_fstatfs                      (fd_t, __fd_t)
#define __NR32AT1_fstatfs                      (struct __statfsx32 *, struct __statfsx32 *)
#define __NR32AT0_ioperm                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_ioperm                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_ioperm                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_socketcall                   (__ULONG32_TYPE__, __ULONG32_TYPE__)
#define __NR32AT1_socketcall                   (__ULONG32_TYPE__ *, __ULONG32_TYPE__ *)
#define __NR32AT0_syslog                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_syslog                       (char const *, char const *)
#define __NR32AT2_syslog                       (size_t, __size_t)
#define __NR32AT0_setitimer                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_setitimer                    (struct __itimervalx32 const *, struct __itimervalx32 const *)
#define __NR32AT2_setitimer                    (struct __itimervalx32 *, struct __itimervalx32 *)
#define __NR32AT0_getitimer                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_getitimer                    (struct __itimervalx32 *, struct __itimervalx32 *)
#define __NR32AT0_stat                         (char const *, char const *)
#define __NR32AT1_stat                         (struct linux_statx32 *, struct linux_statx32 *)
#define __NR32AT0_lstat                        (char const *, char const *)
#define __NR32AT1_lstat                        (struct linux_statx32 *, struct linux_statx32 *)
#define __NR32AT0_fstat                        (fd_t, __fd_t)
#define __NR32AT1_fstat                        (struct linux_statx32 *, struct linux_statx32 *)
#define __NR32AT0_olduname                     (struct linux_olduname *, struct linux_olduname *)
#define __NR32AT0_iopl                         (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_vm86old                      (int, int)
#define __NR32AT0_wait4                        (pid_t, __pid_t)
#define __NR32AT1_wait4                        (int32_t *, __int32_t *)
#define __NR32AT2_wait4                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_wait4                        (struct rusagex32 *, struct __rusagex32 *)
#define __NR32AT0_swapoff                      (char const *, char const *)
#define __NR32AT0_sysinfo                      (struct __sysinfox32 *, struct __sysinfox32 *)
#define __NR32AT0_ipc                          (int, int)
#define __NR32AT0_fsync                        (fd_t, __fd_t)
#define __NR32AT0_clone                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_clone                        (void *, void *)
#define __NR32AT2_clone                        (pid_t *, __pid_t *)
#define __NR32AT3_clone                        (uintptr_t, __uintptr_t)
#define __NR32AT4_clone                        (pid_t *, __pid_t *)
#define __NR32AT0_setdomainname                (char const *, char const *)
#define __NR32AT1_setdomainname                (size_t, __size_t)
#define __NR32AT0_uname                        (struct utsname *, struct utsname *)
#define __NR32AT0_modify_ldt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_modify_ldt                   (void *, void *)
#define __NR32AT2_modify_ldt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_adjtimex                     (struct timex *, struct timex *)
#define __NR32AT0_mprotect                     (void *, void *)
#define __NR32AT1_mprotect                     (size_t, __size_t)
#define __NR32AT2_mprotect                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_sigprocmask                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_sigprocmask                  (struct __old_sigset_struct const *, struct __old_sigset_struct const *)
#define __NR32AT2_sigprocmask                  (struct __old_sigset_struct *, struct __old_sigset_struct *)
#define __NR32AT0_init_module                  (void const *, void const *)
#define __NR32AT1_init_module                  (size_t, __size_t)
#define __NR32AT2_init_module                  (char const *, char const *)
#define __NR32AT0_delete_module                (char const *, char const *)
#define __NR32AT1_delete_module                (oflag_t, __oflag_t)
#define __NR32AT0_quotactl                     (int, int)
#define __NR32AT0_getpgid                      (pid_t, __pid_t)
#define __NR32AT0_fchdir                       (fd_t, __fd_t)
#define __NR32AT0_bdflush                      (int, int)
#define __NR32AT0_sysfs                        (int, int)
#define __NR32AT0_personality                  (int, int)
#define __NR32AT0_setfsuid                     (uint16_t, __uint16_t)
#define __NR32AT0_setfsgid                     (uint16_t, __uint16_t)
#define __NR32AT0__llseek                      (fd_t, __fd_t)
#define __NR32AT1__llseek                      (int64_t, __int64_t)
#define __NR32AT2__llseek                      (uint64_t *, __uint64_t *)
#define __NR32AT3__llseek                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_getdents                     (fd_t, __fd_t)
#define __NR32AT1_getdents                     (struct linux_direntx32 *, struct linux_direntx32 *)
#define __NR32AT2_getdents                     (size_t, __size_t)
#define __NR32AT0__newselect                   (size_t, __size_t)
#define __NR32AT1__newselect                   (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT2__newselect                   (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT3__newselect                   (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT4__newselect                   (struct timevalx32 *, struct __timevalx32 *)
#define __NR32AT0_flock                        (fd_t, __fd_t)
#define __NR32AT1_flock                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_msync                        (void *, void *)
#define __NR32AT1_msync                        (size_t, __size_t)
#define __NR32AT2_msync                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_readv                        (fd_t, __fd_t)
#define __NR32AT1_readv                        (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_readv                        (size_t, __size_t)
#define __NR32AT0_writev                       (fd_t, __fd_t)
#define __NR32AT1_writev                       (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_writev                       (size_t, __size_t)
#define __NR32AT0_getsid                       (pid_t, __pid_t)
#define __NR32AT0_fdatasync                    (fd_t, __fd_t)
#define __NR32AT0__sysctl                      (int, int)
#define __NR32AT0_mlock                        (void const *, void const *)
#define __NR32AT1_mlock                        (size_t, __size_t)
#define __NR32AT0_munlock                      (void const *, void const *)
#define __NR32AT1_munlock                      (size_t, __size_t)
#define __NR32AT0_mlockall                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_sched_setparam               (pid_t, __pid_t)
#define __NR32AT1_sched_setparam               (struct sched_param const *, struct sched_param const *)
#define __NR32AT0_sched_getparam               (pid_t, __pid_t)
#define __NR32AT1_sched_getparam               (struct sched_param *, struct sched_param *)
#define __NR32AT0_sched_setscheduler           (pid_t, __pid_t)
#define __NR32AT1_sched_setscheduler           (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_sched_setscheduler           (struct sched_param const *, struct sched_param const *)
#define __NR32AT0_sched_getscheduler           (pid_t, __pid_t)
#define __NR32AT0_sched_get_priority_max       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_sched_get_priority_min       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_sched_rr_get_interval        (pid_t, __pid_t)
#define __NR32AT1_sched_rr_get_interval        (struct timespecx32 *, struct __timespecx32 *)
#define __NR32AT0_nanosleep                    (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT1_nanosleep                    (struct timespecx32 *, struct __timespecx32 *)
#define __NR32AT0_mremap                       (void *, void *)
#define __NR32AT1_mremap                       (size_t, __size_t)
#define __NR32AT2_mremap                       (size_t, __size_t)
#define __NR32AT3_mremap                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_mremap                       (void *, void *)
#define __NR32AT0_setresuid                    (uint16_t, __uint16_t)
#define __NR32AT1_setresuid                    (uint16_t, __uint16_t)
#define __NR32AT2_setresuid                    (uint16_t, __uint16_t)
#define __NR32AT0_getresuid                    (uint16_t *, __uint16_t *)
#define __NR32AT1_getresuid                    (uint16_t *, __uint16_t *)
#define __NR32AT2_getresuid                    (uint16_t *, __uint16_t *)
#define __NR32AT0_vm86                         (int, int)
#define __NR32AT0_poll                         (struct pollfd *, struct pollfd *)
#define __NR32AT1_poll                         (size_t, __size_t)
#define __NR32AT2_poll                         (syscall_slong_t, __syscall_slong_t)
#define __NR32AT0_nfsservctl                   (int, int)
#define __NR32AT0_setresgid                    (uint16_t, __uint16_t)
#define __NR32AT1_setresgid                    (uint16_t, __uint16_t)
#define __NR32AT2_setresgid                    (uint16_t, __uint16_t)
#define __NR32AT0_getresgid                    (uint16_t *, __uint16_t *)
#define __NR32AT1_getresgid                    (uint16_t *, __uint16_t *)
#define __NR32AT2_getresgid                    (uint16_t *, __uint16_t *)
#define __NR32AT0_prctl                        (unsigned int, unsigned int)
#define __NR32AT1_prctl                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_prctl                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_prctl                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_prctl                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_rt_sigaction                 (signo_t, __signo_t)
#define __NR32AT1_rt_sigaction                 (struct __kernel_sigactionx32 const *, struct __kernel_sigactionx32 const *)
#define __NR32AT2_rt_sigaction                 (struct __kernel_sigactionx32 *, struct __kernel_sigactionx32 *)
#define __NR32AT3_rt_sigaction                 (size_t, __size_t)
#define __NR32AT0_rt_sigprocmask               (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_rt_sigprocmask               (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR32AT2_rt_sigprocmask               (struct __sigset_struct *, struct __sigset_struct *)
#define __NR32AT3_rt_sigprocmask               (size_t, __size_t)
#define __NR32AT0_rt_sigpending                (struct __sigset_struct *, struct __sigset_struct *)
#define __NR32AT1_rt_sigpending                (size_t, __size_t)
#define __NR32AT0_rt_sigtimedwait              (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR32AT1_rt_sigtimedwait              (struct __siginfox32_struct *, struct __siginfox32_struct *)
#define __NR32AT2_rt_sigtimedwait              (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT3_rt_sigtimedwait              (size_t, __size_t)
#define __NR32AT0_rt_sigqueueinfo              (pid_t, __pid_t)
#define __NR32AT1_rt_sigqueueinfo              (signo_t, __signo_t)
#define __NR32AT2_rt_sigqueueinfo              (struct __siginfox32_struct const *, struct __siginfox32_struct const *)
#define __NR32AT0_rt_sigsuspend                (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR32AT1_rt_sigsuspend                (size_t, __size_t)
#define __NR32AT0_pread64                      (fd_t, __fd_t)
#define __NR32AT1_pread64                      (void *, void *)
#define __NR32AT2_pread64                      (size_t, __size_t)
#define __NR32AT3_pread64                      (uint64_t, __uint64_t)
#define __NR32AT0_pwrite64                     (fd_t, __fd_t)
#define __NR32AT1_pwrite64                     (void const *, void const *)
#define __NR32AT2_pwrite64                     (size_t, __size_t)
#define __NR32AT3_pwrite64                     (uint64_t, __uint64_t)
#define __NR32AT0_chown                        (char const *, char const *)
#define __NR32AT1_chown                        (uint16_t, __uint16_t)
#define __NR32AT2_chown                        (uint16_t, __uint16_t)
#define __NR32AT0_getcwd                       (char *, char *)
#define __NR32AT1_getcwd                       (size_t, __size_t)
#define __NR32AT0_capget                       (int, int)
#define __NR32AT0_capset                       (int, int)
#define __NR32AT0_sigaltstack                  (struct __sigaltstackx32 const *, struct __sigaltstackx32 const *)
#define __NR32AT1_sigaltstack                  (struct __sigaltstackx32 *, struct __sigaltstackx32 *)
#define __NR32AT0_sendfile                     (fd_t, __fd_t)
#define __NR32AT1_sendfile                     (fd_t, __fd_t)
#define __NR32AT2_sendfile                     (__ULONG32_TYPE__ *, __ULONG32_TYPE__ *)
#define __NR32AT3_sendfile                     (size_t, __size_t)
#define __NR32AT0_ugetrlimit                   (int, int)
#define __NR32AT0_mmap2                        (void *, void *)
#define __NR32AT1_mmap2                        (size_t, __size_t)
#define __NR32AT2_mmap2                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_mmap2                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_mmap2                        (fd_t, __fd_t)
#define __NR32AT5_mmap2                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_truncate64                   (char const *, char const *)
#define __NR32AT1_truncate64                   (uint64_t, __uint64_t)
#define __NR32AT0_ftruncate64                  (fd_t, __fd_t)
#define __NR32AT1_ftruncate64                  (uint64_t, __uint64_t)
#define __NR32AT0_stat64                       (char const *, char const *)
#define __NR32AT1_stat64                       (struct linux_statx32_64 *, struct linux_statx32_64 *)
#define __NR32AT0_lstat64                      (char const *, char const *)
#define __NR32AT1_lstat64                      (struct linux_statx32_64 *, struct linux_statx32_64 *)
#define __NR32AT0_fstat64                      (fd_t, __fd_t)
#define __NR32AT1_fstat64                      (struct linux_statx32_64 *, struct linux_statx32_64 *)
#define __NR32AT0_lchown32                     (char const *, char const *)
#define __NR32AT1_lchown32                     (uint32_t, __uint32_t)
#define __NR32AT2_lchown32                     (uint32_t, __uint32_t)
#define __NR32AT0_setreuid32                   (uint32_t, __uint32_t)
#define __NR32AT1_setreuid32                   (uint32_t, __uint32_t)
#define __NR32AT0_setregid32                   (uint32_t, __uint32_t)
#define __NR32AT1_setregid32                   (uint32_t, __uint32_t)
#define __NR32AT0_getgroups32                  (size_t, __size_t)
#define __NR32AT1_getgroups32                  (uint32_t *, __uint32_t *)
#define __NR32AT0_setgroups32                  (size_t, __size_t)
#define __NR32AT1_setgroups32                  (uint32_t const *, __uint32_t const *)
#define __NR32AT0_fchown32                     (fd_t, __fd_t)
#define __NR32AT1_fchown32                     (uint32_t, __uint32_t)
#define __NR32AT2_fchown32                     (uint32_t, __uint32_t)
#define __NR32AT0_setresuid32                  (uint32_t, __uint32_t)
#define __NR32AT1_setresuid32                  (uint32_t, __uint32_t)
#define __NR32AT2_setresuid32                  (uint32_t, __uint32_t)
#define __NR32AT0_getresuid32                  (uint32_t *, __uint32_t *)
#define __NR32AT1_getresuid32                  (uint32_t *, __uint32_t *)
#define __NR32AT2_getresuid32                  (uint32_t *, __uint32_t *)
#define __NR32AT0_setresgid32                  (uint32_t, __uint32_t)
#define __NR32AT1_setresgid32                  (uint32_t, __uint32_t)
#define __NR32AT2_setresgid32                  (uint32_t, __uint32_t)
#define __NR32AT0_getresgid32                  (uint32_t *, __uint32_t *)
#define __NR32AT1_getresgid32                  (uint32_t *, __uint32_t *)
#define __NR32AT2_getresgid32                  (uint32_t *, __uint32_t *)
#define __NR32AT0_chown32                      (char const *, char const *)
#define __NR32AT1_chown32                      (uint32_t, __uint32_t)
#define __NR32AT2_chown32                      (uint32_t, __uint32_t)
#define __NR32AT0_setuid32                     (uint32_t, __uint32_t)
#define __NR32AT0_setgid32                     (uint32_t, __uint32_t)
#define __NR32AT0_setfsuid32                   (uint32_t, __uint32_t)
#define __NR32AT0_setfsgid32                   (uint32_t, __uint32_t)
#define __NR32AT0_pivot_root                   (int, int)
#define __NR32AT0_mincore                      (void *, void *)
#define __NR32AT1_mincore                      (size_t, __size_t)
#define __NR32AT2_mincore                      (uint8_t *, __uint8_t *)
#define __NR32AT0_madvise                      (void *, void *)
#define __NR32AT1_madvise                      (size_t, __size_t)
#define __NR32AT2_madvise                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_getdents64                   (fd_t, __fd_t)
#define __NR32AT1_getdents64                   (struct linux_dirent64 *, struct linux_dirent64 *)
#define __NR32AT2_getdents64                   (size_t, __size_t)
#define __NR32AT0_fcntl64                      (fd_t, __fd_t)
#define __NR32AT1_fcntl64                      (fcntl_t, __fcntl_t)
#define __NR32AT2_fcntl64                      (void *, void *)
#define __NR32AT0_readahead                    (fd_t, __fd_t)
#define __NR32AT1_readahead                    (uint64_t, __uint64_t)
#define __NR32AT2_readahead                    (size_t, __size_t)
#define __NR32AT0_setxattr                     (char const *, char const *)
#define __NR32AT1_setxattr                     (char const *, char const *)
#define __NR32AT2_setxattr                     (void const *, void const *)
#define __NR32AT3_setxattr                     (size_t, __size_t)
#define __NR32AT4_setxattr                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_lsetxattr                    (char const *, char const *)
#define __NR32AT1_lsetxattr                    (char const *, char const *)
#define __NR32AT2_lsetxattr                    (void const *, void const *)
#define __NR32AT3_lsetxattr                    (size_t, __size_t)
#define __NR32AT4_lsetxattr                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_fsetxattr                    (fd_t, __fd_t)
#define __NR32AT1_fsetxattr                    (char const *, char const *)
#define __NR32AT2_fsetxattr                    (void const *, void const *)
#define __NR32AT3_fsetxattr                    (size_t, __size_t)
#define __NR32AT4_fsetxattr                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_getxattr                     (char const *, char const *)
#define __NR32AT1_getxattr                     (char const *, char const *)
#define __NR32AT2_getxattr                     (void *, void *)
#define __NR32AT3_getxattr                     (size_t, __size_t)
#define __NR32AT0_lgetxattr                    (char const *, char const *)
#define __NR32AT1_lgetxattr                    (char const *, char const *)
#define __NR32AT2_lgetxattr                    (void *, void *)
#define __NR32AT3_lgetxattr                    (size_t, __size_t)
#define __NR32AT0_fgetxattr                    (fd_t, __fd_t)
#define __NR32AT1_fgetxattr                    (char const *, char const *)
#define __NR32AT2_fgetxattr                    (void *, void *)
#define __NR32AT3_fgetxattr                    (size_t, __size_t)
#define __NR32AT0_listxattr                    (char const *, char const *)
#define __NR32AT1_listxattr                    (char *, char *)
#define __NR32AT2_listxattr                    (size_t, __size_t)
#define __NR32AT0_llistxattr                   (char const *, char const *)
#define __NR32AT1_llistxattr                   (char *, char *)
#define __NR32AT2_llistxattr                   (size_t, __size_t)
#define __NR32AT0_flistxattr                   (fd_t, __fd_t)
#define __NR32AT1_flistxattr                   (char *, char *)
#define __NR32AT2_flistxattr                   (size_t, __size_t)
#define __NR32AT0_removexattr                  (char const *, char const *)
#define __NR32AT1_removexattr                  (char const *, char const *)
#define __NR32AT0_lremovexattr                 (char const *, char const *)
#define __NR32AT1_lremovexattr                 (char const *, char const *)
#define __NR32AT0_fremovexattr                 (fd_t, __fd_t)
#define __NR32AT1_fremovexattr                 (char const *, char const *)
#define __NR32AT0_tkill                        (pid_t, __pid_t)
#define __NR32AT1_tkill                        (signo_t, __signo_t)
#define __NR32AT0_sendfile64                   (fd_t, __fd_t)
#define __NR32AT1_sendfile64                   (fd_t, __fd_t)
#define __NR32AT2_sendfile64                   (__ULONG64_TYPE__ *, __ULONG64_TYPE__ *)
#define __NR32AT3_sendfile64                   (size_t, __size_t)
#define __NR32AT0_futex                        (uint32_t *, __uint32_t *)
#define __NR32AT1_futex                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_futex                        (uint32_t, __uint32_t)
#define __NR32AT3_futex                        (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT4_futex                        (uint32_t *, __uint32_t *)
#define __NR32AT5_futex                        (uint32_t, __uint32_t)
#define __NR32AT0_sched_setaffinity            (pid_t, __pid_t)
#define __NR32AT1_sched_setaffinity            (size_t, __size_t)
#define __NR32AT2_sched_setaffinity            (struct __cpu_set_struct const *, struct __cpu_set_struct const *)
#define __NR32AT0_sched_getaffinity            (pid_t, __pid_t)
#define __NR32AT1_sched_getaffinity            (size_t, __size_t)
#define __NR32AT2_sched_getaffinity            (struct __cpu_set_struct *, struct __cpu_set_struct *)
#define __NR32AT0_set_thread_area              (int, int)
#define __NR32AT0_get_thread_area              (int, int)
#define __NR32AT0_io_setup                     (int, int)
#define __NR32AT0_io_destroy                   (int, int)
#define __NR32AT0_io_getevents                 (int, int)
#define __NR32AT0_io_submit                    (int, int)
#define __NR32AT0_io_cancel                    (int, int)
#define __NR32AT0_fadvise64                    (int, int)
#define __NR32AT0_exit_group                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_lookup_dcookie               (int, int)
#define __NR32AT0_epoll_create                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_epoll_ctl                    (fd_t, __fd_t)
#define __NR32AT1_epoll_ctl                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_epoll_ctl                    (fd_t, __fd_t)
#define __NR32AT3_epoll_ctl                    (struct epoll_event *, struct epoll_event *)
#define __NR32AT0_epoll_wait                   (fd_t, __fd_t)
#define __NR32AT1_epoll_wait                   (struct epoll_event *, struct epoll_event *)
#define __NR32AT2_epoll_wait                   (size_t, __size_t)
#define __NR32AT3_epoll_wait                   (syscall_slong_t, __syscall_slong_t)
#define __NR32AT0_remap_file_pages             (void *, void *)
#define __NR32AT1_remap_file_pages             (size_t, __size_t)
#define __NR32AT2_remap_file_pages             (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_remap_file_pages             (size_t, __size_t)
#define __NR32AT4_remap_file_pages             (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_set_tid_address              (pid_t *, __pid_t *)
#define __NR32AT0_timer_create                 (clockid_t, __clockid_t)
#define __NR32AT1_timer_create                 (struct sigevent *, struct sigevent *)
#define __NR32AT2_timer_create                 (timer_t *, __timer_t *)
#define __NR32AT0_timer_settime                (timer_t, __timer_t)
#define __NR32AT1_timer_settime                (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_timer_settime                (struct itimerspecx32 const *, struct __itimerspecx32 const *)
#define __NR32AT3_timer_settime                (struct itimerspecx32 *, struct __itimerspecx32 *)
#define __NR32AT0_timer_gettime                (timer_t, __timer_t)
#define __NR32AT1_timer_gettime                (struct itimerspecx32 *, struct __itimerspecx32 *)
#define __NR32AT0_timer_getoverrun             (timer_t, __timer_t)
#define __NR32AT0_timer_delete                 (timer_t, __timer_t)
#define __NR32AT0_clock_settime                (clockid_t, __clockid_t)
#define __NR32AT1_clock_settime                (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT0_clock_gettime                (clockid_t, __clockid_t)
#define __NR32AT1_clock_gettime                (struct timespecx32 *, struct __timespecx32 *)
#define __NR32AT0_clock_getres                 (clockid_t, __clockid_t)
#define __NR32AT1_clock_getres                 (struct timespecx32 *, struct __timespecx32 *)
#define __NR32AT0_clock_nanosleep              (clockid_t, __clockid_t)
#define __NR32AT1_clock_nanosleep              (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_clock_nanosleep              (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT3_clock_nanosleep              (struct timespecx32 *, struct __timespecx32 *)
#define __NR32AT0_statfs64                     (char const *, char const *)
#define __NR32AT1_statfs64                     (struct __statfsx32_64 *, struct __statfsx32_64 *)
#define __NR32AT0_fstatfs64                    (fd_t, __fd_t)
#define __NR32AT1_fstatfs64                    (struct __statfsx32_64 *, struct __statfsx32_64 *)
#define __NR32AT0_tgkill                       (pid_t, __pid_t)
#define __NR32AT1_tgkill                       (pid_t, __pid_t)
#define __NR32AT2_tgkill                       (signo_t, __signo_t)
#define __NR32AT0_utimes                       (char const *, char const *)
#define __NR32AT1_utimes                       (struct timevalx32 const *, struct __timevalx32 const *)
#define __NR32AT0_fadvise64_64                 (int, int)
#define __NR32AT0_mbind                        (int, int)
#define __NR32AT0_get_mempolicy                (int, int)
#define __NR32AT0_set_mempolicy                (int, int)
#define __NR32AT0_mq_open                      (char const *, char const *)
#define __NR32AT1_mq_open                      (oflag_t, __oflag_t)
#define __NR32AT2_mq_open                      (mode_t, __mode_t)
#define __NR32AT0_mq_unlink                    (char const *, char const *)
#define __NR32AT0_mq_timedsend                 (fd_t, __fd_t)
#define __NR32AT1_mq_timedsend                 (char const *, char const *)
#define __NR32AT2_mq_timedsend                 (size_t, __size_t)
#define __NR32AT3_mq_timedsend                 (uint32_t, __uint32_t)
#define __NR32AT4_mq_timedsend                 (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT0_mq_timedreceive              (fd_t, __fd_t)
#define __NR32AT1_mq_timedreceive              (char *, char *)
#define __NR32AT2_mq_timedreceive              (size_t, __size_t)
#define __NR32AT3_mq_timedreceive              (uint32_t *, __uint32_t *)
#define __NR32AT4_mq_timedreceive              (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT0_mq_notify                    (fd_t, __fd_t)
#define __NR32AT1_mq_notify                    (struct sigevent const *, struct sigevent const *)
#define __NR32AT0_mq_getsetattr                (fd_t, __fd_t)
#define __NR32AT1_mq_getsetattr                (struct mq_attr const *, struct mq_attr const *)
#define __NR32AT2_mq_getsetattr                (struct mq_attr *, struct mq_attr *)
#define __NR32AT0_kexec_load                   (int, int)
#define __NR32AT0_waitid                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_waitid                       (id_t, __id_t)
#define __NR32AT2_waitid                       (struct __siginfox32_struct *, struct __siginfox32_struct *)
#define __NR32AT3_waitid                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_waitid                       (struct rusagex32 *, struct __rusagex32 *)
#define __NR32AT0_add_key                      (int, int)
#define __NR32AT0_request_key                  (int, int)
#define __NR32AT0_keyctl                       (int, int)
#define __NR32AT0_ioprio_set                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_ioprio_set                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_ioprio_set                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_ioprio_get                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_ioprio_get                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_inotify_add_watch            (fd_t, __fd_t)
#define __NR32AT1_inotify_add_watch            (char const *, char const *)
#define __NR32AT2_inotify_add_watch            (uint32_t, __uint32_t)
#define __NR32AT0_inotify_rm_watch             (fd_t, __fd_t)
#define __NR32AT1_inotify_rm_watch             (int, int)
#define __NR32AT0_migrate_pages                (int, int)
#define __NR32AT0_openat                       (fd_t, __fd_t)
#define __NR32AT1_openat                       (char const *, char const *)
#define __NR32AT2_openat                       (oflag_t, __oflag_t)
#define __NR32AT3_openat                       (mode_t, __mode_t)
#define __NR32AT0_mkdirat                      (fd_t, __fd_t)
#define __NR32AT1_mkdirat                      (char const *, char const *)
#define __NR32AT2_mkdirat                      (mode_t, __mode_t)
#define __NR32AT0_mknodat                      (fd_t, __fd_t)
#define __NR32AT1_mknodat                      (char const *, char const *)
#define __NR32AT2_mknodat                      (mode_t, __mode_t)
#define __NR32AT3_mknodat                      (dev_t, __dev_t)
#define __NR32AT0_fchownat                     (fd_t, __fd_t)
#define __NR32AT1_fchownat                     (char const *, char const *)
#define __NR32AT2_fchownat                     (uid_t, __uid_t)
#define __NR32AT3_fchownat                     (gid_t, __gid_t)
#define __NR32AT4_fchownat                     (atflag_t, __atflag_t)
#define __NR32AT0_futimesat                    (fd_t, __fd_t)
#define __NR32AT1_futimesat                    (char const *, char const *)
#define __NR32AT2_futimesat                    (struct timevalx32 const *, struct __timevalx32 const *)
#define __NR32AT0_fstatat64                    (fd_t, __fd_t)
#define __NR32AT1_fstatat64                    (char const *, char const *)
#define __NR32AT2_fstatat64                    (struct linux_statx32_64 *, struct linux_statx32_64 *)
#define __NR32AT3_fstatat64                    (atflag_t, __atflag_t)
#define __NR32AT0_unlinkat                     (fd_t, __fd_t)
#define __NR32AT1_unlinkat                     (char const *, char const *)
#define __NR32AT2_unlinkat                     (atflag_t, __atflag_t)
#define __NR32AT0_renameat                     (fd_t, __fd_t)
#define __NR32AT1_renameat                     (char const *, char const *)
#define __NR32AT2_renameat                     (fd_t, __fd_t)
#define __NR32AT3_renameat                     (char const *, char const *)
#define __NR32AT0_linkat                       (fd_t, __fd_t)
#define __NR32AT1_linkat                       (char const *, char const *)
#define __NR32AT2_linkat                       (fd_t, __fd_t)
#define __NR32AT3_linkat                       (char const *, char const *)
#define __NR32AT4_linkat                       (atflag_t, __atflag_t)
#define __NR32AT0_symlinkat                    (char const *, char const *)
#define __NR32AT1_symlinkat                    (fd_t, __fd_t)
#define __NR32AT2_symlinkat                    (char const *, char const *)
#define __NR32AT0_readlinkat                   (fd_t, __fd_t)
#define __NR32AT1_readlinkat                   (char const *, char const *)
#define __NR32AT2_readlinkat                   (char *, char *)
#define __NR32AT3_readlinkat                   (size_t, __size_t)
#define __NR32AT0_fchmodat                     (fd_t, __fd_t)
#define __NR32AT1_fchmodat                     (char const *, char const *)
#define __NR32AT2_fchmodat                     (mode_t, __mode_t)
#define __NR32AT3_fchmodat                     (atflag_t, __atflag_t)
#define __NR32AT0_faccessat                    (fd_t, __fd_t)
#define __NR32AT1_faccessat                    (char const *, char const *)
#define __NR32AT2_faccessat                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_pselect6                     (size_t, __size_t)
#define __NR32AT1_pselect6                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT2_pselect6                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT3_pselect6                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT4_pselect6                     (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT5_pselect6                     (struct __sigset_with_sizex32 const *, struct __sigset_with_sizex32 const *)
#define __NR32AT0_ppoll                        (struct pollfd *, struct pollfd *)
#define __NR32AT1_ppoll                        (size_t, __size_t)
#define __NR32AT2_ppoll                        (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT3_ppoll                        (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR32AT4_ppoll                        (size_t, __size_t)
#define __NR32AT0_unshare                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_set_robust_list              (int, int)
#define __NR32AT0_get_robust_list              (int, int)
#define __NR32AT0_splice                       (fd_t, __fd_t)
#define __NR32AT1_splice                       (uint64_t *, __uint64_t *)
#define __NR32AT2_splice                       (fd_t, __fd_t)
#define __NR32AT3_splice                       (uint64_t *, __uint64_t *)
#define __NR32AT4_splice                       (size_t, __size_t)
#define __NR32AT5_splice                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_sync_file_range              (fd_t, __fd_t)
#define __NR32AT1_sync_file_range              (uint64_t, __uint64_t)
#define __NR32AT2_sync_file_range              (uint64_t, __uint64_t)
#define __NR32AT3_sync_file_range              (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_tee                          (fd_t, __fd_t)
#define __NR32AT1_tee                          (fd_t, __fd_t)
#define __NR32AT2_tee                          (size_t, __size_t)
#define __NR32AT3_tee                          (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_vmsplice                     (fd_t, __fd_t)
#define __NR32AT1_vmsplice                     (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_vmsplice                     (size_t, __size_t)
#define __NR32AT3_vmsplice                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_move_pages                   (int, int)
#define __NR32AT0_getcpu                       (uint32_t *, __uint32_t *)
#define __NR32AT1_getcpu                       (uint32_t *, __uint32_t *)
#define __NR32AT2_getcpu                       (struct getcpu_cache *, struct getcpu_cache *)
#define __NR32AT0_epoll_pwait                  (fd_t, __fd_t)
#define __NR32AT1_epoll_pwait                  (struct epoll_event *, struct epoll_event *)
#define __NR32AT2_epoll_pwait                  (size_t, __size_t)
#define __NR32AT3_epoll_pwait                  (syscall_slong_t, __syscall_slong_t)
#define __NR32AT4_epoll_pwait                  (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR32AT5_epoll_pwait                  (size_t, __size_t)
#define __NR32AT0_utimensat                    (fd_t, __fd_t)
#define __NR32AT1_utimensat                    (char const *, char const *)
#define __NR32AT2_utimensat                    (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT3_utimensat                    (atflag_t, __atflag_t)
#define __NR32AT0_signalfd                     (fd_t, __fd_t)
#define __NR32AT1_signalfd                     (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR32AT2_signalfd                     (size_t, __size_t)
#define __NR32AT0_timerfd_create               (clockid_t, __clockid_t)
#define __NR32AT1_timerfd_create               (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_eventfd                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_fallocate                    (fd_t, __fd_t)
#define __NR32AT1_fallocate                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_fallocate                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_fallocate                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_timerfd_settime              (fd_t, __fd_t)
#define __NR32AT1_timerfd_settime              (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_timerfd_settime              (struct itimerspecx32 const *, struct __itimerspecx32 const *)
#define __NR32AT3_timerfd_settime              (struct itimerspecx32 *, struct __itimerspecx32 *)
#define __NR32AT0_timerfd_gettime              (fd_t, __fd_t)
#define __NR32AT1_timerfd_gettime              (struct itimerspecx32 *, struct __itimerspecx32 *)
#define __NR32AT0_signalfd4                    (fd_t, __fd_t)
#define __NR32AT1_signalfd4                    (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR32AT2_signalfd4                    (size_t, __size_t)
#define __NR32AT3_signalfd4                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_eventfd2                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_eventfd2                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_epoll_create1                (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_dup3                         (fd_t, __fd_t)
#define __NR32AT1_dup3                         (fd_t, __fd_t)
#define __NR32AT2_dup3                         (oflag_t, __oflag_t)
#define __NR32AT0_pipe2                        (fd_t *, __fd_t *)
#define __NR32AT1_pipe2                        (oflag_t, __oflag_t)
#define __NR32AT0_inotify_init1                (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_preadv                       (fd_t, __fd_t)
#define __NR32AT1_preadv                       (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_preadv                       (size_t, __size_t)
#define __NR32AT3_preadv                       (uint64_t, __uint64_t)
#define __NR32AT0_pwritev                      (fd_t, __fd_t)
#define __NR32AT1_pwritev                      (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_pwritev                      (size_t, __size_t)
#define __NR32AT3_pwritev                      (uint64_t, __uint64_t)
#define __NR32AT0_rt_tgsigqueueinfo            (pid_t, __pid_t)
#define __NR32AT1_rt_tgsigqueueinfo            (pid_t, __pid_t)
#define __NR32AT2_rt_tgsigqueueinfo            (signo_t, __signo_t)
#define __NR32AT3_rt_tgsigqueueinfo            (struct __siginfox32_struct const *, struct __siginfox32_struct const *)
#define __NR32AT0_perf_event_open              (int, int)
#define __NR32AT0_recvmmsg                     (fd_t, __fd_t)
#define __NR32AT1_recvmmsg                     (struct mmsghdrx32 *, struct __mmsghdrx32 *)
#define __NR32AT2_recvmmsg                     (size_t, __size_t)
#define __NR32AT3_recvmmsg                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_recvmmsg                     (struct timespecx32 const *, struct __timespecx32 const *)
#define __NR32AT0_fanotify_init                (int, int)
#define __NR32AT0_fanotify_mark                (int, int)
#define __NR32AT0_prlimit64                    (pid_t, __pid_t)
#define __NR32AT1_prlimit64                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_prlimit64                    (struct rlimitx32_64 const *, struct __rlimitx32_64 const *)
#define __NR32AT3_prlimit64                    (struct rlimitx32_64 *, struct __rlimitx32_64 *)
#define __NR32AT0_name_to_handle_at            (fd_t, __fd_t)
#define __NR32AT1_name_to_handle_at            (char const *, char const *)
#define __NR32AT2_name_to_handle_at            (struct file_handle *, struct file_handle *)
#define __NR32AT3_name_to_handle_at            (int32_t *, __int32_t *)
#define __NR32AT4_name_to_handle_at            (atflag_t, __atflag_t)
#define __NR32AT0_open_by_handle_at            (fd_t, __fd_t)
#define __NR32AT1_open_by_handle_at            (struct file_handle const *, struct file_handle const *)
#define __NR32AT2_open_by_handle_at            (oflag_t, __oflag_t)
#define __NR32AT0_clock_adjtime                (int, int)
#define __NR32AT0_syncfs                       (fd_t, __fd_t)
#define __NR32AT0_sendmmsg                     (fd_t, __fd_t)
#define __NR32AT1_sendmmsg                     (struct mmsghdrx32 *, struct __mmsghdrx32 *)
#define __NR32AT2_sendmmsg                     (size_t, __size_t)
#define __NR32AT3_sendmmsg                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_setns                        (fd_t, __fd_t)
#define __NR32AT1_setns                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_process_vm_readv             (pid_t, __pid_t)
#define __NR32AT1_process_vm_readv             (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_process_vm_readv             (size_t, __size_t)
#define __NR32AT3_process_vm_readv             (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT4_process_vm_readv             (size_t, __size_t)
#define __NR32AT5_process_vm_readv             (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_process_vm_writev            (pid_t, __pid_t)
#define __NR32AT1_process_vm_writev            (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_process_vm_writev            (size_t, __size_t)
#define __NR32AT3_process_vm_writev            (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT4_process_vm_writev            (size_t, __size_t)
#define __NR32AT5_process_vm_writev            (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_kcmp                         (pid_t, __pid_t)
#define __NR32AT1_kcmp                         (pid_t, __pid_t)
#define __NR32AT2_kcmp                         (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_kcmp                         (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_kcmp                         (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_finit_module                 (fd_t, __fd_t)
#define __NR32AT1_finit_module                 (char const *, char const *)
#define __NR32AT2_finit_module                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_sched_setattr                (int, int)
#define __NR32AT0_sched_getattr                (int, int)
#define __NR32AT0_renameat2                    (fd_t, __fd_t)
#define __NR32AT1_renameat2                    (char const *, char const *)
#define __NR32AT2_renameat2                    (fd_t, __fd_t)
#define __NR32AT3_renameat2                    (char const *, char const *)
#define __NR32AT4_renameat2                    (atflag_t, __atflag_t)
#define __NR32AT0_seccomp                      (int, int)
#define __NR32AT0_getrandom                    (void *, void *)
#define __NR32AT1_getrandom                    (size_t, __size_t)
#define __NR32AT2_getrandom                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_memfd_create                 (char const *, char const *)
#define __NR32AT1_memfd_create                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_bpf                          (int, int)
#define __NR32AT0_execveat                     (fd_t, __fd_t)
#define __NR32AT1_execveat                     (char const *, char const *)
#define __NR32AT2_execveat                     (__HYBRID_PTR32(char const) const *, __HYBRID_PTR32(char const) const *)
#define __NR32AT3_execveat                     (__HYBRID_PTR32(char const) const *, __HYBRID_PTR32(char const) const *)
#define __NR32AT4_execveat                     (atflag_t, __atflag_t)
#define __NR32AT0_socket                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_socket                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_socket                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_socketpair                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_socketpair                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_socketpair                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_socketpair                   (fd_t *, __fd_t *)
#define __NR32AT0_bind                         (fd_t, __fd_t)
#define __NR32AT1_bind                         (struct sockaddr const *, struct sockaddr const *)
#define __NR32AT2_bind                         (socklen_t, __socklen_t)
#define __NR32AT0_connect                      (fd_t, __fd_t)
#define __NR32AT1_connect                      (struct sockaddr const *, struct sockaddr const *)
#define __NR32AT2_connect                      (socklen_t, __socklen_t)
#define __NR32AT0_listen                       (fd_t, __fd_t)
#define __NR32AT1_listen                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_accept4                      (fd_t, __fd_t)
#define __NR32AT1_accept4                      (struct sockaddr *, struct sockaddr *)
#define __NR32AT2_accept4                      (socklen_t *, __socklen_t *)
#define __NR32AT3_accept4                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_getsockopt                   (fd_t, __fd_t)
#define __NR32AT1_getsockopt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_getsockopt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_getsockopt                   (void *, void *)
#define __NR32AT4_getsockopt                   (socklen_t *, __socklen_t *)
#define __NR32AT0_setsockopt                   (fd_t, __fd_t)
#define __NR32AT1_setsockopt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_setsockopt                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_setsockopt                   (void const *, void const *)
#define __NR32AT4_setsockopt                   (socklen_t, __socklen_t)
#define __NR32AT0_getsockname                  (fd_t, __fd_t)
#define __NR32AT1_getsockname                  (struct sockaddr *, struct sockaddr *)
#define __NR32AT2_getsockname                  (socklen_t *, __socklen_t *)
#define __NR32AT0_getpeername                  (fd_t, __fd_t)
#define __NR32AT1_getpeername                  (struct sockaddr *, struct sockaddr *)
#define __NR32AT2_getpeername                  (socklen_t *, __socklen_t *)
#define __NR32AT0_sendto                       (fd_t, __fd_t)
#define __NR32AT1_sendto                       (void const *, void const *)
#define __NR32AT2_sendto                       (size_t, __size_t)
#define __NR32AT3_sendto                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_sendto                       (struct sockaddr const *, struct sockaddr const *)
#define __NR32AT5_sendto                       (socklen_t, __socklen_t)
#define __NR32AT0_sendmsg                      (fd_t, __fd_t)
#define __NR32AT1_sendmsg                      (struct msghdrx32 const *, struct __msghdrx32 const *)
#define __NR32AT2_sendmsg                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_recvfrom                     (fd_t, __fd_t)
#define __NR32AT1_recvfrom                     (void *, void *)
#define __NR32AT2_recvfrom                     (size_t, __size_t)
#define __NR32AT3_recvfrom                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_recvfrom                     (struct sockaddr *, struct sockaddr *)
#define __NR32AT5_recvfrom                     (socklen_t *, __socklen_t *)
#define __NR32AT0_recvmsg                      (fd_t, __fd_t)
#define __NR32AT1_recvmsg                      (struct msghdrx32 *, struct __msghdrx32 *)
#define __NR32AT2_recvmsg                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_shutdown                     (fd_t, __fd_t)
#define __NR32AT1_shutdown                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_userfaultfd                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_membarrier                   (int, int)
#define __NR32AT0_mlock2                       (void const *, void const *)
#define __NR32AT1_mlock2                       (size_t, __size_t)
#define __NR32AT2_mlock2                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_copy_file_range              (int, int)
#define __NR32AT0_preadv2                      (int, int)
#define __NR32AT0_pwritev2                     (int, int)
#define __NR32AT0_pkey_mprotect                (void *, void *)
#define __NR32AT1_pkey_mprotect                (size_t, __size_t)
#define __NR32AT2_pkey_mprotect                (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_pkey_mprotect                (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_pkey_alloc                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_pkey_alloc                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_pkey_free                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_statx                        (int, int)
#define __NR32AT0_arch_prctl                   (unsigned int, unsigned int)
#define __NR32AT1_arch_prctl                   (uint32_t *, __uint32_t *)
#define __NR32AT0_io_pgetevents                (int, int)
#define __NR32AT0_rseq                         (int, int)
#define __NR32AT0_semget                       (int, int)
#define __NR32AT0_semctl                       (int, int)
#define __NR32AT0_shmget                       (key_t, __key_t)
#define __NR32AT1_shmget                       (size_t, __size_t)
#define __NR32AT2_shmget                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_shmctl                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_shmctl                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_shmctl                       (struct shmid_ds *, struct shmid_ds *)
#define __NR32AT0_shmat                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_shmat                        (void const *, void const *)
#define __NR32AT2_shmat                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_shmdt                        (void const *, void const *)
#define __NR32AT0_msgget                       (int, int)
#define __NR32AT0_msgsnd                       (int, int)
#define __NR32AT0_msgrcv                       (int, int)
#define __NR32AT0_msgctl                       (int, int)
#define __NR32AT0_clock_gettime64              (clockid_t, __clockid_t)
#define __NR32AT1_clock_gettime64              (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NR32AT0_clock_settime64              (clockid_t, __clockid_t)
#define __NR32AT1_clock_settime64              (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT0_clock_adjtime64              (int, int)
#define __NR32AT0_clock_getres_time64          (clockid_t, __clockid_t)
#define __NR32AT1_clock_getres_time64          (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NR32AT0_clock_nanosleep_time64       (clockid_t, __clockid_t)
#define __NR32AT1_clock_nanosleep_time64       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_clock_nanosleep_time64       (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT3_clock_nanosleep_time64       (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NR32AT0_timer_gettime64              (timer_t, __timer_t)
#define __NR32AT1_timer_gettime64              (struct itimerspecx32_64 *, struct __itimerspecx32_64 *)
#define __NR32AT0_timer_settime64              (timer_t, __timer_t)
#define __NR32AT1_timer_settime64              (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_timer_settime64              (struct itimerspecx32_64 const *, struct __itimerspecx32_64 const *)
#define __NR32AT3_timer_settime64              (struct itimerspecx32_64 *, struct __itimerspecx32_64 *)
#define __NR32AT0_timerfd_gettime64            (fd_t, __fd_t)
#define __NR32AT1_timerfd_gettime64            (struct itimerspecx32_64 *, struct __itimerspecx32_64 *)
#define __NR32AT0_timerfd_settime64            (fd_t, __fd_t)
#define __NR32AT1_timerfd_settime64            (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_timerfd_settime64            (struct itimerspecx32_64 const *, struct __itimerspecx32_64 const *)
#define __NR32AT3_timerfd_settime64            (struct itimerspecx32_64 *, struct __itimerspecx32_64 *)
#define __NR32AT0_utimensat_time64             (fd_t, __fd_t)
#define __NR32AT1_utimensat_time64             (char const *, char const *)
#define __NR32AT2_utimensat_time64             (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT3_utimensat_time64             (atflag_t, __atflag_t)
#define __NR32AT0_pselect6_time64              (size_t, __size_t)
#define __NR32AT1_pselect6_time64              (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT2_pselect6_time64              (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT3_pselect6_time64              (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT4_pselect6_time64              (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT5_pselect6_time64              (struct __sigset_with_sizex32 const *, struct __sigset_with_sizex32 const *)
#define __NR32AT0_ppoll_time64                 (struct pollfd *, struct pollfd *)
#define __NR32AT1_ppoll_time64                 (size_t, __size_t)
#define __NR32AT2_ppoll_time64                 (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT3_ppoll_time64                 (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR32AT4_ppoll_time64                 (size_t, __size_t)
#define __NR32AT0_io_pgetevents_time64         (int, int)
#define __NR32AT0_recvmmsg_time64              (fd_t, __fd_t)
#define __NR32AT1_recvmmsg_time64              (struct mmsghdrx32 *, struct __mmsghdrx32 *)
#define __NR32AT2_recvmmsg_time64              (size_t, __size_t)
#define __NR32AT3_recvmmsg_time64              (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_recvmmsg_time64              (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT0_mq_timedsend_time64          (fd_t, __fd_t)
#define __NR32AT1_mq_timedsend_time64          (char const *, char const *)
#define __NR32AT2_mq_timedsend_time64          (size_t, __size_t)
#define __NR32AT3_mq_timedsend_time64          (uint32_t, __uint32_t)
#define __NR32AT4_mq_timedsend_time64          (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT0_mq_timedreceive_time64       (fd_t, __fd_t)
#define __NR32AT1_mq_timedreceive_time64       (char *, char *)
#define __NR32AT2_mq_timedreceive_time64       (size_t, __size_t)
#define __NR32AT3_mq_timedreceive_time64       (uint32_t *, __uint32_t *)
#define __NR32AT4_mq_timedreceive_time64       (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT0_semtimedop_time64            (int, int)
#define __NR32AT0_rt_sigtimedwait_time64       (struct __sigset_struct const *, struct __sigset_struct const *)
#define __NR32AT1_rt_sigtimedwait_time64       (struct __siginfox32_struct *, struct __siginfox32_struct *)
#define __NR32AT2_rt_sigtimedwait_time64       (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT3_rt_sigtimedwait_time64       (size_t, __size_t)
#define __NR32AT0_futex_time64                 (uint32_t *, __uint32_t *)
#define __NR32AT1_futex_time64                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_futex_time64                 (uint32_t, __uint32_t)
#define __NR32AT3_futex_time64                 (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT4_futex_time64                 (uint32_t *, __uint32_t *)
#define __NR32AT5_futex_time64                 (uint32_t, __uint32_t)
#define __NR32AT0_sched_rr_get_interval_time64 (pid_t, __pid_t)
#define __NR32AT1_sched_rr_get_interval_time64 (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NR32AT0_pidfd_send_signal            (fd_t, __fd_t)
#define __NR32AT1_pidfd_send_signal            (signo_t, __signo_t)
#define __NR32AT2_pidfd_send_signal            (struct __siginfox32_struct const *, struct __siginfox32_struct const *)
#define __NR32AT3_pidfd_send_signal            (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_io_uring_setup               (int, int)
#define __NR32AT0_io_uring_enter               (int, int)
#define __NR32AT0_io_uring_register            (int, int)
#define __NR32AT0_open_tree                    (int, int)
#define __NR32AT0_move_mount                   (int, int)
#define __NR32AT0_fsopen                       (int, int)
#define __NR32AT0_fsconfig                     (int, int)
#define __NR32AT0_fsmount                      (int, int)
#define __NR32AT0_fspick                       (int, int)
#define __NR32AT0_pidfd_open                   (pid_t, __pid_t)
#define __NR32AT1_pidfd_open                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_clone3                       (struct clone_args *, struct clone_args *)
#define __NR32AT1_clone3                       (size_t, __size_t)
#define __NR32AT0_close_range                  (unsigned int, unsigned int)
#define __NR32AT1_close_range                  (unsigned int, unsigned int)
#define __NR32AT2_close_range                  (unsigned int, unsigned int)
#define __NR32AT0_openat2                      (int, int)
#define __NR32AT0_pidfd_getfd                  (fd_t, __fd_t)
#define __NR32AT1_pidfd_getfd                  (fd_t, __fd_t)
#define __NR32AT2_pidfd_getfd                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_faccessat2                   (fd_t, __fd_t)
#define __NR32AT1_faccessat2                   (char const *, char const *)
#define __NR32AT2_faccessat2                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_faccessat2                   (atflag_t, __atflag_t)
#define __NR32AT0_pwritevf                     (fd_t, __fd_t)
#define __NR32AT1_pwritevf                     (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_pwritevf                     (size_t, __size_t)
#define __NR32AT3_pwritevf                     (uint64_t, __uint64_t)
#define __NR32AT4_pwritevf                     (iomode_t, __iomode_t)
#define __NR32AT0_preadvf                      (fd_t, __fd_t)
#define __NR32AT1_preadvf                      (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_preadvf                      (size_t, __size_t)
#define __NR32AT3_preadvf                      (uint64_t, __uint64_t)
#define __NR32AT4_preadvf                      (iomode_t, __iomode_t)
#define __NR32AT0_fallocate64                  (fd_t, __fd_t)
#define __NR32AT1_fallocate64                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_fallocate64                  (uint64_t, __uint64_t)
#define __NR32AT3_fallocate64                  (uint64_t, __uint64_t)
#define __NR32AT0_freadlinkat                  (fd_t, __fd_t)
#define __NR32AT1_freadlinkat                  (char const *, char const *)
#define __NR32AT2_freadlinkat                  (char *, char *)
#define __NR32AT3_freadlinkat                  (size_t, __size_t)
#define __NR32AT4_freadlinkat                  (atflag_t, __atflag_t)
#define __NR32AT0_fsymlinkat                   (char const *, char const *)
#define __NR32AT1_fsymlinkat                   (fd_t, __fd_t)
#define __NR32AT2_fsymlinkat                   (char const *, char const *)
#define __NR32AT3_fsymlinkat                   (atflag_t, __atflag_t)
#define __NR32AT0_kfstatat                     (fd_t, __fd_t)
#define __NR32AT1_kfstatat                     (char const *, char const *)
#define __NR32AT2_kfstatat                     (struct __kos_stat *, struct __kos_stat *)
#define __NR32AT3_kfstatat                     (atflag_t, __atflag_t)
#define __NR32AT0_futimesat64                  (fd_t, __fd_t)
#define __NR32AT1_futimesat64                  (char const *, char const *)
#define __NR32AT2_futimesat64                  (struct timevalx32_64 const *, struct __timevalx32_64 const *)
#define __NR32AT0_fmknodat                     (fd_t, __fd_t)
#define __NR32AT1_fmknodat                     (char const *, char const *)
#define __NR32AT2_fmknodat                     (mode_t, __mode_t)
#define __NR32AT3_fmknodat                     (dev_t, __dev_t)
#define __NR32AT4_fmknodat                     (atflag_t, __atflag_t)
#define __NR32AT0_fmkdirat                     (fd_t, __fd_t)
#define __NR32AT1_fmkdirat                     (char const *, char const *)
#define __NR32AT2_fmkdirat                     (mode_t, __mode_t)
#define __NR32AT3_fmkdirat                     (atflag_t, __atflag_t)
#define __NR32AT0_inotify_add_watch_at         (fd_t, __fd_t)
#define __NR32AT1_inotify_add_watch_at         (fd_t, __fd_t)
#define __NR32AT2_inotify_add_watch_at         (char const *, char const *)
#define __NR32AT3_inotify_add_watch_at         (atflag_t, __atflag_t)
#define __NR32AT4_inotify_add_watch_at         (uint32_t, __uint32_t)
#define __NR32AT0_waitid64                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_waitid64                     (id_t, __id_t)
#define __NR32AT2_waitid64                     (struct __siginfox32_struct *, struct __siginfox32_struct *)
#define __NR32AT3_waitid64                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_waitid64                     (struct rusagex32_64 *, struct __rusagex32_64 *)
#define __NR32AT0_utimes64                     (char const *, char const *)
#define __NR32AT1_utimes64                     (struct timevalx32_64 const *, struct __timevalx32_64 const *)
#define __NR32AT0_kreaddirf                    (fd_t, __fd_t)
#define __NR32AT1_kreaddirf                    (struct dirent *, struct dirent *)
#define __NR32AT2_kreaddirf                    (size_t, __size_t)
#define __NR32AT3_kreaddirf                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT4_kreaddirf                    (iomode_t, __iomode_t)
#define __NR32AT0_kfstat                       (fd_t, __fd_t)
#define __NR32AT1_kfstat                       (struct __kos_stat *, struct __kos_stat *)
#define __NR32AT0_klstat                       (char const *, char const *)
#define __NR32AT1_klstat                       (struct __kos_stat *, struct __kos_stat *)
#define __NR32AT0_kstat                        (char const *, char const *)
#define __NR32AT1_kstat                        (struct __kos_stat *, struct __kos_stat *)
#define __NR32AT0_pwrite64f                    (fd_t, __fd_t)
#define __NR32AT1_pwrite64f                    (void const *, void const *)
#define __NR32AT2_pwrite64f                    (size_t, __size_t)
#define __NR32AT3_pwrite64f                    (uint64_t, __uint64_t)
#define __NR32AT4_pwrite64f                    (iomode_t, __iomode_t)
#define __NR32AT0_pread64f                     (fd_t, __fd_t)
#define __NR32AT1_pread64f                     (void *, void *)
#define __NR32AT2_pread64f                     (size_t, __size_t)
#define __NR32AT3_pread64f                     (uint64_t, __uint64_t)
#define __NR32AT4_pread64f                     (iomode_t, __iomode_t)
#define __NR32AT0_ksigreturn                   (struct fpustate32 const *, struct fpustate32 const *)
#define __NR32AT1_ksigreturn                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_ksigreturn                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_ksigreturn                   (struct __sigset_with_sizex32 const *, struct __sigset_with_sizex32 const *)
#define __NR32AT4_ksigreturn                   (struct rpc_syscall_info32 const *, struct rpc_syscall_info32 const *)
#define __NR32AT5_ksigreturn                   (struct ucpustate32 const *, struct ucpustate32 const *)
#define __NR32AT0_nanosleep64                  (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT1_nanosleep64                  (struct timespecx32_64 *, struct __timespecx32_64 *)
#define __NR32AT0_ksysctl                      (ioctl_t, __ioctl_t)
#define __NR32AT1_ksysctl                      (void *, void *)
#define __NR32AT0_writevf                      (fd_t, __fd_t)
#define __NR32AT1_writevf                      (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_writevf                      (size_t, __size_t)
#define __NR32AT3_writevf                      (iomode_t, __iomode_t)
#define __NR32AT0_readvf                       (fd_t, __fd_t)
#define __NR32AT1_readvf                       (struct iovecx32 const *, struct __iovecx32 const *)
#define __NR32AT2_readvf                       (size_t, __size_t)
#define __NR32AT3_readvf                       (iomode_t, __iomode_t)
#define __NR32AT0_kreaddir                     (fd_t, __fd_t)
#define __NR32AT1_kreaddir                     (struct dirent *, struct dirent *)
#define __NR32AT2_kreaddir                     (size_t, __size_t)
#define __NR32AT3_kreaddir                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_wait4_64                     (pid_t, __pid_t)
#define __NR32AT1_wait4_64                     (int32_t *, __int32_t *)
#define __NR32AT2_wait4_64                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT3_wait4_64                     (struct rusagex32_64 *, struct __rusagex32_64 *)
#define __NR32AT0_getitimer64                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_getitimer64                  (struct __itimervalx32_64 *, struct __itimervalx32_64 *)
#define __NR32AT0_setitimer64                  (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_setitimer64                  (struct __itimervalx32_64 const *, struct __itimervalx32_64 const *)
#define __NR32AT2_setitimer64                  (struct __itimervalx32_64 *, struct __itimervalx32_64 *)
#define __NR32AT0_maplibrary                   (void *, void *)
#define __NR32AT1_maplibrary                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_maplibrary                   (fd_t, __fd_t)
#define __NR32AT3_maplibrary                   (struct elf32_phdr const *, struct elf32_phdr const *)
#define __NR32AT4_maplibrary                   (size_t, __size_t)
#define __NR32AT0_select64                     (size_t, __size_t)
#define __NR32AT1_select64                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT2_select64                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT3_select64                     (struct __fd_set_struct *, struct __fd_set_struct *)
#define __NR32AT4_select64                     (struct timevalx32_64 *, struct __timevalx32_64 *)
#define __NR32AT0_settimeofday64               (struct timevalx32_64 const *, struct __timevalx32_64 const *)
#define __NR32AT1_settimeofday64               (struct timezone const *, struct timezone const *)
#define __NR32AT0_gettimeofday64               (struct timevalx32_64 *, struct __timevalx32_64 *)
#define __NR32AT1_gettimeofday64               (struct timezone *, struct timezone *)
#define __NR32AT0_getrusage64                  (syscall_slong_t, __syscall_slong_t)
#define __NR32AT1_getrusage64                  (struct rusagex32_64 *, struct __rusagex32_64 *)
#define __NR32AT0_fsmode                       (uint64_t, __uint64_t)
#define __NR32AT0_ioctlf                       (fd_t, __fd_t)
#define __NR32AT1_ioctlf                       (ioctl_t, __ioctl_t)
#define __NR32AT2_ioctlf                       (iomode_t, __iomode_t)
#define __NR32AT3_ioctlf                       (void *, void *)
#define __NR32AT0_rtm_abort                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_ftime64                      (struct timebx32_64 *, struct __timebx32_64 *)
#define __NR32AT0_set_userprocmask_address     (struct userprocmask *, struct userprocmask *)
#define __NR32AT0_utime64                      (char const *, char const *)
#define __NR32AT1_utime64                      (struct utimbufx32_64 const *, struct __utimbufx32_64 const *)
#define __NR32AT0_userviofd                    (size_t, __size_t)
#define __NR32AT1_userviofd                    (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_stime64                      (time64_t const *, __time64_t const *)
#define __NR32AT0_coredump                     (struct ucpustate32 const *, struct ucpustate32 const *)
#define __NR32AT1_coredump                     (struct ucpustate32 const *, struct ucpustate32 const *)
#define __NR32AT2_coredump                     (__HYBRID_PTR32(void const) const *, __HYBRID_PTR32(void const) const *)
#define __NR32AT3_coredump                     (size_t, __size_t)
#define __NR32AT4_coredump                     (union coredump_info32 const *, union coredump_info32 const *)
#define __NR32AT5_coredump                     (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_mktty                        (char const *, char const *)
#define __NR32AT1_mktty                        (fd_t, __fd_t)
#define __NR32AT2_mktty                        (fd_t, __fd_t)
#define __NR32AT3_mktty                        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_lfutexexpr                   (uint32_t *, __uint32_t *)
#define __NR32AT1_lfutexexpr                   (void *, void *)
#define __NR32AT2_lfutexexpr                   (struct lfutexexprx32 const *, struct lfutexexprx32 const *)
#define __NR32AT3_lfutexexpr                   (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT4_lfutexexpr                   (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_lseek64                      (fd_t, __fd_t)
#define __NR32AT1_lseek64                      (int64_t, __int64_t)
#define __NR32AT2_lseek64                      (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT0_lfutex                       (uint32_t *, __uint32_t *)
#define __NR32AT1_lfutex                       (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_lfutex                       (uint32_t, __uint32_t)
#define __NR32AT3_lfutex                       (struct timespecx32_64 const *, struct __timespecx32_64 const *)
#define __NR32AT4_lfutex                       (uint32_t, __uint32_t)
#define __NR32AT0_debugtrap                    (struct ucpustate32 const *, struct ucpustate32 const *)
#define __NR32AT1_debugtrap                    (struct debugtrap_reason32 const *, struct debugtrap_reason32 const *)
#define __NR32AT0_get_exception_handler        (__ULONG32_TYPE__ *, __ULONG32_TYPE__ *)
#define __NR32AT1_get_exception_handler        (__except_handler32_t *, __except_handler32_t *)
#define __NR32AT2_get_exception_handler        (__HYBRID_PTR32(void) *, __HYBRID_PTR32(void) *)
#define __NR32AT0_set_exception_handler        (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT1_set_exception_handler        (except_handler_t, __except_handler_t)
#define __NR32AT2_set_exception_handler        (void *, void *)
#define __NR32AT0_time64                       (int64_t *, __int64_t *)
#define __NR32AT0_fchdirat                     (fd_t, __fd_t)
#define __NR32AT1_fchdirat                     (char const *, char const *)
#define __NR32AT2_fchdirat                     (atflag_t, __atflag_t)
#define __NR32AT0_openpty                      (fd_t *, __fd_t *)
#define __NR32AT1_openpty                      (fd_t *, __fd_t *)
#define __NR32AT2_openpty                      (char *, char *)
#define __NR32AT3_openpty                      (struct termios const *, struct termios const *)
#define __NR32AT4_openpty                      (struct winsize const *, struct winsize const *)
#define __NR32AT0_rpc_schedule                 (pid_t, __pid_t)
#define __NR32AT1_rpc_schedule                 (syscall_ulong_t, __syscall_ulong_t)
#define __NR32AT2_rpc_schedule                 (void const *, void const *)
#define __NR32AT3_rpc_schedule                 (__HYBRID_PTR32(void const) const *, __HYBRID_PTR32(void const) const *)
#define __NR32AT4_rpc_schedule                 (size_t, __size_t)
#define __NR32AT0_frealpathat                  (fd_t, __fd_t)
#define __NR32AT1_frealpathat                  (char const *, char const *)
#define __NR32AT2_frealpathat                  (char *, char *)
#define __NR32AT3_frealpathat                  (size_t, __size_t)
#define __NR32AT4_frealpathat                  (atflag_t, __atflag_t)
#define __NR32AT0_frealpath4                   (fd_t, __fd_t)
#define __NR32AT1_frealpath4                   (char *, char *)
#define __NR32AT2_frealpath4                   (size_t, __size_t)
#define __NR32AT3_frealpath4                   (atflag_t, __atflag_t)
#define __NR32AT0_detach                       (pid_t, __pid_t)
#define __NR32AT0_writef                       (fd_t, __fd_t)
#define __NR32AT1_writef                       (void const *, void const *)
#define __NR32AT2_writef                       (size_t, __size_t)
#define __NR32AT3_writef                       (iomode_t, __iomode_t)
#define __NR32AT0_readf                        (fd_t, __fd_t)
#define __NR32AT1_readf                        (void *, void *)
#define __NR32AT2_readf                        (size_t, __size_t)
#define __NR32AT3_readf                        (iomode_t, __iomode_t)
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_TYPES */
#endif /* __WANT_SYSCALL_ARGUMENT_TYPES */


/************************************************************************/
/* SYSCALL ARGUMENT LIST MAKING                                         */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_LIST_MAKER
#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER
#define __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER
#define __NR32AM_restart_syscall(a, b, c, d, e, f)              /* nothing */
#define __NR32AM_exit(a, b, c, d, e, f)                         (__syscall_ulong_t)a
#define __NR32AM_fork(a, b, c, d, e, f)                         /* nothing */
#define __NR32AM_read(a, b, c, d, e, f)                         (__fd_t)a, (void *)b, (__size_t)c
#define __NR32AM_write(a, b, c, d, e, f)                        (__fd_t)a, (void const *)b, (__size_t)c
#define __NR32AM_open(a, b, c, d, e, f)                         (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NR32AM_close(a, b, c, d, e, f)                        (__fd_t)a
#define __NR32AM_waitpid(a, b, c, d, e, f)                      (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c
#define __NR32AM_creat(a, b, c, d, e, f)                        (char const *)a, (__mode_t)b
#define __NR32AM_link(a, b, c, d, e, f)                         (char const *)a, (char const *)b
#define __NR32AM_unlink(a, b, c, d, e, f)                       (char const *)a
#define __NR32AM_execve(a, b, c, d, e, f)                       (char const *)a, (__HYBRID_PTR32(char const) const *)b, (__HYBRID_PTR32(char const) const *)c
#define __NR32AM_chdir(a, b, c, d, e, f)                        (char const *)a
#define __NR32AM_time(a, b, c, d, e, f)                         (__int32_t *)a
#define __NR32AM_mknod(a, b, c, d, e, f)                        (char const *)a, (__mode_t)b, (__dev_t)c
#define __NR32AM_chmod(a, b, c, d, e, f)                        (char const *)a, (__mode_t)b
#define __NR32AM_lchown(a, b, c, d, e, f)                       (char const *)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_break(a, b, c, d, e, f)                        /* nothing */
#define __NR32AM_oldstat(a, b, c, d, e, f)                      (char const *)a, (struct linux_oldstat *)b
#define __NR32AM_lseek(a, b, c, d, e, f)                        (__fd_t)a, (__syscall_slong_t)b, (__syscall_ulong_t)c
#define __NR32AM_getpid(a, b, c, d, e, f)                       /* nothing */
#define __NR32AM_mount(a, b, c, d, e, f)                        (char const *)a, (char const *)b, (char const *)c, (__syscall_ulong_t)d, (void const *)e
#define __NR32AM_umount(a, b, c, d, e, f)                       (char const *)a
#define __NR32AM_setuid(a, b, c, d, e, f)                       (__uint16_t)a
#define __NR32AM_getuid(a, b, c, d, e, f)                       /* nothing */
#define __NR32AM_stime(a, b, c, d, e, f)                        (__time32_t const *)a
#define __NR32AM_ptrace(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__pid_t)b, (void *)c, (void *)d
#define __NR32AM_alarm(a, b, c, d, e, f)                        (__syscall_ulong_t)a
#define __NR32AM_oldfstat(a, b, c, d, e, f)                     (__fd_t)a, (struct linux_oldstat *)b
#define __NR32AM_pause(a, b, c, d, e, f)                        /* nothing */
#define __NR32AM_utime(a, b, c, d, e, f)                        (char const *)a, (struct __utimbufx32 const *)b
#define __NR32AM_stty(a, b, c, d, e, f)                         /* nothing */
#define __NR32AM_gtty(a, b, c, d, e, f)                         /* nothing */
#define __NR32AM_access(a, b, c, d, e, f)                       (char const *)a, (__syscall_ulong_t)b
#define __NR32AM_nice(a, b, c, d, e, f)                         (__syscall_slong_t)a
#define __NR32AM_ftime(a, b, c, d, e, f)                        (struct __timebx32 *)a
#define __NR32AM_sync(a, b, c, d, e, f)                         /* nothing */
#define __NR32AM_kill(a, b, c, d, e, f)                         (__pid_t)a, (__signo_t)b
#define __NR32AM_rename(a, b, c, d, e, f)                       (char const *)a, (char const *)b
#define __NR32AM_mkdir(a, b, c, d, e, f)                        (char const *)a, (__mode_t)b
#define __NR32AM_rmdir(a, b, c, d, e, f)                        (char const *)a
#define __NR32AM_dup(a, b, c, d, e, f)                          (__fd_t)a
#define __NR32AM_pipe(a, b, c, d, e, f)                         (__fd_t *)a
#define __NR32AM_times(a, b, c, d, e, f)                        (struct __tmsx32 *)a
#define __NR32AM_prof(a, b, c, d, e, f)                         /* nothing */
#define __NR32AM_brk(a, b, c, d, e, f)                          (void *)a
#define __NR32AM_setgid(a, b, c, d, e, f)                       (__uint16_t)a
#define __NR32AM_getgid(a, b, c, d, e, f)                       /* nothing */
#define __NR32AM_signal(a, b, c, d, e, f)                       (__signo_t)a, (__sigactionx32_sa_handler_t)b
#define __NR32AM_geteuid(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_getegid(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_acct(a, b, c, d, e, f)                         (char const *)a
#define __NR32AM_umount2(a, b, c, d, e, f)                      (char const *)a, (__syscall_ulong_t)b
#define __NR32AM_lock(a, b, c, d, e, f)                         /* nothing */
#define __NR32AM_ioctl(a, b, c, d, e, f)                        (__fd_t)a, (__ioctl_t)b, (void *)c
#define __NR32AM_fcntl(a, b, c, d, e, f)                        (__fd_t)a, (__fcntl_t)b, (void *)c
#define __NR32AM_mpx(a, b, c, d, e, f)                          /* nothing */
#define __NR32AM_setpgid(a, b, c, d, e, f)                      (__pid_t)a, (__pid_t)b
#define __NR32AM_ulimit(a, b, c, d, e, f)                       /* nothing */
#define __NR32AM_oldolduname(a, b, c, d, e, f)                  (struct linux_oldolduname *)a
#define __NR32AM_umask(a, b, c, d, e, f)                        (__mode_t)a
#define __NR32AM_chroot(a, b, c, d, e, f)                       (char const *)a
#define __NR32AM_ustat(a, b, c, d, e, f)                        (__dev_t)a, (struct ustat *)b
#define __NR32AM_dup2(a, b, c, d, e, f)                         (__fd_t)a, (__fd_t)b
#define __NR32AM_getppid(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_getpgrp(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_setsid(a, b, c, d, e, f)                       /* nothing */
#define __NR32AM_sigaction(a, b, c, d, e, f)                    (__signo_t)a, (struct __old_kernel_sigactionx32 const *)b, (struct __old_kernel_sigactionx32 *)c
#define __NR32AM_sgetmask(a, b, c, d, e, f)                     /* nothing */
#define __NR32AM_ssetmask(a, b, c, d, e, f)                     (__syscall_ulong_t)a
#define __NR32AM_setreuid(a, b, c, d, e, f)                     (__uint16_t)a, (__uint16_t)b
#define __NR32AM_setregid(a, b, c, d, e, f)                     (__uint16_t)a, (__uint16_t)b
#define __NR32AM_sigsuspend(a, b, c, d, e, f)                   (struct __old_sigset_struct const *)a
#define __NR32AM_sigpending(a, b, c, d, e, f)                   (struct __old_sigset_struct *)a
#define __NR32AM_sethostname(a, b, c, d, e, f)                  (char const *)a, (__size_t)b
#define __NR32AM_setrlimit(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (struct __rlimitx32 const *)b
#define __NR32AM_getrlimit(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (struct __rlimitx32 *)b
#define __NR32AM_getrusage(a, b, c, d, e, f)                    (__syscall_slong_t)a, (struct __rusagex32 *)b
#define __NR32AM_gettimeofday(a, b, c, d, e, f)                 (struct __timevalx32 *)a, (struct timezone *)b
#define __NR32AM_settimeofday(a, b, c, d, e, f)                 (struct __timevalx32 const *)a, (struct timezone const *)b
#define __NR32AM_getgroups(a, b, c, d, e, f)                    (__size_t)a, (__uint16_t *)b
#define __NR32AM_setgroups(a, b, c, d, e, f)                    (__size_t)a, (__uint16_t const *)b
#define __NR32AM_select(a, b, c, d, e, f)                       (struct sel_arg_structx32 const *)a
#define __NR32AM_symlink(a, b, c, d, e, f)                      (char const *)a, (char const *)b
#define __NR32AM_oldlstat(a, b, c, d, e, f)                     (char const *)a, (struct linux_oldstat *)b
#define __NR32AM_readlink(a, b, c, d, e, f)                     (char const *)a, (char *)b, (__size_t)c
#define __NR32AM_uselib(a, b, c, d, e, f)                       (char const *)a
#define __NR32AM_swapon(a, b, c, d, e, f)                       (char const *)a, (__syscall_ulong_t)b
#define __NR32AM_reboot(a, b, c, d, e, f)                       (__syscall_ulong_t)a
#define __NR32AM_readdir(a, b, c, d, e, f)                      (__fd_t)a, (struct old_linux_direntx32 *)b
#define __NR32AM_mmap(a, b, c, d, e, f)                         (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NR32AM_munmap(a, b, c, d, e, f)                       (void *)a, (__size_t)b
#define __NR32AM_truncate(a, b, c, d, e, f)                     (char const *)a, (__syscall_ulong_t)b
#define __NR32AM_ftruncate(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_fchmod(a, b, c, d, e, f)                       (__fd_t)a, (__mode_t)b
#define __NR32AM_fchown(a, b, c, d, e, f)                       (__fd_t)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_getpriority(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (__id_t)b
#define __NR32AM_setpriority(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (__id_t)b, (__syscall_ulong_t)c
#define __NR32AM_profil(a, b, c, d, e, f)                       /* nothing */
#define __NR32AM_statfs(a, b, c, d, e, f)                       (char const *)a, (struct __statfsx32 *)b
#define __NR32AM_fstatfs(a, b, c, d, e, f)                      (__fd_t)a, (struct __statfsx32 *)b
#define __NR32AM_ioperm(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AM_socketcall(a, b, c, d, e, f)                   (__ULONG32_TYPE__)a, (__ULONG32_TYPE__ *)b
#define __NR32AM_syslog(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (char const *)b, (__size_t)c
#define __NR32AM_setitimer(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (struct __itimervalx32 const *)b, (struct __itimervalx32 *)c
#define __NR32AM_getitimer(a, b, c, d, e, f)                    (__syscall_ulong_t)a, (struct __itimervalx32 *)b
#define __NR32AM_stat(a, b, c, d, e, f)                         (char const *)a, (struct linux_statx32 *)b
#define __NR32AM_lstat(a, b, c, d, e, f)                        (char const *)a, (struct linux_statx32 *)b
#define __NR32AM_fstat(a, b, c, d, e, f)                        (__fd_t)a, (struct linux_statx32 *)b
#define __NR32AM_olduname(a, b, c, d, e, f)                     (struct linux_olduname *)a
#define __NR32AM_iopl(a, b, c, d, e, f)                         (__syscall_ulong_t)a
#define __NR32AM_vhangup(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_idle(a, b, c, d, e, f)                         /* nothing */
#define __NR32AM_vm86old(a, b, c, d, e, f)                      (int)a
#define __NR32AM_wait4(a, b, c, d, e, f)                        (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c, (struct __rusagex32 *)d
#define __NR32AM_swapoff(a, b, c, d, e, f)                      (char const *)a
#define __NR32AM_sysinfo(a, b, c, d, e, f)                      (struct __sysinfox32 *)a
#define __NR32AM_ipc(a, b, c, d, e, f)                          (int)a
#define __NR32AM_fsync(a, b, c, d, e, f)                        (__fd_t)a
#define __NR32AM_sigreturn(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_clone(a, b, c, d, e, f)                        (__syscall_ulong_t)a, (void *)b, (__pid_t *)c, (__uintptr_t)d, (__pid_t *)e
#define __NR32AM_setdomainname(a, b, c, d, e, f)                (char const *)a, (__size_t)b
#define __NR32AM_uname(a, b, c, d, e, f)                        (struct utsname *)a
#define __NR32AM_modify_ldt(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (void *)b, (__syscall_ulong_t)c
#define __NR32AM_adjtimex(a, b, c, d, e, f)                     (struct timex *)a
#define __NR32AM_mprotect(a, b, c, d, e, f)                     (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR32AM_sigprocmask(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __old_sigset_struct const *)b, (struct __old_sigset_struct *)c
#define __NR32AM_create_module(a, b, c, d, e, f)                /* nothing */
#define __NR32AM_init_module(a, b, c, d, e, f)                  (void const *)a, (__size_t)b, (char const *)c
#define __NR32AM_delete_module(a, b, c, d, e, f)                (char const *)a, (__oflag_t)b
#define __NR32AM_get_kernel_syms(a, b, c, d, e, f)              /* nothing */
#define __NR32AM_quotactl(a, b, c, d, e, f)                     (int)a
#define __NR32AM_getpgid(a, b, c, d, e, f)                      (__pid_t)a
#define __NR32AM_fchdir(a, b, c, d, e, f)                       (__fd_t)a
#define __NR32AM_bdflush(a, b, c, d, e, f)                      (int)a
#define __NR32AM_sysfs(a, b, c, d, e, f)                        (int)a
#define __NR32AM_personality(a, b, c, d, e, f)                  (int)a
#define __NR32AM_afs_syscall(a, b, c, d, e, f)                  /* nothing */
#define __NR32AM_setfsuid(a, b, c, d, e, f)                     (__uint16_t)a
#define __NR32AM_setfsgid(a, b, c, d, e, f)                     (__uint16_t)a
#define __NR32AM__llseek(a, b, c, d, e, f)                      (__fd_t)a, (__int64_t)((__uint64_t)b | (__uint64_t)c << 32), (__uint64_t *)d, (__syscall_ulong_t)e
#define __NR32AM_getdents(a, b, c, d, e, f)                     (__fd_t)a, (struct linux_direntx32 *)b, (__size_t)c
#define __NR32AM__newselect(a, b, c, d, e, f)                   (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timevalx32 *)e
#define __NR32AM_flock(a, b, c, d, e, f)                        (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_msync(a, b, c, d, e, f)                        (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR32AM_readv(a, b, c, d, e, f)                        (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c
#define __NR32AM_writev(a, b, c, d, e, f)                       (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c
#define __NR32AM_getsid(a, b, c, d, e, f)                       (__pid_t)a
#define __NR32AM_fdatasync(a, b, c, d, e, f)                    (__fd_t)a
#define __NR32AM__sysctl(a, b, c, d, e, f)                      (int)a
#define __NR32AM_mlock(a, b, c, d, e, f)                        (void const *)a, (__size_t)b
#define __NR32AM_munlock(a, b, c, d, e, f)                      (void const *)a, (__size_t)b
#define __NR32AM_mlockall(a, b, c, d, e, f)                     (__syscall_ulong_t)a
#define __NR32AM_munlockall(a, b, c, d, e, f)                   /* nothing */
#define __NR32AM_sched_setparam(a, b, c, d, e, f)               (__pid_t)a, (struct sched_param const *)b
#define __NR32AM_sched_getparam(a, b, c, d, e, f)               (__pid_t)a, (struct sched_param *)b
#define __NR32AM_sched_setscheduler(a, b, c, d, e, f)           (__pid_t)a, (__syscall_ulong_t)b, (struct sched_param const *)c
#define __NR32AM_sched_getscheduler(a, b, c, d, e, f)           (__pid_t)a
#define __NR32AM_sched_yield(a, b, c, d, e, f)                  /* nothing */
#define __NR32AM_sched_get_priority_max(a, b, c, d, e, f)       (__syscall_ulong_t)a
#define __NR32AM_sched_get_priority_min(a, b, c, d, e, f)       (__syscall_ulong_t)a
#define __NR32AM_sched_rr_get_interval(a, b, c, d, e, f)        (__pid_t)a, (struct __timespecx32 *)b
#define __NR32AM_nanosleep(a, b, c, d, e, f)                    (struct __timespecx32 const *)a, (struct __timespecx32 *)b
#define __NR32AM_mremap(a, b, c, d, e, f)                       (void *)a, (__size_t)b, (__size_t)c, (__syscall_ulong_t)d, (void *)e
#define __NR32AM_setresuid(a, b, c, d, e, f)                    (__uint16_t)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_getresuid(a, b, c, d, e, f)                    (__uint16_t *)a, (__uint16_t *)b, (__uint16_t *)c
#define __NR32AM_vm86(a, b, c, d, e, f)                         (int)a
#define __NR32AM_query_module(a, b, c, d, e, f)                 /* nothing */
#define __NR32AM_poll(a, b, c, d, e, f)                         (struct pollfd *)a, (__size_t)b, (__syscall_slong_t)c
#define __NR32AM_nfsservctl(a, b, c, d, e, f)                   (int)a
#define __NR32AM_setresgid(a, b, c, d, e, f)                    (__uint16_t)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_getresgid(a, b, c, d, e, f)                    (__uint16_t *)a, (__uint16_t *)b, (__uint16_t *)c
#define __NR32AM_prctl(a, b, c, d, e, f)                        (unsigned int)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AM_rt_sigreturn(a, b, c, d, e, f)                 /* nothing */
#define __NR32AM_rt_sigaction(a, b, c, d, e, f)                 (__signo_t)a, (struct __kernel_sigactionx32 const *)b, (struct __kernel_sigactionx32 *)c, (__size_t)d
#define __NR32AM_rt_sigprocmask(a, b, c, d, e, f)               (__syscall_ulong_t)a, (struct __sigset_struct const *)b, (struct __sigset_struct *)c, (__size_t)d
#define __NR32AM_rt_sigpending(a, b, c, d, e, f)                (struct __sigset_struct *)a, (__size_t)b
#define __NR32AM_rt_sigtimedwait(a, b, c, d, e, f)              (struct __sigset_struct const *)a, (struct __siginfox32_struct *)b, (struct __timespecx32 const *)c, (__size_t)d
#define __NR32AM_rt_sigqueueinfo(a, b, c, d, e, f)              (__pid_t)a, (__signo_t)b, (struct __siginfox32_struct const *)c
#define __NR32AM_rt_sigsuspend(a, b, c, d, e, f)                (struct __sigset_struct const *)a, (__size_t)b
#define __NR32AM_pread64(a, b, c, d, e, f)                      (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NR32AM_pwrite64(a, b, c, d, e, f)                     (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NR32AM_chown(a, b, c, d, e, f)                        (char const *)a, (__uint16_t)b, (__uint16_t)c
#define __NR32AM_getcwd(a, b, c, d, e, f)                       (char *)a, (__size_t)b
#define __NR32AM_capget(a, b, c, d, e, f)                       (int)a
#define __NR32AM_capset(a, b, c, d, e, f)                       (int)a
#define __NR32AM_sigaltstack(a, b, c, d, e, f)                  (struct __sigaltstackx32 const *)a, (struct __sigaltstackx32 *)b
#define __NR32AM_sendfile(a, b, c, d, e, f)                     (__fd_t)a, (__fd_t)b, (__ULONG32_TYPE__ *)c, (__size_t)d
#define __NR32AM_getpmsg(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_putpmsg(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_vfork(a, b, c, d, e, f)                        /* nothing */
#define __NR32AM_ugetrlimit(a, b, c, d, e, f)                   (int)a
#define __NR32AM_mmap2(a, b, c, d, e, f)                        (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__fd_t)e, (__syscall_ulong_t)f
#define __NR32AM_truncate64(a, b, c, d, e, f)                   (char const *)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32)
#define __NR32AM_ftruncate64(a, b, c, d, e, f)                  (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32)
#define __NR32AM_stat64(a, b, c, d, e, f)                       (char const *)a, (struct linux_statx32_64 *)b
#define __NR32AM_lstat64(a, b, c, d, e, f)                      (char const *)a, (struct linux_statx32_64 *)b
#define __NR32AM_fstat64(a, b, c, d, e, f)                      (__fd_t)a, (struct linux_statx32_64 *)b
#define __NR32AM_lchown32(a, b, c, d, e, f)                     (char const *)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_getuid32(a, b, c, d, e, f)                     /* nothing */
#define __NR32AM_getgid32(a, b, c, d, e, f)                     /* nothing */
#define __NR32AM_geteuid32(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_getegid32(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_setreuid32(a, b, c, d, e, f)                   (__uint32_t)a, (__uint32_t)b
#define __NR32AM_setregid32(a, b, c, d, e, f)                   (__uint32_t)a, (__uint32_t)b
#define __NR32AM_getgroups32(a, b, c, d, e, f)                  (__size_t)a, (__uint32_t *)b
#define __NR32AM_setgroups32(a, b, c, d, e, f)                  (__size_t)a, (__uint32_t const *)b
#define __NR32AM_fchown32(a, b, c, d, e, f)                     (__fd_t)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_setresuid32(a, b, c, d, e, f)                  (__uint32_t)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_getresuid32(a, b, c, d, e, f)                  (__uint32_t *)a, (__uint32_t *)b, (__uint32_t *)c
#define __NR32AM_setresgid32(a, b, c, d, e, f)                  (__uint32_t)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_getresgid32(a, b, c, d, e, f)                  (__uint32_t *)a, (__uint32_t *)b, (__uint32_t *)c
#define __NR32AM_chown32(a, b, c, d, e, f)                      (char const *)a, (__uint32_t)b, (__uint32_t)c
#define __NR32AM_setuid32(a, b, c, d, e, f)                     (__uint32_t)a
#define __NR32AM_setgid32(a, b, c, d, e, f)                     (__uint32_t)a
#define __NR32AM_setfsuid32(a, b, c, d, e, f)                   (__uint32_t)a
#define __NR32AM_setfsgid32(a, b, c, d, e, f)                   (__uint32_t)a
#define __NR32AM_pivot_root(a, b, c, d, e, f)                   (int)a
#define __NR32AM_mincore(a, b, c, d, e, f)                      (void *)a, (__size_t)b, (__uint8_t *)c
#define __NR32AM_madvise(a, b, c, d, e, f)                      (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR32AM_getdents64(a, b, c, d, e, f)                   (__fd_t)a, (struct linux_dirent64 *)b, (__size_t)c
#define __NR32AM_fcntl64(a, b, c, d, e, f)                      (__fd_t)a, (__fcntl_t)b, (void *)c
#define __NR32AM_gettid(a, b, c, d, e, f)                       /* nothing */
#define __NR32AM_readahead(a, b, c, d, e, f)                    (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32), (__size_t)d
#define __NR32AM_setxattr(a, b, c, d, e, f)                     (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR32AM_lsetxattr(a, b, c, d, e, f)                    (char const *)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR32AM_fsetxattr(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (void const *)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR32AM_getxattr(a, b, c, d, e, f)                     (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NR32AM_lgetxattr(a, b, c, d, e, f)                    (char const *)a, (char const *)b, (void *)c, (__size_t)d
#define __NR32AM_fgetxattr(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (void *)c, (__size_t)d
#define __NR32AM_listxattr(a, b, c, d, e, f)                    (char const *)a, (char *)b, (__size_t)c
#define __NR32AM_llistxattr(a, b, c, d, e, f)                   (char const *)a, (char *)b, (__size_t)c
#define __NR32AM_flistxattr(a, b, c, d, e, f)                   (__fd_t)a, (char *)b, (__size_t)c
#define __NR32AM_removexattr(a, b, c, d, e, f)                  (char const *)a, (char const *)b
#define __NR32AM_lremovexattr(a, b, c, d, e, f)                 (char const *)a, (char const *)b
#define __NR32AM_fremovexattr(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b
#define __NR32AM_tkill(a, b, c, d, e, f)                        (__pid_t)a, (__signo_t)b
#define __NR32AM_sendfile64(a, b, c, d, e, f)                   (__fd_t)a, (__fd_t)b, (__ULONG64_TYPE__ *)c, (__size_t)d
#define __NR32AM_futex(a, b, c, d, e, f)                        (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct __timespecx32 const *)d, (__uint32_t *)e, (__uint32_t)f
#define __NR32AM_sched_setaffinity(a, b, c, d, e, f)            (__pid_t)a, (__size_t)b, (struct __cpu_set_struct const *)c
#define __NR32AM_sched_getaffinity(a, b, c, d, e, f)            (__pid_t)a, (__size_t)b, (struct __cpu_set_struct *)c
#define __NR32AM_set_thread_area(a, b, c, d, e, f)              (int)a
#define __NR32AM_get_thread_area(a, b, c, d, e, f)              (int)a
#define __NR32AM_io_setup(a, b, c, d, e, f)                     (int)a
#define __NR32AM_io_destroy(a, b, c, d, e, f)                   (int)a
#define __NR32AM_io_getevents(a, b, c, d, e, f)                 (int)a
#define __NR32AM_io_submit(a, b, c, d, e, f)                    (int)a
#define __NR32AM_io_cancel(a, b, c, d, e, f)                    (int)a
#define __NR32AM_fadvise64(a, b, c, d, e, f)                    (int)a
#define __NR32AM_exit_group(a, b, c, d, e, f)                   (__syscall_ulong_t)a
#define __NR32AM_lookup_dcookie(a, b, c, d, e, f)               (int)a
#define __NR32AM_epoll_create(a, b, c, d, e, f)                 (__syscall_ulong_t)a
#define __NR32AM_epoll_ctl(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b, (__fd_t)c, (struct epoll_event *)d
#define __NR32AM_epoll_wait(a, b, c, d, e, f)                   (__fd_t)a, (struct epoll_event *)b, (__size_t)c, (__syscall_slong_t)d
#define __NR32AM_remap_file_pages(a, b, c, d, e, f)             (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__size_t)d, (__syscall_ulong_t)e
#define __NR32AM_set_tid_address(a, b, c, d, e, f)              (__pid_t *)a
#define __NR32AM_timer_create(a, b, c, d, e, f)                 (__clockid_t)a, (struct sigevent *)b, (__timer_t *)c
#define __NR32AM_timer_settime(a, b, c, d, e, f)                (__timer_t)a, (__syscall_ulong_t)b, (struct __itimerspecx32 const *)c, (struct __itimerspecx32 *)d
#define __NR32AM_timer_gettime(a, b, c, d, e, f)                (__timer_t)a, (struct __itimerspecx32 *)b
#define __NR32AM_timer_getoverrun(a, b, c, d, e, f)             (__timer_t)a
#define __NR32AM_timer_delete(a, b, c, d, e, f)                 (__timer_t)a
#define __NR32AM_clock_settime(a, b, c, d, e, f)                (__clockid_t)a, (struct __timespecx32 const *)b
#define __NR32AM_clock_gettime(a, b, c, d, e, f)                (__clockid_t)a, (struct __timespecx32 *)b
#define __NR32AM_clock_getres(a, b, c, d, e, f)                 (__clockid_t)a, (struct __timespecx32 *)b
#define __NR32AM_clock_nanosleep(a, b, c, d, e, f)              (__clockid_t)a, (__syscall_ulong_t)b, (struct __timespecx32 const *)c, (struct __timespecx32 *)d
#define __NR32AM_statfs64(a, b, c, d, e, f)                     (char const *)a, (struct __statfsx32_64 *)b
#define __NR32AM_fstatfs64(a, b, c, d, e, f)                    (__fd_t)a, (struct __statfsx32_64 *)b
#define __NR32AM_tgkill(a, b, c, d, e, f)                       (__pid_t)a, (__pid_t)b, (__signo_t)c
#define __NR32AM_utimes(a, b, c, d, e, f)                       (char const *)a, (struct __timevalx32 const *)b
#define __NR32AM_fadvise64_64(a, b, c, d, e, f)                 (int)a
#define __NR32AM_vserver(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_mbind(a, b, c, d, e, f)                        (int)a
#define __NR32AM_get_mempolicy(a, b, c, d, e, f)                (int)a
#define __NR32AM_set_mempolicy(a, b, c, d, e, f)                (int)a
#define __NR32AM_mq_open(a, b, c, d, e, f)                      (char const *)a, (__oflag_t)b, (__mode_t)c
#define __NR32AM_mq_unlink(a, b, c, d, e, f)                    (char const *)a
#define __NR32AM_mq_timedsend(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__size_t)c, (__uint32_t)d, (struct __timespecx32 const *)e
#define __NR32AM_mq_timedreceive(a, b, c, d, e, f)              (__fd_t)a, (char *)b, (__size_t)c, (__uint32_t *)d, (struct __timespecx32 const *)e
#define __NR32AM_mq_notify(a, b, c, d, e, f)                    (__fd_t)a, (struct sigevent const *)b
#define __NR32AM_mq_getsetattr(a, b, c, d, e, f)                (__fd_t)a, (struct mq_attr const *)b, (struct mq_attr *)c
#define __NR32AM_kexec_load(a, b, c, d, e, f)                   (int)a
#define __NR32AM_waitid(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__id_t)b, (struct __siginfox32_struct *)c, (__syscall_ulong_t)d, (struct __rusagex32 *)e
#define __NR32AM_add_key(a, b, c, d, e, f)                      (int)a
#define __NR32AM_request_key(a, b, c, d, e, f)                  (int)a
#define __NR32AM_keyctl(a, b, c, d, e, f)                       (int)a
#define __NR32AM_ioprio_set(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AM_ioprio_get(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AM_inotify_init(a, b, c, d, e, f)                 /* nothing */
#define __NR32AM_inotify_add_watch(a, b, c, d, e, f)            (__fd_t)a, (char const *)b, (__uint32_t)c
#define __NR32AM_inotify_rm_watch(a, b, c, d, e, f)             (__fd_t)a, (int)b
#define __NR32AM_migrate_pages(a, b, c, d, e, f)                (int)a
#define __NR32AM_openat(a, b, c, d, e, f)                       (__fd_t)a, (char const *)b, (__oflag_t)c, (__mode_t)d
#define __NR32AM_mkdirat(a, b, c, d, e, f)                      (__fd_t)a, (char const *)b, (__mode_t)c
#define __NR32AM_mknodat(a, b, c, d, e, f)                      (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d
#define __NR32AM_fchownat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__uid_t)c, (__gid_t)d, (__atflag_t)e
#define __NR32AM_futimesat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (struct __timevalx32 const *)c
#define __NR32AM_fstatat64(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (struct linux_statx32_64 *)c, (__atflag_t)d
#define __NR32AM_unlinkat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NR32AM_renameat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d
#define __NR32AM_linkat(a, b, c, d, e, f)                       (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NR32AM_symlinkat(a, b, c, d, e, f)                    (char const *)a, (__fd_t)b, (char const *)c
#define __NR32AM_readlinkat(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (char *)c, (__size_t)d
#define __NR32AM_fchmodat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NR32AM_faccessat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (__syscall_ulong_t)c
#define __NR32AM_pselect6(a, b, c, d, e, f)                     (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timespecx32 const *)e, (struct __sigset_with_sizex32 const *)f
#define __NR32AM_ppoll(a, b, c, d, e, f)                        (struct pollfd *)a, (__size_t)b, (struct __timespecx32 const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NR32AM_unshare(a, b, c, d, e, f)                      (__syscall_ulong_t)a
#define __NR32AM_set_robust_list(a, b, c, d, e, f)              (int)a
#define __NR32AM_get_robust_list(a, b, c, d, e, f)              (int)a
#define __NR32AM_splice(a, b, c, d, e, f)                       (__fd_t)a, (__uint64_t *)b, (__fd_t)c, (__uint64_t *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NR32AM_sync_file_range(a, b, c, d, e, f)              (__fd_t)a, (__uint64_t)((__uint64_t)b | (__uint64_t)c << 32), (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__syscall_ulong_t)f
#define __NR32AM_tee(a, b, c, d, e, f)                          (__fd_t)a, (__fd_t)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_vmsplice(a, b, c, d, e, f)                     (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_move_pages(a, b, c, d, e, f)                   (int)a
#define __NR32AM_getcpu(a, b, c, d, e, f)                       (__uint32_t *)a, (__uint32_t *)b, (struct getcpu_cache *)c
#define __NR32AM_epoll_pwait(a, b, c, d, e, f)                  (__fd_t)a, (struct epoll_event *)b, (__size_t)c, (__syscall_slong_t)d, (struct __sigset_struct const *)e, (__size_t)f
#define __NR32AM_utimensat(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (struct __timespecx32 const *)c, (__atflag_t)d
#define __NR32AM_signalfd(a, b, c, d, e, f)                     (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c
#define __NR32AM_timerfd_create(a, b, c, d, e, f)               (__clockid_t)a, (__syscall_ulong_t)b
#define __NR32AM_eventfd(a, b, c, d, e, f)                      (__syscall_ulong_t)a
#define __NR32AM_fallocate(a, b, c, d, e, f)                    (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AM_timerfd_settime(a, b, c, d, e, f)              (__fd_t)a, (__syscall_ulong_t)b, (struct __itimerspecx32 const *)c, (struct __itimerspecx32 *)d
#define __NR32AM_timerfd_gettime(a, b, c, d, e, f)              (__fd_t)a, (struct __itimerspecx32 *)b
#define __NR32AM_signalfd4(a, b, c, d, e, f)                    (__fd_t)a, (struct __sigset_struct const *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_eventfd2(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AM_epoll_create1(a, b, c, d, e, f)                (__syscall_ulong_t)a
#define __NR32AM_dup3(a, b, c, d, e, f)                         (__fd_t)a, (__fd_t)b, (__oflag_t)c
#define __NR32AM_pipe2(a, b, c, d, e, f)                        (__fd_t *)a, (__oflag_t)b
#define __NR32AM_inotify_init1(a, b, c, d, e, f)                (__syscall_ulong_t)a
#define __NR32AM_preadv(a, b, c, d, e, f)                       (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NR32AM_pwritev(a, b, c, d, e, f)                      (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32)
#define __NR32AM_rt_tgsigqueueinfo(a, b, c, d, e, f)            (__pid_t)a, (__pid_t)b, (__signo_t)c, (struct __siginfox32_struct const *)d
#define __NR32AM_perf_event_open(a, b, c, d, e, f)              (int)a
#define __NR32AM_recvmmsg(a, b, c, d, e, f)                     (__fd_t)a, (struct __mmsghdrx32 *)b, (__size_t)c, (__syscall_ulong_t)d, (struct __timespecx32 const *)e
#define __NR32AM_fanotify_init(a, b, c, d, e, f)                (int)a
#define __NR32AM_fanotify_mark(a, b, c, d, e, f)                (int)a
#define __NR32AM_prlimit64(a, b, c, d, e, f)                    (__pid_t)a, (__syscall_ulong_t)b, (struct __rlimitx32_64 const *)c, (struct __rlimitx32_64 *)d
#define __NR32AM_name_to_handle_at(a, b, c, d, e, f)            (__fd_t)a, (char const *)b, (struct file_handle *)c, (__int32_t *)d, (__atflag_t)e
#define __NR32AM_open_by_handle_at(a, b, c, d, e, f)            (__fd_t)a, (struct file_handle const *)b, (__oflag_t)c
#define __NR32AM_clock_adjtime(a, b, c, d, e, f)                (int)a
#define __NR32AM_syncfs(a, b, c, d, e, f)                       (__fd_t)a
#define __NR32AM_sendmmsg(a, b, c, d, e, f)                     (__fd_t)a, (struct __mmsghdrx32 *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_setns(a, b, c, d, e, f)                        (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_process_vm_readv(a, b, c, d, e, f)             (__pid_t)a, (struct __iovecx32 const *)b, (__size_t)c, (struct __iovecx32 const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NR32AM_process_vm_writev(a, b, c, d, e, f)            (__pid_t)a, (struct __iovecx32 const *)b, (__size_t)c, (struct __iovecx32 const *)d, (__size_t)e, (__syscall_ulong_t)f
#define __NR32AM_kcmp(a, b, c, d, e, f)                         (__pid_t)a, (__pid_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AM_finit_module(a, b, c, d, e, f)                 (__fd_t)a, (char const *)b, (__syscall_ulong_t)c
#define __NR32AM_sched_setattr(a, b, c, d, e, f)                (int)a
#define __NR32AM_sched_getattr(a, b, c, d, e, f)                (int)a
#define __NR32AM_renameat2(a, b, c, d, e, f)                    (__fd_t)a, (char const *)b, (__fd_t)c, (char const *)d, (__atflag_t)e
#define __NR32AM_seccomp(a, b, c, d, e, f)                      (int)a
#define __NR32AM_getrandom(a, b, c, d, e, f)                    (void *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR32AM_memfd_create(a, b, c, d, e, f)                 (char const *)a, (__syscall_ulong_t)b
#define __NR32AM_bpf(a, b, c, d, e, f)                          (int)a
#define __NR32AM_execveat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__HYBRID_PTR32(char const) const *)c, (__HYBRID_PTR32(char const) const *)d, (__atflag_t)e
#define __NR32AM_socket(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AM_socketpair(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__fd_t *)d
#define __NR32AM_bind(a, b, c, d, e, f)                         (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NR32AM_connect(a, b, c, d, e, f)                      (__fd_t)a, (struct sockaddr const *)b, (__socklen_t)c
#define __NR32AM_listen(a, b, c, d, e, f)                       (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_accept4(a, b, c, d, e, f)                      (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c, (__syscall_ulong_t)d
#define __NR32AM_getsockopt(a, b, c, d, e, f)                   (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void *)d, (__socklen_t *)e
#define __NR32AM_setsockopt(a, b, c, d, e, f)                   (__fd_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (void const *)d, (__socklen_t)e
#define __NR32AM_getsockname(a, b, c, d, e, f)                  (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NR32AM_getpeername(a, b, c, d, e, f)                  (__fd_t)a, (struct sockaddr *)b, (__socklen_t *)c
#define __NR32AM_sendto(a, b, c, d, e, f)                       (__fd_t)a, (void const *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr const *)e, (__socklen_t)f
#define __NR32AM_sendmsg(a, b, c, d, e, f)                      (__fd_t)a, (struct __msghdrx32 const *)b, (__syscall_ulong_t)c
#define __NR32AM_recvfrom(a, b, c, d, e, f)                     (__fd_t)a, (void *)b, (__size_t)c, (__syscall_ulong_t)d, (struct sockaddr *)e, (__socklen_t *)f
#define __NR32AM_recvmsg(a, b, c, d, e, f)                      (__fd_t)a, (struct __msghdrx32 *)b, (__syscall_ulong_t)c
#define __NR32AM_shutdown(a, b, c, d, e, f)                     (__fd_t)a, (__syscall_ulong_t)b
#define __NR32AM_userfaultfd(a, b, c, d, e, f)                  (__syscall_ulong_t)a
#define __NR32AM_membarrier(a, b, c, d, e, f)                   (int)a
#define __NR32AM_mlock2(a, b, c, d, e, f)                       (void const *)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR32AM_copy_file_range(a, b, c, d, e, f)              (int)a
#define __NR32AM_preadv2(a, b, c, d, e, f)                      (int)a
#define __NR32AM_pwritev2(a, b, c, d, e, f)                     (int)a
#define __NR32AM_pkey_mprotect(a, b, c, d, e, f)                (void *)a, (__size_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AM_pkey_alloc(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AM_pkey_free(a, b, c, d, e, f)                    (__syscall_ulong_t)a
#define __NR32AM_statx(a, b, c, d, e, f)                        (int)a
#define __NR32AM_arch_prctl(a, b, c, d, e, f)                   (unsigned int)a, (__uint32_t *)b
#define __NR32AM_io_pgetevents(a, b, c, d, e, f)                (int)a
#define __NR32AM_rseq(a, b, c, d, e, f)                         (int)a
#define __NR32AM_semget(a, b, c, d, e, f)                       (int)a
#define __NR32AM_semctl(a, b, c, d, e, f)                       (int)a
#define __NR32AM_shmget(a, b, c, d, e, f)                       (__key_t)a, (__size_t)b, (__syscall_ulong_t)c
#define __NR32AM_shmctl(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (struct shmid_ds *)c
#define __NR32AM_shmat(a, b, c, d, e, f)                        (__syscall_ulong_t)a, (void const *)b, (__syscall_ulong_t)c
#define __NR32AM_shmdt(a, b, c, d, e, f)                        (void const *)a
#define __NR32AM_msgget(a, b, c, d, e, f)                       (int)a
#define __NR32AM_msgsnd(a, b, c, d, e, f)                       (int)a
#define __NR32AM_msgrcv(a, b, c, d, e, f)                       (int)a
#define __NR32AM_msgctl(a, b, c, d, e, f)                       (int)a
#define __NR32AM_clock_gettime64(a, b, c, d, e, f)              (__clockid_t)a, (struct __timespecx32_64 *)b
#define __NR32AM_clock_settime64(a, b, c, d, e, f)              (__clockid_t)a, (struct __timespecx32_64 const *)b
#define __NR32AM_clock_adjtime64(a, b, c, d, e, f)              (int)a
#define __NR32AM_clock_getres_time64(a, b, c, d, e, f)          (__clockid_t)a, (struct __timespecx32_64 *)b
#define __NR32AM_clock_nanosleep_time64(a, b, c, d, e, f)       (__clockid_t)a, (__syscall_ulong_t)b, (struct __timespecx32_64 const *)c, (struct __timespecx32_64 *)d
#define __NR32AM_timer_gettime64(a, b, c, d, e, f)              (__timer_t)a, (struct __itimerspecx32_64 *)b
#define __NR32AM_timer_settime64(a, b, c, d, e, f)              (__timer_t)a, (__syscall_ulong_t)b, (struct __itimerspecx32_64 const *)c, (struct __itimerspecx32_64 *)d
#define __NR32AM_timerfd_gettime64(a, b, c, d, e, f)            (__fd_t)a, (struct __itimerspecx32_64 *)b
#define __NR32AM_timerfd_settime64(a, b, c, d, e, f)            (__fd_t)a, (__syscall_ulong_t)b, (struct __itimerspecx32_64 const *)c, (struct __itimerspecx32_64 *)d
#define __NR32AM_utimensat_time64(a, b, c, d, e, f)             (__fd_t)a, (char const *)b, (struct __timespecx32_64 const *)c, (__atflag_t)d
#define __NR32AM_pselect6_time64(a, b, c, d, e, f)              (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timespecx32_64 const *)e, (struct __sigset_with_sizex32 const *)f
#define __NR32AM_ppoll_time64(a, b, c, d, e, f)                 (struct pollfd *)a, (__size_t)b, (struct __timespecx32_64 const *)c, (struct __sigset_struct const *)d, (__size_t)e
#define __NR32AM_io_pgetevents_time64(a, b, c, d, e, f)         (int)a
#define __NR32AM_recvmmsg_time64(a, b, c, d, e, f)              (__fd_t)a, (struct __mmsghdrx32 *)b, (__size_t)c, (__syscall_ulong_t)d, (struct __timespecx32_64 const *)e
#define __NR32AM_mq_timedsend_time64(a, b, c, d, e, f)          (__fd_t)a, (char const *)b, (__size_t)c, (__uint32_t)d, (struct __timespecx32_64 const *)e
#define __NR32AM_mq_timedreceive_time64(a, b, c, d, e, f)       (__fd_t)a, (char *)b, (__size_t)c, (__uint32_t *)d, (struct __timespecx32_64 const *)e
#define __NR32AM_semtimedop_time64(a, b, c, d, e, f)            (int)a
#define __NR32AM_rt_sigtimedwait_time64(a, b, c, d, e, f)       (struct __sigset_struct const *)a, (struct __siginfox32_struct *)b, (struct __timespecx32_64 const *)c, (__size_t)d
#define __NR32AM_futex_time64(a, b, c, d, e, f)                 (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct __timespecx32_64 const *)d, (__uint32_t *)e, (__uint32_t)f
#define __NR32AM_sched_rr_get_interval_time64(a, b, c, d, e, f) (__pid_t)a, (struct __timespecx32_64 *)b
#define __NR32AM_pidfd_send_signal(a, b, c, d, e, f)            (__fd_t)a, (__signo_t)b, (struct __siginfox32_struct const *)c, (__syscall_ulong_t)d
#define __NR32AM_io_uring_setup(a, b, c, d, e, f)               (int)a
#define __NR32AM_io_uring_enter(a, b, c, d, e, f)               (int)a
#define __NR32AM_io_uring_register(a, b, c, d, e, f)            (int)a
#define __NR32AM_open_tree(a, b, c, d, e, f)                    (int)a
#define __NR32AM_move_mount(a, b, c, d, e, f)                   (int)a
#define __NR32AM_fsopen(a, b, c, d, e, f)                       (int)a
#define __NR32AM_fsconfig(a, b, c, d, e, f)                     (int)a
#define __NR32AM_fsmount(a, b, c, d, e, f)                      (int)a
#define __NR32AM_fspick(a, b, c, d, e, f)                       (int)a
#define __NR32AM_pidfd_open(a, b, c, d, e, f)                   (__pid_t)a, (__syscall_ulong_t)b
#define __NR32AM_clone3(a, b, c, d, e, f)                       (struct clone_args *)a, (__size_t)b
#define __NR32AM_close_range(a, b, c, d, e, f)                  (unsigned int)a, (unsigned int)b, (unsigned int)c
#define __NR32AM_openat2(a, b, c, d, e, f)                      (int)a
#define __NR32AM_pidfd_getfd(a, b, c, d, e, f)                  (__fd_t)a, (__fd_t)b, (__syscall_ulong_t)c
#define __NR32AM_faccessat2(a, b, c, d, e, f)                   (__fd_t)a, (char const *)b, (__syscall_ulong_t)c, (__atflag_t)d
#define __NR32AM_pwritevf(a, b, c, d, e, f)                     (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NR32AM_preadvf(a, b, c, d, e, f)                      (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NR32AM_fallocate64(a, b, c, d, e, f)                  (__fd_t)a, (__syscall_ulong_t)b, (__uint64_t)((__uint64_t)c | (__uint64_t)d << 32), (__uint64_t)((__uint64_t)e | (__uint64_t)f << 32)
#define __NR32AM_freadlinkat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NR32AM_fsymlinkat(a, b, c, d, e, f)                   (char const *)a, (__fd_t)b, (char const *)c, (__atflag_t)d
#define __NR32AM_kfstatat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (struct __kos_stat *)c, (__atflag_t)d
#define __NR32AM_futimesat64(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (struct __timevalx32_64 const *)c
#define __NR32AM_fmknodat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__mode_t)c, (__dev_t)d, (__atflag_t)e
#define __NR32AM_fmkdirat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__mode_t)c, (__atflag_t)d
#define __NR32AM_inotify_add_watch_at(a, b, c, d, e, f)         (__fd_t)a, (__fd_t)b, (char const *)c, (__atflag_t)d, (__uint32_t)e
#define __NR32AM_waitid64(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__id_t)b, (struct __siginfox32_struct *)c, (__syscall_ulong_t)d, (struct __rusagex32_64 *)e
#define __NR32AM_utimes64(a, b, c, d, e, f)                     (char const *)a, (struct __timevalx32_64 const *)b
#define __NR32AM_kreaddirf(a, b, c, d, e, f)                    (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d, (__iomode_t)e
#define __NR32AM_kfstat(a, b, c, d, e, f)                       (__fd_t)a, (struct __kos_stat *)b
#define __NR32AM_klstat(a, b, c, d, e, f)                       (char const *)a, (struct __kos_stat *)b
#define __NR32AM_kstat(a, b, c, d, e, f)                        (char const *)a, (struct __kos_stat *)b
#define __NR32AM_pwrite64f(a, b, c, d, e, f)                    (__fd_t)a, (void const *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NR32AM_pread64f(a, b, c, d, e, f)                     (__fd_t)a, (void *)b, (__size_t)c, (__uint64_t)((__uint64_t)d | (__uint64_t)e << 32), (__iomode_t)f
#define __NR32AM_ksigreturn(a, b, c, d, e, f)                   (struct fpustate32 const *)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (struct __sigset_with_sizex32 const *)d, (struct rpc_syscall_info32 const *)e, (struct ucpustate32 const *)f
#define __NR32AM_nanosleep64(a, b, c, d, e, f)                  (struct __timespecx32_64 const *)a, (struct __timespecx32_64 *)b
#define __NR32AM_rpc_serve(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_ksysctl(a, b, c, d, e, f)                      (__ioctl_t)a, (void *)b
#define __NR32AM_writevf(a, b, c, d, e, f)                      (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__iomode_t)d
#define __NR32AM_readvf(a, b, c, d, e, f)                       (__fd_t)a, (struct __iovecx32 const *)b, (__size_t)c, (__iomode_t)d
#define __NR32AM_kreaddir(a, b, c, d, e, f)                     (__fd_t)a, (struct dirent *)b, (__size_t)c, (__syscall_ulong_t)d
#define __NR32AM_wait4_64(a, b, c, d, e, f)                     (__pid_t)a, (__int32_t *)b, (__syscall_ulong_t)c, (struct __rusagex32_64 *)d
#define __NR32AM_getitimer64(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __itimervalx32_64 *)b
#define __NR32AM_setitimer64(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (struct __itimervalx32_64 const *)b, (struct __itimervalx32_64 *)c
#define __NR32AM_maplibrary(a, b, c, d, e, f)                   (void *)a, (__syscall_ulong_t)b, (__fd_t)c, (struct elf32_phdr const *)d, (__size_t)e
#define __NR32AM_select64(a, b, c, d, e, f)                     (__size_t)a, (struct __fd_set_struct *)b, (struct __fd_set_struct *)c, (struct __fd_set_struct *)d, (struct __timevalx32_64 *)e
#define __NR32AM_settimeofday64(a, b, c, d, e, f)               (struct __timevalx32_64 const *)a, (struct timezone const *)b
#define __NR32AM_gettimeofday64(a, b, c, d, e, f)               (struct __timevalx32_64 *)a, (struct timezone *)b
#define __NR32AM_getrusage64(a, b, c, d, e, f)                  (__syscall_slong_t)a, (struct __rusagex32_64 *)b
#define __NR32AM_fsmode(a, b, c, d, e, f)                       (__uint64_t)((__uint64_t)a | (__uint64_t)b << 32)
#define __NR32AM_ioctlf(a, b, c, d, e, f)                       (__fd_t)a, (__ioctl_t)b, (__iomode_t)c, (void *)d
#define __NR32AM_rtm_test(a, b, c, d, e, f)                     /* nothing */
#define __NR32AM_rtm_abort(a, b, c, d, e, f)                    (__syscall_ulong_t)a
#define __NR32AM_rtm_end(a, b, c, d, e, f)                      /* nothing */
#define __NR32AM_rtm_begin(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_ftime64(a, b, c, d, e, f)                      (struct __timebx32_64 *)a
#define __NR32AM_rpc_serve_sysret(a, b, c, d, e, f)             /* nothing */
#define __NR32AM_set_userprocmask_address(a, b, c, d, e, f)     (struct userprocmask *)a
#define __NR32AM_utime64(a, b, c, d, e, f)                      (char const *)a, (struct __utimbufx32_64 const *)b
#define __NR32AM_userviofd(a, b, c, d, e, f)                    (__size_t)a, (__syscall_ulong_t)b
#define __NR32AM_stime64(a, b, c, d, e, f)                      (__time64_t const *)a
#define __NR32AM_coredump(a, b, c, d, e, f)                     (struct ucpustate32 const *)a, (struct ucpustate32 const *)b, (__HYBRID_PTR32(void const) const *)c, (__size_t)d, (union coredump_info32 const *)e, (__syscall_ulong_t)f
#define __NR32AM_mktty(a, b, c, d, e, f)                        (char const *)a, (__fd_t)b, (__fd_t)c, (__syscall_ulong_t)d
#define __NR32AM_lfutexexpr(a, b, c, d, e, f)                   (__uint32_t *)a, (void *)b, (struct lfutexexprx32 const *)c, (struct __timespecx32_64 const *)d, (__syscall_ulong_t)e
#define __NR32AM_lseek64(a, b, c, d, e, f)                      (__fd_t)a, (__int64_t)((__uint64_t)b | (__uint64_t)c << 32), (__syscall_ulong_t)d
#define __NR32AM_lfutex(a, b, c, d, e, f)                       (__uint32_t *)a, (__syscall_ulong_t)b, (__uint32_t)c, (struct __timespecx32_64 const *)d, (__uint32_t)e
#define __NR32AM_debugtrap(a, b, c, d, e, f)                    (struct ucpustate32 const *)a, (struct debugtrap_reason32 const *)b
#define __NR32AM_get_exception_handler(a, b, c, d, e, f)        (__ULONG32_TYPE__ *)a, (__except_handler32_t *)b, (__HYBRID_PTR32(void) *)c
#define __NR32AM_set_exception_handler(a, b, c, d, e, f)        (__syscall_ulong_t)a, (__except_handler_t)b, (void *)c
#define __NR32AM_time64(a, b, c, d, e, f)                       (__int64_t *)a
#define __NR32AM_fchdirat(a, b, c, d, e, f)                     (__fd_t)a, (char const *)b, (__atflag_t)c
#define __NR32AM_openpty(a, b, c, d, e, f)                      (__fd_t *)a, (__fd_t *)b, (char *)c, (struct termios const *)d, (struct winsize const *)e
#define __NR32AM_rpc_schedule(a, b, c, d, e, f)                 (__pid_t)a, (__syscall_ulong_t)b, (void const *)c, (__HYBRID_PTR32(void const) const *)d, (__size_t)e
#define __NR32AM_frealpathat(a, b, c, d, e, f)                  (__fd_t)a, (char const *)b, (char *)c, (__size_t)d, (__atflag_t)e
#define __NR32AM_frealpath4(a, b, c, d, e, f)                   (__fd_t)a, (char *)b, (__size_t)c, (__atflag_t)d
#define __NR32AM_getdrives(a, b, c, d, e, f)                    /* nothing */
#define __NR32AM_detach(a, b, c, d, e, f)                       (__pid_t)a
#define __NR32AM_writef(a, b, c, d, e, f)                       (__fd_t)a, (void const *)b, (__size_t)c, (__iomode_t)d
#define __NR32AM_readf(a, b, c, d, e, f)                        (__fd_t)a, (void *)b, (__size_t)c, (__iomode_t)d
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_MAKER */
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_MAKER */


/************************************************************************/
/* SYSCALL ARGUMENT LIST PACKING                                        */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_LIST_PACKER
#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER
#define __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER
#define __NR32AP_restart_syscall()                              /* nothing */
#define __NR32AP_exit(a)                                        (__syscall_ulong_t)a
#define __NR32AP_fork()                                         /* nothing */
#define __NR32AP_read(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_write(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_open(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_close(a)                                       (__syscall_ulong_t)a
#define __NR32AP_waitpid(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_creat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_link(a, b)                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_unlink(a)                                      (__syscall_ulong_t)a
#define __NR32AP_execve(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_chdir(a)                                       (__syscall_ulong_t)a
#define __NR32AP_time(a)                                        (__syscall_ulong_t)a
#define __NR32AP_mknod(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_chmod(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lchown(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_break()                                        /* nothing */
#define __NR32AP_oldstat(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lseek(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getpid()                                       /* nothing */
#define __NR32AP_mount(a, b, c, d, e)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_umount(a)                                      (__syscall_ulong_t)a
#define __NR32AP_setuid(a)                                      (__syscall_ulong_t)a
#define __NR32AP_getuid()                                       /* nothing */
#define __NR32AP_stime(a)                                       (__syscall_ulong_t)a
#define __NR32AP_ptrace(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_alarm(a)                                       (__syscall_ulong_t)a
#define __NR32AP_oldfstat(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_pause()                                        /* nothing */
#define __NR32AP_utime(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_stty()                                         /* nothing */
#define __NR32AP_gtty()                                         /* nothing */
#define __NR32AP_access(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_nice(a)                                        (__syscall_ulong_t)a
#define __NR32AP_ftime(a)                                       (__syscall_ulong_t)a
#define __NR32AP_sync()                                         /* nothing */
#define __NR32AP_kill(a, b)                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_rename(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_mkdir(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_rmdir(a)                                       (__syscall_ulong_t)a
#define __NR32AP_dup(a)                                         (__syscall_ulong_t)a
#define __NR32AP_pipe(a)                                        (__syscall_ulong_t)a
#define __NR32AP_times(a)                                       (__syscall_ulong_t)a
#define __NR32AP_prof()                                         /* nothing */
#define __NR32AP_brk(a)                                         (__syscall_ulong_t)a
#define __NR32AP_setgid(a)                                      (__syscall_ulong_t)a
#define __NR32AP_getgid()                                       /* nothing */
#define __NR32AP_signal(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_geteuid()                                      /* nothing */
#define __NR32AP_getegid()                                      /* nothing */
#define __NR32AP_acct(a)                                        (__syscall_ulong_t)a
#define __NR32AP_umount2(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lock()                                         /* nothing */
#define __NR32AP_ioctl(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_fcntl(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_mpx()                                          /* nothing */
#define __NR32AP_setpgid(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_ulimit()                                       /* nothing */
#define __NR32AP_oldolduname(a)                                 (__syscall_ulong_t)a
#define __NR32AP_umask(a)                                       (__syscall_ulong_t)a
#define __NR32AP_chroot(a)                                      (__syscall_ulong_t)a
#define __NR32AP_ustat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_dup2(a, b)                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getppid()                                      /* nothing */
#define __NR32AP_getpgrp()                                      /* nothing */
#define __NR32AP_setsid()                                       /* nothing */
#define __NR32AP_sigaction(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sgetmask()                                     /* nothing */
#define __NR32AP_ssetmask(a)                                    (__syscall_ulong_t)a
#define __NR32AP_setreuid(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setregid(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sigsuspend(a)                                  (__syscall_ulong_t)a
#define __NR32AP_sigpending(a)                                  (__syscall_ulong_t)a
#define __NR32AP_sethostname(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setrlimit(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getrlimit(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getrusage(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_gettimeofday(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_settimeofday(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getgroups(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setgroups(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_select(a)                                      (__syscall_ulong_t)a
#define __NR32AP_symlink(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_oldlstat(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_readlink(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_uselib(a)                                      (__syscall_ulong_t)a
#define __NR32AP_swapon(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_reboot(a)                                      (__syscall_ulong_t)a
#define __NR32AP_readdir(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_mmap(a, b, c, d, e, f)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_munmap(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_truncate(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_ftruncate(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fchmod(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fchown(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getpriority(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setpriority(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_profil()                                       /* nothing */
#define __NR32AP_statfs(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fstatfs(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_ioperm(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_socketcall(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_syslog(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setitimer(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getitimer(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_stat(a, b)                                     (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lstat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fstat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_olduname(a)                                    (__syscall_ulong_t)a
#define __NR32AP_iopl(a)                                        (__syscall_ulong_t)a
#define __NR32AP_vhangup()                                      /* nothing */
#define __NR32AP_idle()                                         /* nothing */
#define __NR32AP_vm86old(a)                                     (__syscall_ulong_t)a
#define __NR32AP_wait4(a, b, c, d)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_swapoff(a)                                     (__syscall_ulong_t)a
#define __NR32AP_sysinfo(a)                                     (__syscall_ulong_t)a
#define __NR32AP_ipc(a)                                         (__syscall_ulong_t)a
#define __NR32AP_fsync(a)                                       (__syscall_ulong_t)a
#define __NR32AP_sigreturn()                                    /* nothing */
#define __NR32AP_clone(a, b, c, d, e)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_setdomainname(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_uname(a)                                       (__syscall_ulong_t)a
#define __NR32AP_modify_ldt(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_adjtimex(a)                                    (__syscall_ulong_t)a
#define __NR32AP_mprotect(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sigprocmask(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_create_module()                                /* nothing */
#define __NR32AP_init_module(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_delete_module(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_get_kernel_syms()                              /* nothing */
#define __NR32AP_quotactl(a)                                    (__syscall_ulong_t)a
#define __NR32AP_getpgid(a)                                     (__syscall_ulong_t)a
#define __NR32AP_fchdir(a)                                      (__syscall_ulong_t)a
#define __NR32AP_bdflush(a)                                     (__syscall_ulong_t)a
#define __NR32AP_sysfs(a)                                       (__syscall_ulong_t)a
#define __NR32AP_personality(a)                                 (__syscall_ulong_t)a
#define __NR32AP_afs_syscall()                                  /* nothing */
#define __NR32AP_setfsuid(a)                                    (__syscall_ulong_t)a
#define __NR32AP_setfsgid(a)                                    (__syscall_ulong_t)a
#define __NR32AP__llseek(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_getdents(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP__newselect(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_flock(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_msync(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_readv(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_writev(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getsid(a)                                      (__syscall_ulong_t)a
#define __NR32AP_fdatasync(a)                                   (__syscall_ulong_t)a
#define __NR32AP__sysctl(a)                                     (__syscall_ulong_t)a
#define __NR32AP_mlock(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_munlock(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_mlockall(a)                                    (__syscall_ulong_t)a
#define __NR32AP_munlockall()                                   /* nothing */
#define __NR32AP_sched_setparam(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sched_getparam(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sched_setscheduler(a, b, c)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sched_getscheduler(a)                          (__syscall_ulong_t)a
#define __NR32AP_sched_yield()                                  /* nothing */
#define __NR32AP_sched_get_priority_max(a)                      (__syscall_ulong_t)a
#define __NR32AP_sched_get_priority_min(a)                      (__syscall_ulong_t)a
#define __NR32AP_sched_rr_get_interval(a, b)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_nanosleep(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_mremap(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_setresuid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getresuid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_vm86(a)                                        (__syscall_ulong_t)a
#define __NR32AP_query_module()                                 /* nothing */
#define __NR32AP_poll(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_nfsservctl(a)                                  (__syscall_ulong_t)a
#define __NR32AP_setresgid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getresgid(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_prctl(a, b, c, d, e)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_rt_sigreturn()                                 /* nothing */
#define __NR32AP_rt_sigaction(a, b, c, d)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_rt_sigprocmask(a, b, c, d)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_rt_sigpending(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_rt_sigtimedwait(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_rt_sigqueueinfo(a, b, c)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_rt_sigsuspend(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_pread64(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_pwrite64(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_chown(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getcwd(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_capget(a)                                      (__syscall_ulong_t)a
#define __NR32AP_capset(a)                                      (__syscall_ulong_t)a
#define __NR32AP_sigaltstack(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sendfile(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_getpmsg()                                      /* nothing */
#define __NR32AP_putpmsg()                                      /* nothing */
#define __NR32AP_vfork()                                        /* nothing */
#define __NR32AP_ugetrlimit(a)                                  (__syscall_ulong_t)a
#define __NR32AP_mmap2(a, b, c, d, e, f)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_truncate64(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32)
#define __NR32AP_ftruncate64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32)
#define __NR32AP_stat64(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lstat64(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fstat64(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lchown32(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getuid32()                                     /* nothing */
#define __NR32AP_getgid32()                                     /* nothing */
#define __NR32AP_geteuid32()                                    /* nothing */
#define __NR32AP_getegid32()                                    /* nothing */
#define __NR32AP_setreuid32(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setregid32(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getgroups32(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setgroups32(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fchown32(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setresuid32(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getresuid32(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setresgid32(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getresgid32(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_chown32(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_setuid32(a)                                    (__syscall_ulong_t)a
#define __NR32AP_setgid32(a)                                    (__syscall_ulong_t)a
#define __NR32AP_setfsuid32(a)                                  (__syscall_ulong_t)a
#define __NR32AP_setfsgid32(a)                                  (__syscall_ulong_t)a
#define __NR32AP_pivot_root(a)                                  (__syscall_ulong_t)a
#define __NR32AP_mincore(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_madvise(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getdents64(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_fcntl64(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_gettid()                                       /* nothing */
#define __NR32AP_readahead(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c
#define __NR32AP_setxattr(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_lsetxattr(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_fsetxattr(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_getxattr(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_lgetxattr(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_fgetxattr(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_listxattr(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_llistxattr(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_flistxattr(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_removexattr(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_lremovexattr(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fremovexattr(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_tkill(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_sendfile64(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_futex(a, b, c, d, e, f)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_sched_setaffinity(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sched_getaffinity(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_set_thread_area(a)                             (__syscall_ulong_t)a
#define __NR32AP_get_thread_area(a)                             (__syscall_ulong_t)a
#define __NR32AP_io_setup(a)                                    (__syscall_ulong_t)a
#define __NR32AP_io_destroy(a)                                  (__syscall_ulong_t)a
#define __NR32AP_io_getevents(a)                                (__syscall_ulong_t)a
#define __NR32AP_io_submit(a)                                   (__syscall_ulong_t)a
#define __NR32AP_io_cancel(a)                                   (__syscall_ulong_t)a
#define __NR32AP_fadvise64(a)                                   (__syscall_ulong_t)a
#define __NR32AP_exit_group(a)                                  (__syscall_ulong_t)a
#define __NR32AP_lookup_dcookie(a)                              (__syscall_ulong_t)a
#define __NR32AP_epoll_create(a)                                (__syscall_ulong_t)a
#define __NR32AP_epoll_ctl(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_epoll_wait(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_remap_file_pages(a, b, c, d, e)                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_set_tid_address(a)                             (__syscall_ulong_t)a
#define __NR32AP_timer_create(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_timer_settime(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timer_gettime(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_timer_getoverrun(a)                            (__syscall_ulong_t)a
#define __NR32AP_timer_delete(a)                                (__syscall_ulong_t)a
#define __NR32AP_clock_settime(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_gettime(a, b)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_getres(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_nanosleep(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_statfs64(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fstatfs64(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_tgkill(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_utimes(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fadvise64_64(a)                                (__syscall_ulong_t)a
#define __NR32AP_vserver()                                      /* nothing */
#define __NR32AP_mbind(a)                                       (__syscall_ulong_t)a
#define __NR32AP_get_mempolicy(a)                               (__syscall_ulong_t)a
#define __NR32AP_set_mempolicy(a)                               (__syscall_ulong_t)a
#define __NR32AP_mq_open(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_mq_unlink(a)                                   (__syscall_ulong_t)a
#define __NR32AP_mq_timedsend(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_mq_timedreceive(a, b, c, d, e)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_mq_notify(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_mq_getsetattr(a, b, c)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_kexec_load(a)                                  (__syscall_ulong_t)a
#define __NR32AP_waitid(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_add_key(a)                                     (__syscall_ulong_t)a
#define __NR32AP_request_key(a)                                 (__syscall_ulong_t)a
#define __NR32AP_keyctl(a)                                      (__syscall_ulong_t)a
#define __NR32AP_ioprio_set(a, b, c)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_ioprio_get(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_inotify_init()                                 /* nothing */
#define __NR32AP_inotify_add_watch(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_inotify_rm_watch(a, b)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_migrate_pages(a)                               (__syscall_ulong_t)a
#define __NR32AP_openat(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_mkdirat(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_mknodat(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_fchownat(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_futimesat(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_fstatat64(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_unlinkat(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_renameat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_linkat(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_symlinkat(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_readlinkat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_fchmodat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_faccessat(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_pselect6(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_ppoll(a, b, c, d, e)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_unshare(a)                                     (__syscall_ulong_t)a
#define __NR32AP_set_robust_list(a)                             (__syscall_ulong_t)a
#define __NR32AP_get_robust_list(a)                             (__syscall_ulong_t)a
#define __NR32AP_splice(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_sync_file_range(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c, (__syscall_ulong_t)((__uint64_t)c >> 32), (__syscall_ulong_t)d
#define __NR32AP_tee(a, b, c, d)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_vmsplice(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_move_pages(a)                                  (__syscall_ulong_t)a
#define __NR32AP_getcpu(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_epoll_pwait(a, b, c, d, e, f)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_utimensat(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_signalfd(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_timerfd_create(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_eventfd(a)                                     (__syscall_ulong_t)a
#define __NR32AP_fallocate(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timerfd_settime(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timerfd_gettime(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_signalfd4(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_eventfd2(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_epoll_create1(a)                               (__syscall_ulong_t)a
#define __NR32AP_dup3(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_pipe2(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_inotify_init1(a)                               (__syscall_ulong_t)a
#define __NR32AP_preadv(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_pwritev(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_rt_tgsigqueueinfo(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_perf_event_open(a)                             (__syscall_ulong_t)a
#define __NR32AP_recvmmsg(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_fanotify_init(a)                               (__syscall_ulong_t)a
#define __NR32AP_fanotify_mark(a)                               (__syscall_ulong_t)a
#define __NR32AP_prlimit64(a, b, c, d)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_name_to_handle_at(a, b, c, d, e)               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_open_by_handle_at(a, b, c)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_clock_adjtime(a)                               (__syscall_ulong_t)a
#define __NR32AP_syncfs(a)                                      (__syscall_ulong_t)a
#define __NR32AP_sendmmsg(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_setns(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_process_vm_readv(a, b, c, d, e, f)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_process_vm_writev(a, b, c, d, e, f)            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_kcmp(a, b, c, d, e)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_finit_module(a, b, c)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sched_setattr(a)                               (__syscall_ulong_t)a
#define __NR32AP_sched_getattr(a)                               (__syscall_ulong_t)a
#define __NR32AP_renameat2(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_seccomp(a)                                     (__syscall_ulong_t)a
#define __NR32AP_getrandom(a, b, c)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_memfd_create(a, b)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_bpf(a)                                         (__syscall_ulong_t)a
#define __NR32AP_execveat(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_socket(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_socketpair(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_bind(a, b, c)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_connect(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_listen(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_accept4(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_getsockopt(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_setsockopt(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_getsockname(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_getpeername(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_sendto(a, b, c, d, e, f)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_sendmsg(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_recvfrom(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_recvmsg(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_shutdown(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_userfaultfd(a)                                 (__syscall_ulong_t)a
#define __NR32AP_membarrier(a)                                  (__syscall_ulong_t)a
#define __NR32AP_mlock2(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_copy_file_range(a)                             (__syscall_ulong_t)a
#define __NR32AP_preadv2(a)                                     (__syscall_ulong_t)a
#define __NR32AP_pwritev2(a)                                    (__syscall_ulong_t)a
#define __NR32AP_pkey_mprotect(a, b, c, d)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_pkey_alloc(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_pkey_free(a)                                   (__syscall_ulong_t)a
#define __NR32AP_statx(a)                                       (__syscall_ulong_t)a
#define __NR32AP_arch_prctl(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_io_pgetevents(a)                               (__syscall_ulong_t)a
#define __NR32AP_rseq(a)                                        (__syscall_ulong_t)a
#define __NR32AP_semget(a)                                      (__syscall_ulong_t)a
#define __NR32AP_semctl(a)                                      (__syscall_ulong_t)a
#define __NR32AP_shmget(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_shmctl(a, b, c)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_shmat(a, b, c)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_shmdt(a)                                       (__syscall_ulong_t)a
#define __NR32AP_msgget(a)                                      (__syscall_ulong_t)a
#define __NR32AP_msgsnd(a)                                      (__syscall_ulong_t)a
#define __NR32AP_msgrcv(a)                                      (__syscall_ulong_t)a
#define __NR32AP_msgctl(a)                                      (__syscall_ulong_t)a
#define __NR32AP_clock_gettime64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_settime64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_adjtime64(a)                             (__syscall_ulong_t)a
#define __NR32AP_clock_getres_time64(a, b)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clock_nanosleep_time64(a, b, c, d)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timer_gettime64(a, b)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_timer_settime64(a, b, c, d)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_timerfd_gettime64(a, b)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_timerfd_settime64(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_utimensat_time64(a, b, c, d)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_pselect6_time64(a, b, c, d, e, f)              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_ppoll_time64(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_io_pgetevents_time64(a)                        (__syscall_ulong_t)a
#define __NR32AP_recvmmsg_time64(a, b, c, d, e)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_mq_timedsend_time64(a, b, c, d, e)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_mq_timedreceive_time64(a, b, c, d, e)          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_semtimedop_time64(a)                           (__syscall_ulong_t)a
#define __NR32AP_rt_sigtimedwait_time64(a, b, c, d)             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_futex_time64(a, b, c, d, e, f)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_sched_rr_get_interval_time64(a, b)             (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_pidfd_send_signal(a, b, c, d)                  (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_io_uring_setup(a)                              (__syscall_ulong_t)a
#define __NR32AP_io_uring_enter(a)                              (__syscall_ulong_t)a
#define __NR32AP_io_uring_register(a)                           (__syscall_ulong_t)a
#define __NR32AP_open_tree(a)                                   (__syscall_ulong_t)a
#define __NR32AP_move_mount(a)                                  (__syscall_ulong_t)a
#define __NR32AP_fsopen(a)                                      (__syscall_ulong_t)a
#define __NR32AP_fsconfig(a)                                    (__syscall_ulong_t)a
#define __NR32AP_fsmount(a)                                     (__syscall_ulong_t)a
#define __NR32AP_fspick(a)                                      (__syscall_ulong_t)a
#define __NR32AP_pidfd_open(a, b)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_clone3(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_close_range(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_openat2(a)                                     (__syscall_ulong_t)a
#define __NR32AP_pidfd_getfd(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_faccessat2(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_pwritevf(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NR32AP_preadvf(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NR32AP_fallocate64(a, b, c, d)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)((__uint64_t)c >> 32), (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32)
#define __NR32AP_freadlinkat(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_fsymlinkat(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_kfstatat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_futimesat64(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_fmknodat(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_fmkdirat(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_inotify_add_watch_at(a, b, c, d, e)            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_waitid64(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_utimes64(a, b)                                 (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_kreaddirf(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_kfstat(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_klstat(a, b)                                   (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_kstat(a, b)                                    (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_pwrite64f(a, b, c, d, e)                       (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NR32AP_pread64f(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)((__uint64_t)d >> 32), (__syscall_ulong_t)e
#define __NR32AP_ksigreturn(a, b, c, d, e, f)                   (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_nanosleep64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_rpc_serve()                                    /* nothing */
#define __NR32AP_ksysctl(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_writevf(a, b, c, d)                            (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_readvf(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_kreaddir(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_wait4_64(a, b, c, d)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_getitimer64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_setitimer64(a, b, c)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_maplibrary(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_select64(a, b, c, d, e)                        (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_settimeofday64(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_gettimeofday64(a, b)                           (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_getrusage64(a, b)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_fsmode(a)                                      (__syscall_ulong_t)a, (__syscall_ulong_t)((__uint64_t)a >> 32)
#define __NR32AP_ioctlf(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_rtm_test()                                     /* nothing */
#define __NR32AP_rtm_abort(a)                                   (__syscall_ulong_t)a
#define __NR32AP_rtm_end()                                      /* nothing */
#define __NR32AP_rtm_begin()                                    /* nothing */
#define __NR32AP_ftime64(a)                                     (__syscall_ulong_t)a
#define __NR32AP_rpc_serve_sysret()                             /* nothing */
#define __NR32AP_set_userprocmask_address(a)                    (__syscall_ulong_t)a
#define __NR32AP_utime64(a, b)                                  (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_userviofd(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_stime64(a)                                     (__syscall_ulong_t)a
#define __NR32AP_coredump(a, b, c, d, e, f)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e, (__syscall_ulong_t)f
#define __NR32AP_mktty(a, b, c, d)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_lfutexexpr(a, b, c, d, e)                      (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_lseek64(a, b, c)                               (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)((__uint64_t)b >> 32), (__syscall_ulong_t)c
#define __NR32AP_lfutex(a, b, c, d, e)                          (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_debugtrap(a, b)                                (__syscall_ulong_t)a, (__syscall_ulong_t)b
#define __NR32AP_get_exception_handler(a, b, c)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_set_exception_handler(a, b, c)                 (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_time64(a)                                      (__syscall_ulong_t)a
#define __NR32AP_fchdirat(a, b, c)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c
#define __NR32AP_openpty(a, b, c, d, e)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_rpc_schedule(a, b, c, d, e)                    (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_frealpathat(a, b, c, d, e)                     (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d, (__syscall_ulong_t)e
#define __NR32AP_frealpath4(a, b, c, d)                         (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_getdrives()                                    /* nothing */
#define __NR32AP_detach(a)                                      (__syscall_ulong_t)a
#define __NR32AP_writef(a, b, c, d)                             (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#define __NR32AP_readf(a, b, c, d)                              (__syscall_ulong_t)a, (__syscall_ulong_t)b, (__syscall_ulong_t)c, (__syscall_ulong_t)d
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_LIST_PACKER */
#endif /* __WANT_SYSCALL_ARGUMENT_LIST_PACKER */

