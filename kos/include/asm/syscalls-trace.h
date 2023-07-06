/* HASH CRC-32:0xe0d564b1 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

/************************************************************************/
/* SYSCALL ARGUMENT NAMES                                               */
/*  - __NRAN<argI>_<name> : ArgumentName                                */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_NAMES
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#define __NRAN0_io_setup               TODO_PROTOTYPE
#define __NRAN0_io_destroy             TODO_PROTOTYPE
#define __NRAN0_io_submit              TODO_PROTOTYPE
#define __NRAN0_io_cancel              TODO_PROTOTYPE
#define __NRAN0_io_getevents           TODO_PROTOTYPE
#define __NRAN0_setxattr               path
#define __NRAN1_setxattr               name
#define __NRAN2_setxattr               buf
#define __NRAN3_setxattr               bufsize
#define __NRAN4_setxattr               flags
#define __NRAN0_lsetxattr              path
#define __NRAN1_lsetxattr              name
#define __NRAN2_lsetxattr              buf
#define __NRAN3_lsetxattr              bufsize
#define __NRAN4_lsetxattr              flags
#define __NRAN0_fsetxattr              fd
#define __NRAN1_fsetxattr              name
#define __NRAN2_fsetxattr              buf
#define __NRAN3_fsetxattr              bufsize
#define __NRAN4_fsetxattr              flags
#define __NRAN0_getxattr               path
#define __NRAN1_getxattr               name
#define __NRAN2_getxattr               buf
#define __NRAN3_getxattr               bufsize
#define __NRAN0_lgetxattr              path
#define __NRAN1_lgetxattr              name
#define __NRAN2_lgetxattr              buf
#define __NRAN3_lgetxattr              bufsize
#define __NRAN0_fgetxattr              fd
#define __NRAN1_fgetxattr              name
#define __NRAN2_fgetxattr              buf
#define __NRAN3_fgetxattr              bufsize
#define __NRAN0_listxattr              path
#define __NRAN1_listxattr              listbuf
#define __NRAN2_listxattr              listbufsize
#define __NRAN0_llistxattr             path
#define __NRAN1_llistxattr             listbuf
#define __NRAN2_llistxattr             listbufsize
#define __NRAN0_flistxattr             fd
#define __NRAN1_flistxattr             listbuf
#define __NRAN2_flistxattr             listbufsize
#define __NRAN0_removexattr            path
#define __NRAN1_removexattr            name
#define __NRAN0_lremovexattr           path
#define __NRAN1_lremovexattr           name
#define __NRAN0_fremovexattr           fd
#define __NRAN1_fremovexattr           name
#define __NRAN0_getcwd                 buf
#define __NRAN1_getcwd                 size
#define __NRAN0_lookup_dcookie         TODO_PROTOTYPE
#define __NRAN0_eventfd2               initval
#define __NRAN1_eventfd2               flags
#define __NRAN0_epoll_create1          flags
#define __NRAN0_epoll_ctl              epfd
#define __NRAN1_epoll_ctl              op
#define __NRAN2_epoll_ctl              fd
#define __NRAN3_epoll_ctl              info
#define __NRAN0_epoll_pwait            epfd
#define __NRAN1_epoll_pwait            events
#define __NRAN2_epoll_pwait            maxevents
#define __NRAN3_epoll_pwait            timeout
#define __NRAN4_epoll_pwait            ss
#define __NRAN5_epoll_pwait            sigsetsize
#define __NRAN0_dup                    fd
#define __NRAN0_dup3                   oldfd
#define __NRAN1_dup3                   newfd
#define __NRAN2_dup3                   flags
#define __NRAN0_inotify_init1          flags
#define __NRAN0_inotify_add_watch      notify_fd
#define __NRAN1_inotify_add_watch      pathname
#define __NRAN2_inotify_add_watch      mask
#define __NRAN0_inotify_rm_watch       notify_fd
#define __NRAN1_inotify_rm_watch       wd
#define __NRAN0_ioctl                  fd
#define __NRAN1_ioctl                  command
#define __NRAN2_ioctl                  arg
#define __NRAN0_ioprio_set             who
#define __NRAN1_ioprio_set             id
#define __NRAN2_ioprio_set             ioprio
#define __NRAN0_ioprio_get             who
#define __NRAN1_ioprio_get             id
#define __NRAN0_flock                  fd
#define __NRAN1_flock                  operation
#define __NRAN0_mknodat                dirfd
#define __NRAN1_mknodat                nodename
#define __NRAN2_mknodat                mode
#define __NRAN3_mknodat                dev
#define __NRAN0_mkdirat                dirfd
#define __NRAN1_mkdirat                pathname
#define __NRAN2_mkdirat                mode
#define __NRAN0_unlinkat               dirfd
#define __NRAN1_unlinkat               name
#define __NRAN2_unlinkat               flags
#define __NRAN0_symlinkat              link_text
#define __NRAN1_symlinkat              tofd
#define __NRAN2_symlinkat              target_path
#define __NRAN0_linkat                 fromfd
#define __NRAN1_linkat                 existing_file
#define __NRAN2_linkat                 tofd
#define __NRAN3_linkat                 target_path
#define __NRAN4_linkat                 flags
#define __NRAN0_renameat               oldfd
#define __NRAN1_renameat               oldname
#define __NRAN2_renameat               newfd
#define __NRAN3_renameat               newname_or_path
#define __NRAN0_umount2                special_file
#define __NRAN1_umount2                flags
#define __NRAN0_mount                  special_file
#define __NRAN1_mount                  dir
#define __NRAN2_mount                  fstype
#define __NRAN3_mount                  mountflags
#define __NRAN4_mount                  data
#define __NRAN0_pivot_root             TODO_PROTOTYPE
#define __NRAN0_nfsservctl             TODO_PROTOTYPE
#define __NRAN0_fallocate              fd
#define __NRAN1_fallocate              mode
#define __NRAN2_fallocate              offset
#define __NRAN3_fallocate              length
#define __NRAN0_faccessat              dirfd
#define __NRAN1_faccessat              filename
#define __NRAN2_faccessat              type
#define __NRAN0_chdir                  path
#define __NRAN0_fchdir                 fd
#define __NRAN0_chroot                 path
#define __NRAN0_fchmod                 fd
#define __NRAN1_fchmod                 mode
#define __NRAN0_fchmodat               dirfd
#define __NRAN1_fchmodat               filename
#define __NRAN2_fchmodat               mode
#define __NRAN3_fchmodat               flags
#define __NRAN0_fchownat               dirfd
#define __NRAN1_fchownat               filename
#define __NRAN2_fchownat               owner
#define __NRAN3_fchownat               group
#define __NRAN4_fchownat               flags
#define __NRAN0_fchown                 fd
#define __NRAN1_fchown                 owner
#define __NRAN2_fchown                 group
#define __NRAN0_openat                 dirfd
#define __NRAN1_openat                 filename
#define __NRAN2_openat                 oflags
#define __NRAN3_openat                 mode
#define __NRAN0_close                  fd
#define __NRAN0_pipe2                  pipedes
#define __NRAN1_pipe2                  flags
#define __NRAN0_quotactl               TODO_PROTOTYPE
#define __NRAN0_getdents64             fd
#define __NRAN1_getdents64             buf
#define __NRAN2_getdents64             buflen
#define __NRAN0_read                   fd
#define __NRAN1_read                   buf
#define __NRAN2_read                   bufsize
#define __NRAN0_write                  fd
#define __NRAN1_write                  buf
#define __NRAN2_write                  bufsize
#define __NRAN0_readv                  fd
#define __NRAN1_readv                  iovec
#define __NRAN2_readv                  count
#define __NRAN0_writev                 fd
#define __NRAN1_writev                 iovec
#define __NRAN2_writev                 count
#define __NRAN0_pread64                fd
#define __NRAN1_pread64                buf
#define __NRAN2_pread64                bufsize
#define __NRAN3_pread64                offset
#define __NRAN0_pwrite64               fd
#define __NRAN1_pwrite64               buf
#define __NRAN2_pwrite64               bufsize
#define __NRAN3_pwrite64               offset
#define __NRAN0_preadv                 fd
#define __NRAN1_preadv                 iovec
#define __NRAN2_preadv                 count
#define __NRAN3_preadv                 offset
#define __NRAN0_pwritev                fd
#define __NRAN1_pwritev                iovec
#define __NRAN2_pwritev                count
#define __NRAN3_pwritev                offset
#define __NRAN0_pselect6               nfds
#define __NRAN1_pselect6               readfds
#define __NRAN2_pselect6               writefds
#define __NRAN3_pselect6               exceptfds
#define __NRAN4_pselect6               timeout
#define __NRAN5_pselect6               sigmask_sigset_with_size
#define __NRAN0_ppoll                  fds
#define __NRAN1_ppoll                  nfds
#define __NRAN2_ppoll                  timeout_ts
#define __NRAN3_ppoll                  sigmask
#define __NRAN4_ppoll                  sigsetsize
#define __NRAN0_signalfd4              fd
#define __NRAN1_signalfd4              sigmask
#define __NRAN2_signalfd4              sigmasksize
#define __NRAN3_signalfd4              flags
#define __NRAN0_vmsplice               fdout
#define __NRAN1_vmsplice               iov
#define __NRAN2_vmsplice               count
#define __NRAN3_vmsplice               flags
#define __NRAN0_splice                 fdin
#define __NRAN1_splice                 offin
#define __NRAN2_splice                 fdout
#define __NRAN3_splice                 offout
#define __NRAN4_splice                 length
#define __NRAN5_splice                 flags
#define __NRAN0_tee                    fdin
#define __NRAN1_tee                    fdout
#define __NRAN2_tee                    length
#define __NRAN3_tee                    flags
#define __NRAN0_readlinkat             dirfd
#define __NRAN1_readlinkat             path
#define __NRAN2_readlinkat             buf
#define __NRAN3_readlinkat             buflen
#define __NRAN0_fsync                  fd
#define __NRAN0_fdatasync              fd
#define __NRAN0_sync_file_range        fd
#define __NRAN1_sync_file_range        offset
#define __NRAN2_sync_file_range        count
#define __NRAN3_sync_file_range        flags
#define __NRAN0_timerfd_create         clock_id
#define __NRAN1_timerfd_create         flags
#define __NRAN0_timerfd_settime        timerfd
#define __NRAN1_timerfd_settime        flags
#define __NRAN2_timerfd_settime        utmr
#define __NRAN3_timerfd_settime        otmr
#define __NRAN0_timerfd_gettime        timerfd
#define __NRAN1_timerfd_gettime        otmr
#define __NRAN0_utimensat              dirfd
#define __NRAN1_utimensat              filename
#define __NRAN2_utimensat              times
#define __NRAN3_utimensat              flags
#define __NRAN0_acct                   filename
#define __NRAN0_capget                 TODO_PROTOTYPE
#define __NRAN0_capset                 TODO_PROTOTYPE
#define __NRAN0_personality            TODO_PROTOTYPE
#define __NRAN0_exit                   exit_code
#define __NRAN0_exit_group             exit_code
#define __NRAN0_waitid                 idtype
#define __NRAN1_waitid                 id
#define __NRAN2_waitid                 infop
#define __NRAN3_waitid                 options
#define __NRAN4_waitid                 ru
#define __NRAN0_set_tid_address        tidptr
#define __NRAN0_unshare                what
#define __NRAN0_futex                  uaddr
#define __NRAN1_futex                  futex_op
#define __NRAN2_futex                  val
#define __NRAN3_futex                  timeout_or_val2
#define __NRAN4_futex                  uaddr2
#define __NRAN5_futex                  val3
#define __NRAN0_set_robust_list        TODO_PROTOTYPE
#define __NRAN0_get_robust_list        TODO_PROTOTYPE
#define __NRAN0_nanosleep              req
#define __NRAN1_nanosleep              rem
#define __NRAN0_getitimer              which
#define __NRAN1_getitimer              curr_value
#define __NRAN0_setitimer              which
#define __NRAN1_setitimer              newval
#define __NRAN2_setitimer              oldval
#define __NRAN0_kexec_load             TODO_PROTOTYPE
#define __NRAN0_init_module            module_image
#define __NRAN1_init_module            len
#define __NRAN2_init_module            uargs
#define __NRAN0_delete_module          name
#define __NRAN1_delete_module          flags
#define __NRAN0_timer_create           clock_id
#define __NRAN1_timer_create           evp
#define __NRAN2_timer_create           timerid
#define __NRAN0_timer_gettime          timerid
#define __NRAN1_timer_gettime          value
#define __NRAN0_timer_getoverrun       timerid
#define __NRAN0_timer_settime          timerid
#define __NRAN1_timer_settime          flags
#define __NRAN2_timer_settime          value
#define __NRAN3_timer_settime          ovalue
#define __NRAN0_timer_delete           timerid
#define __NRAN0_clock_settime          clock_id
#define __NRAN1_clock_settime          tp
#define __NRAN0_clock_gettime          clock_id
#define __NRAN1_clock_gettime          tp
#define __NRAN0_clock_getres           clock_id
#define __NRAN1_clock_getres           res
#define __NRAN0_clock_nanosleep        clock_id
#define __NRAN1_clock_nanosleep        flags
#define __NRAN2_clock_nanosleep        requested_time
#define __NRAN3_clock_nanosleep        remaining
#define __NRAN0_syslog                 level
#define __NRAN1_syslog                 str
#define __NRAN2_syslog                 len
#define __NRAN0_ptrace                 request
#define __NRAN1_ptrace                 pid
#define __NRAN2_ptrace                 addr
#define __NRAN3_ptrace                 data
#define __NRAN0_sched_setparam         pid
#define __NRAN1_sched_setparam         param
#define __NRAN0_sched_setscheduler     pid
#define __NRAN1_sched_setscheduler     policy
#define __NRAN2_sched_setscheduler     param
#define __NRAN0_sched_getscheduler     pid
#define __NRAN0_sched_getparam         pid
#define __NRAN1_sched_getparam         param
#define __NRAN0_sched_setaffinity      pid
#define __NRAN1_sched_setaffinity      cpusetsize
#define __NRAN2_sched_setaffinity      cpuset
#define __NRAN0_sched_getaffinity      pid
#define __NRAN1_sched_getaffinity      cpusetsize
#define __NRAN2_sched_getaffinity      cpuset
#define __NRAN0_sched_get_priority_max algorithm
#define __NRAN0_sched_get_priority_min algorithm
#define __NRAN0_sched_rr_get_interval  pid
#define __NRAN1_sched_rr_get_interval  ts
#define __NRAN0_kill                   pid
#define __NRAN1_kill                   signo
#define __NRAN0_tkill                  tid
#define __NRAN1_tkill                  signo
#define __NRAN0_tgkill                 pid
#define __NRAN1_tgkill                 tid
#define __NRAN2_tgkill                 signo
#define __NRAN0_sigaltstack            ss
#define __NRAN1_sigaltstack            oss
#define __NRAN0_rt_sigsuspend          set
#define __NRAN1_rt_sigsuspend          sigsetsize
#define __NRAN0_rt_sigaction           signo
#define __NRAN1_rt_sigaction           act
#define __NRAN2_rt_sigaction           oact
#define __NRAN3_rt_sigaction           sigsetsize
#define __NRAN0_rt_sigprocmask         how
#define __NRAN1_rt_sigprocmask         set
#define __NRAN2_rt_sigprocmask         oset
#define __NRAN3_rt_sigprocmask         sigsetsize
#define __NRAN0_rt_sigpending          set
#define __NRAN1_rt_sigpending          sigsetsize
#define __NRAN0_rt_sigtimedwait        set
#define __NRAN1_rt_sigtimedwait        info
#define __NRAN2_rt_sigtimedwait        timeout
#define __NRAN3_rt_sigtimedwait        sigsetsize
#define __NRAN0_rt_sigqueueinfo        pid
#define __NRAN1_rt_sigqueueinfo        usigno
#define __NRAN2_rt_sigqueueinfo        uinfo
#define __NRAN0_setpriority            which
#define __NRAN1_setpriority            who
#define __NRAN2_setpriority            value
#define __NRAN0_getpriority            which
#define __NRAN1_getpriority            who
#define __NRAN0_reboot                 how
#define __NRAN0_setregid               rgid
#define __NRAN1_setregid               egid
#define __NRAN0_setgid                 gid
#define __NRAN0_setreuid               ruid
#define __NRAN1_setreuid               euid
#define __NRAN0_setuid                 uid
#define __NRAN0_setresuid              ruid
#define __NRAN1_setresuid              euid
#define __NRAN2_setresuid              suid
#define __NRAN0_getresuid              ruid
#define __NRAN1_getresuid              euid
#define __NRAN2_getresuid              suid
#define __NRAN0_setresgid              rgid
#define __NRAN1_setresgid              egid
#define __NRAN2_setresgid              sgid
#define __NRAN0_getresgid              rgid
#define __NRAN1_getresgid              egid
#define __NRAN2_getresgid              sgid
#define __NRAN0_setfsuid               uid
#define __NRAN0_setfsgid               gid
#define __NRAN0_times                  buf
#define __NRAN0_setpgid                pid
#define __NRAN1_setpgid                pgid
#define __NRAN0_getpgid                pid
#define __NRAN0_getsid                 pid
#define __NRAN0_getgroups              count
#define __NRAN1_getgroups              list
#define __NRAN0_setgroups              count
#define __NRAN1_setgroups              groups
#define __NRAN0_uname                  name
#define __NRAN0_sethostname            name
#define __NRAN1_sethostname            len
#define __NRAN0_setdomainname          name
#define __NRAN1_setdomainname          len
#define __NRAN0_getrlimit              resource
#define __NRAN1_getrlimit              rlimits
#define __NRAN0_setrlimit              resource
#define __NRAN1_setrlimit              rlimits
#define __NRAN0_getrusage              who
#define __NRAN1_getrusage              usage
#define __NRAN0_umask                  mode
#define __NRAN0_prctl                  command
#define __NRAN1_prctl                  arg2
#define __NRAN2_prctl                  arg3
#define __NRAN3_prctl                  arg4
#define __NRAN4_prctl                  arg5
#define __NRAN0_getcpu                 cpu
#define __NRAN1_getcpu                 node
#define __NRAN2_getcpu                 tcache
#define __NRAN0_gettimeofday           tv
#define __NRAN1_gettimeofday           tz
#define __NRAN0_settimeofday           tv
#define __NRAN1_settimeofday           tz
#define __NRAN0_adjtimex               ntx
#define __NRAN0_sysinfo                info
#define __NRAN0_mq_open                name
#define __NRAN1_mq_open                oflags
#define __NRAN2_mq_open                mode
#define __NRAN0_mq_unlink              name
#define __NRAN0_mq_timedsend           mqdes
#define __NRAN1_mq_timedsend           msg_ptr
#define __NRAN2_mq_timedsend           msg_len
#define __NRAN3_mq_timedsend           msg_prio
#define __NRAN4_mq_timedsend           abs_timeout
#define __NRAN0_mq_timedreceive        mqdes
#define __NRAN1_mq_timedreceive        msg_ptr
#define __NRAN2_mq_timedreceive        msg_len
#define __NRAN3_mq_timedreceive        pmsg_prio
#define __NRAN4_mq_timedreceive        abs_timeout
#define __NRAN0_mq_notify              mqdes
#define __NRAN1_mq_notify              notification
#define __NRAN0_mq_getsetattr          mqdes
#define __NRAN1_mq_getsetattr          newattr
#define __NRAN2_mq_getsetattr          oldattr
#define __NRAN0_msgget                 TODO_PROTOTYPE
#define __NRAN0_msgctl                 TODO_PROTOTYPE
#define __NRAN0_msgrcv                 TODO_PROTOTYPE
#define __NRAN0_msgsnd                 TODO_PROTOTYPE
#define __NRAN0_semget                 TODO_PROTOTYPE
#define __NRAN0_semctl                 TODO_PROTOTYPE
#define __NRAN0_semtimedop             TODO_PROTOTYPE
#define __NRAN0_semop                  TODO_PROTOTYPE
#define __NRAN0_shmget                 key
#define __NRAN1_shmget                 size
#define __NRAN2_shmget                 shmflg
#define __NRAN0_shmctl                 shmid
#define __NRAN1_shmctl                 cmd
#define __NRAN2_shmctl                 buf
#define __NRAN0_shmat                  shmid
#define __NRAN1_shmat                  shmaddr
#define __NRAN2_shmat                  shmflg
#define __NRAN0_shmdt                  shmaddr
#define __NRAN0_socket                 domain
#define __NRAN1_socket                 type
#define __NRAN2_socket                 protocol
#define __NRAN0_socketpair             domain
#define __NRAN1_socketpair             type
#define __NRAN2_socketpair             protocol
#define __NRAN3_socketpair             fds
#define __NRAN0_bind                   sockfd
#define __NRAN1_bind                   addr
#define __NRAN2_bind                   addr_len
#define __NRAN0_listen                 sockfd
#define __NRAN1_listen                 max_backlog
#define __NRAN0_accept                 sockfd
#define __NRAN1_accept                 addr
#define __NRAN2_accept                 addr_len
#define __NRAN0_connect                sockfd
#define __NRAN1_connect                addr
#define __NRAN2_connect                addr_len
#define __NRAN0_getsockname            sockfd
#define __NRAN1_getsockname            addr
#define __NRAN2_getsockname            addr_len
#define __NRAN0_getpeername            sockfd
#define __NRAN1_getpeername            addr
#define __NRAN2_getpeername            addr_len
#define __NRAN0_sendto                 sockfd
#define __NRAN1_sendto                 buf
#define __NRAN2_sendto                 bufsize
#define __NRAN3_sendto                 msg_flags
#define __NRAN4_sendto                 addr
#define __NRAN5_sendto                 addr_len
#define __NRAN0_recvfrom               sockfd
#define __NRAN1_recvfrom               buf
#define __NRAN2_recvfrom               bufsize
#define __NRAN3_recvfrom               msg_flags
#define __NRAN4_recvfrom               addr
#define __NRAN5_recvfrom               addr_len
#define __NRAN0_setsockopt             sockfd
#define __NRAN1_setsockopt             level
#define __NRAN2_setsockopt             optname
#define __NRAN3_setsockopt             optval
#define __NRAN4_setsockopt             optlen
#define __NRAN0_getsockopt             sockfd
#define __NRAN1_getsockopt             level
#define __NRAN2_getsockopt             optname
#define __NRAN3_getsockopt             optval
#define __NRAN4_getsockopt             optlen
#define __NRAN0_shutdown               sockfd
#define __NRAN1_shutdown               how
#define __NRAN0_sendmsg                sockfd
#define __NRAN1_sendmsg                message
#define __NRAN2_sendmsg                msg_flags
#define __NRAN0_recvmsg                sockfd
#define __NRAN1_recvmsg                message
#define __NRAN2_recvmsg                msg_flags
#define __NRAN0_readahead              fd
#define __NRAN1_readahead              offset
#define __NRAN2_readahead              count
#define __NRAN0_brk                    addr
#define __NRAN0_munmap                 addr
#define __NRAN1_munmap                 len
#define __NRAN0_mremap                 addr
#define __NRAN1_mremap                 old_len
#define __NRAN2_mremap                 new_len
#define __NRAN3_mremap                 flags
#define __NRAN4_mremap                 new_address
#define __NRAN0_add_key                TODO_PROTOTYPE
#define __NRAN0_request_key            TODO_PROTOTYPE
#define __NRAN0_keyctl                 TODO_PROTOTYPE
#define __NRAN0_clone                  flags
#define __NRAN1_clone                  child_stack
#define __NRAN2_clone                  ptid
#define __NRAN3_clone                  newtls
#define __NRAN4_clone                  ctid
#define __NRAN0_execve                 path
#define __NRAN1_execve                 argv
#define __NRAN2_execve                 envp
#define __NRAN0_swapon                 pathname
#define __NRAN1_swapon                 swapflags
#define __NRAN0_swapoff                pathname
#define __NRAN0_mprotect               addr
#define __NRAN1_mprotect               len
#define __NRAN2_mprotect               prot
#define __NRAN0_msync                  addr
#define __NRAN1_msync                  len
#define __NRAN2_msync                  flags
#define __NRAN0_mlock                  addr
#define __NRAN1_mlock                  len
#define __NRAN0_munlock                addr
#define __NRAN1_munlock                len
#define __NRAN0_mlockall               flags
#define __NRAN0_mincore                start
#define __NRAN1_mincore                len
#define __NRAN2_mincore                vec
#define __NRAN0_madvise                addr
#define __NRAN1_madvise                len
#define __NRAN2_madvise                advice
#define __NRAN0_remap_file_pages       start
#define __NRAN1_remap_file_pages       size
#define __NRAN2_remap_file_pages       prot
#define __NRAN3_remap_file_pages       pgoff
#define __NRAN4_remap_file_pages       flags
#define __NRAN0_mbind                  TODO_PROTOTYPE
#define __NRAN0_get_mempolicy          TODO_PROTOTYPE
#define __NRAN0_set_mempolicy          TODO_PROTOTYPE
#define __NRAN0_migrate_pages          TODO_PROTOTYPE
#define __NRAN0_move_pages             TODO_PROTOTYPE
#define __NRAN0_rt_tgsigqueueinfo      pid
#define __NRAN1_rt_tgsigqueueinfo      tid
#define __NRAN2_rt_tgsigqueueinfo      usigno
#define __NRAN3_rt_tgsigqueueinfo      uinfo
#define __NRAN0_perf_event_open        TODO_PROTOTYPE
#define __NRAN0_accept4                sockfd
#define __NRAN1_accept4                addr
#define __NRAN2_accept4                addr_len
#define __NRAN3_accept4                sock_flags
#define __NRAN0_recvmmsg               sockfd
#define __NRAN1_recvmmsg               vmessages
#define __NRAN2_recvmmsg               vlen
#define __NRAN3_recvmmsg               msg_flags
#define __NRAN4_recvmmsg               tmo
#define __NRAN0_wait4                  pid
#define __NRAN1_wait4                  stat_loc
#define __NRAN2_wait4                  options
#define __NRAN3_wait4                  usage
#define __NRAN0_prlimit64              pid
#define __NRAN1_prlimit64              resource
#define __NRAN2_prlimit64              new_limit
#define __NRAN3_prlimit64              old_limit
#define __NRAN0_fanotify_init          TODO_PROTOTYPE
#define __NRAN0_fanotify_mark          TODO_PROTOTYPE
#define __NRAN0_name_to_handle_at      dirfd
#define __NRAN1_name_to_handle_at      filename
#define __NRAN2_name_to_handle_at      handle
#define __NRAN3_name_to_handle_at      mnt_id
#define __NRAN4_name_to_handle_at      flags
#define __NRAN0_open_by_handle_at      mountdirfd
#define __NRAN1_open_by_handle_at      handle
#define __NRAN2_open_by_handle_at      flags
#define __NRAN0_clock_adjtime          TODO_PROTOTYPE
#define __NRAN0_syncfs                 fd
#define __NRAN0_setns                  fd
#define __NRAN1_setns                  nstype
#define __NRAN0_sendmmsg               sockfd
#define __NRAN1_sendmmsg               vmessages
#define __NRAN2_sendmmsg               vlen
#define __NRAN3_sendmmsg               msg_flags
#define __NRAN0_process_vm_readv       pid
#define __NRAN1_process_vm_readv       local_iov
#define __NRAN2_process_vm_readv       liovcnt
#define __NRAN3_process_vm_readv       remote_iov
#define __NRAN4_process_vm_readv       riovcnt
#define __NRAN5_process_vm_readv       flags
#define __NRAN0_process_vm_writev      pid
#define __NRAN1_process_vm_writev      local_iov
#define __NRAN2_process_vm_writev      liovcnt
#define __NRAN3_process_vm_writev      remote_iov
#define __NRAN4_process_vm_writev      riovcnt
#define __NRAN5_process_vm_writev      flags
#define __NRAN0_kcmp                   pid1
#define __NRAN1_kcmp                   pid2
#define __NRAN2_kcmp                   type
#define __NRAN3_kcmp                   idx1
#define __NRAN4_kcmp                   idx2
#define __NRAN0_finit_module           fd
#define __NRAN1_finit_module           uargs
#define __NRAN2_finit_module           flags
#define __NRAN0_sched_setattr          TODO_PROTOTYPE
#define __NRAN0_sched_getattr          TODO_PROTOTYPE
#define __NRAN0_renameat2              olddirfd
#define __NRAN1_renameat2              oldpath
#define __NRAN2_renameat2              newdirfd
#define __NRAN3_renameat2              newpath
#define __NRAN4_renameat2              flags
#define __NRAN0_seccomp                TODO_PROTOTYPE
#define __NRAN0_getrandom              buf
#define __NRAN1_getrandom              num_bytes
#define __NRAN2_getrandom              flags
#define __NRAN0_memfd_create           name
#define __NRAN1_memfd_create           flags
#define __NRAN0_bpf                    TODO_PROTOTYPE
#define __NRAN0_execveat               dirfd
#define __NRAN1_execveat               pathname
#define __NRAN2_execveat               argv
#define __NRAN3_execveat               envp
#define __NRAN4_execveat               flags
#define __NRAN0_userfaultfd            flags
#define __NRAN0_membarrier             TODO_PROTOTYPE
#define __NRAN0_mlock2                 addr
#define __NRAN1_mlock2                 length
#define __NRAN2_mlock2                 flags
#define __NRAN0_open                   filename
#define __NRAN1_open                   oflags
#define __NRAN2_open                   mode
#define __NRAN0_link                   existing_file
#define __NRAN1_link                   link_file
#define __NRAN0_unlink                 filename
#define __NRAN0_mknod                  nodename
#define __NRAN1_mknod                  mode
#define __NRAN2_mknod                  dev
#define __NRAN0_chmod                  filename
#define __NRAN1_chmod                  mode
#define __NRAN0_chown                  filename
#define __NRAN1_chown                  owner
#define __NRAN2_chown                  group
#define __NRAN0_mkdir                  pathname
#define __NRAN1_mkdir                  mode
#define __NRAN0_rmdir                  path
#define __NRAN0_lchown                 filename
#define __NRAN1_lchown                 owner
#define __NRAN2_lchown                 group
#define __NRAN0_access                 filename
#define __NRAN1_access                 type
#define __NRAN0_rename                 oldname
#define __NRAN1_rename                 newname_or_path
#define __NRAN0_readlink               path
#define __NRAN1_readlink               buf
#define __NRAN2_readlink               buflen
#define __NRAN0_symlink                link_text
#define __NRAN1_symlink                target_path
#define __NRAN0_utimes                 filename
#define __NRAN1_utimes                 times
#define __NRAN0_pipe                   pipedes
#define __NRAN0_dup2                   oldfd
#define __NRAN1_dup2                   newfd
#define __NRAN0_epoll_create           size
#define __NRAN0_eventfd                initval
#define __NRAN0_signalfd               fd
#define __NRAN1_signalfd               sigmask
#define __NRAN2_signalfd               sigmasksize
#define __NRAN0_sendfile               outfd
#define __NRAN1_sendfile               infd
#define __NRAN2_sendfile               pin_offset
#define __NRAN3_sendfile               num_bytes
#define __NRAN0_ftruncate              fd
#define __NRAN1_ftruncate              length
#define __NRAN0_truncate               filename
#define __NRAN1_truncate               length
#define __NRAN0_stat                   filename
#define __NRAN1_stat                   statbuf
#define __NRAN0_lstat                  filename
#define __NRAN1_lstat                  statbuf
#define __NRAN0_fstat                  fd
#define __NRAN1_fstat                  statbuf
#define __NRAN0_fcntl                  fd
#define __NRAN1_fcntl                  command
#define __NRAN2_fcntl                  arg
#define __NRAN0_fadvise64              TODO_PROTOTYPE
#define __NRAN0_newfstatat             dirfd
#define __NRAN1_newfstatat             filename
#define __NRAN2_newfstatat             statbuf
#define __NRAN3_newfstatat             flags
#define __NRAN0_fstatfs                file
#define __NRAN1_fstatfs                buf
#define __NRAN0_statfs                 file
#define __NRAN1_statfs                 buf
#define __NRAN0_lseek                  fd
#define __NRAN1_lseek                  offset
#define __NRAN2_lseek                  whence
#define __NRAN0_mmap                   addr
#define __NRAN1_mmap                   len
#define __NRAN2_mmap                   prot
#define __NRAN3_mmap                   flags
#define __NRAN4_mmap                   fd
#define __NRAN5_mmap                   offset
#define __NRAN0_alarm                  seconds
#define __NRAN0_time                   timer
#define __NRAN0_utime                  filename
#define __NRAN1_utime                  times
#define __NRAN0_creat                  filename
#define __NRAN1_creat                  mode
#define __NRAN0_getdents               fd
#define __NRAN1_getdents               buf
#define __NRAN2_getdents               buflen
#define __NRAN0_futimesat              dirfd
#define __NRAN1_futimesat              filename
#define __NRAN2_futimesat              times
#define __NRAN0_select                 nfds
#define __NRAN1_select                 readfds
#define __NRAN2_select                 writefds
#define __NRAN3_select                 exceptfds
#define __NRAN4_select                 timeout
#define __NRAN0_poll                   fds
#define __NRAN1_poll                   nfds
#define __NRAN2_poll                   timeout
#define __NRAN0_epoll_wait             epfd
#define __NRAN1_epoll_wait             events
#define __NRAN2_epoll_wait             maxevents
#define __NRAN3_epoll_wait             timeout
#define __NRAN0_ustat                  dev
#define __NRAN1_ustat                  ubuf
#define __NRAN0_oldwait4               pid
#define __NRAN1_oldwait4               stat_loc
#define __NRAN2_oldwait4               options
#define __NRAN3_oldwait4               usage
#define __NRAN0_recv                   sockfd
#define __NRAN1_recv                   buf
#define __NRAN2_recv                   bufsize
#define __NRAN3_recv                   msg_flags
#define __NRAN0_send                   sockfd
#define __NRAN1_send                   buf
#define __NRAN2_send                   bufsize
#define __NRAN3_send                   msg_flags
#define __NRAN0_bdflush                TODO_PROTOTYPE
#define __NRAN0_umount                 special_file
#define __NRAN0_uselib                 library
#define __NRAN0__sysctl                TODO_PROTOTYPE
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_NAMES */
#endif /* __WANT_SYSCALL_ARGUMENT_NAMES */


/************************************************************************/
/* SYSCALL ARGUMENT FORMAT                                              */
/*  - __NRRTR_<name>       : ReturnTypeRepresentation                   */
/*  - __NRATR<argI>_<name> : ArgumentTypeRepresentation                 */
/*  - __NRATL<argI>_<name> : ArgumentTypeLink                           */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_FORMAT
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#define __NRATR0_io_setup               SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_io_setup                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_io_destroy             SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_io_destroy              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_io_submit              SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_io_submit               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_io_cancel              SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_io_cancel               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_io_getevents           SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_io_getevents            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setxattr               SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_setxattr               SC_REPR_STRING                                          /* name */ 
#define __NRATR2_setxattr               SC_REPR_BUFFER                                          /* buf */ 
#define __NRATL2_setxattr               3                                                       /* buf -> bufsize */ 
#define __NRATR3_setxattr               SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRATR4_setxattr               SC_REPR_XATTR_FLAGS                                     /* flags */ 
#define __NRRTR_setxattr                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_lsetxattr              SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_lsetxattr              SC_REPR_STRING                                          /* name */ 
#define __NRATR2_lsetxattr              SC_REPR_BUFFER                                          /* buf */ 
#define __NRATL2_lsetxattr              3                                                       /* buf -> bufsize */ 
#define __NRATR3_lsetxattr              SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRATR4_lsetxattr              SC_REPR_XATTR_FLAGS                                     /* flags */ 
#define __NRRTR_lsetxattr               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fsetxattr              SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_fsetxattr              SC_REPR_STRING                                          /* name */ 
#define __NRATR2_fsetxattr              SC_REPR_BUFFER                                          /* buf */ 
#define __NRATL2_fsetxattr              3                                                       /* buf -> bufsize */ 
#define __NRATR3_fsetxattr              SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRATR4_fsetxattr              SC_REPR_XATTR_FLAGS                                     /* flags */ 
#define __NRRTR_fsetxattr               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getxattr               SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_getxattr               SC_REPR_STRING                                          /* name */ 
#define __NRATR2_getxattr               SC_REPR_POINTER                                         /* buf */ 
#define __NRATR3_getxattr               SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRRTR_getxattr                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_lgetxattr              SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_lgetxattr              SC_REPR_STRING                                          /* name */ 
#define __NRATR2_lgetxattr              SC_REPR_POINTER                                         /* buf */ 
#define __NRATR3_lgetxattr              SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRRTR_lgetxattr               SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_fgetxattr              SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_fgetxattr              SC_REPR_STRING                                          /* name */ 
#define __NRATR2_fgetxattr              SC_REPR_POINTER                                         /* buf */ 
#define __NRATR3_fgetxattr              SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRRTR_fgetxattr               SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_listxattr              SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_listxattr              SC_REPR_POINTER                                         /* listbuf */ 
#define __NRATR2_listxattr              SC_REPR_SIZE_T                                          /* listbufsize */ 
#define __NRRTR_listxattr               SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_llistxattr             SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_llistxattr             SC_REPR_POINTER                                         /* listbuf */ 
#define __NRATR2_llistxattr             SC_REPR_SIZE_T                                          /* listbufsize */ 
#define __NRRTR_llistxattr              SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_flistxattr             SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_flistxattr             SC_REPR_POINTER                                         /* listbuf */ 
#define __NRATR2_flistxattr             SC_REPR_SIZE_T                                          /* listbufsize */ 
#define __NRRTR_flistxattr              SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_removexattr            SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_removexattr            SC_REPR_STRING                                          /* name */ 
#define __NRRTR_removexattr             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_lremovexattr           SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_lremovexattr           SC_REPR_STRING                                          /* name */ 
#define __NRRTR_lremovexattr            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fremovexattr           SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_fremovexattr           SC_REPR_STRING                                          /* name */ 
#define __NRRTR_fremovexattr            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getcwd                 SC_REPR_POINTER                                         /* buf */ 
#define __NRATR1_getcwd                 SC_REPR_SIZE_T                                          /* size */ 
#define __NRRTR_getcwd                  SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_lookup_dcookie         SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_lookup_dcookie          SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_eventfd2               SC_REPR_SYSCALL_ULONG_T                                 /* initval */ 
#define __NRATR1_eventfd2               SC_REPR_EVENTFD2_FLAGS                                  /* flags */ 
#define __NRRTR_eventfd2                SC_REPR_FD_T                                            /* return */
#define __NRATR0_epoll_create1          SC_REPR_EPOLL_CREATE1_FLAGS                             /* flags */ 
#define __NRRTR_epoll_create1           SC_REPR_FD_T                                            /* return */
#define __NRATR0_epoll_ctl              SC_REPR_FD_T                                            /* epfd */ 
#define __NRATR1_epoll_ctl              SC_REPR_EPOLL_OP                                        /* op */ 
#define __NRATR2_epoll_ctl              SC_REPR_FD_T                                            /* fd */ 
#define __NRATR3_epoll_ctl              SC_REPR_STRUCT_EPOLL_EVENT                              /* info */ 
#define __NRRTR_epoll_ctl               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_epoll_pwait            SC_REPR_FD_T                                            /* epfd */ 
#define __NRATR1_epoll_pwait            SC_REPR_POINTER                                         /* events */ 
#define __NRATR2_epoll_pwait            SC_REPR_SIZE_T                                          /* maxevents */ 
#define __NRATR3_epoll_pwait            SC_REPR_SYSCALL_SLONG_T                                 /* timeout */ 
#define __NRATR4_epoll_pwait            SC_REPR_STRUCT_SIGSET                                   /* ss */ 
#define __NRATL4_epoll_pwait            5                                                       /* ss -> sigsetsize */ 
#define __NRATR5_epoll_pwait            SC_REPR_SIZE_T                                          /* sigsetsize */ 
#define __NRRTR_epoll_pwait             SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_dup                    SC_REPR_FD_T                                            /* fd */ 
#define __NRRTR_dup                     SC_REPR_FD_T                                            /* return */
#define __NRATR0_dup3                   SC_REPR_FD_T                                            /* oldfd */ 
#define __NRATR1_dup3                   SC_REPR_FD_T                                            /* newfd */ 
#define __NRATR2_dup3                   SC_REPR_OFLAG__CLOEXEC__CLOFORK                         /* flags */ 
#define __NRRTR_dup3                    SC_REPR_FD_T                                            /* return */
#define __NRATR0_inotify_init1          SC_REPR_INOTIFY_INIT_FLAGS                              /* flags */ 
#define __NRRTR_inotify_init1           SC_REPR_FD_T                                            /* return */
#define __NRATR0_inotify_add_watch      SC_REPR_FD_T                                            /* notify_fd */ 
#define __NRATR1_inotify_add_watch      SC_REPR_STRING                                          /* pathname */ 
#define __NRATR2_inotify_add_watch      SC_REPR_INOTIFY_MASK                                    /* mask */ 
#define __NRRTR_inotify_add_watch       SC_REPR_INT                                             /* return */
#define __NRATR0_inotify_rm_watch       SC_REPR_FD_T                                            /* notify_fd */ 
#define __NRATR1_inotify_rm_watch       SC_REPR_INT                                             /* wd */ 
#define __NRRTR_inotify_rm_watch        SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_ioctl                  SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_ioctl                  SC_REPR_IOCTL_COMMAND                                   /* command */ 
#define __NRATR2_ioctl                  SC_REPR_IOCTL_ARG                                       /* arg */ 
#define __NRATL2_ioctl                  1                                                       /* arg -> command */ 
#define __NRRTR_ioctl                   SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_ioprio_set             SC_REPR_IOPRIO_WHO                                      /* who */ 
#define __NRATR1_ioprio_set             SC_REPR_IOPRIO_ID                                       /* id */ 
#define __NRATL1_ioprio_set             0                                                       /* id -> who */ 
#define __NRATR2_ioprio_set             SC_REPR_IOPRIO_VALUE                                    /* ioprio */ 
#define __NRRTR_ioprio_set              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_ioprio_get             SC_REPR_IOPRIO_WHO                                      /* who */ 
#define __NRATR1_ioprio_get             SC_REPR_IOPRIO_ID                                       /* id */ 
#define __NRATL1_ioprio_get             0                                                       /* id -> who */ 
#define __NRRTR_ioprio_get              SC_REPR_IOPRIO_VALUE                                    /* return */
#define __NRATR0_flock                  SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_flock                  SC_REPR_SYSCALL_ULONG_T                                 /* operation */ 
#define __NRRTR_flock                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mknodat                SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_mknodat                SC_REPR_FILENAME                                        /* nodename */ 
#define __NRATL1_mknodat                0                                                       /* nodename -> dirfd */ 
#define __NRATR2_mknodat                SC_REPR_MODE_T                                          /* mode */ 
#define __NRATR3_mknodat                SC_REPR_DEV_T                                           /* dev */ 
#define __NRATL3_mknodat                2                                                       /* dev -> mode */ 
#define __NRRTR_mknodat                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mkdirat                SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_mkdirat                SC_REPR_FILENAME                                        /* pathname */ 
#define __NRATL1_mkdirat                0                                                       /* pathname -> dirfd */ 
#define __NRATR2_mkdirat                SC_REPR_MODE_T                                          /* mode */ 
#define __NRRTR_mkdirat                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_unlinkat               SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_unlinkat               SC_REPR_FILENAME                                        /* name */ 
#define __NRATL1_unlinkat               0                                                       /* name -> dirfd */ 
#define __NRATR2_unlinkat               SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH           /* flags */ 
#define __NRRTR_unlinkat                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_symlinkat              SC_REPR_STRING                                          /* link_text */ 
#define __NRATR1_symlinkat              SC_REPR_FD_T                                            /* tofd */ 
#define __NRATR2_symlinkat              SC_REPR_FILENAME                                        /* target_path */ 
#define __NRATL2_symlinkat              1                                                       /* target_path -> tofd */ 
#define __NRRTR_symlinkat               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_linkat                 SC_REPR_FD_T                                            /* fromfd */ 
#define __NRATR1_linkat                 SC_REPR_FILENAME                                        /* existing_file */ 
#define __NRATL1_linkat                 0                                                       /* existing_file -> fromfd */ 
#define __NRATR2_linkat                 SC_REPR_FD_T                                            /* tofd */ 
#define __NRATR3_linkat                 SC_REPR_FILENAME                                        /* target_path */ 
#define __NRATL3_linkat                 2                                                       /* target_path -> tofd */ 
#define __NRATR4_linkat                 SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH     /* flags */ 
#define __NRRTR_linkat                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_renameat               SC_REPR_FD_T                                            /* oldfd */ 
#define __NRATR1_renameat               SC_REPR_FILENAME                                        /* oldname */ 
#define __NRATL1_renameat               0                                                       /* oldname -> oldfd */ 
#define __NRATR2_renameat               SC_REPR_FD_T                                            /* newfd */ 
#define __NRATR3_renameat               SC_REPR_FILENAME                                        /* newname_or_path */ 
#define __NRATL3_renameat               2                                                       /* newname_or_path -> newfd */ 
#define __NRRTR_renameat                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_umount2                SC_REPR_STRING                                          /* special_file */ 
#define __NRATR1_umount2                SC_REPR_SYSCALL_ULONG_T                                 /* flags */ 
#define __NRRTR_umount2                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mount                  SC_REPR_FILENAME                                        /* special_file */ 
#define __NRATR1_mount                  SC_REPR_FILENAME                                        /* dir */ 
#define __NRATR2_mount                  SC_REPR_STRING                                          /* fstype */ 
#define __NRATR3_mount                  SC_REPR_MOUNT_FLAGS                                     /* mountflags */ 
#define __NRATR4_mount                  SC_REPR_STRING                                          /* data */ 
#define __NRRTR_mount                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_pivot_root             SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_pivot_root              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_nfsservctl             SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_nfsservctl              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fallocate              SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_fallocate              SC_REPR_FALLOCATE_MODE                                  /* mode */ 
#define __NRATR2_fallocate              SC_REPR_SYSCALL_ULONG_T                                 /* offset */ 
#define __NRATR3_fallocate              SC_REPR_SYSCALL_ULONG_T                                 /* length */ 
#define __NRRTR_fallocate               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_faccessat              SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_faccessat              SC_REPR_FILENAME                                        /* filename */ 
#define __NRATL1_faccessat              0                                                       /* filename -> dirfd */ 
#define __NRATR2_faccessat              SC_REPR_ACCESS_TYPE                                     /* type */ 
#define __NRRTR_faccessat               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_chdir                  SC_REPR_FILENAME                                        /* path */ 
#define __NRRTR_chdir                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fchdir                 SC_REPR_FD_T                                            /* fd */ 
#define __NRRTR_fchdir                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_chroot                 SC_REPR_FILENAME                                        /* path */ 
#define __NRRTR_chroot                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fchmod                 SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_fchmod                 SC_REPR_MODE_T                                          /* mode */ 
#define __NRRTR_fchmod                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fchmodat               SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_fchmodat               SC_REPR_FILENAME                                        /* filename */ 
#define __NRATL1_fchmodat               0                                                       /* filename -> dirfd */ 
#define __NRATR2_fchmodat               SC_REPR_MODE_T                                          /* mode */ 
#define __NRATR3_fchmodat               SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH               /* flags */ 
#define __NRRTR_fchmodat                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fchownat               SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_fchownat               SC_REPR_FILENAME                                        /* filename */ 
#define __NRATL1_fchownat               0                                                       /* filename -> dirfd */ 
#define __NRATR2_fchownat               SC_REPR_UID_T                                           /* owner */ 
#define __NRATR3_fchownat               SC_REPR_GID_T                                           /* group */ 
#define __NRATR4_fchownat               SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH               /* flags */ 
#define __NRRTR_fchownat                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fchown                 SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_fchown                 SC_REPR_UID_T                                           /* owner */ 
#define __NRATR2_fchown                 SC_REPR_GID_T                                           /* group */ 
#define __NRRTR_fchown                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_openat                 SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_openat                 SC_REPR_FILENAME                                        /* filename */ 
#define __NRATL1_openat                 0                                                       /* filename -> dirfd */ 
#define __NRATR2_openat                 SC_REPR_OFLAG_T                                         /* oflags */ 
#define __NRATR3_openat                 SC_REPR_MODE_T                                          /* mode */ 
#define __NRATL3_openat                 2                                                       /* mode -> oflags */ 
#define __NRRTR_openat                  SC_REPR_FD_T                                            /* return */
#define __NRATR0_close                  SC_REPR_FD_T                                            /* fd */ 
#define __NRRTR_close                   SC_REPR_ERRNO_T                                         /* return */
#define __NRRTR_vhangup                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_pipe2                  SC_REPR_POINTER                                         /* pipedes */ 
#define __NRATR1_pipe2                  SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT       /* flags */ 
#define __NRRTR_pipe2                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_quotactl               SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_quotactl                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getdents64             SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_getdents64             SC_REPR_POINTER                                         /* buf */ 
#define __NRATR2_getdents64             SC_REPR_SIZE_T                                          /* buflen */ 
#define __NRRTR_getdents64              SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_read                   SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_read                   SC_REPR_POINTER                                         /* buf */ 
#define __NRATR2_read                   SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRRTR_read                    SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_write                  SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_write                  SC_REPR_BUFFER                                          /* buf */ 
#define __NRATL1_write                  2                                                       /* buf -> bufsize */ 
#define __NRATR2_write                  SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRRTR_write                   SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_readv                  SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_readv                  SC_REPR_STRUCT_IOVEC                                    /* iovec */ 
#define __NRATL1_readv                  2                                                       /* iovec -> count */ 
#define __NRATR2_readv                  SC_REPR_SIZE_T                                          /* count */ 
#define __NRRTR_readv                   SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_writev                 SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_writev                 SC_REPR_STRUCT_IOVEC_C                                  /* iovec */ 
#define __NRATL1_writev                 2                                                       /* iovec -> count */ 
#define __NRATR2_writev                 SC_REPR_SIZE_T                                          /* count */ 
#define __NRRTR_writev                  SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_pread64                SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_pread64                SC_REPR_POINTER                                         /* buf */ 
#define __NRATR2_pread64                SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRATR3_pread64                SC_REPR_UINT64_T                                        /* offset */ 
#define __NRRTR_pread64                 SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_pwrite64               SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_pwrite64               SC_REPR_BUFFER                                          /* buf */ 
#define __NRATL1_pwrite64               2                                                       /* buf -> bufsize */ 
#define __NRATR2_pwrite64               SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRATR3_pwrite64               SC_REPR_UINT64_T                                        /* offset */ 
#define __NRRTR_pwrite64                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_preadv                 SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_preadv                 SC_REPR_STRUCT_IOVEC                                    /* iovec */ 
#define __NRATL1_preadv                 2                                                       /* iovec -> count */ 
#define __NRATR2_preadv                 SC_REPR_SIZE_T                                          /* count */ 
#define __NRATR3_preadv                 SC_REPR_UINT64_T                                        /* offset */ 
#define __NRRTR_preadv                  SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_pwritev                SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_pwritev                SC_REPR_STRUCT_IOVEC_C                                  /* iovec */ 
#define __NRATL1_pwritev                2                                                       /* iovec -> count */ 
#define __NRATR2_pwritev                SC_REPR_SIZE_T                                          /* count */ 
#define __NRATR3_pwritev                SC_REPR_UINT64_T                                        /* offset */ 
#define __NRRTR_pwritev                 SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_pselect6               SC_REPR_SIZE_T                                          /* nfds */ 
#define __NRATR1_pselect6               SC_REPR_STRUCT_FDSET                                    /* readfds */ 
#define __NRATL1_pselect6               0                                                       /* readfds -> nfds */ 
#define __NRATR2_pselect6               SC_REPR_STRUCT_FDSET                                    /* writefds */ 
#define __NRATL2_pselect6               0                                                       /* writefds -> nfds */ 
#define __NRATR3_pselect6               SC_REPR_STRUCT_FDSET                                    /* exceptfds */ 
#define __NRATL3_pselect6               0                                                       /* exceptfds -> nfds */ 
#define __NRATR4_pselect6               SC_REPR_STRUCT_TIMESPEC                                 /* timeout */ 
#define __NRATR5_pselect6               SC_REPR_STRUCT_SIGSET_WITH_SIZE                         /* sigmask_sigset_with_size */ 
#define __NRRTR_pselect6                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_ppoll                  SC_REPR_STRUCT_POLLFD                                   /* fds */ 
#define __NRATL0_ppoll                  1                                                       /* fds -> nfds */ 
#define __NRATR1_ppoll                  SC_REPR_SIZE_T                                          /* nfds */ 
#define __NRATR2_ppoll                  SC_REPR_STRUCT_TIMESPEC                                 /* timeout_ts */ 
#define __NRATR3_ppoll                  SC_REPR_STRUCT_SIGSET                                   /* sigmask */ 
#define __NRATL3_ppoll                  4                                                       /* sigmask -> sigsetsize */ 
#define __NRATR4_ppoll                  SC_REPR_SIZE_T                                          /* sigsetsize */ 
#define __NRRTR_ppoll                   SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_signalfd4              SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_signalfd4              SC_REPR_STRUCT_SIGSET                                   /* sigmask */ 
#define __NRATL1_signalfd4              2                                                       /* sigmask -> sigmasksize */ 
#define __NRATR2_signalfd4              SC_REPR_SIZE_T                                          /* sigmasksize */ 
#define __NRATR3_signalfd4              SC_REPR_SIGNALFD4_FLAGS                                 /* flags */ 
#define __NRRTR_signalfd4               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_vmsplice               SC_REPR_FD_T                                            /* fdout */ 
#define __NRATR1_vmsplice               SC_REPR_STRUCT_IOVEC_C                                  /* iov */ 
#define __NRATL1_vmsplice               2                                                       /* iov -> count */ 
#define __NRATR2_vmsplice               SC_REPR_SIZE_T                                          /* count */ 
#define __NRATR3_vmsplice               SC_REPR_SPLICE_FLAGS                                    /* flags */ 
#define __NRRTR_vmsplice                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_splice                 SC_REPR_FD_T                                            /* fdin */ 
#define __NRATR1_splice                 SC_REPR_POINTER                                         /* offin */ 
#define __NRATR2_splice                 SC_REPR_FD_T                                            /* fdout */ 
#define __NRATR3_splice                 SC_REPR_POINTER                                         /* offout */ 
#define __NRATR4_splice                 SC_REPR_SIZE_T                                          /* length */ 
#define __NRATR5_splice                 SC_REPR_SPLICE_FLAGS                                    /* flags */ 
#define __NRRTR_splice                  SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_tee                    SC_REPR_FD_T                                            /* fdin */ 
#define __NRATR1_tee                    SC_REPR_FD_T                                            /* fdout */ 
#define __NRATR2_tee                    SC_REPR_SIZE_T                                          /* length */ 
#define __NRATR3_tee                    SC_REPR_SPLICE_FLAGS                                    /* flags */ 
#define __NRRTR_tee                     SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_readlinkat             SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_readlinkat             SC_REPR_FILENAME                                        /* path */ 
#define __NRATL1_readlinkat             0                                                       /* path -> dirfd */ 
#define __NRATR2_readlinkat             SC_REPR_POINTER                                         /* buf */ 
#define __NRATR3_readlinkat             SC_REPR_SIZE_T                                          /* buflen */ 
#define __NRRTR_readlinkat              SC_REPR_SSIZE_T                                         /* return */
#define __NRRTR_sync                    SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fsync                  SC_REPR_FD_T                                            /* fd */ 
#define __NRRTR_fsync                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fdatasync              SC_REPR_FD_T                                            /* fd */ 
#define __NRRTR_fdatasync               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sync_file_range        SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_sync_file_range        SC_REPR_UINT64_T                                        /* offset */ 
#define __NRATR2_sync_file_range        SC_REPR_UINT64_T                                        /* count */ 
#define __NRATR3_sync_file_range        SC_REPR_SYNC_FILE_RANGE_FLAGS                           /* flags */ 
#define __NRRTR_sync_file_range         SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_timerfd_create         SC_REPR_CLOCKID_T                                       /* clock_id */ 
#define __NRATR1_timerfd_create         SC_REPR_TIMERFD_FLAGS                                   /* flags */ 
#define __NRRTR_timerfd_create          SC_REPR_FD_T                                            /* return */
#define __NRATR0_timerfd_settime        SC_REPR_FD_T                                            /* timerfd */ 
#define __NRATR1_timerfd_settime        SC_REPR_TIMERFD_TIMER_FLAGS                             /* flags */ 
#define __NRATR2_timerfd_settime        SC_REPR_STRUCT_ITIMERSPEC                               /* utmr */ 
#define __NRATR3_timerfd_settime        SC_REPR_POINTER                                         /* otmr */ 
#define __NRRTR_timerfd_settime         SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_timerfd_gettime        SC_REPR_FD_T                                            /* timerfd */ 
#define __NRATR1_timerfd_gettime        SC_REPR_POINTER                                         /* otmr */ 
#define __NRRTR_timerfd_gettime         SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_utimensat              SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_utimensat              SC_REPR_FILENAME                                        /* filename */ 
#define __NRATL1_utimensat              0                                                       /* filename -> dirfd */ 
#define __NRATR2_utimensat              SC_REPR_STRUCT_TIMESPEC_VEC2_OR_3                       /* times */ 
#define __NRATL2_utimensat              3                                                       /* times -> flags */ 
#define __NRATR3_utimensat              SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_BTIME__DOSPATH /* flags */ 
#define __NRRTR_utimensat               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_acct                   SC_REPR_FILENAME                                        /* filename */ 
#define __NRRTR_acct                    SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_capget                 SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_capget                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_capset                 SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_capset                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_personality            SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_personality             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_exit                   SC_REPR_EXIT_STATUS                                     /* exit_code */ 
#define __NRRTR_exit                    SC_REPR_SIGNO_T                                         /* return */
#define __NRATR0_exit_group             SC_REPR_EXIT_STATUS                                     /* exit_code */ 
#define __NRRTR_exit_group              SC_REPR_SIGNO_T                                         /* return */
#define __NRATR0_waitid                 SC_REPR_IDTYPE_T                                        /* idtype */ 
#define __NRATR1_waitid                 SC_REPR_ID_T                                            /* id */ 
#define __NRATL1_waitid                 0                                                       /* id -> idtype */ 
#define __NRATR2_waitid                 SC_REPR_POINTER                                         /* infop */ 
#define __NRATR3_waitid                 SC_REPR_WAITFLAGS                                       /* options */ 
#define __NRATR4_waitid                 SC_REPR_POINTER                                         /* ru */ 
#define __NRRTR_waitid                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_set_tid_address        SC_REPR_POINTER                                         /* tidptr */ 
#define __NRRTR_set_tid_address         SC_REPR_PID_T                                           /* return */
#define __NRATR0_unshare                SC_REPR_CLONE_FLAGS_UNSHARE                             /* what */ 
#define __NRRTR_unshare                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_futex                  SC_REPR_POINTER                                         /* uaddr */ 
#define __NRATR1_futex                  SC_REPR_FUTEX_OP                                        /* futex_op */ 
#define __NRATR2_futex                  SC_REPR_UINT32_T                                        /* val */ 
#define __NRATR3_futex                  SC_REPR_STRUCT_TIMESPEC_OR_UINT32                       /* timeout_or_val2 */ 
#define __NRATL3_futex                  1                                                       /* timeout_or_val2 -> futex_op */ 
#define __NRATR4_futex                  SC_REPR_POINTER                                         /* uaddr2 */ 
#define __NRATR5_futex                  SC_REPR_UINT32_T                                        /* val3 */ 
#define __NRRTR_futex                   SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_set_robust_list        SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_set_robust_list         SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_get_robust_list        SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_get_robust_list         SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_nanosleep              SC_REPR_STRUCT_TIMESPEC                                 /* req */ 
#define __NRATR1_nanosleep              SC_REPR_POINTER                                         /* rem */ 
#define __NRRTR_nanosleep               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getitimer              SC_REPR_ITIMER_WHICH                                    /* which */ 
#define __NRATR1_getitimer              SC_REPR_POINTER                                         /* curr_value */ 
#define __NRRTR_getitimer               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setitimer              SC_REPR_ITIMER_WHICH                                    /* which */ 
#define __NRATR1_setitimer              SC_REPR_STRUCT_ITIMERVAL                                /* newval */ 
#define __NRATR2_setitimer              SC_REPR_POINTER                                         /* oldval */ 
#define __NRRTR_setitimer               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_kexec_load             SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_kexec_load              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_init_module            SC_REPR_POINTER                                         /* module_image */ 
#define __NRATR1_init_module            SC_REPR_SIZE_T                                          /* len */ 
#define __NRATR2_init_module            SC_REPR_STRING                                          /* uargs */ 
#define __NRRTR_init_module             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_delete_module          SC_REPR_STRING                                          /* name */ 
#define __NRATR1_delete_module          SC_REPR_OFLAG_T                                         /* flags */ 
#define __NRRTR_delete_module           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_timer_create           SC_REPR_CLOCKID_T                                       /* clock_id */ 
#define __NRATR1_timer_create           SC_REPR_POINTER                                         /* evp */ 
#define __NRATR2_timer_create           SC_REPR_POINTER                                         /* timerid */ 
#define __NRRTR_timer_create            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_timer_gettime          SC_REPR_TIMER_T                                         /* timerid */ 
#define __NRATR1_timer_gettime          SC_REPR_POINTER                                         /* value */ 
#define __NRRTR_timer_gettime           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_timer_getoverrun       SC_REPR_TIMER_T                                         /* timerid */ 
#define __NRRTR_timer_getoverrun        SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_timer_settime          SC_REPR_TIMER_T                                         /* timerid */ 
#define __NRATR1_timer_settime          SC_REPR_TIMER_FLAGS                                     /* flags */ 
#define __NRATR2_timer_settime          SC_REPR_STRUCT_ITIMERSPEC                               /* value */ 
#define __NRATR3_timer_settime          SC_REPR_POINTER                                         /* ovalue */ 
#define __NRRTR_timer_settime           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_timer_delete           SC_REPR_TIMER_T                                         /* timerid */ 
#define __NRRTR_timer_delete            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_clock_settime          SC_REPR_CLOCKID_T                                       /* clock_id */ 
#define __NRATR1_clock_settime          SC_REPR_STRUCT_TIMESPEC                                 /* tp */ 
#define __NRRTR_clock_settime           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_clock_gettime          SC_REPR_CLOCKID_T                                       /* clock_id */ 
#define __NRATR1_clock_gettime          SC_REPR_POINTER                                         /* tp */ 
#define __NRRTR_clock_gettime           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_clock_getres           SC_REPR_CLOCKID_T                                       /* clock_id */ 
#define __NRATR1_clock_getres           SC_REPR_POINTER                                         /* res */ 
#define __NRRTR_clock_getres            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_clock_nanosleep        SC_REPR_CLOCKID_T                                       /* clock_id */ 
#define __NRATR1_clock_nanosleep        SC_REPR_TIMER_FLAGS                                     /* flags */ 
#define __NRATR2_clock_nanosleep        SC_REPR_STRUCT_TIMESPEC                                 /* requested_time */ 
#define __NRATR3_clock_nanosleep        SC_REPR_POINTER                                         /* remaining */ 
#define __NRRTR_clock_nanosleep         SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_syslog                 SC_REPR_SYSLOG_LEVEL                                    /* level */ 
#define __NRATR1_syslog                 SC_REPR_STRING                                          /* str */ 
#define __NRATL1_syslog                 2                                                       /* str -> len */ 
#define __NRATR2_syslog                 SC_REPR_SIZE_T                                          /* len */ 
#define __NRRTR_syslog                  SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_ptrace                 SC_REPR_SYSCALL_ULONG_T                                 /* request */ 
#define __NRATR1_ptrace                 SC_REPR_PID_T                                           /* pid */ 
#define __NRATR2_ptrace                 SC_REPR_POINTER                                         /* addr */ 
#define __NRATR3_ptrace                 SC_REPR_POINTER                                         /* data */ 
#define __NRRTR_ptrace                  SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_sched_setparam         SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_sched_setparam         SC_REPR_STRUCT_SCHED_PARAM                              /* param */ 
#define __NRRTR_sched_setparam          SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sched_setscheduler     SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_sched_setscheduler     SC_REPR_SCHED_POLICY                                    /* policy */ 
#define __NRATR2_sched_setscheduler     SC_REPR_STRUCT_SCHED_PARAM                              /* param */ 
#define __NRRTR_sched_setscheduler      SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sched_getscheduler     SC_REPR_PID_T                                           /* pid */ 
#define __NRRTR_sched_getscheduler      SC_REPR_SCHED_POLICY                                    /* return */
#define __NRATR0_sched_getparam         SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_sched_getparam         SC_REPR_POINTER                                         /* param */ 
#define __NRRTR_sched_getparam          SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sched_setaffinity      SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_sched_setaffinity      SC_REPR_SIZE_T                                          /* cpusetsize */ 
#define __NRATR2_sched_setaffinity      SC_REPR_CPUSET                                          /* cpuset */ 
#define __NRATL2_sched_setaffinity      1                                                       /* cpuset -> cpusetsize */ 
#define __NRRTR_sched_setaffinity       SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sched_getaffinity      SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_sched_getaffinity      SC_REPR_SIZE_T                                          /* cpusetsize */ 
#define __NRATR2_sched_getaffinity      SC_REPR_POINTER                                         /* cpuset */ 
#define __NRRTR_sched_getaffinity       SC_REPR_ERRNO_T                                         /* return */
#define __NRRTR_sched_yield             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sched_get_priority_max SC_REPR_SCHED_POLICY                                    /* algorithm */ 
#define __NRRTR_sched_get_priority_max  SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_sched_get_priority_min SC_REPR_SCHED_POLICY                                    /* algorithm */ 
#define __NRRTR_sched_get_priority_min  SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_sched_rr_get_interval  SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_sched_rr_get_interval  SC_REPR_POINTER                                         /* ts */ 
#define __NRRTR_sched_rr_get_interval   SC_REPR_ERRNO_T                                         /* return */
#define __NRRTR_restart_syscall         SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_kill                   SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_kill                   SC_REPR_SIGNO_T                                         /* signo */ 
#define __NRRTR_kill                    SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_tkill                  SC_REPR_PID_T                                           /* tid */ 
#define __NRATR1_tkill                  SC_REPR_SIGNO_T                                         /* signo */ 
#define __NRRTR_tkill                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_tgkill                 SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_tgkill                 SC_REPR_PID_T                                           /* tid */ 
#define __NRATR2_tgkill                 SC_REPR_SIGNO_T                                         /* signo */ 
#define __NRRTR_tgkill                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sigaltstack            SC_REPR_STRUCT_SIGALTSTACK                              /* ss */ 
#define __NRATR1_sigaltstack            SC_REPR_POINTER                                         /* oss */ 
#define __NRRTR_sigaltstack             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_rt_sigsuspend          SC_REPR_STRUCT_SIGSET                                   /* set */ 
#define __NRATL0_rt_sigsuspend          1                                                       /* set -> sigsetsize */ 
#define __NRATR1_rt_sigsuspend          SC_REPR_SIZE_T                                          /* sigsetsize */ 
#define __NRRTR_rt_sigsuspend           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_rt_sigaction           SC_REPR_SIGNO_T                                         /* signo */ 
#define __NRATR1_rt_sigaction           SC_REPR_STRUCT_KERNEL_SIGACTION                         /* act */ 
#define __NRATL1_rt_sigaction           3                                                       /* act -> sigsetsize */ 
#define __NRATR2_rt_sigaction           SC_REPR_POINTER                                         /* oact */ 
#define __NRATR3_rt_sigaction           SC_REPR_SIZE_T                                          /* sigsetsize */ 
#define __NRRTR_rt_sigaction            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_rt_sigprocmask         SC_REPR_SIGPROCMASK_HOW                                 /* how */ 
#define __NRATR1_rt_sigprocmask         SC_REPR_STRUCT_SIGSET                                   /* set */ 
#define __NRATL1_rt_sigprocmask         3                                                       /* set -> sigsetsize */ 
#define __NRATR2_rt_sigprocmask         SC_REPR_POINTER                                         /* oset */ 
#define __NRATR3_rt_sigprocmask         SC_REPR_SIZE_T                                          /* sigsetsize */ 
#define __NRRTR_rt_sigprocmask          SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_rt_sigpending          SC_REPR_POINTER                                         /* set */ 
#define __NRATR1_rt_sigpending          SC_REPR_SIZE_T                                          /* sigsetsize */ 
#define __NRRTR_rt_sigpending           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_rt_sigtimedwait        SC_REPR_STRUCT_SIGSET                                   /* set */ 
#define __NRATL0_rt_sigtimedwait        3                                                       /* set -> sigsetsize */ 
#define __NRATR1_rt_sigtimedwait        SC_REPR_POINTER                                         /* info */ 
#define __NRATR2_rt_sigtimedwait        SC_REPR_STRUCT_TIMESPEC                                 /* timeout */ 
#define __NRATR3_rt_sigtimedwait        SC_REPR_SIZE_T                                          /* sigsetsize */ 
#define __NRRTR_rt_sigtimedwait         SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_rt_sigqueueinfo        SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_rt_sigqueueinfo        SC_REPR_SIGNO_T                                         /* usigno */ 
#define __NRATR2_rt_sigqueueinfo        SC_REPR_STRUCT_SIGINFO                                  /* uinfo */ 
#define __NRRTR_rt_sigqueueinfo         SC_REPR_ERRNO_T                                         /* return */
#define __NRRTR_rt_sigreturn            SC_REPR_SIGNO_T                                         /* return */
#define __NRATR0_setpriority            SC_REPR_SCHED_PRIORITY_WHICH                            /* which */ 
#define __NRATR1_setpriority            SC_REPR_ID_T                                            /* who */ 
#define __NRATR2_setpriority            SC_REPR_SYSCALL_ULONG_T                                 /* value */ 
#define __NRRTR_setpriority             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getpriority            SC_REPR_SCHED_PRIORITY_WHICH                            /* which */ 
#define __NRATR1_getpriority            SC_REPR_ID_T                                            /* who */ 
#define __NRRTR_getpriority             SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_reboot                 SC_REPR_REBOOT_HOW                                      /* how */ 
#define __NRRTR_reboot                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setregid               SC_REPR_GID_T                                           /* rgid */ 
#define __NRATR1_setregid               SC_REPR_GID_T                                           /* egid */ 
#define __NRRTR_setregid                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setgid                 SC_REPR_GID_T                                           /* gid */ 
#define __NRRTR_setgid                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setreuid               SC_REPR_UID_T                                           /* ruid */ 
#define __NRATR1_setreuid               SC_REPR_UID_T                                           /* euid */ 
#define __NRRTR_setreuid                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setuid                 SC_REPR_UID_T                                           /* uid */ 
#define __NRRTR_setuid                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setresuid              SC_REPR_UID_T                                           /* ruid */ 
#define __NRATR1_setresuid              SC_REPR_UID_T                                           /* euid */ 
#define __NRATR2_setresuid              SC_REPR_UID_T                                           /* suid */ 
#define __NRRTR_setresuid               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getresuid              SC_REPR_POINTER                                         /* ruid */ 
#define __NRATR1_getresuid              SC_REPR_POINTER                                         /* euid */ 
#define __NRATR2_getresuid              SC_REPR_POINTER                                         /* suid */ 
#define __NRRTR_getresuid               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setresgid              SC_REPR_GID_T                                           /* rgid */ 
#define __NRATR1_setresgid              SC_REPR_GID_T                                           /* egid */ 
#define __NRATR2_setresgid              SC_REPR_GID_T                                           /* sgid */ 
#define __NRRTR_setresgid               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getresgid              SC_REPR_POINTER                                         /* rgid */ 
#define __NRATR1_getresgid              SC_REPR_POINTER                                         /* egid */ 
#define __NRATR2_getresgid              SC_REPR_POINTER                                         /* sgid */ 
#define __NRRTR_getresgid               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setfsuid               SC_REPR_UID_T                                           /* uid */ 
#define __NRRTR_setfsuid                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setfsgid               SC_REPR_GID_T                                           /* gid */ 
#define __NRRTR_setfsgid                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_times                  SC_REPR_POINTER                                         /* buf */ 
#define __NRRTR_times                   SC_REPR_SIGNO_T                                         /* return */
#define __NRATR0_setpgid                SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_setpgid                SC_REPR_PID_T                                           /* pgid */ 
#define __NRRTR_setpgid                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getpgid                SC_REPR_PID_T                                           /* pid */ 
#define __NRRTR_getpgid                 SC_REPR_PID_T                                           /* return */
#define __NRATR0_getsid                 SC_REPR_PID_T                                           /* pid */ 
#define __NRRTR_getsid                  SC_REPR_PID_T                                           /* return */
#define __NRRTR_setsid                  SC_REPR_PID_T                                           /* return */
#define __NRATR0_getgroups              SC_REPR_SIZE_T                                          /* count */ 
#define __NRATR1_getgroups              SC_REPR_POINTER                                         /* list */ 
#define __NRRTR_getgroups               SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_setgroups              SC_REPR_SIZE_T                                          /* count */ 
#define __NRATR1_setgroups              SC_REPR_GID_VECTOR                                      /* groups */ 
#define __NRATL1_setgroups              0                                                       /* groups -> count */ 
#define __NRRTR_setgroups               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_uname                  SC_REPR_POINTER                                         /* name */ 
#define __NRRTR_uname                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sethostname            SC_REPR_STRING                                          /* name */ 
#define __NRATL0_sethostname            1                                                       /* name -> len */ 
#define __NRATR1_sethostname            SC_REPR_SIZE_T                                          /* len */ 
#define __NRRTR_sethostname             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setdomainname          SC_REPR_STRING                                          /* name */ 
#define __NRATL0_setdomainname          1                                                       /* name -> len */ 
#define __NRATR1_setdomainname          SC_REPR_SIZE_T                                          /* len */ 
#define __NRRTR_setdomainname           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getrlimit              SC_REPR_RLIMIT_RESOURCE                                 /* resource */ 
#define __NRATR1_getrlimit              SC_REPR_POINTER                                         /* rlimits */ 
#define __NRRTR_getrlimit               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setrlimit              SC_REPR_RLIMIT_RESOURCE                                 /* resource */ 
#define __NRATR1_setrlimit              SC_REPR_STRUCT_RLIMIT                                   /* rlimits */ 
#define __NRRTR_setrlimit               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getrusage              SC_REPR_GETRUSAGE_WHO                                   /* who */ 
#define __NRATR1_getrusage              SC_REPR_POINTER                                         /* usage */ 
#define __NRRTR_getrusage               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_umask                  SC_REPR_MODE_T                                          /* mode */ 
#define __NRRTR_umask                   SC_REPR_MODE_T                                          /* return */
#define __NRATR0_prctl                  SC_REPR_PRCTL_COMMAND                                   /* command */ 
#define __NRATR1_prctl                  SC_REPR_SYSCALL_ULONG_T                                 /* arg2 */ 
#define __NRATR2_prctl                  SC_REPR_SYSCALL_ULONG_T                                 /* arg3 */ 
#define __NRATR3_prctl                  SC_REPR_SYSCALL_ULONG_T                                 /* arg4 */ 
#define __NRATR4_prctl                  SC_REPR_SYSCALL_ULONG_T                                 /* arg5 */ 
#define __NRRTR_prctl                   SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_getcpu                 SC_REPR_POINTER                                         /* cpu */ 
#define __NRATR1_getcpu                 SC_REPR_POINTER                                         /* node */ 
#define __NRATR2_getcpu                 SC_REPR_POINTER                                         /* tcache */ 
#define __NRRTR_getcpu                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_gettimeofday           SC_REPR_POINTER                                         /* tv */ 
#define __NRATR1_gettimeofday           SC_REPR_POINTER                                         /* tz */ 
#define __NRRTR_gettimeofday            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_settimeofday           SC_REPR_STRUCT_TIMEVAL                                  /* tv */ 
#define __NRATR1_settimeofday           SC_REPR_STRUCT_TIMEZONE                                 /* tz */ 
#define __NRRTR_settimeofday            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_adjtimex               SC_REPR_POINTER                                         /* ntx */ 
#define __NRRTR_adjtimex                SC_REPR_ERRNO_T                                         /* return */
#define __NRRTR_getpid                  SC_REPR_PID_T                                           /* return */
#define __NRRTR_getppid                 SC_REPR_PID_T                                           /* return */
#define __NRRTR_getuid                  SC_REPR_UID_T                                           /* return */
#define __NRRTR_geteuid                 SC_REPR_UID_T                                           /* return */
#define __NRRTR_getgid                  SC_REPR_GID_T                                           /* return */
#define __NRRTR_getegid                 SC_REPR_GID_T                                           /* return */
#define __NRRTR_gettid                  SC_REPR_PID_T                                           /* return */
#define __NRATR0_sysinfo                SC_REPR_POINTER                                         /* info */ 
#define __NRRTR_sysinfo                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mq_open                SC_REPR_STRING                                          /* name */ 
#define __NRATR1_mq_open                SC_REPR_OFLAG_T                                         /* oflags */ 
#define __NRATR2_mq_open                SC_REPR_MODE_T                                          /* mode */ 
#define __NRATL2_mq_open                1                                                       /* mode -> oflags */ 
#define __NRRTR_mq_open                 SC_REPR_FD_T                                            /* return */
#define __NRATR0_mq_unlink              SC_REPR_STRING                                          /* name */ 
#define __NRRTR_mq_unlink               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mq_timedsend           SC_REPR_FD_T                                            /* mqdes */ 
#define __NRATR1_mq_timedsend           SC_REPR_BUFFER                                          /* msg_ptr */ 
#define __NRATL1_mq_timedsend           2                                                       /* msg_ptr -> msg_len */ 
#define __NRATR2_mq_timedsend           SC_REPR_SIZE_T                                          /* msg_len */ 
#define __NRATR3_mq_timedsend           SC_REPR_UINT32_T                                        /* msg_prio */ 
#define __NRATR4_mq_timedsend           SC_REPR_STRUCT_TIMESPEC                                 /* abs_timeout */ 
#define __NRRTR_mq_timedsend            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mq_timedreceive        SC_REPR_FD_T                                            /* mqdes */ 
#define __NRATR1_mq_timedreceive        SC_REPR_POINTER                                         /* msg_ptr */ 
#define __NRATR2_mq_timedreceive        SC_REPR_SIZE_T                                          /* msg_len */ 
#define __NRATR3_mq_timedreceive        SC_REPR_POINTER                                         /* pmsg_prio */ 
#define __NRATR4_mq_timedreceive        SC_REPR_STRUCT_TIMESPEC                                 /* abs_timeout */ 
#define __NRRTR_mq_timedreceive         SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_mq_notify              SC_REPR_FD_T                                            /* mqdes */ 
#define __NRATR1_mq_notify              SC_REPR_STRUCT_SIGEVENT                                 /* notification */ 
#define __NRRTR_mq_notify               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mq_getsetattr          SC_REPR_FD_T                                            /* mqdes */ 
#define __NRATR1_mq_getsetattr          SC_REPR_STRUCT_MQ_ATTR                                  /* newattr */ 
#define __NRATR2_mq_getsetattr          SC_REPR_POINTER                                         /* oldattr */ 
#define __NRRTR_mq_getsetattr           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_msgget                 SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_msgget                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_msgctl                 SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_msgctl                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_msgrcv                 SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_msgrcv                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_msgsnd                 SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_msgsnd                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_semget                 SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_semget                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_semctl                 SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_semctl                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_semtimedop             SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_semtimedop              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_semop                  SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_semop                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_shmget                 SC_REPR_SIGNO_T                                         /* key */ 
#define __NRATR1_shmget                 SC_REPR_SIZE_T                                          /* size */ 
#define __NRATR2_shmget                 SC_REPR_SYSCALL_ULONG_T                                 /* shmflg */ 
#define __NRRTR_shmget                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_shmctl                 SC_REPR_SYSCALL_ULONG_T                                 /* shmid */ 
#define __NRATR1_shmctl                 SC_REPR_SYSCALL_ULONG_T                                 /* cmd */ 
#define __NRATR2_shmctl                 SC_REPR_POINTER                                         /* buf */ 
#define __NRRTR_shmctl                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_shmat                  SC_REPR_SYSCALL_ULONG_T                                 /* shmid */ 
#define __NRATR1_shmat                  SC_REPR_POINTER                                         /* shmaddr */ 
#define __NRATR2_shmat                  SC_REPR_SYSCALL_ULONG_T                                 /* shmflg */ 
#define __NRRTR_shmat                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_shmdt                  SC_REPR_POINTER                                         /* shmaddr */ 
#define __NRRTR_shmdt                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_socket                 SC_REPR_SOCKET_DOMAIN                                   /* domain */ 
#define __NRATR1_socket                 SC_REPR_SOCKET_TYPE                                     /* type */ 
#define __NRATR2_socket                 SC_REPR_SOCKET_PROTOCOL                                 /* protocol */ 
#define __NRATL2_socket                 0                                                       /* protocol -> domain */ 
#define __NRRTR_socket                  SC_REPR_FD_T                                            /* return */
#define __NRATR0_socketpair             SC_REPR_SOCKET_DOMAIN                                   /* domain */ 
#define __NRATR1_socketpair             SC_REPR_SOCKET_TYPE                                     /* type */ 
#define __NRATR2_socketpair             SC_REPR_SOCKET_PROTOCOL                                 /* protocol */ 
#define __NRATL2_socketpair             0                                                       /* protocol -> domain */ 
#define __NRATR3_socketpair             SC_REPR_POINTER                                         /* fds */ 
#define __NRRTR_socketpair              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_bind                   SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_bind                   SC_REPR_STRUCT_SOCKADDR                                 /* addr */ 
#define __NRATL1_bind                   2                                                       /* addr -> addr_len */ 
#define __NRATR2_bind                   SC_REPR_SOCKLEN_T                                       /* addr_len */ 
#define __NRRTR_bind                    SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_listen                 SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_listen                 SC_REPR_SYSCALL_ULONG_T                                 /* max_backlog */ 
#define __NRRTR_listen                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_accept                 SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_accept                 SC_REPR_POINTER                                         /* addr */ 
#define __NRATR2_accept                 SC_REPR_POINTER                                         /* addr_len */ 
#define __NRRTR_accept                  SC_REPR_FD_T                                            /* return */
#define __NRATR0_connect                SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_connect                SC_REPR_STRUCT_SOCKADDR                                 /* addr */ 
#define __NRATL1_connect                2                                                       /* addr -> addr_len */ 
#define __NRATR2_connect                SC_REPR_SOCKLEN_T                                       /* addr_len */ 
#define __NRRTR_connect                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getsockname            SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_getsockname            SC_REPR_POINTER                                         /* addr */ 
#define __NRATR2_getsockname            SC_REPR_POINTER                                         /* addr_len */ 
#define __NRRTR_getsockname             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getpeername            SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_getpeername            SC_REPR_POINTER                                         /* addr */ 
#define __NRATR2_getpeername            SC_REPR_POINTER                                         /* addr_len */ 
#define __NRRTR_getpeername             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sendto                 SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_sendto                 SC_REPR_BUFFER                                          /* buf */ 
#define __NRATL1_sendto                 2                                                       /* buf -> bufsize */ 
#define __NRATR2_sendto                 SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRATR3_sendto                 SC_REPR_SOCKET_SENDMSG_FLAGS                            /* msg_flags */ 
#define __NRATR4_sendto                 SC_REPR_STRUCT_SOCKADDR                                 /* addr */ 
#define __NRATL4_sendto                 5                                                       /* addr -> addr_len */ 
#define __NRATR5_sendto                 SC_REPR_SOCKLEN_T                                       /* addr_len */ 
#define __NRRTR_sendto                  SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_recvfrom               SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_recvfrom               SC_REPR_POINTER                                         /* buf */ 
#define __NRATR2_recvfrom               SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRATR3_recvfrom               SC_REPR_SOCKET_RECVMSG_FLAGS                            /* msg_flags */ 
#define __NRATR4_recvfrom               SC_REPR_POINTER                                         /* addr */ 
#define __NRATR5_recvfrom               SC_REPR_POINTER                                         /* addr_len */ 
#define __NRRTR_recvfrom                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_setsockopt             SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_setsockopt             SC_REPR_SOCKOPT_LEVEL                                   /* level */ 
#define __NRATR2_setsockopt             SC_REPR_SOCKOPT_OPTNAME                                 /* optname */ 
#define __NRATL2_setsockopt             1                                                       /* optname -> level */ 
#define __NRATR3_setsockopt             SC_REPR_SOCKOPT_OPTVAL                                  /* optval */ 
#define __NRATL3_setsockopt             4                                                       /* optval -> optlen */ 
#define __NRATR4_setsockopt             SC_REPR_SOCKLEN_T                                       /* optlen */ 
#define __NRATL4_setsockopt             2                                                       /* optlen -> optname */ 
#define __NRRTR_setsockopt              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getsockopt             SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_getsockopt             SC_REPR_SOCKOPT_LEVEL                                   /* level */ 
#define __NRATR2_getsockopt             SC_REPR_SOCKOPT_OPTNAME                                 /* optname */ 
#define __NRATL2_getsockopt             1                                                       /* optname -> level */ 
#define __NRATR3_getsockopt             SC_REPR_POINTER                                         /* optval */ 
#define __NRATR4_getsockopt             SC_REPR_POINTER                                         /* optlen */ 
#define __NRRTR_getsockopt              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_shutdown               SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_shutdown               SC_REPR_SOCKET_SHUTDOWN_HOW                             /* how */ 
#define __NRRTR_shutdown                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sendmsg                SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_sendmsg                SC_REPR_STRUCT_MSGHDR                                   /* message */ 
#define __NRATR2_sendmsg                SC_REPR_SOCKET_SENDMSG_FLAGS                            /* msg_flags */ 
#define __NRRTR_sendmsg                 SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_recvmsg                SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_recvmsg                SC_REPR_POINTER                                         /* message */ 
#define __NRATR2_recvmsg                SC_REPR_SOCKET_RECVMSG_FLAGS2                           /* msg_flags */ 
#define __NRRTR_recvmsg                 SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_readahead              SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_readahead              SC_REPR_UINT64_T                                        /* offset */ 
#define __NRATR2_readahead              SC_REPR_SIZE_T                                          /* count */ 
#define __NRRTR_readahead               SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_brk                    SC_REPR_POINTER                                         /* addr */ 
#define __NRRTR_brk                     SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_munmap                 SC_REPR_POINTER                                         /* addr */ 
#define __NRATR1_munmap                 SC_REPR_SIZE_T                                          /* len */ 
#define __NRRTR_munmap                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mremap                 SC_REPR_POINTER                                         /* addr */ 
#define __NRATR1_mremap                 SC_REPR_SIZE_T                                          /* old_len */ 
#define __NRATR2_mremap                 SC_REPR_SIZE_T                                          /* new_len */ 
#define __NRATR3_mremap                 SC_REPR_MREMAP_FLAGS                                    /* flags */ 
#define __NRATR4_mremap                 SC_REPR_POINTER                                         /* new_address */ 
#define __NRRTR_mremap                  SC_REPR_POINTER                                         /* return */
#define __NRATR0_add_key                SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_add_key                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_request_key            SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_request_key             SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_keyctl                 SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_keyctl                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_clone                  SC_REPR_CLONE_FLAGS                                     /* flags */ 
#define __NRATR1_clone                  SC_REPR_POINTER                                         /* child_stack */ 
#define __NRATR2_clone                  SC_REPR_POINTER                                         /* ptid */ 
#define __NRATR3_clone                  SC_REPR_POINTER                                         /* newtls */ 
#define __NRATR4_clone                  SC_REPR_POINTER                                         /* ctid */ 
#define __NRRTR_clone                   SC_REPR_PID_T                                           /* return */
#define __NRATR0_execve                 SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_execve                 SC_REPR_STRING_VECTOR                                   /* argv */ 
#define __NRATR2_execve                 SC_REPR_STRING_VECTOR                                   /* envp */ 
#define __NRRTR_execve                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_swapon                 SC_REPR_FILENAME                                        /* pathname */ 
#define __NRATR1_swapon                 SC_REPR_SWAPFLAGS                                       /* swapflags */ 
#define __NRRTR_swapon                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_swapoff                SC_REPR_FILENAME                                        /* pathname */ 
#define __NRRTR_swapoff                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mprotect               SC_REPR_POINTER                                         /* addr */ 
#define __NRATR1_mprotect               SC_REPR_SIZE_T                                          /* len */ 
#define __NRATR2_mprotect               SC_REPR_MMAP_PROT                                       /* prot */ 
#define __NRRTR_mprotect                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_msync                  SC_REPR_POINTER                                         /* addr */ 
#define __NRATR1_msync                  SC_REPR_SIZE_T                                          /* len */ 
#define __NRATR2_msync                  SC_REPR_SYSCALL_ULONG_T                                 /* flags */ 
#define __NRRTR_msync                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mlock                  SC_REPR_POINTER                                         /* addr */ 
#define __NRATR1_mlock                  SC_REPR_SIZE_T                                          /* len */ 
#define __NRRTR_mlock                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_munlock                SC_REPR_POINTER                                         /* addr */ 
#define __NRATR1_munlock                SC_REPR_SIZE_T                                          /* len */ 
#define __NRRTR_munlock                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mlockall               SC_REPR_MLOCKALL_FLAGS                                  /* flags */ 
#define __NRRTR_mlockall                SC_REPR_ERRNO_T                                         /* return */
#define __NRRTR_munlockall              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mincore                SC_REPR_POINTER                                         /* start */ 
#define __NRATR1_mincore                SC_REPR_SIZE_T                                          /* len */ 
#define __NRATR2_mincore                SC_REPR_POINTER                                         /* vec */ 
#define __NRRTR_mincore                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_madvise                SC_REPR_POINTER                                         /* addr */ 
#define __NRATR1_madvise                SC_REPR_SIZE_T                                          /* len */ 
#define __NRATR2_madvise                SC_REPR_SYSCALL_ULONG_T                                 /* advice */ 
#define __NRRTR_madvise                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_remap_file_pages       SC_REPR_POINTER                                         /* start */ 
#define __NRATR1_remap_file_pages       SC_REPR_SIZE_T                                          /* size */ 
#define __NRATR2_remap_file_pages       SC_REPR_MMAP_PROT                                       /* prot */ 
#define __NRATR3_remap_file_pages       SC_REPR_SIZE_T                                          /* pgoff */ 
#define __NRATR4_remap_file_pages       SC_REPR_SYSCALL_ULONG_T                                 /* flags */ 
#define __NRRTR_remap_file_pages        SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mbind                  SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_mbind                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_get_mempolicy          SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_get_mempolicy           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_set_mempolicy          SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_set_mempolicy           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_migrate_pages          SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_migrate_pages           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_move_pages             SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_move_pages              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_rt_tgsigqueueinfo      SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_rt_tgsigqueueinfo      SC_REPR_PID_T                                           /* tid */ 
#define __NRATR2_rt_tgsigqueueinfo      SC_REPR_SIGNO_T                                         /* usigno */ 
#define __NRATR3_rt_tgsigqueueinfo      SC_REPR_STRUCT_SIGINFO                                  /* uinfo */ 
#define __NRRTR_rt_tgsigqueueinfo       SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_perf_event_open        SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_perf_event_open         SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_accept4                SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_accept4                SC_REPR_POINTER                                         /* addr */ 
#define __NRATR2_accept4                SC_REPR_POINTER                                         /* addr_len */ 
#define __NRATR3_accept4                SC_REPR_ACCEPT4_FLAGS                                   /* sock_flags */ 
#define __NRRTR_accept4                 SC_REPR_FD_T                                            /* return */
#define __NRATR0_recvmmsg               SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_recvmmsg               SC_REPR_POINTER                                         /* vmessages */ 
#define __NRATR2_recvmmsg               SC_REPR_SIZE_T                                          /* vlen */ 
#define __NRATR3_recvmmsg               SC_REPR_SOCKET_RECVMSG_FLAGS3                           /* msg_flags */ 
#define __NRATR4_recvmmsg               SC_REPR_STRUCT_TIMESPEC                                 /* tmo */ 
#define __NRRTR_recvmmsg                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_wait4                  SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_wait4                  SC_REPR_POINTER                                         /* stat_loc */ 
#define __NRATR2_wait4                  SC_REPR_WAITFLAGS                                       /* options */ 
#define __NRATR3_wait4                  SC_REPR_POINTER                                         /* usage */ 
#define __NRRTR_wait4                   SC_REPR_PID_T                                           /* return */
#define __NRATR0_prlimit64              SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_prlimit64              SC_REPR_RLIMIT_RESOURCE                                 /* resource */ 
#define __NRATR2_prlimit64              SC_REPR_STRUCT_RLIMIT64                                 /* new_limit */ 
#define __NRATR3_prlimit64              SC_REPR_POINTER                                         /* old_limit */ 
#define __NRRTR_prlimit64               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fanotify_init          SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_fanotify_init           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fanotify_mark          SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_fanotify_mark           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_name_to_handle_at      SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_name_to_handle_at      SC_REPR_FILENAME                                        /* filename */ 
#define __NRATL1_name_to_handle_at      0                                                       /* filename -> dirfd */ 
#define __NRATR2_name_to_handle_at      SC_REPR_POINTER                                         /* handle */ 
#define __NRATR3_name_to_handle_at      SC_REPR_POINTER                                         /* mnt_id */ 
#define __NRATR4_name_to_handle_at      SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH     /* flags */ 
#define __NRRTR_name_to_handle_at       SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_open_by_handle_at      SC_REPR_FD_T                                            /* mountdirfd */ 
#define __NRATR1_open_by_handle_at      SC_REPR_STRUCT_FILE_HANDLE                              /* handle */ 
#define __NRATR2_open_by_handle_at      SC_REPR_OFLAG_T                                         /* flags */ 
#define __NRRTR_open_by_handle_at       SC_REPR_FD_T                                            /* return */
#define __NRATR0_clock_adjtime          SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_clock_adjtime           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_syncfs                 SC_REPR_FD_T                                            /* fd */ 
#define __NRRTR_syncfs                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_setns                  SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_setns                  SC_REPR_CLONE_FLAGS_SETNS                               /* nstype */ 
#define __NRRTR_setns                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sendmmsg               SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_sendmmsg               SC_REPR_STRUCT_MMSGHDR                                  /* vmessages */ 
#define __NRATL1_sendmmsg               2                                                       /* vmessages -> vlen */ 
#define __NRATR2_sendmmsg               SC_REPR_SIZE_T                                          /* vlen */ 
#define __NRATR3_sendmmsg               SC_REPR_SOCKET_SENDMSG_FLAGS                            /* msg_flags */ 
#define __NRRTR_sendmmsg                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_process_vm_readv       SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_process_vm_readv       SC_REPR_STRUCT_IOVEC                                    /* local_iov */ 
#define __NRATL1_process_vm_readv       2                                                       /* local_iov -> liovcnt */ 
#define __NRATR2_process_vm_readv       SC_REPR_SIZE_T                                          /* liovcnt */ 
#define __NRATR3_process_vm_readv       SC_REPR_STRUCT_IOVEC                                    /* remote_iov */ 
#define __NRATL3_process_vm_readv       4                                                       /* remote_iov -> riovcnt */ 
#define __NRATR4_process_vm_readv       SC_REPR_SIZE_T                                          /* riovcnt */ 
#define __NRATR5_process_vm_readv       SC_REPR_SYSCALL_ULONG_T                                 /* flags */ 
#define __NRRTR_process_vm_readv        SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_process_vm_writev      SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_process_vm_writev      SC_REPR_STRUCT_IOVEC_C                                  /* local_iov */ 
#define __NRATL1_process_vm_writev      2                                                       /* local_iov -> liovcnt */ 
#define __NRATR2_process_vm_writev      SC_REPR_SIZE_T                                          /* liovcnt */ 
#define __NRATR3_process_vm_writev      SC_REPR_STRUCT_IOVEC                                    /* remote_iov */ 
#define __NRATL3_process_vm_writev      4                                                       /* remote_iov -> riovcnt */ 
#define __NRATR4_process_vm_writev      SC_REPR_SIZE_T                                          /* riovcnt */ 
#define __NRATR5_process_vm_writev      SC_REPR_SYSCALL_ULONG_T                                 /* flags */ 
#define __NRRTR_process_vm_writev       SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_kcmp                   SC_REPR_PID_T                                           /* pid1 */ 
#define __NRATR1_kcmp                   SC_REPR_PID_T                                           /* pid2 */ 
#define __NRATR2_kcmp                   SC_REPR_KCMP_TYPE                                       /* type */ 
#define __NRATR3_kcmp                   SC_REPR_SYSCALL_ULONG_T                                 /* idx1 */ 
#define __NRATR4_kcmp                   SC_REPR_SYSCALL_ULONG_T                                 /* idx2 */ 
#define __NRRTR_kcmp                    SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_finit_module           SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_finit_module           SC_REPR_STRING                                          /* uargs */ 
#define __NRATR2_finit_module           SC_REPR_SYSCALL_ULONG_T                                 /* flags */ 
#define __NRRTR_finit_module            SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sched_setattr          SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_sched_setattr           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sched_getattr          SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_sched_getattr           SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_renameat2              SC_REPR_FD_T                                            /* olddirfd */ 
#define __NRATR1_renameat2              SC_REPR_FILENAME                                        /* oldpath */ 
#define __NRATL1_renameat2              0                                                       /* oldpath -> olddirfd */ 
#define __NRATR2_renameat2              SC_REPR_FD_T                                            /* newdirfd */ 
#define __NRATR3_renameat2              SC_REPR_FILENAME                                        /* newpath */ 
#define __NRATL3_renameat2              2                                                       /* newpath -> newdirfd */ 
#define __NRATR4_renameat2              SC_REPR_RENAMEAT2_FLAGS                                 /* flags */ 
#define __NRRTR_renameat2               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_seccomp                SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_seccomp                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_getrandom              SC_REPR_POINTER                                         /* buf */ 
#define __NRATR1_getrandom              SC_REPR_SIZE_T                                          /* num_bytes */ 
#define __NRATR2_getrandom              SC_REPR_GETRANDOM_FLAGS                                 /* flags */ 
#define __NRRTR_getrandom               SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_memfd_create           SC_REPR_STRING                                          /* name */ 
#define __NRATR1_memfd_create           SC_REPR_MEMFD_CREATE_FLAGS                              /* flags */ 
#define __NRRTR_memfd_create            SC_REPR_FD_T                                            /* return */
#define __NRATR0_bpf                    SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_bpf                     SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_execveat               SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_execveat               SC_REPR_FILENAME                                        /* pathname */ 
#define __NRATL1_execveat               0                                                       /* pathname -> dirfd */ 
#define __NRATR2_execveat               SC_REPR_STRING_VECTOR                                   /* argv */ 
#define __NRATR3_execveat               SC_REPR_STRING_VECTOR                                   /* envp */ 
#define __NRATR4_execveat               SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH   /* flags */ 
#define __NRRTR_execveat                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_userfaultfd            SC_REPR_SYSCALL_ULONG_T                                 /* flags */ 
#define __NRRTR_userfaultfd             SC_REPR_FD_T                                            /* return */
#define __NRATR0_membarrier             SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_membarrier              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mlock2                 SC_REPR_POINTER                                         /* addr */ 
#define __NRATR1_mlock2                 SC_REPR_SIZE_T                                          /* length */ 
#define __NRATR2_mlock2                 SC_REPR_SYSCALL_ULONG_T                                 /* flags */ 
#define __NRRTR_mlock2                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_open                   SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_open                   SC_REPR_OFLAG_T                                         /* oflags */ 
#define __NRATR2_open                   SC_REPR_MODE_T                                          /* mode */ 
#define __NRATL2_open                   1                                                       /* mode -> oflags */ 
#define __NRRTR_open                    SC_REPR_FD_T                                            /* return */
#define __NRATR0_link                   SC_REPR_FILENAME                                        /* existing_file */ 
#define __NRATR1_link                   SC_REPR_FILENAME                                        /* link_file */ 
#define __NRRTR_link                    SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_unlink                 SC_REPR_FILENAME                                        /* filename */ 
#define __NRRTR_unlink                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mknod                  SC_REPR_FILENAME                                        /* nodename */ 
#define __NRATR1_mknod                  SC_REPR_MODE_T                                          /* mode */ 
#define __NRATR2_mknod                  SC_REPR_DEV_T                                           /* dev */ 
#define __NRATL2_mknod                  1                                                       /* dev -> mode */ 
#define __NRRTR_mknod                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_chmod                  SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_chmod                  SC_REPR_MODE_T                                          /* mode */ 
#define __NRRTR_chmod                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_chown                  SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_chown                  SC_REPR_UID_T                                           /* owner */ 
#define __NRATR2_chown                  SC_REPR_GID_T                                           /* group */ 
#define __NRRTR_chown                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_mkdir                  SC_REPR_FILENAME                                        /* pathname */ 
#define __NRATR1_mkdir                  SC_REPR_MODE_T                                          /* mode */ 
#define __NRRTR_mkdir                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_rmdir                  SC_REPR_STRING                                          /* path */ 
#define __NRRTR_rmdir                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_lchown                 SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_lchown                 SC_REPR_UID_T                                           /* owner */ 
#define __NRATR2_lchown                 SC_REPR_GID_T                                           /* group */ 
#define __NRRTR_lchown                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_access                 SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_access                 SC_REPR_ACCESS_TYPE                                     /* type */ 
#define __NRRTR_access                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_rename                 SC_REPR_FILENAME                                        /* oldname */ 
#define __NRATR1_rename                 SC_REPR_FILENAME                                        /* newname_or_path */ 
#define __NRRTR_rename                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_readlink               SC_REPR_FILENAME                                        /* path */ 
#define __NRATR1_readlink               SC_REPR_POINTER                                         /* buf */ 
#define __NRATR2_readlink               SC_REPR_SIZE_T                                          /* buflen */ 
#define __NRRTR_readlink                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_symlink                SC_REPR_STRING                                          /* link_text */ 
#define __NRATR1_symlink                SC_REPR_FILENAME                                        /* target_path */ 
#define __NRRTR_symlink                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_utimes                 SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_utimes                 SC_REPR_STRUCT_TIMEVAL_VEC2                             /* times */ 
#define __NRRTR_utimes                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_pipe                   SC_REPR_POINTER                                         /* pipedes */ 
#define __NRRTR_pipe                    SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_dup2                   SC_REPR_FD_T                                            /* oldfd */ 
#define __NRATR1_dup2                   SC_REPR_FD_T                                            /* newfd */ 
#define __NRRTR_dup2                    SC_REPR_FD_T                                            /* return */
#define __NRATR0_epoll_create           SC_REPR_SYSCALL_ULONG_T                                 /* size */ 
#define __NRRTR_epoll_create            SC_REPR_FD_T                                            /* return */
#define __NRRTR_inotify_init            SC_REPR_FD_T                                            /* return */
#define __NRATR0_eventfd                SC_REPR_SYSCALL_ULONG_T                                 /* initval */ 
#define __NRRTR_eventfd                 SC_REPR_FD_T                                            /* return */
#define __NRATR0_signalfd               SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_signalfd               SC_REPR_STRUCT_SIGSET                                   /* sigmask */ 
#define __NRATL1_signalfd               2                                                       /* sigmask -> sigmasksize */ 
#define __NRATR2_signalfd               SC_REPR_SIZE_T                                          /* sigmasksize */ 
#define __NRRTR_signalfd                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_sendfile               SC_REPR_FD_T                                            /* outfd */ 
#define __NRATR1_sendfile               SC_REPR_FD_T                                            /* infd */ 
#define __NRATR2_sendfile               SC_REPR_POINTER                                         /* pin_offset */ 
#define __NRATR3_sendfile               SC_REPR_SIZE_T                                          /* num_bytes */ 
#define __NRRTR_sendfile                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_ftruncate              SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_ftruncate              SC_REPR_SYSCALL_ULONG_T                                 /* length */ 
#define __NRRTR_ftruncate               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_truncate               SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_truncate               SC_REPR_SYSCALL_ULONG_T                                 /* length */ 
#define __NRRTR_truncate                SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_stat                   SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_stat                   SC_REPR_POINTER                                         /* statbuf */ 
#define __NRRTR_stat                    SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_lstat                  SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_lstat                  SC_REPR_POINTER                                         /* statbuf */ 
#define __NRRTR_lstat                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fstat                  SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_fstat                  SC_REPR_POINTER                                         /* statbuf */ 
#define __NRRTR_fstat                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fcntl                  SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_fcntl                  SC_REPR_FCNTL_COMMAND                                   /* command */ 
#define __NRATR2_fcntl                  SC_REPR_FCNTL_ARG                                       /* arg */ 
#define __NRATL2_fcntl                  1                                                       /* arg -> command */ 
#define __NRRTR_fcntl                   SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_fadvise64              SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_fadvise64               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_newfstatat             SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_newfstatat             SC_REPR_FILENAME                                        /* filename */ 
#define __NRATL1_newfstatat             0                                                       /* filename -> dirfd */ 
#define __NRATR2_newfstatat             SC_REPR_POINTER                                         /* statbuf */ 
#define __NRATR3_newfstatat             SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH               /* flags */ 
#define __NRRTR_newfstatat              SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_fstatfs                SC_REPR_FD_T                                            /* file */ 
#define __NRATR1_fstatfs                SC_REPR_POINTER                                         /* buf */ 
#define __NRRTR_fstatfs                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_statfs                 SC_REPR_FILENAME                                        /* file */ 
#define __NRATR1_statfs                 SC_REPR_POINTER                                         /* buf */ 
#define __NRRTR_statfs                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_lseek                  SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_lseek                  SC_REPR_SYSCALL_SLONG_T                                 /* offset */ 
#define __NRATR2_lseek                  SC_REPR_SEEK_WHENCE                                     /* whence */ 
#define __NRRTR_lseek                   SC_REPR_SYSCALL_SLONG_T                                 /* return */
#define __NRATR0_mmap                   SC_REPR_POINTER                                         /* addr */ 
#define __NRATR1_mmap                   SC_REPR_SIZE_T                                          /* len */ 
#define __NRATR2_mmap                   SC_REPR_MMAP_PROT                                       /* prot */ 
#define __NRATR3_mmap                   SC_REPR_MMAP_FLAGS                                      /* flags */ 
#define __NRATR4_mmap                   SC_REPR_FD_T                                            /* fd */ 
#define __NRATR5_mmap                   SC_REPR_SYSCALL_ULONG_T                                 /* offset */ 
#define __NRRTR_mmap                    SC_REPR_POINTER                                         /* return */
#define __NRATR0_alarm                  SC_REPR_SYSCALL_ULONG_T                                 /* seconds */ 
#define __NRRTR_alarm                   SC_REPR_SYSCALL_ULONG_T                                 /* return */
#define __NRRTR_getpgrp                 SC_REPR_PID_T                                           /* return */
#define __NRRTR_pause                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_time                   SC_REPR_POINTER                                         /* timer */ 
#define __NRRTR_time                    SC_REPR_TIME_T                                          /* return */
#define __NRATR0_utime                  SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_utime                  SC_REPR_STRUCT_UTIMBUF                                  /* times */ 
#define __NRRTR_utime                   SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_creat                  SC_REPR_FILENAME                                        /* filename */ 
#define __NRATR1_creat                  SC_REPR_MODE_T                                          /* mode */ 
#define __NRRTR_creat                   SC_REPR_FD_T                                            /* return */
#define __NRATR0_getdents               SC_REPR_FD_T                                            /* fd */ 
#define __NRATR1_getdents               SC_REPR_POINTER                                         /* buf */ 
#define __NRATR2_getdents               SC_REPR_SIZE_T                                          /* buflen */ 
#define __NRRTR_getdents                SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_futimesat              SC_REPR_FD_T                                            /* dirfd */ 
#define __NRATR1_futimesat              SC_REPR_FILENAME                                        /* filename */ 
#define __NRATL1_futimesat              0                                                       /* filename -> dirfd */ 
#define __NRATR2_futimesat              SC_REPR_STRUCT_TIMEVAL_VEC2                             /* times */ 
#define __NRRTR_futimesat               SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_select                 SC_REPR_SIZE_T                                          /* nfds */ 
#define __NRATR1_select                 SC_REPR_STRUCT_FDSET                                    /* readfds */ 
#define __NRATL1_select                 0                                                       /* readfds -> nfds */ 
#define __NRATR2_select                 SC_REPR_STRUCT_FDSET                                    /* writefds */ 
#define __NRATL2_select                 0                                                       /* writefds -> nfds */ 
#define __NRATR3_select                 SC_REPR_STRUCT_FDSET                                    /* exceptfds */ 
#define __NRATL3_select                 0                                                       /* exceptfds -> nfds */ 
#define __NRATR4_select                 SC_REPR_STRUCT_TIMEVAL                                  /* timeout */ 
#define __NRRTR_select                  SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_poll                   SC_REPR_STRUCT_POLLFD                                   /* fds */ 
#define __NRATL0_poll                   1                                                       /* fds -> nfds */ 
#define __NRATR1_poll                   SC_REPR_SIZE_T                                          /* nfds */ 
#define __NRATR2_poll                   SC_REPR_SYSCALL_SLONG_T                                 /* timeout */ 
#define __NRRTR_poll                    SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_epoll_wait             SC_REPR_FD_T                                            /* epfd */ 
#define __NRATR1_epoll_wait             SC_REPR_POINTER                                         /* events */ 
#define __NRATR2_epoll_wait             SC_REPR_SIZE_T                                          /* maxevents */ 
#define __NRATR3_epoll_wait             SC_REPR_SYSCALL_SLONG_T                                 /* timeout */ 
#define __NRRTR_epoll_wait              SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_ustat                  SC_REPR_DEV_BLK                                         /* dev */ 
#define __NRATR1_ustat                  SC_REPR_POINTER                                         /* ubuf */ 
#define __NRRTR_ustat                   SC_REPR_ERRNO_T                                         /* return */
#define __NRRTR_vfork                   SC_REPR_PID_T                                           /* return */
#define __NRATR0_oldwait4               SC_REPR_PID_T                                           /* pid */ 
#define __NRATR1_oldwait4               SC_REPR_POINTER                                         /* stat_loc */ 
#define __NRATR2_oldwait4               SC_REPR_WAITFLAGS                                       /* options */ 
#define __NRATR3_oldwait4               SC_REPR_POINTER                                         /* usage */ 
#define __NRRTR_oldwait4                SC_REPR_PID_T                                           /* return */
#define __NRATR0_recv                   SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_recv                   SC_REPR_POINTER                                         /* buf */ 
#define __NRATR2_recv                   SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRATR3_recv                   SC_REPR_SOCKET_RECVMSG_FLAGS                            /* msg_flags */ 
#define __NRRTR_recv                    SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_send                   SC_REPR_FD_T                                            /* sockfd */ 
#define __NRATR1_send                   SC_REPR_BUFFER                                          /* buf */ 
#define __NRATL1_send                   2                                                       /* buf -> bufsize */ 
#define __NRATR2_send                   SC_REPR_SIZE_T                                          /* bufsize */ 
#define __NRATR3_send                   SC_REPR_SOCKET_SENDMSG_FLAGS                            /* msg_flags */ 
#define __NRRTR_send                    SC_REPR_SSIZE_T                                         /* return */
#define __NRATR0_bdflush                SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR_bdflush                 SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_umount                 SC_REPR_FILENAME                                        /* special_file */ 
#define __NRRTR_umount                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0_uselib                 SC_REPR_FILENAME                                        /* library */ 
#define __NRRTR_uselib                  SC_REPR_ERRNO_T                                         /* return */
#define __NRATR0__sysctl                SC_REPR_INT                                             /* TODO_PROTOTYPE */ 
#define __NRRTR__sysctl                 SC_REPR_ERRNO_T                                         /* return */
#define __NRRTR_fork                    SC_REPR_PID_T                                           /* return */
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT */
#endif /* __WANT_SYSCALL_ARGUMENT_FORMAT */


/************************************************************************/
/* SYSCALL ARGUMENT DOUBLE WIDE                                         */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE */
#endif /* __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE */

