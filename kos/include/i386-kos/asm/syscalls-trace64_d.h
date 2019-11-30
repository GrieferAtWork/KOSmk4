/* HASH CRC-32:0xfeb75e28 */
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
/* SYSCALL ARGUMENT NAMES                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_NAMES
#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#define __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES 1
#define __NR64AN0_read                   fd
#define __NR64AN1_read                   buf
#define __NR64AN2_read                   bufsize
#define __NR64AN0_write                  fd
#define __NR64AN1_write                  buf
#define __NR64AN2_write                  bufsize
#define __NR64AN0_open                   filename
#define __NR64AN1_open                   oflags
#define __NR64AN2_open                   mode
#define __NR64AN0_close                  fd
#define __NR64AN0_linux_stat64           filename
#define __NR64AN1_linux_stat64           statbuf
#define __NR64AN0_linux_fstat64          fd
#define __NR64AN1_linux_fstat64          statbuf
#define __NR64AN0_linux_lstat64          filename
#define __NR64AN1_linux_lstat64          statbuf
#define __NR64AN0_poll                   fds
#define __NR64AN1_poll                   nfds
#define __NR64AN2_poll                   timeout
#define __NR64AN0_lseek64                fd
#define __NR64AN1_lseek64                offset
#define __NR64AN2_lseek64                whence
#define __NR64AN0_mmap                   addr
#define __NR64AN1_mmap                   len
#define __NR64AN2_mmap                   prot
#define __NR64AN3_mmap                   flags
#define __NR64AN4_mmap                   fd
#define __NR64AN5_mmap                   offset
#define __NR64AN0_mprotect               addr
#define __NR64AN1_mprotect               len
#define __NR64AN2_mprotect               prot
#define __NR64AN0_munmap                 addr
#define __NR64AN1_munmap                 len
#define __NR64AN0_brk                    addr
#define __NR64AN0_rt_sigaction           signo
#define __NR64AN1_rt_sigaction           act
#define __NR64AN2_rt_sigaction           oact
#define __NR64AN3_rt_sigaction           sigsetsize
#define __NR64AN0_rt_sigprocmask         how
#define __NR64AN1_rt_sigprocmask         set
#define __NR64AN2_rt_sigprocmask         oset
#define __NR64AN3_rt_sigprocmask         sigsetsize
#define __NR64AN0_rt_sigreturn           restore_fpu
#define __NR64AN1_rt_sigreturn           restore_sigmask
#define __NR64AN2_rt_sigreturn           sc_info
#define __NR64AN3_rt_sigreturn           restore_cpu
#define __NR64AN0_ioctl                  fd
#define __NR64AN1_ioctl                  request
#define __NR64AN2_ioctl                  arg
#define __NR64AN0_pread64                fd
#define __NR64AN1_pread64                buf
#define __NR64AN2_pread64                bufsize
#define __NR64AN3_pread64                offset
#define __NR64AN0_pwrite64               fd
#define __NR64AN1_pwrite64               buf
#define __NR64AN2_pwrite64               bufsize
#define __NR64AN3_pwrite64               offset
#define __NR64AN0_readv                  fd
#define __NR64AN1_readv                  iovec
#define __NR64AN2_readv                  count
#define __NR64AN0_writev                 fd
#define __NR64AN1_writev                 iovec
#define __NR64AN2_writev                 count
#define __NR64AN0_access                 filename
#define __NR64AN1_access                 type
#define __NR64AN0_pipe                   pipedes
#define __NR64AN0_select                 nfds
#define __NR64AN1_select                 readfds
#define __NR64AN2_select                 writefds
#define __NR64AN3_select                 exceptfds
#define __NR64AN4_select                 timeout
#define __NR64AN0_mremap                 addr
#define __NR64AN1_mremap                 old_len
#define __NR64AN2_mremap                 new_len
#define __NR64AN3_mremap                 flags
#define __NR64AN4_mremap                 new_address
#define __NR64AN0_msync                  addr
#define __NR64AN1_msync                  len
#define __NR64AN2_msync                  flags
#define __NR64AN0_mincore                start
#define __NR64AN1_mincore                len
#define __NR64AN2_mincore                vec
#define __NR64AN0_madvise                addr
#define __NR64AN1_madvise                len
#define __NR64AN2_madvise                advice
#define __NR64AN0_shmget                 TODO_PROTOTYPE
#define __NR64AN0_shmat                  TODO_PROTOTYPE
#define __NR64AN0_shmctl                 TODO_PROTOTYPE
#define __NR64AN0_dup                    fd
#define __NR64AN0_dup2                   oldfd
#define __NR64AN1_dup2                   newfd
#define __NR64AN0_nanosleep              req
#define __NR64AN1_nanosleep              rem
#define __NR64AN0_getitimer              which
#define __NR64AN1_getitimer              curr_value
#define __NR64AN0_alarm                  seconds
#define __NR64AN0_setitimer              which
#define __NR64AN1_setitimer              newval
#define __NR64AN2_setitimer              oldval
#define __NR64AN0_sendfile               out_fd
#define __NR64AN1_sendfile               in_fd
#define __NR64AN2_sendfile               offset
#define __NR64AN3_sendfile               count
#define __NR64AN0_socket                 domain
#define __NR64AN1_socket                 type
#define __NR64AN2_socket                 protocol
#define __NR64AN0_connect                sockfd
#define __NR64AN1_connect                addr
#define __NR64AN2_connect                addr_len
#define __NR64AN0_accept                 TODO_PROTOTYPE
#define __NR64AN0_sendto                 sockfd
#define __NR64AN1_sendto                 buf
#define __NR64AN2_sendto                 bufsize
#define __NR64AN3_sendto                 flags
#define __NR64AN4_sendto                 addr
#define __NR64AN5_sendto                 addr_len
#define __NR64AN0_recvfrom               sockfd
#define __NR64AN1_recvfrom               buf
#define __NR64AN2_recvfrom               bufsize
#define __NR64AN3_recvfrom               flags
#define __NR64AN4_recvfrom               addr
#define __NR64AN5_recvfrom               addr_len
#define __NR64AN0_sendmsg                sockfd
#define __NR64AN1_sendmsg                message
#define __NR64AN2_sendmsg                flags
#define __NR64AN0_recvmsg                sockfd
#define __NR64AN1_recvmsg                message
#define __NR64AN2_recvmsg                flags
#define __NR64AN0_shutdown               sockfd
#define __NR64AN1_shutdown               how
#define __NR64AN0_bind                   sockfd
#define __NR64AN1_bind                   addr
#define __NR64AN2_bind                   addr_len
#define __NR64AN0_listen                 sockfd
#define __NR64AN1_listen                 max_backlog
#define __NR64AN0_getsockname            sockfd
#define __NR64AN1_getsockname            addr
#define __NR64AN2_getsockname            addr_len
#define __NR64AN0_getpeername            sockfd
#define __NR64AN1_getpeername            addr
#define __NR64AN2_getpeername            addr_len
#define __NR64AN0_socketpair             domain
#define __NR64AN1_socketpair             type
#define __NR64AN2_socketpair             protocol
#define __NR64AN3_socketpair             fds
#define __NR64AN0_setsockopt             sockfd
#define __NR64AN1_setsockopt             level
#define __NR64AN2_setsockopt             optname
#define __NR64AN3_setsockopt             optval
#define __NR64AN4_setsockopt             optlen
#define __NR64AN0_getsockopt             sockfd
#define __NR64AN1_getsockopt             level
#define __NR64AN2_getsockopt             optname
#define __NR64AN3_getsockopt             optval
#define __NR64AN4_getsockopt             optlen
#define __NR64AN0_clone                  flags
#define __NR64AN1_clone                  child_stack
#define __NR64AN2_clone                  ptid
#define __NR64AN3_clone                  ctid
#define __NR64AN4_clone                  newtls
#define __NR64AN0_execve                 path
#define __NR64AN1_execve                 argv
#define __NR64AN2_execve                 envp
#define __NR64AN0_exit                   status
#define __NR64AN0_wait4                  pid
#define __NR64AN1_wait4                  stat_loc
#define __NR64AN2_wait4                  options
#define __NR64AN3_wait4                  usage
#define __NR64AN0_kill                   pid
#define __NR64AN1_kill                   signo
#define __NR64AN0_uname                  name
#define __NR64AN0_semget                 TODO_PROTOTYPE
#define __NR64AN0_semop                  TODO_PROTOTYPE
#define __NR64AN0_semctl                 TODO_PROTOTYPE
#define __NR64AN0_shmdt                  TODO_PROTOTYPE
#define __NR64AN0_msgget                 TODO_PROTOTYPE
#define __NR64AN0_msgsnd                 TODO_PROTOTYPE
#define __NR64AN0_msgrcv                 TODO_PROTOTYPE
#define __NR64AN0_msgctl                 TODO_PROTOTYPE
#define __NR64AN0_fcntl                  fd
#define __NR64AN1_fcntl                  cmd
#define __NR64AN2_fcntl                  arg
#define __NR64AN0_flock                  fd
#define __NR64AN1_flock                  operation
#define __NR64AN0_fsync                  fd
#define __NR64AN0_fdatasync              fd
#define __NR64AN0_truncate               filename
#define __NR64AN1_truncate               length
#define __NR64AN0_ftruncate              fd
#define __NR64AN1_ftruncate              length
#define __NR64AN0_getdents               fd
#define __NR64AN1_getdents               dirp
#define __NR64AN2_getdents               count
#define __NR64AN0_getcwd                 buf
#define __NR64AN1_getcwd                 size
#define __NR64AN0_chdir                  path
#define __NR64AN0_fchdir                 fd
#define __NR64AN0_rename                 oldname
#define __NR64AN1_rename                 newname_or_path
#define __NR64AN0_mkdir                  pathname
#define __NR64AN1_mkdir                  mode
#define __NR64AN0_rmdir                  path
#define __NR64AN0_creat                  filename
#define __NR64AN1_creat                  mode
#define __NR64AN0_link                   existing_file
#define __NR64AN1_link                   link_file
#define __NR64AN0_unlink                 filename
#define __NR64AN0_symlink                link_text
#define __NR64AN1_symlink                target_path
#define __NR64AN0_readlink               path
#define __NR64AN1_readlink               buf
#define __NR64AN2_readlink               buflen
#define __NR64AN0_chmod                  filename
#define __NR64AN1_chmod                  mode
#define __NR64AN0_fchmod                 fd
#define __NR64AN1_fchmod                 mode
#define __NR64AN0_chown                  filename
#define __NR64AN1_chown                  owner
#define __NR64AN2_chown                  group
#define __NR64AN0_fchown                 fd
#define __NR64AN1_fchown                 owner
#define __NR64AN2_fchown                 group
#define __NR64AN0_lchown                 filename
#define __NR64AN1_lchown                 owner
#define __NR64AN2_lchown                 group
#define __NR64AN0_umask                  mode
#define __NR64AN0_gettimeofday           tv
#define __NR64AN1_gettimeofday           tz
#define __NR64AN0_getrlimit              resource
#define __NR64AN1_getrlimit              rlimits
#define __NR64AN0_getrusage              who
#define __NR64AN1_getrusage              usage
#define __NR64AN0_sysinfo                info
#define __NR64AN0_times                  buf
#define __NR64AN0_ptrace                 request
#define __NR64AN1_ptrace                 pid
#define __NR64AN2_ptrace                 addr
#define __NR64AN3_ptrace                 data
#define __NR64AN0_syslog                 level
#define __NR64AN1_syslog                 str
#define __NR64AN2_syslog                 len
#define __NR64AN0_setuid                 uid
#define __NR64AN0_setgid                 gid
#define __NR64AN0_setpgid                pid
#define __NR64AN1_setpgid                pgid
#define __NR64AN0_setreuid               ruid
#define __NR64AN1_setreuid               euid
#define __NR64AN0_setregid               rgid
#define __NR64AN1_setregid               egid
#define __NR64AN0_getgroups              size
#define __NR64AN1_getgroups              list
#define __NR64AN0_setgroups              count
#define __NR64AN1_setgroups              groups
#define __NR64AN0_setresuid              ruid
#define __NR64AN1_setresuid              euid
#define __NR64AN2_setresuid              suid
#define __NR64AN0_getresuid              ruid
#define __NR64AN1_getresuid              euid
#define __NR64AN2_getresuid              suid
#define __NR64AN0_setresgid              rgid
#define __NR64AN1_setresgid              egid
#define __NR64AN2_setresgid              sgid
#define __NR64AN0_getresgid              rgid
#define __NR64AN1_getresgid              egid
#define __NR64AN2_getresgid              sgid
#define __NR64AN0_getpgid                pid
#define __NR64AN0_setfsuid               uid
#define __NR64AN0_setfsgid               gid
#define __NR64AN0_getsid                 pid
#define __NR64AN0_capget                 TODO_PROTOTYPE
#define __NR64AN0_capset                 TODO_PROTOTYPE
#define __NR64AN0_rt_sigpending          set
#define __NR64AN1_rt_sigpending          sigsetsize
#define __NR64AN0_rt_sigtimedwait        set
#define __NR64AN1_rt_sigtimedwait        info
#define __NR64AN2_rt_sigtimedwait        timeout
#define __NR64AN3_rt_sigtimedwait        sigsetsize
#define __NR64AN0_rt_sigqueueinfo        tgid
#define __NR64AN1_rt_sigqueueinfo        signo
#define __NR64AN2_rt_sigqueueinfo        uinfo
#define __NR64AN0_rt_sigsuspend          set
#define __NR64AN1_rt_sigsuspend          sigsetsize
#define __NR64AN0_sigaltstack            ss
#define __NR64AN1_sigaltstack            oss
#define __NR64AN0_utime                  filename
#define __NR64AN1_utime                  times
#define __NR64AN0_mknod                  nodename
#define __NR64AN1_mknod                  mode
#define __NR64AN2_mknod                  dev
#define __NR64AN0_uselib                 library
#define __NR64AN0_personality            TODO_PROTOTYPE
#define __NR64AN0_ustat                  dev
#define __NR64AN1_ustat                  ubuf
#define __NR64AN0_statfs                 file
#define __NR64AN1_statfs                 buf
#define __NR64AN0_fstatfs                file
#define __NR64AN1_fstatfs                buf
#define __NR64AN0_sysfs                  TODO_PROTOTYPE
#define __NR64AN0_getpriority            which
#define __NR64AN1_getpriority            who
#define __NR64AN0_setpriority            which
#define __NR64AN1_setpriority            who
#define __NR64AN2_setpriority            value
#define __NR64AN0_sched_setparam         pid
#define __NR64AN1_sched_setparam         param
#define __NR64AN0_sched_getparam         pid
#define __NR64AN1_sched_getparam         param
#define __NR64AN0_sched_setscheduler     pid
#define __NR64AN1_sched_setscheduler     policy
#define __NR64AN2_sched_setscheduler     param
#define __NR64AN0_sched_getscheduler     pid
#define __NR64AN0_sched_get_priority_max algorithm
#define __NR64AN0_sched_get_priority_min algorithm
#define __NR64AN0_sched_rr_get_interval  pid
#define __NR64AN1_sched_rr_get_interval  tms
#define __NR64AN0_mlock                  addr
#define __NR64AN1_mlock                  len
#define __NR64AN0_munlock                addr
#define __NR64AN1_munlock                len
#define __NR64AN0_mlockall               flags
#define __NR64AN0_modify_ldt             func
#define __NR64AN1_modify_ldt             ptr
#define __NR64AN2_modify_ldt             bytecount
#define __NR64AN0_pivot_root             TODO_PROTOTYPE
#define __NR64AN0__sysctl                TODO_PROTOTYPE
#define __NR64AN0_prctl                  TODO_PROTOTYPE
#define __NR64AN0_arch_prctl             TODO_PROTOTYPE
#define __NR64AN0_adjtimex               TODO_PROTOTYPE
#define __NR64AN0_setrlimit              resource
#define __NR64AN1_setrlimit              rlimits
#define __NR64AN0_chroot                 path
#define __NR64AN0_acct                   filename
#define __NR64AN0_settimeofday           tv
#define __NR64AN1_settimeofday           tz
#define __NR64AN0_mount                  special_file
#define __NR64AN1_mount                  dir
#define __NR64AN2_mount                  fstype
#define __NR64AN3_mount                  rwflag
#define __NR64AN4_mount                  data
#define __NR64AN0_umount2                special_file
#define __NR64AN1_umount2                flags
#define __NR64AN0_swapon                 pathname
#define __NR64AN1_swapon                 swapflags
#define __NR64AN0_swapoff                pathname
#define __NR64AN0_reboot                 how
#define __NR64AN0_sethostname            name
#define __NR64AN1_sethostname            len
#define __NR64AN0_setdomainname          name
#define __NR64AN1_setdomainname          len
#define __NR64AN0_iopl                   level
#define __NR64AN0_ioperm                 from
#define __NR64AN1_ioperm                 num
#define __NR64AN2_ioperm                 turn_on
#define __NR64AN0_create_module          TODO_PROTOTYPE
#define __NR64AN0_init_module            TODO_PROTOTYPE
#define __NR64AN0_delete_module          TODO_PROTOTYPE
#define __NR64AN0_get_kernel_syms        TODO_PROTOTYPE
#define __NR64AN0_query_module           TODO_PROTOTYPE
#define __NR64AN0_quotactl               TODO_PROTOTYPE
#define __NR64AN0_nfsservctl             TODO_PROTOTYPE
#define __NR64AN0_getpmsg                TODO_PROTOTYPE
#define __NR64AN0_putpmsg                TODO_PROTOTYPE
#define __NR64AN0_afs_syscall            TODO_PROTOTYPE
#define __NR64AN0_tuxcall                TODO_PROTOTYPE
#define __NR64AN0_security               TODO_PROTOTYPE
#define __NR64AN0_readahead              fd
#define __NR64AN1_readahead              offset
#define __NR64AN2_readahead              count
#define __NR64AN0_setxattr               path
#define __NR64AN1_setxattr               name
#define __NR64AN2_setxattr               buf
#define __NR64AN3_setxattr               bufsize
#define __NR64AN4_setxattr               flags
#define __NR64AN0_lsetxattr              path
#define __NR64AN1_lsetxattr              name
#define __NR64AN2_lsetxattr              buf
#define __NR64AN3_lsetxattr              bufsize
#define __NR64AN4_lsetxattr              flags
#define __NR64AN0_fsetxattr              fd
#define __NR64AN1_fsetxattr              name
#define __NR64AN2_fsetxattr              buf
#define __NR64AN3_fsetxattr              bufsize
#define __NR64AN4_fsetxattr              flags
#define __NR64AN0_getxattr               path
#define __NR64AN1_getxattr               name
#define __NR64AN2_getxattr               buf
#define __NR64AN3_getxattr               bufsize
#define __NR64AN0_lgetxattr              path
#define __NR64AN1_lgetxattr              name
#define __NR64AN2_lgetxattr              buf
#define __NR64AN3_lgetxattr              bufsize
#define __NR64AN0_fgetxattr              fd
#define __NR64AN1_fgetxattr              name
#define __NR64AN2_fgetxattr              buf
#define __NR64AN3_fgetxattr              bufsize
#define __NR64AN0_listxattr              path
#define __NR64AN1_listxattr              listbuf
#define __NR64AN2_listxattr              listbufsize
#define __NR64AN0_llistxattr             path
#define __NR64AN1_llistxattr             listbuf
#define __NR64AN2_llistxattr             listbufsize
#define __NR64AN0_flistxattr             fd
#define __NR64AN1_flistxattr             listbuf
#define __NR64AN2_flistxattr             listbufsize
#define __NR64AN0_removexattr            path
#define __NR64AN1_removexattr            name
#define __NR64AN0_lremovexattr           path
#define __NR64AN1_lremovexattr           name
#define __NR64AN0_fremovexattr           fd
#define __NR64AN1_fremovexattr           name
#define __NR64AN0_tkill                  tid
#define __NR64AN1_tkill                  signo
#define __NR64AN0_time                   timer
#define __NR64AN0_futex                  uaddr
#define __NR64AN1_futex                  futex_op
#define __NR64AN2_futex                  val
#define __NR64AN3_futex                  timeout_or_val2
#define __NR64AN4_futex                  uaddr2
#define __NR64AN5_futex                  val3
#define __NR64AN0_sched_setaffinity      pid
#define __NR64AN1_sched_setaffinity      cpusetsize
#define __NR64AN2_sched_setaffinity      cpuset
#define __NR64AN0_sched_getaffinity      pid
#define __NR64AN1_sched_getaffinity      cpusetsize
#define __NR64AN2_sched_getaffinity      cpuset
#define __NR64AN0_set_thread_area        TODO_PROTOTYPE
#define __NR64AN0_io_setup               TODO_PROTOTYPE
#define __NR64AN0_io_destroy             TODO_PROTOTYPE
#define __NR64AN0_io_getevents           TODO_PROTOTYPE
#define __NR64AN0_io_submit              TODO_PROTOTYPE
#define __NR64AN0_io_cancel              TODO_PROTOTYPE
#define __NR64AN0_get_thread_area        TODO_PROTOTYPE
#define __NR64AN0_lookup_dcookie         TODO_PROTOTYPE
#define __NR64AN0_epoll_create           size
#define __NR64AN0_epoll_ctl_old          epfd
#define __NR64AN1_epoll_ctl_old          op
#define __NR64AN2_epoll_ctl_old          fd
#define __NR64AN3_epoll_ctl_old          event
#define __NR64AN0_epoll_wait_old         epfd
#define __NR64AN1_epoll_wait_old         events
#define __NR64AN2_epoll_wait_old         maxevents
#define __NR64AN3_epoll_wait_old         timeout
#define __NR64AN0_remap_file_pages       start
#define __NR64AN1_remap_file_pages       size
#define __NR64AN2_remap_file_pages       prot
#define __NR64AN3_remap_file_pages       pgoff
#define __NR64AN4_remap_file_pages       flags
#define __NR64AN0_getdents64             fd
#define __NR64AN1_getdents64             dirp
#define __NR64AN2_getdents64             count
#define __NR64AN0_set_tid_address        tidptr
#define __NR64AN0_semtimedop             TODO_PROTOTYPE
#define __NR64AN0_fadvise64              TODO_PROTOTYPE
#define __NR64AN0_timer_create           clock_id
#define __NR64AN1_timer_create           evp
#define __NR64AN2_timer_create           timerid
#define __NR64AN0_timer_settime          timerid
#define __NR64AN1_timer_settime          flags
#define __NR64AN2_timer_settime          value
#define __NR64AN3_timer_settime          ovalue
#define __NR64AN0_timer_gettime          timerid
#define __NR64AN1_timer_gettime          value
#define __NR64AN0_timer_getoverrun       timerid
#define __NR64AN0_timer_delete           timerid
#define __NR64AN0_clock_settime          clock_id
#define __NR64AN1_clock_settime          tp
#define __NR64AN0_clock_gettime          clock_id
#define __NR64AN1_clock_gettime          tp
#define __NR64AN0_clock_getres           clock_id
#define __NR64AN1_clock_getres           res
#define __NR64AN0_clock_nanosleep        clock_id
#define __NR64AN1_clock_nanosleep        flags
#define __NR64AN2_clock_nanosleep        requested_time
#define __NR64AN3_clock_nanosleep        remaining
#define __NR64AN0_exit_group             exit_code
#define __NR64AN0_epoll_wait             epfd
#define __NR64AN1_epoll_wait             events
#define __NR64AN2_epoll_wait             maxevents
#define __NR64AN3_epoll_wait             timeout
#define __NR64AN0_epoll_ctl              epfd
#define __NR64AN1_epoll_ctl              op
#define __NR64AN2_epoll_ctl              fd
#define __NR64AN3_epoll_ctl              event
#define __NR64AN0_tgkill                 tgid
#define __NR64AN1_tgkill                 tid
#define __NR64AN2_tgkill                 signo
#define __NR64AN0_utimes                 filename
#define __NR64AN1_utimes                 times
#define __NR64AN0_vserver                TODO_PROTOTYPE
#define __NR64AN0_mbind                  TODO_PROTOTYPE
#define __NR64AN0_set_mempolicy          TODO_PROTOTYPE
#define __NR64AN0_get_mempolicy          TODO_PROTOTYPE
#define __NR64AN0_mq_open                TODO_PROTOTYPE
#define __NR64AN0_mq_unlink              TODO_PROTOTYPE
#define __NR64AN0_mq_timedsend           TODO_PROTOTYPE
#define __NR64AN0_mq_timedreceive        TODO_PROTOTYPE
#define __NR64AN0_mq_notify              TODO_PROTOTYPE
#define __NR64AN0_mq_getsetattr          TODO_PROTOTYPE
#define __NR64AN0_kexec_load             TODO_PROTOTYPE
#define __NR64AN0_waitid                 idtype
#define __NR64AN1_waitid                 id
#define __NR64AN2_waitid                 infop
#define __NR64AN3_waitid                 options
#define __NR64AN4_waitid                 ru
#define __NR64AN0_add_key                TODO_PROTOTYPE
#define __NR64AN0_request_key            TODO_PROTOTYPE
#define __NR64AN0_keyctl                 TODO_PROTOTYPE
#define __NR64AN0_ioprio_set             which
#define __NR64AN1_ioprio_set             who
#define __NR64AN2_ioprio_set             ioprio
#define __NR64AN0_ioprio_get             which
#define __NR64AN1_ioprio_get             who
#define __NR64AN0_inotify_init           TODO_PROTOTYPE
#define __NR64AN0_inotify_add_watch      TODO_PROTOTYPE
#define __NR64AN0_inotify_rm_watch       TODO_PROTOTYPE
#define __NR64AN0_migrate_pages          TODO_PROTOTYPE
#define __NR64AN0_openat                 dirfd
#define __NR64AN1_openat                 filename
#define __NR64AN2_openat                 oflags
#define __NR64AN3_openat                 mode
#define __NR64AN0_mkdirat                dirfd
#define __NR64AN1_mkdirat                pathname
#define __NR64AN2_mkdirat                mode
#define __NR64AN0_mknodat                dirfd
#define __NR64AN1_mknodat                nodename
#define __NR64AN2_mknodat                mode
#define __NR64AN3_mknodat                dev
#define __NR64AN0_fchownat               dirfd
#define __NR64AN1_fchownat               filename
#define __NR64AN2_fchownat               owner
#define __NR64AN3_fchownat               group
#define __NR64AN4_fchownat               flags
#define __NR64AN0_futimesat              dirfd
#define __NR64AN1_futimesat              filename
#define __NR64AN2_futimesat              times
#define __NR64AN0_linux_fstatat          dirfd
#define __NR64AN1_linux_fstatat          filename
#define __NR64AN2_linux_fstatat          statbuf
#define __NR64AN3_linux_fstatat          flags
#define __NR64AN0_unlinkat               dirfd
#define __NR64AN1_unlinkat               name
#define __NR64AN2_unlinkat               flags
#define __NR64AN0_renameat               oldfd
#define __NR64AN1_renameat               oldname
#define __NR64AN2_renameat               newfd
#define __NR64AN3_renameat               newname_or_path
#define __NR64AN0_linkat                 fromfd
#define __NR64AN1_linkat                 existing_file
#define __NR64AN2_linkat                 tofd
#define __NR64AN3_linkat                 target_path
#define __NR64AN4_linkat                 flags
#define __NR64AN0_symlinkat              link_text
#define __NR64AN1_symlinkat              tofd
#define __NR64AN2_symlinkat              target_path
#define __NR64AN0_readlinkat             dirfd
#define __NR64AN1_readlinkat             path
#define __NR64AN2_readlinkat             buf
#define __NR64AN3_readlinkat             buflen
#define __NR64AN0_fchmodat               dirfd
#define __NR64AN1_fchmodat               filename
#define __NR64AN2_fchmodat               mode
#define __NR64AN3_fchmodat               flags
#define __NR64AN0_faccessat              dirfd
#define __NR64AN1_faccessat              filename
#define __NR64AN2_faccessat              type
#define __NR64AN3_faccessat              flags
#define __NR64AN0_pselect6               nfds
#define __NR64AN1_pselect6               readfds
#define __NR64AN2_pselect6               writefds
#define __NR64AN3_pselect6               exceptfds
#define __NR64AN4_pselect6               timeout
#define __NR64AN5_pselect6               sigmask_sigset_and_len
#define __NR64AN0_ppoll                  fds
#define __NR64AN1_ppoll                  nfds
#define __NR64AN2_ppoll                  timeout_ts
#define __NR64AN3_ppoll                  sigmask
#define __NR64AN4_ppoll                  sigsetsize
#define __NR64AN0_unshare                flags
#define __NR64AN0_set_robust_list        TODO_PROTOTYPE
#define __NR64AN0_get_robust_list        TODO_PROTOTYPE
#define __NR64AN0_splice                 fdin
#define __NR64AN1_splice                 offin
#define __NR64AN2_splice                 fdout
#define __NR64AN3_splice                 offout
#define __NR64AN4_splice                 length
#define __NR64AN5_splice                 flags
#define __NR64AN0_tee                    fdin
#define __NR64AN1_tee                    fdout
#define __NR64AN2_tee                    length
#define __NR64AN3_tee                    flags
#define __NR64AN0_sync_file_range        fd
#define __NR64AN1_sync_file_range        offset
#define __NR64AN2_sync_file_range        count
#define __NR64AN3_sync_file_range        flags
#define __NR64AN0_vmsplice               fdout
#define __NR64AN1_vmsplice               iov
#define __NR64AN2_vmsplice               count
#define __NR64AN3_vmsplice               flags
#define __NR64AN0_move_pages             TODO_PROTOTYPE
#define __NR64AN0_utimensat              dirfd
#define __NR64AN1_utimensat              filename
#define __NR64AN2_utimensat              times
#define __NR64AN3_utimensat              flags
#define __NR64AN0_epoll_pwait            epfd
#define __NR64AN1_epoll_pwait            events
#define __NR64AN2_epoll_pwait            maxevents
#define __NR64AN3_epoll_pwait            timeout
#define __NR64AN4_epoll_pwait            ss
#define __NR64AN0_signalfd               fd
#define __NR64AN1_signalfd               sigmask
#define __NR64AN2_signalfd               sigsetsize
#define __NR64AN0_timerfd_create         clock_id
#define __NR64AN1_timerfd_create         flags
#define __NR64AN0_eventfd                initval
#define __NR64AN0_fallocate              fd
#define __NR64AN1_fallocate              mode
#define __NR64AN2_fallocate              offset
#define __NR64AN3_fallocate              length
#define __NR64AN0_timerfd_settime        ufd
#define __NR64AN1_timerfd_settime        flags
#define __NR64AN2_timerfd_settime        utmr
#define __NR64AN3_timerfd_settime        otmr
#define __NR64AN0_timerfd_gettime        ufd
#define __NR64AN1_timerfd_gettime        otmr
#define __NR64AN0_accept4                sockfd
#define __NR64AN1_accept4                addr
#define __NR64AN2_accept4                addr_len
#define __NR64AN3_accept4                flags
#define __NR64AN0_signalfd4              fd
#define __NR64AN1_signalfd4              sigmask
#define __NR64AN2_signalfd4              sigsetsize
#define __NR64AN3_signalfd4              flags
#define __NR64AN0_eventfd2               initval
#define __NR64AN1_eventfd2               flags
#define __NR64AN0_epoll_create1          flags
#define __NR64AN0_dup3                   oldfd
#define __NR64AN1_dup3                   newfd
#define __NR64AN2_dup3                   flags
#define __NR64AN0_pipe2                  pipedes
#define __NR64AN1_pipe2                  flags
#define __NR64AN0_inotify_init1          TODO_PROTOTYPE
#define __NR64AN0_preadv                 fd
#define __NR64AN1_preadv                 iovec
#define __NR64AN2_preadv                 count
#define __NR64AN3_preadv                 offset
#define __NR64AN0_pwritev                fd
#define __NR64AN1_pwritev                iovec
#define __NR64AN2_pwritev                count
#define __NR64AN3_pwritev                offset
#define __NR64AN0_rt_tgsigqueueinfo      tgid
#define __NR64AN1_rt_tgsigqueueinfo      tid
#define __NR64AN2_rt_tgsigqueueinfo      signo
#define __NR64AN3_rt_tgsigqueueinfo      uinfo
#define __NR64AN0_perf_event_open        TODO_PROTOTYPE
#define __NR64AN0_recvmmsg               sockfd
#define __NR64AN1_recvmmsg               vmessages
#define __NR64AN2_recvmmsg               vlen
#define __NR64AN3_recvmmsg               flags
#define __NR64AN4_recvmmsg               tmo
#define __NR64AN0_fanotify_init          TODO_PROTOTYPE
#define __NR64AN0_fanotify_mark          TODO_PROTOTYPE
#define __NR64AN0_prlimit64              pid
#define __NR64AN1_prlimit64              resource
#define __NR64AN2_prlimit64              new_limit
#define __NR64AN3_prlimit64              old_limit
#define __NR64AN0_name_to_handle_at      dirfd
#define __NR64AN1_name_to_handle_at      name
#define __NR64AN2_name_to_handle_at      handle
#define __NR64AN3_name_to_handle_at      mnt_id
#define __NR64AN4_name_to_handle_at      flags
#define __NR64AN0_open_by_handle_at      mountdirfd
#define __NR64AN1_open_by_handle_at      handle
#define __NR64AN2_open_by_handle_at      flags
#define __NR64AN0_clock_adjtime          TODO_PROTOTYPE
#define __NR64AN0_syncfs                 fd
#define __NR64AN0_sendmmsg               sockfd
#define __NR64AN1_sendmmsg               vmessages
#define __NR64AN2_sendmmsg               vlen
#define __NR64AN3_sendmmsg               flags
#define __NR64AN0_setns                  fd
#define __NR64AN1_setns                  nstype
#define __NR64AN0_getcpu                 cpu
#define __NR64AN1_getcpu                 node
#define __NR64AN2_getcpu                 tcache
#define __NR64AN0_process_vm_readv       pid
#define __NR64AN1_process_vm_readv       lvec
#define __NR64AN2_process_vm_readv       liovcnt
#define __NR64AN3_process_vm_readv       rvec
#define __NR64AN4_process_vm_readv       riovcnt
#define __NR64AN5_process_vm_readv       flags
#define __NR64AN0_process_vm_writev      pid
#define __NR64AN1_process_vm_writev      lvec
#define __NR64AN2_process_vm_writev      liovcnt
#define __NR64AN3_process_vm_writev      rvec
#define __NR64AN4_process_vm_writev      riovcnt
#define __NR64AN5_process_vm_writev      flags
#define __NR64AN0_kcmp                   pid1
#define __NR64AN1_kcmp                   pid2
#define __NR64AN2_kcmp                   type
#define __NR64AN3_kcmp                   idx1
#define __NR64AN4_kcmp                   idx2
#define __NR64AN0_finit_module           TODO_PROTOTYPE
#define __NR64AN0_sched_setattr          TODO_PROTOTYPE
#define __NR64AN0_sched_getattr          TODO_PROTOTYPE
#define __NR64AN0_renameat2              olddirfd
#define __NR64AN1_renameat2              oldpath
#define __NR64AN2_renameat2              newdirfd
#define __NR64AN3_renameat2              newpath
#define __NR64AN4_renameat2              flags
#define __NR64AN0_seccomp                TODO_PROTOTYPE
#define __NR64AN0_getrandom              TODO_PROTOTYPE
#define __NR64AN0_memfd_create           TODO_PROTOTYPE
#define __NR64AN0_kexec_file_load        TODO_PROTOTYPE
#define __NR64AN0_bpf                    TODO_PROTOTYPE
#define __NR64AN0_execveat               dirfd
#define __NR64AN1_execveat               pathname
#define __NR64AN2_execveat               argv
#define __NR64AN3_execveat               envp
#define __NR64AN4_execveat               flags
#define __NR64AN0_userfaultfd            TODO_PROTOTYPE
#define __NR64AN0_membarrier             TODO_PROTOTYPE
#define __NR64AN0_mlock2                 TODO_PROTOTYPE
#define __NR64AN0_readf                  fd
#define __NR64AN1_readf                  buf
#define __NR64AN2_readf                  bufsize
#define __NR64AN3_readf                  mode
#define __NR64AN0_writef                 fd
#define __NR64AN1_writef                 buf
#define __NR64AN2_writef                 bufsize
#define __NR64AN3_writef                 mode
#define __NR64AN0_hop                    fd
#define __NR64AN1_hop                    command
#define __NR64AN2_hop                    arg
#define __NR64AN0_hopf                   fd
#define __NR64AN1_hopf                   command
#define __NR64AN2_hopf                   mode
#define __NR64AN3_hopf                   arg
#define __NR64AN0_kstat                  filename
#define __NR64AN1_kstat                  statbuf
#define __NR64AN0_kfstat                 fd
#define __NR64AN1_kfstat                 statbuf
#define __NR64AN0_klstat                 filename
#define __NR64AN1_klstat                 statbuf
#define __NR64AN0_detach                 pid
#define __NR64AN0_frealpath4             fd
#define __NR64AN1_frealpath4             buf
#define __NR64AN2_frealpath4             buflen
#define __NR64AN3_frealpath4             flags
#define __NR64AN0_frealpathat            dirfd
#define __NR64AN1_frealpathat            filename
#define __NR64AN2_frealpathat            buf
#define __NR64AN3_frealpathat            buflen
#define __NR64AN4_frealpathat            flags
#define __NR64AN0_rpc_schedule           target
#define __NR64AN1_rpc_schedule           flags
#define __NR64AN2_rpc_schedule           program
#define __NR64AN3_rpc_schedule           arguments
#define __NR64AN0_sysctl                 command
#define __NR64AN1_sysctl                 arg
#define __NR64AN0_openpty                amaster
#define __NR64AN1_openpty                aslave
#define __NR64AN2_openpty                name
#define __NR64AN3_openpty                termp
#define __NR64AN4_openpty                winp
#define __NR64AN0_set_exception_handler  mode
#define __NR64AN1_set_exception_handler  handler
#define __NR64AN2_set_exception_handler  handler_sp
#define __NR64AN0_get_exception_handler  pmode
#define __NR64AN1_get_exception_handler  phandler
#define __NR64AN2_get_exception_handler  phandler_sp
#define __NR64AN0_ioctlf                 fd
#define __NR64AN1_ioctlf                 command
#define __NR64AN2_ioctlf                 mode
#define __NR64AN3_ioctlf                 arg
#define __NR64AN0_pread64f               fd
#define __NR64AN1_pread64f               buf
#define __NR64AN2_pread64f               bufsize
#define __NR64AN3_pread64f               offset
#define __NR64AN4_pread64f               mode
#define __NR64AN0_pwrite64f              fd
#define __NR64AN1_pwrite64f              buf
#define __NR64AN2_pwrite64f              bufsize
#define __NR64AN3_pwrite64f              offset
#define __NR64AN4_pwrite64f              mode
#define __NR64AN0_readvf                 fd
#define __NR64AN1_readvf                 iovec
#define __NR64AN2_readvf                 count
#define __NR64AN3_readvf                 mode
#define __NR64AN0_writevf                fd
#define __NR64AN1_writevf                iovec
#define __NR64AN2_writevf                count
#define __NR64AN3_writevf                mode
#define __NR64AN0_set_library_listdef    listdef
#define __NR64AN0_debugtrap              state
#define __NR64AN1_debugtrap              reason
#define __NR64AN0_lfutex                 uaddr
#define __NR64AN1_lfutex                 futex_op
#define __NR64AN2_lfutex                 val
#define __NR64AN3_lfutex                 timeout
#define __NR64AN4_lfutex                 val2
#define __NR64AN0_lfutexexpr             base
#define __NR64AN1_lfutexexpr             exprc
#define __NR64AN2_lfutexexpr             exprv
#define __NR64AN3_lfutexexpr             timeout
#define __NR64AN4_lfutexexpr             timeout_flags
#define __NR64AN0_lfutexlockexpr         ulockaddr
#define __NR64AN1_lfutexlockexpr         base
#define __NR64AN2_lfutexlockexpr         exprc
#define __NR64AN3_lfutexlockexpr         exprv
#define __NR64AN4_lfutexlockexpr         timeout
#define __NR64AN5_lfutexlockexpr         timeout_flags
#define __NR64AN0_mktty                  keyboard
#define __NR64AN1_mktty                  display
#define __NR64AN2_mktty                  name
#define __NR64AN3_mktty                  rsvd
#define __NR64AN0_raiseat                state
#define __NR64AN1_raiseat                si
#define __NR64AN0_coredump               curr_state
#define __NR64AN1_coredump               orig_state
#define __NR64AN2_coredump               traceback_vector
#define __NR64AN3_coredump               traceback_length
#define __NR64AN4_coredump               exception
#define __NR64AN5_coredump               unwind_error
#define __NR64AN0_kreaddir               fd
#define __NR64AN1_kreaddir               buf
#define __NR64AN2_kreaddir               bufsize
#define __NR64AN3_kreaddir               mode
#define __NR64AN0_fchdirat               dirfd
#define __NR64AN1_fchdirat               path
#define __NR64AN2_fchdirat               flags
#define __NR64AN0_fsmode                 mode
#define __NR64AN0_maplibrary             addr
#define __NR64AN1_maplibrary             flags
#define __NR64AN2_maplibrary             fd
#define __NR64AN3_maplibrary             hdrv
#define __NR64AN4_maplibrary             hdrc
#define __NR64AN0_kreaddirf              fd
#define __NR64AN1_kreaddirf              buf
#define __NR64AN2_kreaddirf              bufsize
#define __NR64AN3_kreaddirf              mode
#define __NR64AN4_kreaddirf              iomode
#define __NR64AN0_fmkdirat               dirfd
#define __NR64AN1_fmkdirat               pathname
#define __NR64AN2_fmkdirat               mode
#define __NR64AN3_fmkdirat               flags
#define __NR64AN0_fmknodat               dirfd
#define __NR64AN1_fmknodat               nodename
#define __NR64AN2_fmknodat               mode
#define __NR64AN3_fmknodat               dev
#define __NR64AN4_fmknodat               flags
#define __NR64AN0_kfstatat               dirfd
#define __NR64AN1_kfstatat               filename
#define __NR64AN2_kfstatat               statbuf
#define __NR64AN3_kfstatat               flags
#define __NR64AN0_frenameat              oldfd
#define __NR64AN1_frenameat              oldname
#define __NR64AN2_frenameat              newfd
#define __NR64AN3_frenameat              newname_or_path
#define __NR64AN4_frenameat              flags
#define __NR64AN0_fsymlinkat             link_text
#define __NR64AN1_fsymlinkat             tofd
#define __NR64AN2_fsymlinkat             target_path
#define __NR64AN3_fsymlinkat             flags
#define __NR64AN0_freadlinkat            dirfd
#define __NR64AN1_freadlinkat            path
#define __NR64AN2_freadlinkat            buf
#define __NR64AN3_freadlinkat            buflen
#define __NR64AN4_freadlinkat            flags
#define __NR64AN0_preadvf                fd
#define __NR64AN1_preadvf                iovec
#define __NR64AN2_preadvf                count
#define __NR64AN3_preadvf                offset
#define __NR64AN4_preadvf                mode
#define __NR64AN0_pwritevf               fd
#define __NR64AN1_pwritevf               iovec
#define __NR64AN2_pwritevf               count
#define __NR64AN3_pwritevf               offset
#define __NR64AN4_pwritevf               mode
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES */
#endif /* __WANT_SYSCALL_ARGUMENT_NAMES */


/************************************************************************/
/* SYSCALL ARGUMENT FORMAT                                              */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_FORMAT
#ifndef __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#define __NR64FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT 1
#define __NR64ATRF0_read                   "%d"
#define __NR64ATRA0_read(fd, buf, bufsize) ,(int)(fd)
#define __NR64ATRF1_read                   "%p"
#define __NR64ATRA1_read(fd, buf, bufsize) ,buf
#define __NR64ATRF2_read                   "%" PRIuSIZ
#define __NR64ATRA2_read(fd, buf, bufsize) ,bufsize
#define __NR64ATRF0_write                  "%d"
#define __NR64ATRA0_write(fd, buf, bufsize) ,(int)(fd)
#define __NR64ATRF1_write                  "%p"
#define __NR64ATRA1_write(fd, buf, bufsize) ,buf
#define __NR64ATRF2_write                  "%" PRIuSIZ
#define __NR64ATRA2_write(fd, buf, bufsize) ,bufsize
#define __NR64ATRF0_open                   "%q"
#define __NR64ATRA0_open(filename, oflags, mode) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_open                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA1_open(filename, oflags, mode) ,(uintptr_t)(oflags),(oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
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
#define __NR64ATRF2_open                   "%#" PRIoSIZ
#define __NR64ATRA2_open(filename, oflags, mode) ,(uintptr_t)(mode)
#define __NR64ATRF0_close                  "%d"
#define __NR64ATRA0_close(fd)              ,(int)(fd)
#define __NR64ATRF0_linux_stat64           "%q"
#define __NR64ATRA0_linux_stat64(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_linux_stat64           "%p"
#define __NR64ATRA1_linux_stat64(filename, statbuf) ,statbuf
#define __NR64ATRF0_linux_fstat64          "%d"
#define __NR64ATRA0_linux_fstat64(fd, statbuf) ,(int)(fd)
#define __NR64ATRF1_linux_fstat64          "%p"
#define __NR64ATRA1_linux_fstat64(fd, statbuf) ,statbuf
#define __NR64ATRF0_linux_lstat64          "%q"
#define __NR64ATRA0_linux_lstat64(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_linux_lstat64          "%p"
#define __NR64ATRA1_linux_lstat64(filename, statbuf) ,statbuf
#define __NR64ATRF0_poll                   "%p"
#define __NR64ATRA0_poll(fds, nfds, timeout) ,fds
#define __NR64ATRF1_poll                   "%" PRIuSIZ
#define __NR64ATRA1_poll(fds, nfds, timeout) ,nfds
#define __NR64ATRF2_poll                   "%" PRIdSIZ
#define __NR64ATRA2_poll(fds, nfds, timeout) ,(intptr_t)(timeout)
#define __NR64ATRF0_lseek64                "%d"
#define __NR64ATRA0_lseek64(fd, offset, whence) ,(int)(fd)
#define __NR64ATRF1_lseek64                "%" PRId64
#define __NR64ATRA1_lseek64(fd, offset, whence) ,offset
#define __NR64ATRF2_lseek64                "%#Ix=%s"
#define __NR64ATRA2_lseek64(fd, offset, whence) ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NR64ATRF0_mmap                   "%p"
#define __NR64ATRA0_mmap(addr, len, prot, flags, fd, offset) ,addr
#define __NR64ATRF1_mmap                   "%" PRIuSIZ
#define __NR64ATRA1_mmap(addr, len, prot, flags, fd, offset) ,len
#define __NR64ATRF2_mmap                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA2_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(prot),(prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                                             ,((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "",(prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                                             ,((prot) & PROT_READ) && ((prot) & (PROT_EXEC|PROT_WRITE)) ? "|" : "",(prot) & PROT_READ ? "PROT_READ" : "" \
                                                             ,((prot) & PROT_SEM) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ)) ? "|" : "",(prot) & PROT_SEM ? "PROT_SEM" : "" \
                                                             ,((prot) & PROT_LOOSE) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM)) ? "|" : "",(prot) & PROT_LOOSE ? "PROT_LOOSE" : "" \
                                                             ,((prot) & PROT_SHARED) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE)) ? "|" : "",(prot) & PROT_SHARED ? "PROT_SHARED" : ""
#define __NR64ATRF3_mmap                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA3_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(flags),(flags) & MAP_SHARED ? "MAP_SHARED" : (flags) ? "" : "MAP_AUTOMATIC" \
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
                                                             ,((flags) & MAP_DONT_OVERRIDE) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE|MAP_POPULATE|MAP_NONBLOCK|MAP_STACK|MAP_UNINITIALIZED|MAP_DONT_MAP)) ? "|" : "",(flags) & MAP_DONT_OVERRIDE ? "MAP_DONT_OVERRIDE" : ""
#define __NR64ATRF4_mmap                   "%d"
#define __NR64ATRA4_mmap(addr, len, prot, flags, fd, offset) ,(int)(fd)
#define __NR64ATRF5_mmap                   "%#" PRIxSIZ
#define __NR64ATRA5_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(offset)
#define __NR64ATRF0_mprotect               "%p"
#define __NR64ATRA0_mprotect(addr, len, prot) ,addr
#define __NR64ATRF1_mprotect               "%" PRIuSIZ
#define __NR64ATRA1_mprotect(addr, len, prot) ,len
#define __NR64ATRF2_mprotect               "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR64ATRA2_mprotect(addr, len, prot) ,(uintptr_t)(prot),(prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                              ,((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "",(prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                              ,((prot) & PROT_READ) && ((prot) & (PROT_EXEC|PROT_WRITE)) ? "|" : "",(prot) & PROT_READ ? "PROT_READ" : "" \
                                              ,((prot) & PROT_SEM) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ)) ? "|" : "",(prot) & PROT_SEM ? "PROT_SEM" : ""
#define __NR64ATRF0_munmap                 "%p"
#define __NR64ATRA0_munmap(addr, len)      ,addr
#define __NR64ATRF1_munmap                 "%" PRIuSIZ
#define __NR64ATRA1_munmap(addr, len)      ,len
#define __NR64ATRF0_brk                    "%p"
#define __NR64ATRA0_brk(addr)              ,addr
#define __NR64ATRF0_rt_sigaction           "%#" PRIxSIZ
#define __NR64ATRA0_rt_sigaction(signo, act, oact, sigsetsize) ,(uintptr_t)(signo)
#define __NR64ATRF1_rt_sigaction           "%p"
#define __NR64ATRA1_rt_sigaction(signo, act, oact, sigsetsize) ,act
#define __NR64ATRF2_rt_sigaction           "%p"
#define __NR64ATRA2_rt_sigaction(signo, act, oact, sigsetsize) ,oact
#define __NR64ATRF3_rt_sigaction           "%" PRIuSIZ
#define __NR64ATRA3_rt_sigaction(signo, act, oact, sigsetsize) ,sigsetsize
#define __NR64ATRF0_rt_sigprocmask         "%#" PRIxSIZ
#define __NR64ATRA0_rt_sigprocmask(how, set, oset, sigsetsize) ,(uintptr_t)(how)
#define __NR64ATRF1_rt_sigprocmask         "%p"
#define __NR64ATRA1_rt_sigprocmask(how, set, oset, sigsetsize) ,set
#define __NR64ATRF2_rt_sigprocmask         "%p"
#define __NR64ATRA2_rt_sigprocmask(how, set, oset, sigsetsize) ,oset
#define __NR64ATRF3_rt_sigprocmask         "%" PRIuSIZ
#define __NR64ATRA3_rt_sigprocmask(how, set, oset, sigsetsize) ,sigsetsize
#define __NR64ATRF0_rt_sigreturn           "%p"
#define __NR64ATRA0_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) ,restore_fpu
#define __NR64ATRF1_rt_sigreturn           "%p"
#define __NR64ATRA1_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) ,restore_sigmask
#define __NR64ATRF2_rt_sigreturn           "%p"
#define __NR64ATRA2_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) ,sc_info
#define __NR64ATRF3_rt_sigreturn           "%p"
#define __NR64ATRA3_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) ,restore_cpu
#define __NR64ATRF0_ioctl                  "%d"
#define __NR64ATRA0_ioctl(fd, request, arg) ,(int)(fd)
#define __NR64ATRF1_ioctl                  "%#" PRIxSIZ
#define __NR64ATRA1_ioctl(fd, request, arg) ,(uintptr_t)(request)
#define __NR64ATRF2_ioctl                  "%p"
#define __NR64ATRA2_ioctl(fd, request, arg) ,arg
#define __NR64ATRF0_pread64                "%d"
#define __NR64ATRA0_pread64(fd, buf, bufsize, offset) ,(int)(fd)
#define __NR64ATRF1_pread64                "%p"
#define __NR64ATRA1_pread64(fd, buf, bufsize, offset) ,buf
#define __NR64ATRF2_pread64                "%" PRIuSIZ
#define __NR64ATRA2_pread64(fd, buf, bufsize, offset) ,bufsize
#define __NR64ATRF3_pread64                "%" PRIu64
#define __NR64ATRA3_pread64(fd, buf, bufsize, offset) ,offset
#define __NR64ATRF0_pwrite64               "%d"
#define __NR64ATRA0_pwrite64(fd, buf, bufsize, offset) ,(int)(fd)
#define __NR64ATRF1_pwrite64               "%p"
#define __NR64ATRA1_pwrite64(fd, buf, bufsize, offset) ,buf
#define __NR64ATRF2_pwrite64               "%" PRIuSIZ
#define __NR64ATRA2_pwrite64(fd, buf, bufsize, offset) ,bufsize
#define __NR64ATRF3_pwrite64               "%" PRIu64
#define __NR64ATRA3_pwrite64(fd, buf, bufsize, offset) ,offset
#define __NR64ATRF0_readv                  "%d"
#define __NR64ATRA0_readv(fd, iovec, count) ,(int)(fd)
#define __NR64ATRF1_readv                  "%p"
#define __NR64ATRA1_readv(fd, iovec, count) ,iovec
#define __NR64ATRF2_readv                  "%" PRIuSIZ
#define __NR64ATRA2_readv(fd, iovec, count) ,count
#define __NR64ATRF0_writev                 "%d"
#define __NR64ATRA0_writev(fd, iovec, count) ,(int)(fd)
#define __NR64ATRF1_writev                 "%p"
#define __NR64ATRA1_writev(fd, iovec, count) ,iovec
#define __NR64ATRF2_writev                 "%" PRIuSIZ
#define __NR64ATRA2_writev(fd, iovec, count) ,count
#define __NR64ATRF0_access                 "%q"
#define __NR64ATRA0_access(filename, type) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_access                 "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA1_access(filename, type) ,(uintptr_t)(type),(type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                           ,((type) & W_OK) && ((type) & (R_OK)) ? "|" : "",(type) & W_OK ? "W_OK" : "" \
                                           ,((type) & X_OK) && ((type) & (R_OK|W_OK)) ? "|" : "",(type) & X_OK ? "X_OK" : ""
#define __NR64ATRF0_pipe                   "%p"
#define __NR64ATRA0_pipe(pipedes)          ,pipedes
#define __NR64ATRF0_select                 "%" PRIuSIZ
#define __NR64ATRA0_select(nfds, readfds, writefds, exceptfds, timeout) ,nfds
#define __NR64ATRF1_select                 "%p"
#define __NR64ATRA1_select(nfds, readfds, writefds, exceptfds, timeout) ,readfds
#define __NR64ATRF2_select                 "%p"
#define __NR64ATRA2_select(nfds, readfds, writefds, exceptfds, timeout) ,writefds
#define __NR64ATRF3_select                 "%p"
#define __NR64ATRA3_select(nfds, readfds, writefds, exceptfds, timeout) ,exceptfds
#define __NR64ATRF4_select                 "%p"
#define __NR64ATRA4_select(nfds, readfds, writefds, exceptfds, timeout) ,timeout
#define __NR64ATRF0_mremap                 "%p"
#define __NR64ATRA0_mremap(addr, old_len, new_len, flags, new_address) ,addr
#define __NR64ATRF1_mremap                 "%" PRIuSIZ
#define __NR64ATRA1_mremap(addr, old_len, new_len, flags, new_address) ,old_len
#define __NR64ATRF2_mremap                 "%" PRIuSIZ
#define __NR64ATRA2_mremap(addr, old_len, new_len, flags, new_address) ,new_len
#define __NR64ATRF3_mremap                 "%#" PRIxSIZ "=%s%s%s"
#define __NR64ATRA3_mremap(addr, old_len, new_len, flags, new_address) ,(uintptr_t)(flags),(flags) & MREMAP_MAYMOVE ? "MREMAP_MAYMOVE" : "" \
                                                                       ,((flags) & MREMAP_FIXED) && ((flags) & (MREMAP_MAYMOVE)) ? "|" : "",(flags) & MREMAP_FIXED ? "MREMAP_FIXED" : ""
#define __NR64ATRF4_mremap                 "%p"
#define __NR64ATRA4_mremap(addr, old_len, new_len, flags, new_address) ,new_address
#define __NR64ATRF0_msync                  "%p"
#define __NR64ATRA0_msync(addr, len, flags) ,addr
#define __NR64ATRF1_msync                  "%" PRIuSIZ
#define __NR64ATRA1_msync(addr, len, flags) ,len
#define __NR64ATRF2_msync                  "%#" PRIxSIZ
#define __NR64ATRA2_msync(addr, len, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_mincore                "%p"
#define __NR64ATRA0_mincore(start, len, vec) ,start
#define __NR64ATRF1_mincore                "%" PRIuSIZ
#define __NR64ATRA1_mincore(start, len, vec) ,len
#define __NR64ATRF2_mincore                "%p"
#define __NR64ATRA2_mincore(start, len, vec) ,vec
#define __NR64ATRF0_madvise                "%p"
#define __NR64ATRA0_madvise(addr, len, advice) ,addr
#define __NR64ATRF1_madvise                "%" PRIuSIZ
#define __NR64ATRA1_madvise(addr, len, advice) ,len
#define __NR64ATRF2_madvise                "%#" PRIxSIZ
#define __NR64ATRA2_madvise(addr, len, advice) ,(uintptr_t)(advice)
#define __NR64ATRF0_shmget                 "%d"
#define __NR64ATRA0_shmget(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_shmat                  "%d"
#define __NR64ATRA0_shmat(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR64ATRF0_shmctl                 "%d"
#define __NR64ATRA0_shmctl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_dup                    "%d"
#define __NR64ATRA0_dup(fd)                ,(int)(fd)
#define __NR64ATRF0_dup2                   "%d"
#define __NR64ATRA0_dup2(oldfd, newfd)     ,(int)(oldfd)
#define __NR64ATRF1_dup2                   "%d"
#define __NR64ATRA1_dup2(oldfd, newfd)     ,(int)(newfd)
#define __NR64ATRF0_nanosleep              "%p"
#define __NR64ATRA0_nanosleep(req, rem)    ,req
#define __NR64ATRF1_nanosleep              "%p"
#define __NR64ATRA1_nanosleep(req, rem)    ,rem
#define __NR64ATRF0_getitimer              "%#" PRIxSIZ
#define __NR64ATRA0_getitimer(which, curr_value) ,(uintptr_t)(which)
#define __NR64ATRF1_getitimer              "%p"
#define __NR64ATRA1_getitimer(which, curr_value) ,curr_value
#define __NR64ATRF0_alarm                  "%#" PRIxSIZ
#define __NR64ATRA0_alarm(seconds)         ,(uintptr_t)(seconds)
#define __NR64ATRF0_setitimer              "%#" PRIxSIZ
#define __NR64ATRA0_setitimer(which, newval, oldval) ,(uintptr_t)(which)
#define __NR64ATRF1_setitimer              "%p"
#define __NR64ATRA1_setitimer(which, newval, oldval) ,newval
#define __NR64ATRF2_setitimer              "%p"
#define __NR64ATRA2_setitimer(which, newval, oldval) ,oldval
#define __NR64ATRF0_sendfile               "%d"
#define __NR64ATRA0_sendfile(out_fd, in_fd, offset, count) ,(int)(out_fd)
#define __NR64ATRF1_sendfile               "%d"
#define __NR64ATRA1_sendfile(out_fd, in_fd, offset, count) ,(int)(in_fd)
#define __NR64ATRF2_sendfile               "%p"
#define __NR64ATRA2_sendfile(out_fd, in_fd, offset, count) ,offset
#define __NR64ATRF3_sendfile               "%" PRIuSIZ
#define __NR64ATRA3_sendfile(out_fd, in_fd, offset, count) ,count
#define __NR64ATRF0_socket                 "%#" PRIxSIZ
#define __NR64ATRA0_socket(domain, type, protocol) ,(uintptr_t)(domain)
#define __NR64ATRF1_socket                 "%#" PRIxSIZ
#define __NR64ATRA1_socket(domain, type, protocol) ,(uintptr_t)(type)
#define __NR64ATRF2_socket                 "%#" PRIxSIZ
#define __NR64ATRA2_socket(domain, type, protocol) ,(uintptr_t)(protocol)
#define __NR64ATRF0_connect                "%d"
#define __NR64ATRA0_connect(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR64ATRF1_connect                "%p"
#define __NR64ATRA1_connect(sockfd, addr, addr_len) ,addr
#define __NR64ATRF2_connect                "%" PRIuSIZ
#define __NR64ATRA2_connect(sockfd, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NR64ATRF0_accept                 "%d"
#define __NR64ATRA0_accept(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_sendto                 "%d"
#define __NR64ATRA0_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(int)(sockfd)
#define __NR64ATRF1_sendto                 "%p"
#define __NR64ATRA1_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,buf
#define __NR64ATRF2_sendto                 "%" PRIuSIZ
#define __NR64ATRA2_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,bufsize
#define __NR64ATRF3_sendto                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA3_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(flags),(flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                                        ,((flags) & MSG_DONTROUTE) && ((flags) & (MSG_CONFIRM)) ? "|" : "",(flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                                        ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                        ,((flags) & MSG_EOR) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                                        ,((flags) & MSG_MORE) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR)) ? "|" : "",(flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                                        ,((flags) & MSG_NOSIGNAL) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE)) ? "|" : "",(flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                                        ,((flags) & MSG_OOB) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NR64ATRF4_sendto                 "%p"
#define __NR64ATRA4_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,addr
#define __NR64ATRF5_sendto                 "%" PRIuSIZ
#define __NR64ATRA5_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NR64ATRF0_recvfrom               "%d"
#define __NR64ATRA0_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,(int)(sockfd)
#define __NR64ATRF1_recvfrom               "%p"
#define __NR64ATRA1_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,buf
#define __NR64ATRF2_recvfrom               "%" PRIuSIZ
#define __NR64ATRA2_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,bufsize
#define __NR64ATRF3_recvfrom               "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA3_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(flags),(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                          ,((flags) & MSG_ERRQUEUE) && ((flags) & (MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                                          ,((flags) & MSG_OOB) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                                          ,((flags) & MSG_PEEK) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB)) ? "|" : "",(flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                                          ,((flags) & MSG_TRUNC) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK)) ? "|" : "",(flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                                          ,((flags) & MSG_WAITALL) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK|MSG_TRUNC)) ? "|" : "",(flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NR64ATRF4_recvfrom               "%p"
#define __NR64ATRA4_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,addr
#define __NR64ATRF5_recvfrom               "%p"
#define __NR64ATRA5_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,addr_len
#define __NR64ATRF0_sendmsg                "%d"
#define __NR64ATRA0_sendmsg(sockfd, message, flags) ,(int)(sockfd)
#define __NR64ATRF1_sendmsg                "%p"
#define __NR64ATRA1_sendmsg(sockfd, message, flags) ,message
#define __NR64ATRF2_sendmsg                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA2_sendmsg(sockfd, message, flags) ,(uintptr_t)(flags),(flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                    ,((flags) & MSG_DONTROUTE) && ((flags) & (MSG_CONFIRM)) ? "|" : "",(flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                    ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                    ,((flags) & MSG_EOR) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                    ,((flags) & MSG_MORE) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR)) ? "|" : "",(flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                    ,((flags) & MSG_NOSIGNAL) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE)) ? "|" : "",(flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                    ,((flags) & MSG_OOB) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NR64ATRF0_recvmsg                "%d"
#define __NR64ATRA0_recvmsg(sockfd, message, flags) ,(int)(sockfd)
#define __NR64ATRF1_recvmsg                "%p"
#define __NR64ATRA1_recvmsg(sockfd, message, flags) ,message
#define __NR64ATRF2_recvmsg                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA2_recvmsg(sockfd, message, flags) ,(uintptr_t)(flags),(flags) & MSG_CMSG_CLOEXEC ? "MSG_CMSG_CLOEXEC" : "" \
                                                    ,((flags) & MSG_CMSG_CLOFORK) && ((flags) & (MSG_CMSG_CLOEXEC)) ? "|" : "",(flags) & MSG_CMSG_CLOFORK ? "MSG_CMSG_CLOFORK" : "" \
                                                    ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                    ,((flags) & MSG_ERRQUEUE) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                    ,((flags) & MSG_OOB) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                    ,((flags) & MSG_PEEK) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB)) ? "|" : "",(flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                    ,((flags) & MSG_TRUNC) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK)) ? "|" : "",(flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                    ,((flags) & MSG_WAITALL) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK|MSG_TRUNC)) ? "|" : "",(flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NR64ATRF0_shutdown               "%d"
#define __NR64ATRA0_shutdown(sockfd, how)  ,(int)(sockfd)
#define __NR64ATRF1_shutdown               "%#Ix=%s"
#define __NR64ATRA1_shutdown(sockfd, how)  ,(how),(how) == SHUT_RD ? "SHUT_RD" : (how) == SHUT_WR ? "SHUT_WR" : (how) == SHUT_RDWR ? "SHUT_RDWR" : "?"
#define __NR64ATRF0_bind                   "%d"
#define __NR64ATRA0_bind(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR64ATRF1_bind                   "%p"
#define __NR64ATRA1_bind(sockfd, addr, addr_len) ,addr
#define __NR64ATRF2_bind                   "%" PRIuSIZ
#define __NR64ATRA2_bind(sockfd, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NR64ATRF0_listen                 "%d"
#define __NR64ATRA0_listen(sockfd, max_backlog) ,(int)(sockfd)
#define __NR64ATRF1_listen                 "%#" PRIxSIZ
#define __NR64ATRA1_listen(sockfd, max_backlog) ,(uintptr_t)(max_backlog)
#define __NR64ATRF0_getsockname            "%d"
#define __NR64ATRA0_getsockname(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR64ATRF1_getsockname            "%p"
#define __NR64ATRA1_getsockname(sockfd, addr, addr_len) ,addr
#define __NR64ATRF2_getsockname            "%p"
#define __NR64ATRA2_getsockname(sockfd, addr, addr_len) ,addr_len
#define __NR64ATRF0_getpeername            "%d"
#define __NR64ATRA0_getpeername(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR64ATRF1_getpeername            "%p"
#define __NR64ATRA1_getpeername(sockfd, addr, addr_len) ,addr
#define __NR64ATRF2_getpeername            "%p"
#define __NR64ATRA2_getpeername(sockfd, addr, addr_len) ,addr_len
#define __NR64ATRF0_socketpair             "%#" PRIxSIZ
#define __NR64ATRA0_socketpair(domain, type, protocol, fds) ,(uintptr_t)(domain)
#define __NR64ATRF1_socketpair             "%#" PRIxSIZ
#define __NR64ATRA1_socketpair(domain, type, protocol, fds) ,(uintptr_t)(type)
#define __NR64ATRF2_socketpair             "%#" PRIxSIZ
#define __NR64ATRA2_socketpair(domain, type, protocol, fds) ,(uintptr_t)(protocol)
#define __NR64ATRF3_socketpair             "%p"
#define __NR64ATRA3_socketpair(domain, type, protocol, fds) ,fds
#define __NR64ATRF0_setsockopt             "%d"
#define __NR64ATRA0_setsockopt(sockfd, level, optname, optval, optlen) ,(int)(sockfd)
#define __NR64ATRF1_setsockopt             "%#Ix=%s"
#define __NR64ATRA1_setsockopt(sockfd, level, optname, optval, optlen) ,(level),(level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NR64ATRF2_setsockopt             "%#" PRIxSIZ
#define __NR64ATRA2_setsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optname)
#define __NR64ATRF3_setsockopt             "%p"
#define __NR64ATRA3_setsockopt(sockfd, level, optname, optval, optlen) ,optval
#define __NR64ATRF4_setsockopt             "%" PRIuSIZ
#define __NR64ATRA4_setsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optlen)
#define __NR64ATRF0_getsockopt             "%d"
#define __NR64ATRA0_getsockopt(sockfd, level, optname, optval, optlen) ,(int)(sockfd)
#define __NR64ATRF1_getsockopt             "%#Ix=%s"
#define __NR64ATRA1_getsockopt(sockfd, level, optname, optval, optlen) ,(level),(level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NR64ATRF2_getsockopt             "%#" PRIxSIZ
#define __NR64ATRA2_getsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optname)
#define __NR64ATRF3_getsockopt             "%p"
#define __NR64ATRA3_getsockopt(sockfd, level, optname, optval, optlen) ,optval
#define __NR64ATRF4_getsockopt             "%p"
#define __NR64ATRA4_getsockopt(sockfd, level, optname, optval, optlen) ,optlen
#define __NR64ATRF0_clone                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA0_clone(flags, child_stack, ptid, ctid, newtls) ,(uintptr_t)(flags),(flags) & CLONE_VM ? "CLONE_VM" : "" \
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
#define __NR64ATRF1_clone                  "%p"
#define __NR64ATRA1_clone(flags, child_stack, ptid, ctid, newtls) ,child_stack
#define __NR64ATRF2_clone                  "%p"
#define __NR64ATRA2_clone(flags, child_stack, ptid, ctid, newtls) ,ptid
#define __NR64ATRF3_clone                  "%p"
#define __NR64ATRA3_clone(flags, child_stack, ptid, ctid, newtls) ,ctid
#define __NR64ATRF4_clone                  "%p"
#define __NR64ATRA4_clone(flags, child_stack, ptid, ctid, newtls) ,newtls
#define __NR64ATRF0_execve                 "%q"
#define __NR64ATRA0_execve(path, argv, envp) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_execve                 "%p"
#define __NR64ATRA1_execve(path, argv, envp) ,argv
#define __NR64ATRF2_execve                 "%p"
#define __NR64ATRA2_execve(path, argv, envp) ,envp
#define __NR64ATRF0_exit                   "%" PRIuSIZ
#define __NR64ATRA0_exit(status)           ,(uintptr_t)(status)
#define __NR64ATRF0_wait4                  "%" PRIdSIZ
#define __NR64ATRA0_wait4(pid, stat_loc, options, usage) ,(intptr_t)(pid)
#define __NR64ATRF1_wait4                  "%p"
#define __NR64ATRA1_wait4(pid, stat_loc, options, usage) ,stat_loc
#define __NR64ATRF2_wait4                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR64ATRA2_wait4(pid, stat_loc, options, usage) ,(uintptr_t)(options),(options) & WNOHANG ? "WNOHANG" : "" \
                                                         ,((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "",(options) & WUNTRACED ? "WUNTRACED" : "" \
                                                         ,((options) & WCONTINUED) && ((options) & (WNOHANG|WUNTRACED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                         ,((options) & WNOWAIT) && ((options) & (WNOHANG|WUNTRACED|WCONTINUED)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NR64ATRF3_wait4                  "%p"
#define __NR64ATRA3_wait4(pid, stat_loc, options, usage) ,usage
#define __NR64ATRF0_kill                   "%" PRIdSIZ
#define __NR64ATRA0_kill(pid, signo)       ,(intptr_t)(pid)
#define __NR64ATRF1_kill                   "%#" PRIxSIZ
#define __NR64ATRA1_kill(pid, signo)       ,(uintptr_t)(signo)
#define __NR64ATRF0_uname                  "%p"
#define __NR64ATRA0_uname(name)            ,name
#define __NR64ATRF0_semget                 "%d"
#define __NR64ATRA0_semget(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_semop                  "%d"
#define __NR64ATRA0_semop(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR64ATRF0_semctl                 "%d"
#define __NR64ATRA0_semctl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_shmdt                  "%d"
#define __NR64ATRA0_shmdt(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR64ATRF0_msgget                 "%d"
#define __NR64ATRA0_msgget(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_msgsnd                 "%d"
#define __NR64ATRA0_msgsnd(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_msgrcv                 "%d"
#define __NR64ATRA0_msgrcv(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_msgctl                 "%d"
#define __NR64ATRA0_msgctl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_fcntl                  "%d"
#define __NR64ATRA0_fcntl(fd, cmd, arg)    ,(int)(fd)
#define __NR64ATRF1_fcntl                  "%#" PRIxSIZ
#define __NR64ATRA1_fcntl(fd, cmd, arg)    ,(uintptr_t)(cmd)
#define __NR64ATRF2_fcntl                  "%p"
#define __NR64ATRA2_fcntl(fd, cmd, arg)    ,arg
#define __NR64ATRF0_flock                  "%d"
#define __NR64ATRA0_flock(fd, operation)   ,(int)(fd)
#define __NR64ATRF1_flock                  "%#" PRIxSIZ
#define __NR64ATRA1_flock(fd, operation)   ,(uintptr_t)(operation)
#define __NR64ATRF0_fsync                  "%d"
#define __NR64ATRA0_fsync(fd)              ,(int)(fd)
#define __NR64ATRF0_fdatasync              "%d"
#define __NR64ATRA0_fdatasync(fd)          ,(int)(fd)
#define __NR64ATRF0_truncate               "%q"
#define __NR64ATRA0_truncate(filename, length) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_truncate               "%#" PRIxSIZ
#define __NR64ATRA1_truncate(filename, length) ,(uintptr_t)(length)
#define __NR64ATRF0_ftruncate              "%d"
#define __NR64ATRA0_ftruncate(fd, length)  ,(int)(fd)
#define __NR64ATRF1_ftruncate              "%#" PRIxSIZ
#define __NR64ATRA1_ftruncate(fd, length)  ,(uintptr_t)(length)
#define __NR64ATRF0_getdents               "%d"
#define __NR64ATRA0_getdents(fd, dirp, count) ,(int)(fd)
#define __NR64ATRF1_getdents               "%p"
#define __NR64ATRA1_getdents(fd, dirp, count) ,dirp
#define __NR64ATRF2_getdents               "%" PRIuSIZ
#define __NR64ATRA2_getdents(fd, dirp, count) ,count
#define __NR64ATRF0_getcwd                 "%p"
#define __NR64ATRA0_getcwd(buf, size)      ,buf
#define __NR64ATRF1_getcwd                 "%" PRIuSIZ
#define __NR64ATRA1_getcwd(buf, size)      ,size
#define __NR64ATRF0_chdir                  "%q"
#define __NR64ATRA0_chdir(path)            ,(validate_readable_opt(path,1),path)
#define __NR64ATRF0_fchdir                 "%d"
#define __NR64ATRA0_fchdir(fd)             ,(int)(fd)
#define __NR64ATRF0_rename                 "%q"
#define __NR64ATRA0_rename(oldname, newname_or_path) ,(validate_readable_opt(oldname,1),oldname)
#define __NR64ATRF1_rename                 "%q"
#define __NR64ATRA1_rename(oldname, newname_or_path) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NR64ATRF0_mkdir                  "%q"
#define __NR64ATRA0_mkdir(pathname, mode)  ,(validate_readable_opt(pathname,1),pathname)
#define __NR64ATRF1_mkdir                  "%#" PRIoSIZ
#define __NR64ATRA1_mkdir(pathname, mode)  ,(uintptr_t)(mode)
#define __NR64ATRF0_rmdir                  "%q"
#define __NR64ATRA0_rmdir(path)            ,(validate_readable_opt(path,1),path)
#define __NR64ATRF0_creat                  "%q"
#define __NR64ATRA0_creat(filename, mode)  ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_creat                  "%#" PRIoSIZ
#define __NR64ATRA1_creat(filename, mode)  ,(uintptr_t)(mode)
#define __NR64ATRF0_link                   "%q"
#define __NR64ATRA0_link(existing_file, link_file) ,(validate_readable_opt(existing_file,1),existing_file)
#define __NR64ATRF1_link                   "%q"
#define __NR64ATRA1_link(existing_file, link_file) ,(validate_readable_opt(link_file,1),link_file)
#define __NR64ATRF0_unlink                 "%q"
#define __NR64ATRA0_unlink(filename)       ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF0_symlink                "%q"
#define __NR64ATRA0_symlink(link_text, target_path) ,(validate_readable_opt(link_text,1),link_text)
#define __NR64ATRF1_symlink                "%q"
#define __NR64ATRA1_symlink(link_text, target_path) ,(validate_readable_opt(target_path,1),target_path)
#define __NR64ATRF0_readlink               "%q"
#define __NR64ATRA0_readlink(path, buf, buflen) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_readlink               "%p"
#define __NR64ATRA1_readlink(path, buf, buflen) ,buf
#define __NR64ATRF2_readlink               "%" PRIuSIZ
#define __NR64ATRA2_readlink(path, buf, buflen) ,buflen
#define __NR64ATRF0_chmod                  "%q"
#define __NR64ATRA0_chmod(filename, mode)  ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_chmod                  "%#" PRIoSIZ
#define __NR64ATRA1_chmod(filename, mode)  ,(uintptr_t)(mode)
#define __NR64ATRF0_fchmod                 "%d"
#define __NR64ATRA0_fchmod(fd, mode)       ,(int)(fd)
#define __NR64ATRF1_fchmod                 "%#" PRIoSIZ
#define __NR64ATRA1_fchmod(fd, mode)       ,(uintptr_t)(mode)
#define __NR64ATRF0_chown                  "%q"
#define __NR64ATRA0_chown(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_chown                  "%" PRIu32
#define __NR64ATRA1_chown(filename, owner, group) ,(uint32_t)(owner)
#define __NR64ATRF2_chown                  "%" PRIu32
#define __NR64ATRA2_chown(filename, owner, group) ,(uint32_t)(group)
#define __NR64ATRF0_fchown                 "%d"
#define __NR64ATRA0_fchown(fd, owner, group) ,(int)(fd)
#define __NR64ATRF1_fchown                 "%" PRIu32
#define __NR64ATRA1_fchown(fd, owner, group) ,(uint32_t)(owner)
#define __NR64ATRF2_fchown                 "%" PRIu32
#define __NR64ATRA2_fchown(fd, owner, group) ,(uint32_t)(group)
#define __NR64ATRF0_lchown                 "%q"
#define __NR64ATRA0_lchown(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_lchown                 "%" PRIu32
#define __NR64ATRA1_lchown(filename, owner, group) ,(uint32_t)(owner)
#define __NR64ATRF2_lchown                 "%" PRIu32
#define __NR64ATRA2_lchown(filename, owner, group) ,(uint32_t)(group)
#define __NR64ATRF0_umask                  "%#" PRIoSIZ
#define __NR64ATRA0_umask(mode)            ,(uintptr_t)(mode)
#define __NR64ATRF0_gettimeofday           "%p"
#define __NR64ATRA0_gettimeofday(tv, tz)   ,tv
#define __NR64ATRF1_gettimeofday           "%p"
#define __NR64ATRA1_gettimeofday(tv, tz)   ,tz
#define __NR64ATRF0_getrlimit              "%#" PRIxSIZ
#define __NR64ATRA0_getrlimit(resource, rlimits) ,(uintptr_t)(resource)
#define __NR64ATRF1_getrlimit              "%p"
#define __NR64ATRA1_getrlimit(resource, rlimits) ,rlimits
#define __NR64ATRF0_getrusage              "%" PRIdSIZ
#define __NR64ATRA0_getrusage(who, usage)  ,(intptr_t)(who)
#define __NR64ATRF1_getrusage              "%p"
#define __NR64ATRA1_getrusage(who, usage)  ,usage
#define __NR64ATRF0_sysinfo                "%p"
#define __NR64ATRA0_sysinfo(info)          ,info
#define __NR64ATRF0_times                  "%p"
#define __NR64ATRA0_times(buf)             ,buf
#define __NR64ATRF0_ptrace                 "%#" PRIxSIZ
#define __NR64ATRA0_ptrace(request, pid, addr, data) ,(uintptr_t)(request)
#define __NR64ATRF1_ptrace                 "%" PRIdSIZ
#define __NR64ATRA1_ptrace(request, pid, addr, data) ,(intptr_t)(pid)
#define __NR64ATRF2_ptrace                 "%p"
#define __NR64ATRA2_ptrace(request, pid, addr, data) ,addr
#define __NR64ATRF3_ptrace                 "%p"
#define __NR64ATRA3_ptrace(request, pid, addr, data) ,data
#define __NR64ATRF0_syslog                 "%" PRIuSIZ
#define __NR64ATRA0_syslog(level, str, len) ,(uintptr_t)(level)
#define __NR64ATRF1_syslog                 "%$q"
#define __NR64ATRA1_syslog(level, str, len) ,len,(validate_readable(str,len),str)
#define __NR64ATRF2_syslog                 "%" PRIuSIZ
#define __NR64ATRA2_syslog(level, str, len) ,len
#define __NR64ATRF0_setuid                 "%" PRIu32
#define __NR64ATRA0_setuid(uid)            ,(uint32_t)(uid)
#define __NR64ATRF0_setgid                 "%" PRIu32
#define __NR64ATRA0_setgid(gid)            ,(uint32_t)(gid)
#define __NR64ATRF0_setpgid                "%" PRIdSIZ
#define __NR64ATRA0_setpgid(pid, pgid)     ,(intptr_t)(pid)
#define __NR64ATRF1_setpgid                "%" PRIdSIZ
#define __NR64ATRA1_setpgid(pid, pgid)     ,(intptr_t)(pgid)
#define __NR64ATRF0_setreuid               "%" PRIu32
#define __NR64ATRA0_setreuid(ruid, euid)   ,(uint32_t)(ruid)
#define __NR64ATRF1_setreuid               "%" PRIu32
#define __NR64ATRA1_setreuid(ruid, euid)   ,(uint32_t)(euid)
#define __NR64ATRF0_setregid               "%" PRIu32
#define __NR64ATRA0_setregid(rgid, egid)   ,(uint32_t)(rgid)
#define __NR64ATRF1_setregid               "%" PRIu32
#define __NR64ATRA1_setregid(rgid, egid)   ,(uint32_t)(egid)
#define __NR64ATRF0_getgroups              "%" PRIuSIZ
#define __NR64ATRA0_getgroups(size, list)  ,size
#define __NR64ATRF1_getgroups              "%p"
#define __NR64ATRA1_getgroups(size, list)  ,list
#define __NR64ATRF0_setgroups              "%" PRIuSIZ
#define __NR64ATRA0_setgroups(count, groups) ,count
#define __NR64ATRF1_setgroups              "%p"
#define __NR64ATRA1_setgroups(count, groups) ,groups
#define __NR64ATRF0_setresuid              "%" PRIu32
#define __NR64ATRA0_setresuid(ruid, euid, suid) ,(uint32_t)(ruid)
#define __NR64ATRF1_setresuid              "%" PRIu32
#define __NR64ATRA1_setresuid(ruid, euid, suid) ,(uint32_t)(euid)
#define __NR64ATRF2_setresuid              "%" PRIu32
#define __NR64ATRA2_setresuid(ruid, euid, suid) ,(uint32_t)(suid)
#define __NR64ATRF0_getresuid              "%p"
#define __NR64ATRA0_getresuid(ruid, euid, suid) ,ruid
#define __NR64ATRF1_getresuid              "%p"
#define __NR64ATRA1_getresuid(ruid, euid, suid) ,euid
#define __NR64ATRF2_getresuid              "%p"
#define __NR64ATRA2_getresuid(ruid, euid, suid) ,suid
#define __NR64ATRF0_setresgid              "%" PRIu32
#define __NR64ATRA0_setresgid(rgid, egid, sgid) ,(uint32_t)(rgid)
#define __NR64ATRF1_setresgid              "%" PRIu32
#define __NR64ATRA1_setresgid(rgid, egid, sgid) ,(uint32_t)(egid)
#define __NR64ATRF2_setresgid              "%" PRIu32
#define __NR64ATRA2_setresgid(rgid, egid, sgid) ,(uint32_t)(sgid)
#define __NR64ATRF0_getresgid              "%p"
#define __NR64ATRA0_getresgid(rgid, egid, sgid) ,rgid
#define __NR64ATRF1_getresgid              "%p"
#define __NR64ATRA1_getresgid(rgid, egid, sgid) ,egid
#define __NR64ATRF2_getresgid              "%p"
#define __NR64ATRA2_getresgid(rgid, egid, sgid) ,sgid
#define __NR64ATRF0_getpgid                "%" PRIdSIZ
#define __NR64ATRA0_getpgid(pid)           ,(intptr_t)(pid)
#define __NR64ATRF0_setfsuid               "%" PRIu32
#define __NR64ATRA0_setfsuid(uid)          ,(uint32_t)(uid)
#define __NR64ATRF0_setfsgid               "%" PRIu32
#define __NR64ATRA0_setfsgid(gid)          ,(uint32_t)(gid)
#define __NR64ATRF0_getsid                 "%" PRIdSIZ
#define __NR64ATRA0_getsid(pid)            ,(intptr_t)(pid)
#define __NR64ATRF0_capget                 "%d"
#define __NR64ATRA0_capget(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_capset                 "%d"
#define __NR64ATRA0_capset(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_rt_sigpending          "%p"
#define __NR64ATRA0_rt_sigpending(set, sigsetsize) ,set
#define __NR64ATRF1_rt_sigpending          "%" PRIuSIZ
#define __NR64ATRA1_rt_sigpending(set, sigsetsize) ,sigsetsize
#define __NR64ATRF0_rt_sigtimedwait        "%p"
#define __NR64ATRA0_rt_sigtimedwait(set, info, timeout, sigsetsize) ,set
#define __NR64ATRF1_rt_sigtimedwait        "%p"
#define __NR64ATRA1_rt_sigtimedwait(set, info, timeout, sigsetsize) ,info
#define __NR64ATRF2_rt_sigtimedwait        "%p"
#define __NR64ATRA2_rt_sigtimedwait(set, info, timeout, sigsetsize) ,timeout
#define __NR64ATRF3_rt_sigtimedwait        "%" PRIuSIZ
#define __NR64ATRA3_rt_sigtimedwait(set, info, timeout, sigsetsize) ,sigsetsize
#define __NR64ATRF0_rt_sigqueueinfo        "%" PRIdSIZ
#define __NR64ATRA0_rt_sigqueueinfo(tgid, signo, uinfo) ,(intptr_t)(tgid)
#define __NR64ATRF1_rt_sigqueueinfo        "%#" PRIxSIZ
#define __NR64ATRA1_rt_sigqueueinfo(tgid, signo, uinfo) ,(uintptr_t)(signo)
#define __NR64ATRF2_rt_sigqueueinfo        "%p"
#define __NR64ATRA2_rt_sigqueueinfo(tgid, signo, uinfo) ,uinfo
#define __NR64ATRF0_rt_sigsuspend          "%p"
#define __NR64ATRA0_rt_sigsuspend(set, sigsetsize) ,set
#define __NR64ATRF1_rt_sigsuspend          "%" PRIuSIZ
#define __NR64ATRA1_rt_sigsuspend(set, sigsetsize) ,sigsetsize
#define __NR64ATRF0_sigaltstack            "%p"
#define __NR64ATRA0_sigaltstack(ss, oss)   ,ss
#define __NR64ATRF1_sigaltstack            "%p"
#define __NR64ATRA1_sigaltstack(ss, oss)   ,oss
#define __NR64ATRF0_utime                  "%q"
#define __NR64ATRA0_utime(filename, times) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_utime                  "%p"
#define __NR64ATRA1_utime(filename, times) ,times
#define __NR64ATRF0_mknod                  "%q"
#define __NR64ATRA0_mknod(nodename, mode, dev) ,(validate_readable_opt(nodename,1),nodename)
#define __NR64ATRF1_mknod                  "%#" PRIoSIZ
#define __NR64ATRA1_mknod(nodename, mode, dev) ,(uintptr_t)(mode)
#define __NR64ATRF2_mknod                  "%.2x:%.2x"
#define __NR64ATRA2_mknod(nodename, mode, dev) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR64ATRF0_uselib                 "%q"
#define __NR64ATRA0_uselib(library)        ,(validate_readable_opt(library,1),library)
#define __NR64ATRF0_personality            "%d"
#define __NR64ATRA0_personality(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_ustat                  "%.2x:%.2x"
#define __NR64ATRA0_ustat(dev, ubuf)       ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR64ATRF1_ustat                  "%p"
#define __NR64ATRA1_ustat(dev, ubuf)       ,ubuf
#define __NR64ATRF0_statfs                 "%q"
#define __NR64ATRA0_statfs(file, buf)      ,(validate_readable_opt(file,1),file)
#define __NR64ATRF1_statfs                 "%p"
#define __NR64ATRA1_statfs(file, buf)      ,buf
#define __NR64ATRF0_fstatfs                "%d"
#define __NR64ATRA0_fstatfs(file, buf)     ,(int)(file)
#define __NR64ATRF1_fstatfs                "%p"
#define __NR64ATRA1_fstatfs(file, buf)     ,buf
#define __NR64ATRF0_sysfs                  "%d"
#define __NR64ATRA0_sysfs(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR64ATRF0_getpriority            "%#" PRIxSIZ
#define __NR64ATRA0_getpriority(which, who) ,(uintptr_t)(which)
#define __NR64ATRF1_getpriority            "%" PRIuSIZ
#define __NR64ATRA1_getpriority(which, who) ,(uintptr_t)(who)
#define __NR64ATRF0_setpriority            "%#" PRIxSIZ
#define __NR64ATRA0_setpriority(which, who, value) ,(uintptr_t)(which)
#define __NR64ATRF1_setpriority            "%" PRIuSIZ
#define __NR64ATRA1_setpriority(which, who, value) ,(uintptr_t)(who)
#define __NR64ATRF2_setpriority            "%#" PRIxSIZ
#define __NR64ATRA2_setpriority(which, who, value) ,(uintptr_t)(value)
#define __NR64ATRF0_sched_setparam         "%" PRIdSIZ
#define __NR64ATRA0_sched_setparam(pid, param) ,(intptr_t)(pid)
#define __NR64ATRF1_sched_setparam         "%p"
#define __NR64ATRA1_sched_setparam(pid, param) ,param
#define __NR64ATRF0_sched_getparam         "%" PRIdSIZ
#define __NR64ATRA0_sched_getparam(pid, param) ,(intptr_t)(pid)
#define __NR64ATRF1_sched_getparam         "%p"
#define __NR64ATRA1_sched_getparam(pid, param) ,param
#define __NR64ATRF0_sched_setscheduler     "%" PRIdSIZ
#define __NR64ATRA0_sched_setscheduler(pid, policy, param) ,(intptr_t)(pid)
#define __NR64ATRF1_sched_setscheduler     "%#" PRIxSIZ
#define __NR64ATRA1_sched_setscheduler(pid, policy, param) ,(uintptr_t)(policy)
#define __NR64ATRF2_sched_setscheduler     "%p"
#define __NR64ATRA2_sched_setscheduler(pid, policy, param) ,param
#define __NR64ATRF0_sched_getscheduler     "%" PRIdSIZ
#define __NR64ATRA0_sched_getscheduler(pid) ,(intptr_t)(pid)
#define __NR64ATRF0_sched_get_priority_max "%#" PRIxSIZ
#define __NR64ATRA0_sched_get_priority_max(algorithm) ,(uintptr_t)(algorithm)
#define __NR64ATRF0_sched_get_priority_min "%#" PRIxSIZ
#define __NR64ATRA0_sched_get_priority_min(algorithm) ,(uintptr_t)(algorithm)
#define __NR64ATRF0_sched_rr_get_interval  "%" PRIdSIZ
#define __NR64ATRA0_sched_rr_get_interval(pid, tms) ,(intptr_t)(pid)
#define __NR64ATRF1_sched_rr_get_interval  "%p"
#define __NR64ATRA1_sched_rr_get_interval(pid, tms) ,tms
#define __NR64ATRF0_mlock                  "%p"
#define __NR64ATRA0_mlock(addr, len)       ,addr
#define __NR64ATRF1_mlock                  "%" PRIuSIZ
#define __NR64ATRA1_mlock(addr, len)       ,len
#define __NR64ATRF0_munlock                "%p"
#define __NR64ATRA0_munlock(addr, len)     ,addr
#define __NR64ATRF1_munlock                "%" PRIuSIZ
#define __NR64ATRA1_munlock(addr, len)     ,len
#define __NR64ATRF0_mlockall               "%#" PRIxSIZ
#define __NR64ATRA0_mlockall(flags)        ,(uintptr_t)(flags)
#define __NR64ATRF0_modify_ldt             "%#" PRIxSIZ
#define __NR64ATRA0_modify_ldt(func, ptr, bytecount) ,(uintptr_t)(func)
#define __NR64ATRF1_modify_ldt             "%p"
#define __NR64ATRA1_modify_ldt(func, ptr, bytecount) ,ptr
#define __NR64ATRF2_modify_ldt             "%#" PRIxSIZ
#define __NR64ATRA2_modify_ldt(func, ptr, bytecount) ,(uintptr_t)(bytecount)
#define __NR64ATRF0_pivot_root             "%d"
#define __NR64ATRA0_pivot_root(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0__sysctl                "%d"
#define __NR64ATRA0__sysctl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_prctl                  "%d"
#define __NR64ATRA0_prctl(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR64ATRF0_arch_prctl             "%d"
#define __NR64ATRA0_arch_prctl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_adjtimex               "%d"
#define __NR64ATRA0_adjtimex(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_setrlimit              "%#" PRIxSIZ
#define __NR64ATRA0_setrlimit(resource, rlimits) ,(uintptr_t)(resource)
#define __NR64ATRF1_setrlimit              "%p"
#define __NR64ATRA1_setrlimit(resource, rlimits) ,rlimits
#define __NR64ATRF0_chroot                 "%q"
#define __NR64ATRA0_chroot(path)           ,(validate_readable_opt(path,1),path)
#define __NR64ATRF0_acct                   "%q"
#define __NR64ATRA0_acct(filename)         ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF0_settimeofday           "%p"
#define __NR64ATRA0_settimeofday(tv, tz)   ,tv
#define __NR64ATRF1_settimeofday           "%p"
#define __NR64ATRA1_settimeofday(tv, tz)   ,tz
#define __NR64ATRF0_mount                  "%q"
#define __NR64ATRA0_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(special_file,1),special_file)
#define __NR64ATRF1_mount                  "%q"
#define __NR64ATRA1_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(dir,1),dir)
#define __NR64ATRF2_mount                  "%q"
#define __NR64ATRA2_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(fstype,1),fstype)
#define __NR64ATRF3_mount                  "%#" PRIxSIZ
#define __NR64ATRA3_mount(special_file, dir, fstype, rwflag, data) ,(uintptr_t)(rwflag)
#define __NR64ATRF4_mount                  "%p"
#define __NR64ATRA4_mount(special_file, dir, fstype, rwflag, data) ,data
#define __NR64ATRF0_umount2                "%q"
#define __NR64ATRA0_umount2(special_file, flags) ,(validate_readable_opt(special_file,1),special_file)
#define __NR64ATRF1_umount2                "%#" PRIxSIZ
#define __NR64ATRA1_umount2(special_file, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_swapon                 "%q"
#define __NR64ATRA0_swapon(pathname, swapflags) ,(validate_readable_opt(pathname,1),pathname)
#define __NR64ATRF1_swapon                 "%#" PRIxSIZ "=%s%s%s"
#define __NR64ATRA1_swapon(pathname, swapflags) ,(uintptr_t)(swapflags),(swapflags) & SWAP_FLAG_PREFER ? "SWAP_FLAG_PREFER" : "" \
                                                ,((swapflags) & SWAP_FLAG_DISCARD) && ((swapflags) & (SWAP_FLAG_PREFER)) ? "|" : "",(swapflags) & SWAP_FLAG_DISCARD ? "SWAP_FLAG_DISCARD" : ""
#define __NR64ATRF0_swapoff                "%q"
#define __NR64ATRA0_swapoff(pathname)      ,(validate_readable_opt(pathname,1),pathname)
#define __NR64ATRF0_reboot                 "%#" PRIxSIZ
#define __NR64ATRA0_reboot(how)            ,(uintptr_t)(how)
#define __NR64ATRF0_sethostname            "%q"
#define __NR64ATRA0_sethostname(name, len) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF1_sethostname            "%" PRIuSIZ
#define __NR64ATRA1_sethostname(name, len) ,len
#define __NR64ATRF0_setdomainname          "%q"
#define __NR64ATRA0_setdomainname(name, len) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF1_setdomainname          "%" PRIuSIZ
#define __NR64ATRA1_setdomainname(name, len) ,len
#define __NR64ATRF0_iopl                   "%#" PRIxSIZ
#define __NR64ATRA0_iopl(level)            ,(uintptr_t)(level)
#define __NR64ATRF0_ioperm                 "%#" PRIxSIZ
#define __NR64ATRA0_ioperm(from, num, turn_on) ,(uintptr_t)(from)
#define __NR64ATRF1_ioperm                 "%#" PRIxSIZ
#define __NR64ATRA1_ioperm(from, num, turn_on) ,(uintptr_t)(num)
#define __NR64ATRF2_ioperm                 "%#" PRIxSIZ
#define __NR64ATRA2_ioperm(from, num, turn_on) ,(uintptr_t)(turn_on)
#define __NR64ATRF0_create_module          "%d"
#define __NR64ATRA0_create_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_init_module            "%d"
#define __NR64ATRA0_init_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_delete_module          "%d"
#define __NR64ATRA0_delete_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_get_kernel_syms        "%d"
#define __NR64ATRA0_get_kernel_syms(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_query_module           "%d"
#define __NR64ATRA0_query_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_quotactl               "%d"
#define __NR64ATRA0_quotactl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_nfsservctl             "%d"
#define __NR64ATRA0_nfsservctl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_getpmsg                "%d"
#define __NR64ATRA0_getpmsg(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_putpmsg                "%d"
#define __NR64ATRA0_putpmsg(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_afs_syscall            "%d"
#define __NR64ATRA0_afs_syscall(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_tuxcall                "%d"
#define __NR64ATRA0_tuxcall(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_security               "%d"
#define __NR64ATRA0_security(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_readahead              "%d"
#define __NR64ATRA0_readahead(fd, offset, count) ,(int)(fd)
#define __NR64ATRF1_readahead              "%" PRIu64
#define __NR64ATRA1_readahead(fd, offset, count) ,offset
#define __NR64ATRF2_readahead              "%" PRIuSIZ
#define __NR64ATRA2_readahead(fd, offset, count) ,count
#define __NR64ATRF0_setxattr               "%q"
#define __NR64ATRA0_setxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_setxattr               "%q"
#define __NR64ATRA1_setxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF2_setxattr               "%p"
#define __NR64ATRA2_setxattr(path, name, buf, bufsize, flags) ,buf
#define __NR64ATRF3_setxattr               "%" PRIuSIZ
#define __NR64ATRA3_setxattr(path, name, buf, bufsize, flags) ,bufsize
#define __NR64ATRF4_setxattr               "%#" PRIxSIZ
#define __NR64ATRA4_setxattr(path, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_lsetxattr              "%q"
#define __NR64ATRA0_lsetxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_lsetxattr              "%q"
#define __NR64ATRA1_lsetxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF2_lsetxattr              "%p"
#define __NR64ATRA2_lsetxattr(path, name, buf, bufsize, flags) ,buf
#define __NR64ATRF3_lsetxattr              "%" PRIuSIZ
#define __NR64ATRA3_lsetxattr(path, name, buf, bufsize, flags) ,bufsize
#define __NR64ATRF4_lsetxattr              "%#" PRIxSIZ
#define __NR64ATRA4_lsetxattr(path, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_fsetxattr              "%d"
#define __NR64ATRA0_fsetxattr(fd, name, buf, bufsize, flags) ,(int)(fd)
#define __NR64ATRF1_fsetxattr              "%q"
#define __NR64ATRA1_fsetxattr(fd, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF2_fsetxattr              "%p"
#define __NR64ATRA2_fsetxattr(fd, name, buf, bufsize, flags) ,buf
#define __NR64ATRF3_fsetxattr              "%" PRIuSIZ
#define __NR64ATRA3_fsetxattr(fd, name, buf, bufsize, flags) ,bufsize
#define __NR64ATRF4_fsetxattr              "%#" PRIxSIZ
#define __NR64ATRA4_fsetxattr(fd, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_getxattr               "%q"
#define __NR64ATRA0_getxattr(path, name, buf, bufsize) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_getxattr               "%q"
#define __NR64ATRA1_getxattr(path, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF2_getxattr               "%p"
#define __NR64ATRA2_getxattr(path, name, buf, bufsize) ,buf
#define __NR64ATRF3_getxattr               "%" PRIuSIZ
#define __NR64ATRA3_getxattr(path, name, buf, bufsize) ,bufsize
#define __NR64ATRF0_lgetxattr              "%q"
#define __NR64ATRA0_lgetxattr(path, name, buf, bufsize) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_lgetxattr              "%q"
#define __NR64ATRA1_lgetxattr(path, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF2_lgetxattr              "%p"
#define __NR64ATRA2_lgetxattr(path, name, buf, bufsize) ,buf
#define __NR64ATRF3_lgetxattr              "%" PRIuSIZ
#define __NR64ATRA3_lgetxattr(path, name, buf, bufsize) ,bufsize
#define __NR64ATRF0_fgetxattr              "%d"
#define __NR64ATRA0_fgetxattr(fd, name, buf, bufsize) ,(int)(fd)
#define __NR64ATRF1_fgetxattr              "%q"
#define __NR64ATRA1_fgetxattr(fd, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF2_fgetxattr              "%p"
#define __NR64ATRA2_fgetxattr(fd, name, buf, bufsize) ,buf
#define __NR64ATRF3_fgetxattr              "%" PRIuSIZ
#define __NR64ATRA3_fgetxattr(fd, name, buf, bufsize) ,bufsize
#define __NR64ATRF0_listxattr              "%q"
#define __NR64ATRA0_listxattr(path, listbuf, listbufsize) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_listxattr              "%p"
#define __NR64ATRA1_listxattr(path, listbuf, listbufsize) ,listbuf
#define __NR64ATRF2_listxattr              "%" PRIuSIZ
#define __NR64ATRA2_listxattr(path, listbuf, listbufsize) ,listbufsize
#define __NR64ATRF0_llistxattr             "%q"
#define __NR64ATRA0_llistxattr(path, listbuf, listbufsize) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_llistxattr             "%p"
#define __NR64ATRA1_llistxattr(path, listbuf, listbufsize) ,listbuf
#define __NR64ATRF2_llistxattr             "%" PRIuSIZ
#define __NR64ATRA2_llistxattr(path, listbuf, listbufsize) ,listbufsize
#define __NR64ATRF0_flistxattr             "%d"
#define __NR64ATRA0_flistxattr(fd, listbuf, listbufsize) ,(int)(fd)
#define __NR64ATRF1_flistxattr             "%p"
#define __NR64ATRA1_flistxattr(fd, listbuf, listbufsize) ,listbuf
#define __NR64ATRF2_flistxattr             "%" PRIuSIZ
#define __NR64ATRA2_flistxattr(fd, listbuf, listbufsize) ,listbufsize
#define __NR64ATRF0_removexattr            "%q"
#define __NR64ATRA0_removexattr(path, name) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_removexattr            "%q"
#define __NR64ATRA1_removexattr(path, name) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF0_lremovexattr           "%q"
#define __NR64ATRA0_lremovexattr(path, name) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF1_lremovexattr           "%q"
#define __NR64ATRA1_lremovexattr(path, name) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF0_fremovexattr           "%d"
#define __NR64ATRA0_fremovexattr(fd, name) ,fd
#define __NR64ATRF1_fremovexattr           "%q"
#define __NR64ATRA1_fremovexattr(fd, name) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF0_tkill                  "%" PRIdSIZ
#define __NR64ATRA0_tkill(tid, signo)      ,(intptr_t)(tid)
#define __NR64ATRF1_tkill                  "%#" PRIxSIZ
#define __NR64ATRA1_tkill(tid, signo)      ,(uintptr_t)(signo)
#define __NR64ATRF0_time                   "%p"
#define __NR64ATRA0_time(timer)            ,timer
#define __NR64ATRF0_futex                  "%p"
#define __NR64ATRA0_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,uaddr
#define __NR64ATRF1_futex                  "%#" PRIxSIZ
#define __NR64ATRA1_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,(uintptr_t)(futex_op)
#define __NR64ATRF2_futex                  "%" PRIu32
#define __NR64ATRA2_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,val
#define __NR64ATRF3_futex                  "%p"
#define __NR64ATRA3_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,timeout_or_val2
#define __NR64ATRF4_futex                  "%p"
#define __NR64ATRA4_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,uaddr2
#define __NR64ATRF5_futex                  "%" PRIu32
#define __NR64ATRA5_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,val3
#define __NR64ATRF0_sched_setaffinity      "%" PRIdSIZ
#define __NR64ATRA0_sched_setaffinity(pid, cpusetsize, cpuset) ,(intptr_t)(pid)
#define __NR64ATRF1_sched_setaffinity      "%" PRIuSIZ
#define __NR64ATRA1_sched_setaffinity(pid, cpusetsize, cpuset) ,cpusetsize
#define __NR64ATRF2_sched_setaffinity      "%p"
#define __NR64ATRA2_sched_setaffinity(pid, cpusetsize, cpuset) ,cpuset
#define __NR64ATRF0_sched_getaffinity      "%" PRIdSIZ
#define __NR64ATRA0_sched_getaffinity(pid, cpusetsize, cpuset) ,(intptr_t)(pid)
#define __NR64ATRF1_sched_getaffinity      "%" PRIuSIZ
#define __NR64ATRA1_sched_getaffinity(pid, cpusetsize, cpuset) ,cpusetsize
#define __NR64ATRF2_sched_getaffinity      "%p"
#define __NR64ATRA2_sched_getaffinity(pid, cpusetsize, cpuset) ,cpuset
#define __NR64ATRF0_set_thread_area        "%d"
#define __NR64ATRA0_set_thread_area(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_io_setup               "%d"
#define __NR64ATRA0_io_setup(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_io_destroy             "%d"
#define __NR64ATRA0_io_destroy(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_io_getevents           "%d"
#define __NR64ATRA0_io_getevents(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_io_submit              "%d"
#define __NR64ATRA0_io_submit(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_io_cancel              "%d"
#define __NR64ATRA0_io_cancel(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_get_thread_area        "%d"
#define __NR64ATRA0_get_thread_area(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_lookup_dcookie         "%d"
#define __NR64ATRA0_lookup_dcookie(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_epoll_create           "%#" PRIxSIZ
#define __NR64ATRA0_epoll_create(size)     ,(uintptr_t)(size)
#define __NR64ATRF0_epoll_ctl_old          "%d"
#define __NR64ATRA0_epoll_ctl_old(epfd, op, fd, event) ,(int)(epfd)
#define __NR64ATRF1_epoll_ctl_old          "%#Ix=%s"
#define __NR64ATRA1_epoll_ctl_old(epfd, op, fd, event) ,(op),(op) == EPOLL_CTL_ADD ? "EPOLL_CTL_ADD" : (op) == EPOLL_CTL_DEL ? "EPOLL_CTL_DEL" : (op) == EPOLL_CTL_MOD ? "EPOLL_CTL_MOD" : "?"
#define __NR64ATRF2_epoll_ctl_old          "%d"
#define __NR64ATRA2_epoll_ctl_old(epfd, op, fd, event) ,(int)(fd)
#define __NR64ATRF3_epoll_ctl_old          "%p"
#define __NR64ATRA3_epoll_ctl_old(epfd, op, fd, event) ,event
#define __NR64ATRF0_epoll_wait_old         "%d"
#define __NR64ATRA0_epoll_wait_old(epfd, events, maxevents, timeout) ,(int)(epfd)
#define __NR64ATRF1_epoll_wait_old         "%p"
#define __NR64ATRA1_epoll_wait_old(epfd, events, maxevents, timeout) ,events
#define __NR64ATRF2_epoll_wait_old         "%#" PRIxSIZ
#define __NR64ATRA2_epoll_wait_old(epfd, events, maxevents, timeout) ,(uintptr_t)(maxevents)
#define __NR64ATRF3_epoll_wait_old         "%" PRIdSIZ
#define __NR64ATRA3_epoll_wait_old(epfd, events, maxevents, timeout) ,(intptr_t)(timeout)
#define __NR64ATRF0_remap_file_pages       "%p"
#define __NR64ATRA0_remap_file_pages(start, size, prot, pgoff, flags) ,start
#define __NR64ATRF1_remap_file_pages       "%" PRIuSIZ
#define __NR64ATRA1_remap_file_pages(start, size, prot, pgoff, flags) ,size
#define __NR64ATRF2_remap_file_pages       "%#" PRIxSIZ
#define __NR64ATRA2_remap_file_pages(start, size, prot, pgoff, flags) ,(uintptr_t)(prot)
#define __NR64ATRF3_remap_file_pages       "%" PRIuSIZ
#define __NR64ATRA3_remap_file_pages(start, size, prot, pgoff, flags) ,pgoff
#define __NR64ATRF4_remap_file_pages       "%#" PRIxSIZ
#define __NR64ATRA4_remap_file_pages(start, size, prot, pgoff, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_getdents64             "%d"
#define __NR64ATRA0_getdents64(fd, dirp, count) ,(int)(fd)
#define __NR64ATRF1_getdents64             "%p"
#define __NR64ATRA1_getdents64(fd, dirp, count) ,dirp
#define __NR64ATRF2_getdents64             "%" PRIuSIZ
#define __NR64ATRA2_getdents64(fd, dirp, count) ,count
#define __NR64ATRF0_set_tid_address        "%p"
#define __NR64ATRA0_set_tid_address(tidptr) ,tidptr
#define __NR64ATRF0_semtimedop             "%d"
#define __NR64ATRA0_semtimedop(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_fadvise64              "%d"
#define __NR64ATRA0_fadvise64(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_timer_create           "%#" PRIxSIZ
#define __NR64ATRA0_timer_create(clock_id, evp, timerid) ,(uintptr_t)(clock_id)
#define __NR64ATRF1_timer_create           "%p"
#define __NR64ATRA1_timer_create(clock_id, evp, timerid) ,evp
#define __NR64ATRF2_timer_create           "%p"
#define __NR64ATRA2_timer_create(clock_id, evp, timerid) ,timerid
#define __NR64ATRF0_timer_settime          "%p"
#define __NR64ATRA0_timer_settime(timerid, flags, value, ovalue) ,timerid
#define __NR64ATRF1_timer_settime          "%#" PRIxSIZ
#define __NR64ATRA1_timer_settime(timerid, flags, value, ovalue) ,(uintptr_t)(flags)
#define __NR64ATRF2_timer_settime          "%p"
#define __NR64ATRA2_timer_settime(timerid, flags, value, ovalue) ,value
#define __NR64ATRF3_timer_settime          "%p"
#define __NR64ATRA3_timer_settime(timerid, flags, value, ovalue) ,ovalue
#define __NR64ATRF0_timer_gettime          "%p"
#define __NR64ATRA0_timer_gettime(timerid, value) ,timerid
#define __NR64ATRF1_timer_gettime          "%p"
#define __NR64ATRA1_timer_gettime(timerid, value) ,value
#define __NR64ATRF0_timer_getoverrun       "%p"
#define __NR64ATRA0_timer_getoverrun(timerid) ,timerid
#define __NR64ATRF0_timer_delete           "%p"
#define __NR64ATRA0_timer_delete(timerid)  ,timerid
#define __NR64ATRF0_clock_settime          "%#" PRIxSIZ
#define __NR64ATRA0_clock_settime(clock_id, tp) ,(uintptr_t)(clock_id)
#define __NR64ATRF1_clock_settime          "%p"
#define __NR64ATRA1_clock_settime(clock_id, tp) ,tp
#define __NR64ATRF0_clock_gettime          "%#" PRIxSIZ
#define __NR64ATRA0_clock_gettime(clock_id, tp) ,(uintptr_t)(clock_id)
#define __NR64ATRF1_clock_gettime          "%p"
#define __NR64ATRA1_clock_gettime(clock_id, tp) ,tp
#define __NR64ATRF0_clock_getres           "%#" PRIxSIZ
#define __NR64ATRA0_clock_getres(clock_id, res) ,(uintptr_t)(clock_id)
#define __NR64ATRF1_clock_getres           "%p"
#define __NR64ATRA1_clock_getres(clock_id, res) ,res
#define __NR64ATRF0_clock_nanosleep        "%#" PRIxSIZ
#define __NR64ATRA0_clock_nanosleep(clock_id, flags, requested_time, remaining) ,(uintptr_t)(clock_id)
#define __NR64ATRF1_clock_nanosleep        "%#" PRIxSIZ
#define __NR64ATRA1_clock_nanosleep(clock_id, flags, requested_time, remaining) ,(uintptr_t)(flags)
#define __NR64ATRF2_clock_nanosleep        "%p"
#define __NR64ATRA2_clock_nanosleep(clock_id, flags, requested_time, remaining) ,requested_time
#define __NR64ATRF3_clock_nanosleep        "%p"
#define __NR64ATRA3_clock_nanosleep(clock_id, flags, requested_time, remaining) ,remaining
#define __NR64ATRF0_exit_group             "%" PRIuSIZ
#define __NR64ATRA0_exit_group(exit_code)  ,(uintptr_t)(exit_code)
#define __NR64ATRF0_epoll_wait             "%d"
#define __NR64ATRA0_epoll_wait(epfd, events, maxevents, timeout) ,(int)(epfd)
#define __NR64ATRF1_epoll_wait             "%p"
#define __NR64ATRA1_epoll_wait(epfd, events, maxevents, timeout) ,events
#define __NR64ATRF2_epoll_wait             "%#" PRIxSIZ
#define __NR64ATRA2_epoll_wait(epfd, events, maxevents, timeout) ,(uintptr_t)(maxevents)
#define __NR64ATRF3_epoll_wait             "%" PRIdSIZ
#define __NR64ATRA3_epoll_wait(epfd, events, maxevents, timeout) ,(intptr_t)(timeout)
#define __NR64ATRF0_epoll_ctl              "%d"
#define __NR64ATRA0_epoll_ctl(epfd, op, fd, event) ,(int)(epfd)
#define __NR64ATRF1_epoll_ctl              "%#Ix=%s"
#define __NR64ATRA1_epoll_ctl(epfd, op, fd, event) ,(op),(op) == EPOLL_CTL_ADD ? "EPOLL_CTL_ADD" : (op) == EPOLL_CTL_DEL ? "EPOLL_CTL_DEL" : (op) == EPOLL_CTL_MOD ? "EPOLL_CTL_MOD" : "?"
#define __NR64ATRF2_epoll_ctl              "%d"
#define __NR64ATRA2_epoll_ctl(epfd, op, fd, event) ,(int)(fd)
#define __NR64ATRF3_epoll_ctl              "%p"
#define __NR64ATRA3_epoll_ctl(epfd, op, fd, event) ,event
#define __NR64ATRF0_tgkill                 "%" PRIdSIZ
#define __NR64ATRA0_tgkill(tgid, tid, signo) ,(intptr_t)(tgid)
#define __NR64ATRF1_tgkill                 "%" PRIdSIZ
#define __NR64ATRA1_tgkill(tgid, tid, signo) ,(intptr_t)(tid)
#define __NR64ATRF2_tgkill                 "%#" PRIxSIZ
#define __NR64ATRA2_tgkill(tgid, tid, signo) ,(uintptr_t)(signo)
#define __NR64ATRF0_utimes                 "%q"
#define __NR64ATRA0_utimes(filename, times) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_utimes                 "%p"
#define __NR64ATRA1_utimes(filename, times) ,times
#define __NR64ATRF0_vserver                "%d"
#define __NR64ATRA0_vserver(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_mbind                  "%d"
#define __NR64ATRA0_mbind(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR64ATRF0_set_mempolicy          "%d"
#define __NR64ATRA0_set_mempolicy(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_get_mempolicy          "%d"
#define __NR64ATRA0_get_mempolicy(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_mq_open                "%d"
#define __NR64ATRA0_mq_open(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_mq_unlink              "%d"
#define __NR64ATRA0_mq_unlink(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_mq_timedsend           "%d"
#define __NR64ATRA0_mq_timedsend(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_mq_timedreceive        "%d"
#define __NR64ATRA0_mq_timedreceive(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_mq_notify              "%d"
#define __NR64ATRA0_mq_notify(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_mq_getsetattr          "%d"
#define __NR64ATRA0_mq_getsetattr(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_kexec_load             "%d"
#define __NR64ATRA0_kexec_load(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_waitid                 "%#Ix=%s"
#define __NR64ATRA0_waitid(idtype, id, infop, options, ru) ,(idtype),(idtype) == P_ALL ? "P_ALL" : (idtype) == P_PID ? "P_PID" : (idtype) == P_PGID ? "P_PGID" : "?"
#define __NR64ATRF1_waitid                 "%" PRIuSIZ
#define __NR64ATRA1_waitid(idtype, id, infop, options, ru) ,(uintptr_t)(id)
#define __NR64ATRF2_waitid                 "%p"
#define __NR64ATRA2_waitid(idtype, id, infop, options, ru) ,infop
#define __NR64ATRF3_waitid                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA3_waitid(idtype, id, infop, options, ru) ,(uintptr_t)(options),(options) & WEXITED ? "WEXITED" : "" \
                                                           ,((options) & WSTOPPED) && ((options) & (WEXITED)) ? "|" : "",(options) & WSTOPPED ? "WSTOPPED" : "" \
                                                           ,((options) & WCONTINUED) && ((options) & (WEXITED|WSTOPPED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                           ,((options) & WNOHANG) && ((options) & (WEXITED|WSTOPPED|WCONTINUED)) ? "|" : "",(options) & WNOHANG ? "WNOHANG" : "" \
                                                           ,((options) & WNOWAIT) && ((options) & (WEXITED|WSTOPPED|WCONTINUED|WNOHANG)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NR64ATRF4_waitid                 "%p"
#define __NR64ATRA4_waitid(idtype, id, infop, options, ru) ,ru
#define __NR64ATRF0_add_key                "%d"
#define __NR64ATRA0_add_key(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_request_key            "%d"
#define __NR64ATRA0_request_key(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_keyctl                 "%d"
#define __NR64ATRA0_keyctl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_ioprio_set             "%#" PRIxSIZ
#define __NR64ATRA0_ioprio_set(which, who, ioprio) ,(uintptr_t)(which)
#define __NR64ATRF1_ioprio_set             "%#" PRIxSIZ
#define __NR64ATRA1_ioprio_set(which, who, ioprio) ,(uintptr_t)(who)
#define __NR64ATRF2_ioprio_set             "%#" PRIxSIZ
#define __NR64ATRA2_ioprio_set(which, who, ioprio) ,(uintptr_t)(ioprio)
#define __NR64ATRF0_ioprio_get             "%#" PRIxSIZ
#define __NR64ATRA0_ioprio_get(which, who) ,(uintptr_t)(which)
#define __NR64ATRF1_ioprio_get             "%#" PRIxSIZ
#define __NR64ATRA1_ioprio_get(which, who) ,(uintptr_t)(who)
#define __NR64ATRF0_inotify_init           "%d"
#define __NR64ATRA0_inotify_init(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_inotify_add_watch      "%d"
#define __NR64ATRA0_inotify_add_watch(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_inotify_rm_watch       "%d"
#define __NR64ATRA0_inotify_rm_watch(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_migrate_pages          "%d"
#define __NR64ATRA0_migrate_pages(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_openat                 "%d"
#define __NR64ATRA0_openat(dirfd, filename, oflags, mode) ,(int)(dirfd)
#define __NR64ATRF1_openat                 "%q"
#define __NR64ATRA1_openat(dirfd, filename, oflags, mode) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF2_openat                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA2_openat(dirfd, filename, oflags, mode) ,(uintptr_t)(oflags),(oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
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
#define __NR64ATRF3_openat                 "%#" PRIoSIZ
#define __NR64ATRA3_openat(dirfd, filename, oflags, mode) ,(uintptr_t)(mode)
#define __NR64ATRF0_mkdirat                "%d"
#define __NR64ATRA0_mkdirat(dirfd, pathname, mode) ,(int)(dirfd)
#define __NR64ATRF1_mkdirat                "%q"
#define __NR64ATRA1_mkdirat(dirfd, pathname, mode) ,(validate_readable_opt(pathname,1),pathname)
#define __NR64ATRF2_mkdirat                "%#" PRIoSIZ
#define __NR64ATRA2_mkdirat(dirfd, pathname, mode) ,(uintptr_t)(mode)
#define __NR64ATRF0_mknodat                "%d"
#define __NR64ATRA0_mknodat(dirfd, nodename, mode, dev) ,(int)(dirfd)
#define __NR64ATRF1_mknodat                "%q"
#define __NR64ATRA1_mknodat(dirfd, nodename, mode, dev) ,(validate_readable_opt(nodename,1),nodename)
#define __NR64ATRF2_mknodat                "%#" PRIoSIZ
#define __NR64ATRA2_mknodat(dirfd, nodename, mode, dev) ,(uintptr_t)(mode)
#define __NR64ATRF3_mknodat                "%.2x:%.2x"
#define __NR64ATRA3_mknodat(dirfd, nodename, mode, dev) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR64ATRF0_fchownat               "%d"
#define __NR64ATRA0_fchownat(dirfd, filename, owner, group, flags) ,(int)(dirfd)
#define __NR64ATRF1_fchownat               "%q"
#define __NR64ATRA1_fchownat(dirfd, filename, owner, group, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF2_fchownat               "%" PRIu32
#define __NR64ATRA2_fchownat(dirfd, filename, owner, group, flags) ,(uint32_t)(owner)
#define __NR64ATRF3_fchownat               "%" PRIu32
#define __NR64ATRA3_fchownat(dirfd, filename, owner, group, flags) ,(uint32_t)(group)
#define __NR64ATRF4_fchownat               "%#" PRIxSIZ "=%s%s%s"
#define __NR64ATRA4_fchownat(dirfd, filename, owner, group, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                   ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_futimesat              "%d"
#define __NR64ATRA0_futimesat(dirfd, filename, times) ,(int)(dirfd)
#define __NR64ATRF1_futimesat              "%p"
#define __NR64ATRA1_futimesat(dirfd, filename, times) ,filename
#define __NR64ATRF2_futimesat              "%p"
#define __NR64ATRA2_futimesat(dirfd, filename, times) ,times
#define __NR64ATRF0_linux_fstatat          "%d"
#define __NR64ATRA0_linux_fstatat(dirfd, filename, statbuf, flags) ,(int)(dirfd)
#define __NR64ATRF1_linux_fstatat          "%q"
#define __NR64ATRA1_linux_fstatat(dirfd, filename, statbuf, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF2_linux_fstatat          "%p"
#define __NR64ATRA2_linux_fstatat(dirfd, filename, statbuf, flags) ,statbuf
#define __NR64ATRF3_linux_fstatat          "%#" PRIxSIZ "=%s%s%s"
#define __NR64ATRA3_linux_fstatat(dirfd, filename, statbuf, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                   ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_unlinkat               "%d"
#define __NR64ATRA0_unlinkat(dirfd, name, flags) ,(int)(dirfd)
#define __NR64ATRF1_unlinkat               "%q"
#define __NR64ATRA1_unlinkat(dirfd, name, flags) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF2_unlinkat               "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA2_unlinkat(dirfd, name, flags) ,(uintptr_t)(flags),(flags) & AT_REMOVEDIR ? "AT_REMOVEDIR" : "" \
                                                 ,((flags) & AT_REMOVEREG) && ((flags) & (AT_REMOVEDIR)) ? "|" : "",(flags) & AT_REMOVEREG ? "AT_REMOVEREG" : "" \
                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_REMOVEDIR|AT_REMOVEREG)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_renameat               "%d"
#define __NR64ATRA0_renameat(oldfd, oldname, newfd, newname_or_path) ,(int)(oldfd)
#define __NR64ATRF1_renameat               "%q"
#define __NR64ATRA1_renameat(oldfd, oldname, newfd, newname_or_path) ,(validate_readable_opt(oldname,1),oldname)
#define __NR64ATRF2_renameat               "%d"
#define __NR64ATRA2_renameat(oldfd, oldname, newfd, newname_or_path) ,(int)(newfd)
#define __NR64ATRF3_renameat               "%q"
#define __NR64ATRA3_renameat(oldfd, oldname, newfd, newname_or_path) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NR64ATRF0_linkat                 "%d"
#define __NR64ATRA0_linkat(fromfd, existing_file, tofd, target_path, flags) ,(int)(fromfd)
#define __NR64ATRF1_linkat                 "%q"
#define __NR64ATRA1_linkat(fromfd, existing_file, tofd, target_path, flags) ,(validate_readable_opt(existing_file,1),existing_file)
#define __NR64ATRF2_linkat                 "%d"
#define __NR64ATRA2_linkat(fromfd, existing_file, tofd, target_path, flags) ,(int)(tofd)
#define __NR64ATRF3_linkat                 "%q"
#define __NR64ATRA3_linkat(fromfd, existing_file, tofd, target_path, flags) ,(validate_readable_opt(target_path,1),target_path)
#define __NR64ATRF4_linkat                 "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA4_linkat(fromfd, existing_file, tofd, target_path, flags) ,(uintptr_t)(flags),(flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                                            ,((flags) & AT_SYMLINK_FOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "",(flags) & AT_SYMLINK_FOLLOW ? "AT_SYMLINK_FOLLOW" : "" \
                                                                            ,((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH|AT_SYMLINK_FOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_symlinkat              "%q"
#define __NR64ATRA0_symlinkat(link_text, tofd, target_path) ,(validate_readable_opt(link_text,1),link_text)
#define __NR64ATRF1_symlinkat              "%d"
#define __NR64ATRA1_symlinkat(link_text, tofd, target_path) ,(int)(tofd)
#define __NR64ATRF2_symlinkat              "%q"
#define __NR64ATRA2_symlinkat(link_text, tofd, target_path) ,(validate_readable_opt(target_path,1),target_path)
#define __NR64ATRF0_readlinkat             "%d"
#define __NR64ATRA0_readlinkat(dirfd, path, buf, buflen) ,(int)(dirfd)
#define __NR64ATRF1_readlinkat             "%q"
#define __NR64ATRA1_readlinkat(dirfd, path, buf, buflen) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF2_readlinkat             "%p"
#define __NR64ATRA2_readlinkat(dirfd, path, buf, buflen) ,buf
#define __NR64ATRF3_readlinkat             "%" PRIuSIZ
#define __NR64ATRA3_readlinkat(dirfd, path, buf, buflen) ,buflen
#define __NR64ATRF0_fchmodat               "%d"
#define __NR64ATRA0_fchmodat(dirfd, filename, mode, flags) ,(int)(dirfd)
#define __NR64ATRF1_fchmodat               "%q"
#define __NR64ATRA1_fchmodat(dirfd, filename, mode, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF2_fchmodat               "%#" PRIoSIZ
#define __NR64ATRA2_fchmodat(dirfd, filename, mode, flags) ,(uintptr_t)(mode)
#define __NR64ATRF3_fchmodat               "%#" PRIxSIZ "=%s%s%s"
#define __NR64ATRA3_fchmodat(dirfd, filename, mode, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                           ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_faccessat              "%d"
#define __NR64ATRA0_faccessat(dirfd, filename, type, flags) ,(int)(dirfd)
#define __NR64ATRF1_faccessat              "%q"
#define __NR64ATRA1_faccessat(dirfd, filename, type, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF2_faccessat              "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA2_faccessat(dirfd, filename, type, flags) ,(uintptr_t)(type),(type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                                            ,((type) & W_OK) && ((type) & (R_OK)) ? "|" : "",(type) & W_OK ? "W_OK" : "" \
                                                            ,((type) & X_OK) && ((type) & (R_OK|W_OK)) ? "|" : "",(type) & X_OK ? "X_OK" : ""
#define __NR64ATRF3_faccessat              "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA3_faccessat(dirfd, filename, type, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                            ,((flags) & AT_EACCESS) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_EACCESS ? "AT_EACCESS" : "" \
                                                            ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_EACCESS)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_pselect6               "%" PRIuSIZ
#define __NR64ATRA0_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,nfds
#define __NR64ATRF1_pselect6               "%p"
#define __NR64ATRA1_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,readfds
#define __NR64ATRF2_pselect6               "%p"
#define __NR64ATRA2_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,writefds
#define __NR64ATRF3_pselect6               "%p"
#define __NR64ATRA3_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,exceptfds
#define __NR64ATRF4_pselect6               "%p"
#define __NR64ATRA4_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,timeout
#define __NR64ATRF5_pselect6               "%p"
#define __NR64ATRA5_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,sigmask_sigset_and_len
#define __NR64ATRF0_ppoll                  "%p"
#define __NR64ATRA0_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,fds
#define __NR64ATRF1_ppoll                  "%" PRIuSIZ
#define __NR64ATRA1_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,nfds
#define __NR64ATRF2_ppoll                  "%p"
#define __NR64ATRA2_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,timeout_ts
#define __NR64ATRF3_ppoll                  "%p"
#define __NR64ATRA3_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigmask
#define __NR64ATRF4_ppoll                  "%" PRIuSIZ
#define __NR64ATRA4_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigsetsize
#define __NR64ATRF0_unshare                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA0_unshare(flags)         ,(uintptr_t)(flags),(flags) & CLONE_VM ? "CLONE_VM" : "" \
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
#define __NR64ATRF0_set_robust_list        "%d"
#define __NR64ATRA0_set_robust_list(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_get_robust_list        "%d"
#define __NR64ATRA0_get_robust_list(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_splice                 "%d"
#define __NR64ATRA0_splice(fdin, offin, fdout, offout, length, flags) ,(int)(fdin)
#define __NR64ATRF1_splice                 "%p"
#define __NR64ATRA1_splice(fdin, offin, fdout, offout, length, flags) ,offin
#define __NR64ATRF2_splice                 "%d"
#define __NR64ATRA2_splice(fdin, offin, fdout, offout, length, flags) ,(int)(fdout)
#define __NR64ATRF3_splice                 "%p"
#define __NR64ATRA3_splice(fdin, offin, fdout, offout, length, flags) ,offout
#define __NR64ATRF4_splice                 "%" PRIuSIZ
#define __NR64ATRA4_splice(fdin, offin, fdout, offout, length, flags) ,length
#define __NR64ATRF5_splice                 "%#" PRIxSIZ
#define __NR64ATRA5_splice(fdin, offin, fdout, offout, length, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_tee                    "%d"
#define __NR64ATRA0_tee(fdin, fdout, length, flags) ,(int)(fdin)
#define __NR64ATRF1_tee                    "%d"
#define __NR64ATRA1_tee(fdin, fdout, length, flags) ,(int)(fdout)
#define __NR64ATRF2_tee                    "%" PRIuSIZ
#define __NR64ATRA2_tee(fdin, fdout, length, flags) ,length
#define __NR64ATRF3_tee                    "%#" PRIxSIZ
#define __NR64ATRA3_tee(fdin, fdout, length, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_sync_file_range        "%d"
#define __NR64ATRA0_sync_file_range(fd, offset, count, flags) ,(int)(fd)
#define __NR64ATRF1_sync_file_range        "%" PRIu64
#define __NR64ATRA1_sync_file_range(fd, offset, count, flags) ,offset
#define __NR64ATRF2_sync_file_range        "%" PRIu64
#define __NR64ATRA2_sync_file_range(fd, offset, count, flags) ,count
#define __NR64ATRF3_sync_file_range        "%#" PRIxSIZ
#define __NR64ATRA3_sync_file_range(fd, offset, count, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_vmsplice               "%d"
#define __NR64ATRA0_vmsplice(fdout, iov, count, flags) ,(int)(fdout)
#define __NR64ATRF1_vmsplice               "%p"
#define __NR64ATRA1_vmsplice(fdout, iov, count, flags) ,iov
#define __NR64ATRF2_vmsplice               "%" PRIuSIZ
#define __NR64ATRA2_vmsplice(fdout, iov, count, flags) ,count
#define __NR64ATRF3_vmsplice               "%#" PRIxSIZ
#define __NR64ATRA3_vmsplice(fdout, iov, count, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_move_pages             "%d"
#define __NR64ATRA0_move_pages(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_utimensat              "%d"
#define __NR64ATRA0_utimensat(dirfd, filename, times, flags) ,(int)(dirfd)
#define __NR64ATRF1_utimensat              "%q"
#define __NR64ATRA1_utimensat(dirfd, filename, times, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF2_utimensat              "%p"
#define __NR64ATRA2_utimensat(dirfd, filename, times, flags) ,times
#define __NR64ATRF3_utimensat              "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA3_utimensat(dirfd, filename, times, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                             ,((flags) & AT_CHANGE_CTIME) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_CHANGE_CTIME ? "AT_CHANGE_CTIME" : "" \
                                                             ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_epoll_pwait            "%d"
#define __NR64ATRA0_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(int)(epfd)
#define __NR64ATRF1_epoll_pwait            "%p"
#define __NR64ATRA1_epoll_pwait(epfd, events, maxevents, timeout, ss) ,events
#define __NR64ATRF2_epoll_pwait            "%#" PRIxSIZ
#define __NR64ATRA2_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(uintptr_t)(maxevents)
#define __NR64ATRF3_epoll_pwait            "%" PRIdSIZ
#define __NR64ATRA3_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(intptr_t)(timeout)
#define __NR64ATRF4_epoll_pwait            "%p"
#define __NR64ATRA4_epoll_pwait(epfd, events, maxevents, timeout, ss) ,ss
#define __NR64ATRF0_signalfd               "%d"
#define __NR64ATRA0_signalfd(fd, sigmask, sigsetsize) ,(int)(fd)
#define __NR64ATRF1_signalfd               "%p"
#define __NR64ATRA1_signalfd(fd, sigmask, sigsetsize) ,sigmask
#define __NR64ATRF2_signalfd               "%" PRIuSIZ
#define __NR64ATRA2_signalfd(fd, sigmask, sigsetsize) ,sigsetsize
#define __NR64ATRF0_timerfd_create         "%#" PRIxSIZ
#define __NR64ATRA0_timerfd_create(clock_id, flags) ,(uintptr_t)(clock_id)
#define __NR64ATRF1_timerfd_create         "%#" PRIxSIZ
#define __NR64ATRA1_timerfd_create(clock_id, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_eventfd                "%#" PRIxSIZ
#define __NR64ATRA0_eventfd(initval)       ,(uintptr_t)(initval)
#define __NR64ATRF0_fallocate              "%d"
#define __NR64ATRA0_fallocate(fd, mode, offset, length) ,(int)(fd)
#define __NR64ATRF1_fallocate              "%#" PRIxSIZ
#define __NR64ATRA1_fallocate(fd, mode, offset, length) ,(uintptr_t)(mode)
#define __NR64ATRF2_fallocate              "%#" PRIxSIZ
#define __NR64ATRA2_fallocate(fd, mode, offset, length) ,(uintptr_t)(offset)
#define __NR64ATRF3_fallocate              "%#" PRIxSIZ
#define __NR64ATRA3_fallocate(fd, mode, offset, length) ,(uintptr_t)(length)
#define __NR64ATRF0_timerfd_settime        "%d"
#define __NR64ATRA0_timerfd_settime(ufd, flags, utmr, otmr) ,(int)(ufd)
#define __NR64ATRF1_timerfd_settime        "%#" PRIxSIZ
#define __NR64ATRA1_timerfd_settime(ufd, flags, utmr, otmr) ,(uintptr_t)(flags)
#define __NR64ATRF2_timerfd_settime        "%p"
#define __NR64ATRA2_timerfd_settime(ufd, flags, utmr, otmr) ,utmr
#define __NR64ATRF3_timerfd_settime        "%p"
#define __NR64ATRA3_timerfd_settime(ufd, flags, utmr, otmr) ,otmr
#define __NR64ATRF0_timerfd_gettime        "%d"
#define __NR64ATRA0_timerfd_gettime(ufd, otmr) ,(int)(ufd)
#define __NR64ATRF1_timerfd_gettime        "%p"
#define __NR64ATRA1_timerfd_gettime(ufd, otmr) ,otmr
#define __NR64ATRF0_accept4                "%d"
#define __NR64ATRA0_accept4(sockfd, addr, addr_len, flags) ,(int)(sockfd)
#define __NR64ATRF1_accept4                "%p"
#define __NR64ATRA1_accept4(sockfd, addr, addr_len, flags) ,addr
#define __NR64ATRF2_accept4                "%p"
#define __NR64ATRA2_accept4(sockfd, addr, addr_len, flags) ,addr_len
#define __NR64ATRF3_accept4                "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA3_accept4(sockfd, addr, addr_len, flags) ,(uintptr_t)(flags),(flags) & SOCK_NONBLOCK ? "SOCK_NONBLOCK" : "" \
                                                           ,((flags) & SOCK_CLOEXEC) && ((flags) & (SOCK_NONBLOCK)) ? "|" : "",(flags) & SOCK_CLOEXEC ? "SOCK_CLOEXEC" : "" \
                                                           ,((flags) & SOCK_CLOFORK) && ((flags) & (SOCK_NONBLOCK|SOCK_CLOEXEC)) ? "|" : "",(flags) & SOCK_CLOFORK ? "SOCK_CLOFORK" : ""
#define __NR64ATRF0_signalfd4              "%d"
#define __NR64ATRA0_signalfd4(fd, sigmask, sigsetsize, flags) ,(int)(fd)
#define __NR64ATRF1_signalfd4              "%p"
#define __NR64ATRA1_signalfd4(fd, sigmask, sigsetsize, flags) ,sigmask
#define __NR64ATRF2_signalfd4              "%" PRIuSIZ
#define __NR64ATRA2_signalfd4(fd, sigmask, sigsetsize, flags) ,sigsetsize
#define __NR64ATRF3_signalfd4              "%#" PRIxSIZ "=%s%s%s"
#define __NR64ATRA3_signalfd4(fd, sigmask, sigsetsize, flags) ,(uintptr_t)(flags),(flags) & SFD_NONBLOCK ? "SFD_NONBLOCK" : "" \
                                                              ,((flags) & SFD_CLOEXEC) && ((flags) & (SFD_NONBLOCK)) ? "|" : "",(flags) & SFD_CLOEXEC ? "SFD_CLOEXEC" : ""
#define __NR64ATRF0_eventfd2               "%#" PRIxSIZ
#define __NR64ATRA0_eventfd2(initval, flags) ,(uintptr_t)(initval)
#define __NR64ATRF1_eventfd2               "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA1_eventfd2(initval, flags) ,(uintptr_t)(flags),(flags) & EFD_SEMAPHORE ? "EFD_SEMAPHORE" : "" \
                                             ,((flags) & EFD_NONBLOCK) && ((flags) & (EFD_SEMAPHORE)) ? "|" : "",(flags) & EFD_NONBLOCK ? "EFD_NONBLOCK" : "" \
                                             ,((flags) & EFD_CLOEXEC) && ((flags) & (EFD_SEMAPHORE|EFD_NONBLOCK)) ? "|" : "",(flags) & EFD_CLOEXEC ? "EFD_CLOEXEC" : ""
#define __NR64ATRF0_epoll_create1          "%#" PRIxSIZ
#define __NR64ATRA0_epoll_create1(flags)   ,(uintptr_t)(flags)
#define __NR64ATRF0_dup3                   "%d"
#define __NR64ATRA0_dup3(oldfd, newfd, flags) ,(int)(oldfd)
#define __NR64ATRF1_dup3                   "%d"
#define __NR64ATRA1_dup3(oldfd, newfd, flags) ,(int)(newfd)
#define __NR64ATRF2_dup3                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA2_dup3(oldfd, newfd, flags) ,(uintptr_t)(flags),(flags) & O_WRONLY ? "O_WRONLY" : (flags) ? "" : "O_RDONLY" \
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
#define __NR64ATRF0_pipe2                  "%p"
#define __NR64ATRA0_pipe2(pipedes, flags)  ,pipedes
#define __NR64ATRF1_pipe2                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR64ATRA1_pipe2(pipedes, flags)  ,(uintptr_t)(flags),(flags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                           ,((flags) & O_CLOFORK) && ((flags) & (O_CLOEXEC)) ? "|" : "",(flags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                           ,((flags) & O_NONBLOCK) && ((flags) & (O_CLOEXEC|O_CLOFORK)) ? "|" : "",(flags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                           ,((flags) & O_DIRECT) && ((flags) & (O_CLOEXEC|O_CLOFORK|O_NONBLOCK)) ? "|" : "",(flags) & O_DIRECT ? "O_DIRECT" : ""
#define __NR64ATRF0_inotify_init1          "%d"
#define __NR64ATRA0_inotify_init1(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_preadv                 "%d"
#define __NR64ATRA0_preadv(fd, iovec, count, offset) ,(int)(fd)
#define __NR64ATRF1_preadv                 "%p"
#define __NR64ATRA1_preadv(fd, iovec, count, offset) ,iovec
#define __NR64ATRF2_preadv                 "%" PRIuSIZ
#define __NR64ATRA2_preadv(fd, iovec, count, offset) ,count
#define __NR64ATRF3_preadv                 "%" PRIu64
#define __NR64ATRA3_preadv(fd, iovec, count, offset) ,offset
#define __NR64ATRF0_pwritev                "%d"
#define __NR64ATRA0_pwritev(fd, iovec, count, offset) ,(int)(fd)
#define __NR64ATRF1_pwritev                "%p"
#define __NR64ATRA1_pwritev(fd, iovec, count, offset) ,iovec
#define __NR64ATRF2_pwritev                "%" PRIuSIZ
#define __NR64ATRA2_pwritev(fd, iovec, count, offset) ,count
#define __NR64ATRF3_pwritev                "%" PRIu64
#define __NR64ATRA3_pwritev(fd, iovec, count, offset) ,offset
#define __NR64ATRF0_rt_tgsigqueueinfo      "%" PRIdSIZ
#define __NR64ATRA0_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(intptr_t)(tgid)
#define __NR64ATRF1_rt_tgsigqueueinfo      "%" PRIdSIZ
#define __NR64ATRA1_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(intptr_t)(tid)
#define __NR64ATRF2_rt_tgsigqueueinfo      "%#" PRIxSIZ
#define __NR64ATRA2_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(uintptr_t)(signo)
#define __NR64ATRF3_rt_tgsigqueueinfo      "%p"
#define __NR64ATRA3_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,uinfo
#define __NR64ATRF0_perf_event_open        "%d"
#define __NR64ATRA0_perf_event_open(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_recvmmsg               "%d"
#define __NR64ATRA0_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,(int)(sockfd)
#define __NR64ATRF1_recvmmsg               "%p"
#define __NR64ATRA1_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,vmessages
#define __NR64ATRF2_recvmmsg               "%" PRIuSIZ
#define __NR64ATRA2_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,vlen
#define __NR64ATRF3_recvmmsg               "%#" PRIxSIZ
#define __NR64ATRA3_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,(uintptr_t)(flags)
#define __NR64ATRF4_recvmmsg               "%p"
#define __NR64ATRA4_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,tmo
#define __NR64ATRF0_fanotify_init          "%d"
#define __NR64ATRA0_fanotify_init(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_fanotify_mark          "%d"
#define __NR64ATRA0_fanotify_mark(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_prlimit64              "%" PRIdSIZ
#define __NR64ATRA0_prlimit64(pid, resource, new_limit, old_limit) ,(intptr_t)(pid)
#define __NR64ATRF1_prlimit64              "%#" PRIxSIZ
#define __NR64ATRA1_prlimit64(pid, resource, new_limit, old_limit) ,(uintptr_t)(resource)
#define __NR64ATRF2_prlimit64              "%p"
#define __NR64ATRA2_prlimit64(pid, resource, new_limit, old_limit) ,new_limit
#define __NR64ATRF3_prlimit64              "%p"
#define __NR64ATRA3_prlimit64(pid, resource, new_limit, old_limit) ,old_limit
#define __NR64ATRF0_name_to_handle_at      "%d"
#define __NR64ATRA0_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(int)(dirfd)
#define __NR64ATRF1_name_to_handle_at      "%q"
#define __NR64ATRA1_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF2_name_to_handle_at      "%p"
#define __NR64ATRA2_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,handle
#define __NR64ATRF3_name_to_handle_at      "%p"
#define __NR64ATRA3_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,mnt_id
#define __NR64ATRF4_name_to_handle_at      "%#" PRIxSIZ
#define __NR64ATRA4_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_open_by_handle_at      "%d"
#define __NR64ATRA0_open_by_handle_at(mountdirfd, handle, flags) ,(int)(mountdirfd)
#define __NR64ATRF1_open_by_handle_at      "%p"
#define __NR64ATRA1_open_by_handle_at(mountdirfd, handle, flags) ,handle
#define __NR64ATRF2_open_by_handle_at      "%#" PRIxSIZ
#define __NR64ATRA2_open_by_handle_at(mountdirfd, handle, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_clock_adjtime          "%d"
#define __NR64ATRA0_clock_adjtime(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_syncfs                 "%d"
#define __NR64ATRA0_syncfs(fd)             ,(int)(fd)
#define __NR64ATRF0_sendmmsg               "%d"
#define __NR64ATRA0_sendmmsg(sockfd, vmessages, vlen, flags) ,(int)(sockfd)
#define __NR64ATRF1_sendmmsg               "%p"
#define __NR64ATRA1_sendmmsg(sockfd, vmessages, vlen, flags) ,vmessages
#define __NR64ATRF2_sendmmsg               "%" PRIuSIZ
#define __NR64ATRA2_sendmmsg(sockfd, vmessages, vlen, flags) ,vlen
#define __NR64ATRF3_sendmmsg               "%#" PRIxSIZ
#define __NR64ATRA3_sendmmsg(sockfd, vmessages, vlen, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_setns                  "%d"
#define __NR64ATRA0_setns(fd, nstype)      ,(int)(fd)
#define __NR64ATRF1_setns                  "%#" PRIxSIZ
#define __NR64ATRA1_setns(fd, nstype)      ,(uintptr_t)(nstype)
#define __NR64ATRF0_getcpu                 "%p"
#define __NR64ATRA0_getcpu(cpu, node, tcache) ,cpu
#define __NR64ATRF1_getcpu                 "%p"
#define __NR64ATRA1_getcpu(cpu, node, tcache) ,node
#define __NR64ATRF2_getcpu                 "%p"
#define __NR64ATRA2_getcpu(cpu, node, tcache) ,tcache
#define __NR64ATRF0_process_vm_readv       "%" PRIdSIZ
#define __NR64ATRA0_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(intptr_t)(pid)
#define __NR64ATRF1_process_vm_readv       "%p"
#define __NR64ATRA1_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,lvec
#define __NR64ATRF2_process_vm_readv       "%" PRIuSIZ
#define __NR64ATRA2_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,liovcnt
#define __NR64ATRF3_process_vm_readv       "%p"
#define __NR64ATRA3_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,rvec
#define __NR64ATRF4_process_vm_readv       "%" PRIuSIZ
#define __NR64ATRA4_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,riovcnt
#define __NR64ATRF5_process_vm_readv       "%#" PRIxSIZ
#define __NR64ATRA5_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_process_vm_writev      "%" PRIdSIZ
#define __NR64ATRA0_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(intptr_t)(pid)
#define __NR64ATRF1_process_vm_writev      "%p"
#define __NR64ATRA1_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,lvec
#define __NR64ATRF2_process_vm_writev      "%" PRIuSIZ
#define __NR64ATRA2_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,liovcnt
#define __NR64ATRF3_process_vm_writev      "%p"
#define __NR64ATRA3_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,rvec
#define __NR64ATRF4_process_vm_writev      "%" PRIuSIZ
#define __NR64ATRA4_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,riovcnt
#define __NR64ATRF5_process_vm_writev      "%#" PRIxSIZ
#define __NR64ATRA5_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_kcmp                   "%" PRIdSIZ
#define __NR64ATRA0_kcmp(pid1, pid2, type, idx1, idx2) ,(intptr_t)(pid1)
#define __NR64ATRF1_kcmp                   "%" PRIdSIZ
#define __NR64ATRA1_kcmp(pid1, pid2, type, idx1, idx2) ,(intptr_t)(pid2)
#define __NR64ATRF2_kcmp                   "%#" PRIxSIZ
#define __NR64ATRA2_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(type)
#define __NR64ATRF3_kcmp                   "%#" PRIxSIZ
#define __NR64ATRA3_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(idx1)
#define __NR64ATRF4_kcmp                   "%#" PRIxSIZ
#define __NR64ATRA4_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(idx2)
#define __NR64ATRF0_finit_module           "%d"
#define __NR64ATRA0_finit_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_sched_setattr          "%d"
#define __NR64ATRA0_sched_setattr(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_sched_getattr          "%d"
#define __NR64ATRA0_sched_getattr(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_renameat2              "%d"
#define __NR64ATRA0_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(int)(olddirfd)
#define __NR64ATRF1_renameat2              "%q"
#define __NR64ATRA1_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(validate_readable_opt(oldpath,1),oldpath)
#define __NR64ATRF2_renameat2              "%d"
#define __NR64ATRA2_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(int)(newdirfd)
#define __NR64ATRF3_renameat2              "%q"
#define __NR64ATRA3_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(validate_readable_opt(newpath,1),newpath)
#define __NR64ATRF4_renameat2              "%#" PRIxSIZ
#define __NR64ATRA4_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(uintptr_t)(flags)
#define __NR64ATRF0_seccomp                "%d"
#define __NR64ATRA0_seccomp(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_getrandom              "%d"
#define __NR64ATRA0_getrandom(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_memfd_create           "%d"
#define __NR64ATRA0_memfd_create(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_kexec_file_load        "%d"
#define __NR64ATRA0_kexec_file_load(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_bpf                    "%d"
#define __NR64ATRA0_bpf(TODO_PROTOTYPE)    ,TODO_PROTOTYPE
#define __NR64ATRF0_execveat               "%d"
#define __NR64ATRA0_execveat(dirfd, pathname, argv, envp, flags) ,(int)(dirfd)
#define __NR64ATRF1_execveat               "%q"
#define __NR64ATRA1_execveat(dirfd, pathname, argv, envp, flags) ,(validate_readable_opt(pathname,1),pathname)
#define __NR64ATRF2_execveat               "%p"
#define __NR64ATRA2_execveat(dirfd, pathname, argv, envp, flags) ,argv
#define __NR64ATRF3_execveat               "%p"
#define __NR64ATRA3_execveat(dirfd, pathname, argv, envp, flags) ,envp
#define __NR64ATRF4_execveat               "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA4_execveat(dirfd, pathname, argv, envp, flags) ,(uintptr_t)(flags),(flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                                 ,((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "",(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_userfaultfd            "%d"
#define __NR64ATRA0_userfaultfd(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_membarrier             "%d"
#define __NR64ATRA0_membarrier(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_mlock2                 "%d"
#define __NR64ATRA0_mlock2(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR64ATRF0_readf                  "%d"
#define __NR64ATRA0_readf(fd, buf, bufsize, mode) ,(int)(fd)
#define __NR64ATRF1_readf                  "%p"
#define __NR64ATRA1_readf(fd, buf, bufsize, mode) ,buf
#define __NR64ATRF2_readf                  "%" PRIuSIZ
#define __NR64ATRA2_readf(fd, buf, bufsize, mode) ,bufsize
#define __NR64ATRF3_readf                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA3_readf(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                  ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                  ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                  ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                  ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                  ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                  ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                  ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                  ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF0_writef                 "%d"
#define __NR64ATRA0_writef(fd, buf, bufsize, mode) ,(int)(fd)
#define __NR64ATRF1_writef                 "%p"
#define __NR64ATRA1_writef(fd, buf, bufsize, mode) ,buf
#define __NR64ATRF2_writef                 "%" PRIuSIZ
#define __NR64ATRA2_writef(fd, buf, bufsize, mode) ,bufsize
#define __NR64ATRF3_writef                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA3_writef(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                   ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                   ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                   ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                   ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                   ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                   ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                   ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                   ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF0_hop                    "%d"
#define __NR64ATRA0_hop(fd, command, arg)  ,(int)(fd)
#define __NR64ATRF1_hop                    "%#" PRIxSIZ
#define __NR64ATRA1_hop(fd, command, arg)  ,(uintptr_t)(command)
#define __NR64ATRF2_hop                    "%p"
#define __NR64ATRA2_hop(fd, command, arg)  ,arg
#define __NR64ATRF0_hopf                   "%d"
#define __NR64ATRA0_hopf(fd, command, mode, arg) ,(int)(fd)
#define __NR64ATRF1_hopf                   "%#" PRIxSIZ
#define __NR64ATRA1_hopf(fd, command, mode, arg) ,(uintptr_t)(command)
#define __NR64ATRF2_hopf                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA2_hopf(fd, command, mode, arg) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                 ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                 ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                 ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                 ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                 ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                 ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                 ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                 ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF3_hopf                   "%p"
#define __NR64ATRA3_hopf(fd, command, mode, arg) ,arg
#define __NR64ATRF0_kstat                  "%q"
#define __NR64ATRA0_kstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_kstat                  "%p"
#define __NR64ATRA1_kstat(filename, statbuf) ,statbuf
#define __NR64ATRF0_kfstat                 "%d"
#define __NR64ATRA0_kfstat(fd, statbuf)    ,(int)(fd)
#define __NR64ATRF1_kfstat                 "%p"
#define __NR64ATRA1_kfstat(fd, statbuf)    ,statbuf
#define __NR64ATRF0_klstat                 "%q"
#define __NR64ATRA0_klstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF1_klstat                 "%p"
#define __NR64ATRA1_klstat(filename, statbuf) ,statbuf
#define __NR64ATRF0_detach                 "%" PRIdSIZ
#define __NR64ATRA0_detach(pid)            ,(intptr_t)(pid)
#define __NR64ATRF0_frealpath4             "%d"
#define __NR64ATRA0_frealpath4(fd, buf, buflen, flags) ,(int)(fd)
#define __NR64ATRF1_frealpath4             "%p"
#define __NR64ATRA1_frealpath4(fd, buf, buflen, flags) ,buf
#define __NR64ATRF2_frealpath4             "%" PRIuSIZ
#define __NR64ATRA2_frealpath4(fd, buf, buflen, flags) ,buflen
#define __NR64ATRF3_frealpath4             "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR64ATRA3_frealpath4(fd, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                       ,((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH)) ? "|" : "",(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                       ,((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH|AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_frealpathat            "%d"
#define __NR64ATRA0_frealpathat(dirfd, filename, buf, buflen, flags) ,(int)(dirfd)
#define __NR64ATRF1_frealpathat            "%q"
#define __NR64ATRA1_frealpathat(dirfd, filename, buf, buflen, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF2_frealpathat            "%p"
#define __NR64ATRA2_frealpathat(dirfd, filename, buf, buflen, flags) ,buf
#define __NR64ATRF3_frealpathat            "%" PRIuSIZ
#define __NR64ATRA3_frealpathat(dirfd, filename, buf, buflen, flags) ,buflen
#define __NR64ATRF4_frealpathat            "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR64ATRA4_frealpathat(dirfd, filename, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                                     ,((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_ALTPATH)) ? "|" : "",(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                     ,((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH|AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                                     ,((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_rpc_schedule           "%" PRIdSIZ
#define __NR64ATRA0_rpc_schedule(target, flags, program, arguments) ,(intptr_t)(target)
#define __NR64ATRF1_rpc_schedule           "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA1_rpc_schedule(target, flags, program, arguments) ,(uintptr_t)(flags),(flags) & RPC_SCHEDULE_ASYNC ? "RPC_SCHEDULE_ASYNC" : (flags) ? "" : "RPC_SCHEDULE_SYNC" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_NONSYSCALL) && ((flags) & (RPC_SCHEDULE_ASYNC)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_NONSYSCALL ? "RPC_SCHEDULE_FLAG_NONSYSCALL" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_WAITFORSTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_WAITFORSTART ? "RPC_SCHEDULE_FLAG_WAITFORSTART" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX ? "RPC_SCHEDULE_FLAG_STATUSFUTEX" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_SYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_SYSRESTART ? "RPC_SCHEDULE_FLAG_SYSRESTART" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART ? "RPC_SCHEDULE_FLAG_NOSYSRESTART" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_WAITSMPACK) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_WAITSMPACK ? "RPC_SCHEDULE_FLAG_WAITSMPACK" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_DONTWAKE) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_DONTWAKE ? "RPC_SCHEDULE_FLAG_DONTWAKE" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_HIGHPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK|RPC_SCHEDULE_FLAG_DONTWAKE)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_HIGHPRIO ? "RPC_SCHEDULE_FLAG_HIGHPRIO" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_LOWPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK|RPC_SCHEDULE_FLAG_DONTWAKE|RPC_SCHEDULE_FLAG_HIGHPRIO)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_LOWPRIO ? "RPC_SCHEDULE_FLAG_LOWPRIO" : ""
#define __NR64ATRF2_rpc_schedule           "%p"
#define __NR64ATRA2_rpc_schedule(target, flags, program, arguments) ,program
#define __NR64ATRF3_rpc_schedule           "%p"
#define __NR64ATRA3_rpc_schedule(target, flags, program, arguments) ,arguments
#define __NR64ATRF0_sysctl                 "%#" PRIxSIZ
#define __NR64ATRA0_sysctl(command, arg)   ,(uintptr_t)(command)
#define __NR64ATRF1_sysctl                 "%p"
#define __NR64ATRA1_sysctl(command, arg)   ,arg
#define __NR64ATRF0_openpty                "%p"
#define __NR64ATRA0_openpty(amaster, aslave, name, termp, winp) ,amaster
#define __NR64ATRF1_openpty                "%p"
#define __NR64ATRA1_openpty(amaster, aslave, name, termp, winp) ,aslave
#define __NR64ATRF2_openpty                "%p"
#define __NR64ATRA2_openpty(amaster, aslave, name, termp, winp) ,name
#define __NR64ATRF3_openpty                "%p"
#define __NR64ATRA3_openpty(amaster, aslave, name, termp, winp) ,termp
#define __NR64ATRF4_openpty                "%p"
#define __NR64ATRA4_openpty(amaster, aslave, name, termp, winp) ,winp
#define __NR64ATRF0_set_exception_handler  "%#" PRIxSIZ
#define __NR64ATRA0_set_exception_handler(mode, handler, handler_sp) ,(uintptr_t)(mode)
#define __NR64ATRF1_set_exception_handler  "%p"
#define __NR64ATRA1_set_exception_handler(mode, handler, handler_sp) ,handler
#define __NR64ATRF2_set_exception_handler  "%p"
#define __NR64ATRA2_set_exception_handler(mode, handler, handler_sp) ,handler_sp
#define __NR64ATRF0_get_exception_handler  "%p"
#define __NR64ATRA0_get_exception_handler(pmode, phandler, phandler_sp) ,pmode
#define __NR64ATRF1_get_exception_handler  "%p"
#define __NR64ATRA1_get_exception_handler(pmode, phandler, phandler_sp) ,phandler
#define __NR64ATRF2_get_exception_handler  "%p"
#define __NR64ATRA2_get_exception_handler(pmode, phandler, phandler_sp) ,phandler_sp
#define __NR64ATRF0_ioctlf                 "%d"
#define __NR64ATRA0_ioctlf(fd, command, mode, arg) ,(int)(fd)
#define __NR64ATRF1_ioctlf                 "%#" PRIxSIZ
#define __NR64ATRA1_ioctlf(fd, command, mode, arg) ,(uintptr_t)(command)
#define __NR64ATRF2_ioctlf                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA2_ioctlf(fd, command, mode, arg) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                   ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                   ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                   ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                   ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                   ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                   ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                   ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                   ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF3_ioctlf                 "%p"
#define __NR64ATRA3_ioctlf(fd, command, mode, arg) ,arg
#define __NR64ATRF0_pread64f               "%d"
#define __NR64ATRA0_pread64f(fd, buf, bufsize, offset, mode) ,(int)(fd)
#define __NR64ATRF1_pread64f               "%p"
#define __NR64ATRA1_pread64f(fd, buf, bufsize, offset, mode) ,buf
#define __NR64ATRF2_pread64f               "%" PRIuSIZ
#define __NR64ATRA2_pread64f(fd, buf, bufsize, offset, mode) ,bufsize
#define __NR64ATRF3_pread64f               "%" PRIu64
#define __NR64ATRA3_pread64f(fd, buf, bufsize, offset, mode) ,offset
#define __NR64ATRF4_pread64f               "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA4_pread64f(fd, buf, bufsize, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                             ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                             ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                             ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                             ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                             ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                             ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                             ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                             ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF0_pwrite64f              "%d"
#define __NR64ATRA0_pwrite64f(fd, buf, bufsize, offset, mode) ,(int)(fd)
#define __NR64ATRF1_pwrite64f              "%p"
#define __NR64ATRA1_pwrite64f(fd, buf, bufsize, offset, mode) ,buf
#define __NR64ATRF2_pwrite64f              "%" PRIuSIZ
#define __NR64ATRA2_pwrite64f(fd, buf, bufsize, offset, mode) ,bufsize
#define __NR64ATRF3_pwrite64f              "%" PRIu64
#define __NR64ATRA3_pwrite64f(fd, buf, bufsize, offset, mode) ,offset
#define __NR64ATRF4_pwrite64f              "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA4_pwrite64f(fd, buf, bufsize, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                              ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                              ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                              ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                              ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                              ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                              ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                              ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                              ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF0_readvf                 "%d"
#define __NR64ATRA0_readvf(fd, iovec, count, mode) ,(int)(fd)
#define __NR64ATRF1_readvf                 "%p"
#define __NR64ATRA1_readvf(fd, iovec, count, mode) ,iovec
#define __NR64ATRF2_readvf                 "%" PRIuSIZ
#define __NR64ATRA2_readvf(fd, iovec, count, mode) ,count
#define __NR64ATRF3_readvf                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA3_readvf(fd, iovec, count, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                   ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                   ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                   ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                   ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                   ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                   ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                   ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                   ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF0_writevf                "%d"
#define __NR64ATRA0_writevf(fd, iovec, count, mode) ,(int)(fd)
#define __NR64ATRF1_writevf                "%p"
#define __NR64ATRA1_writevf(fd, iovec, count, mode) ,iovec
#define __NR64ATRF2_writevf                "%" PRIuSIZ
#define __NR64ATRA2_writevf(fd, iovec, count, mode) ,count
#define __NR64ATRF3_writevf                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA3_writevf(fd, iovec, count, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                    ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                    ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                    ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                    ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                    ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                    ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                    ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                    ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF0_set_library_listdef    "%p"
#define __NR64ATRA0_set_library_listdef(listdef) ,listdef
#define __NR64ATRF0_debugtrap              "%p"
#define __NR64ATRA0_debugtrap(state, reason) ,state
#define __NR64ATRF1_debugtrap              "%p"
#define __NR64ATRA1_debugtrap(state, reason) ,reason
#define __NR64ATRF0_lfutex                 "%p"
#define __NR64ATRA0_lfutex(uaddr, futex_op, val, timeout, val2) ,uaddr
#define __NR64ATRF1_lfutex                 "%#" PRIxSIZ
#define __NR64ATRA1_lfutex(uaddr, futex_op, val, timeout, val2) ,(uintptr_t)(futex_op)
#define __NR64ATRF2_lfutex                 "%p"
#define __NR64ATRA2_lfutex(uaddr, futex_op, val, timeout, val2) ,val
#define __NR64ATRF3_lfutex                 "%p"
#define __NR64ATRA3_lfutex(uaddr, futex_op, val, timeout, val2) ,timeout
#define __NR64ATRF4_lfutex                 "%p"
#define __NR64ATRA4_lfutex(uaddr, futex_op, val, timeout, val2) ,val2
#define __NR64ATRF0_lfutexexpr             "%p"
#define __NR64ATRA0_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,base
#define __NR64ATRF1_lfutexexpr             "%" PRIuSIZ
#define __NR64ATRA1_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,exprc
#define __NR64ATRF2_lfutexexpr             "%p"
#define __NR64ATRA2_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,exprv
#define __NR64ATRF3_lfutexexpr             "%p"
#define __NR64ATRA3_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,timeout
#define __NR64ATRF4_lfutexexpr             "%#" PRIxSIZ
#define __NR64ATRA4_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,(uintptr_t)(timeout_flags)
#define __NR64ATRF0_lfutexlockexpr         "%p"
#define __NR64ATRA0_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,ulockaddr
#define __NR64ATRF1_lfutexlockexpr         "%p"
#define __NR64ATRA1_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,base
#define __NR64ATRF2_lfutexlockexpr         "%" PRIuSIZ
#define __NR64ATRA2_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,exprc
#define __NR64ATRF3_lfutexlockexpr         "%p"
#define __NR64ATRA3_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,exprv
#define __NR64ATRF4_lfutexlockexpr         "%p"
#define __NR64ATRA4_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,timeout
#define __NR64ATRF5_lfutexlockexpr         "%#" PRIxSIZ
#define __NR64ATRA5_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,(uintptr_t)(timeout_flags)
#define __NR64ATRF0_mktty                  "%d"
#define __NR64ATRA0_mktty(keyboard, display, name, rsvd) ,(int)(keyboard)
#define __NR64ATRF1_mktty                  "%d"
#define __NR64ATRA1_mktty(keyboard, display, name, rsvd) ,(int)(display)
#define __NR64ATRF2_mktty                  "%q"
#define __NR64ATRA2_mktty(keyboard, display, name, rsvd) ,(validate_readable_opt(name,1),name)
#define __NR64ATRF3_mktty                  "%#" PRIxSIZ
#define __NR64ATRA3_mktty(keyboard, display, name, rsvd) ,(uintptr_t)(rsvd)
#define __NR64ATRF0_raiseat                "%p"
#define __NR64ATRA0_raiseat(state, si)     ,state
#define __NR64ATRF1_raiseat                "%p"
#define __NR64ATRA1_raiseat(state, si)     ,si
#define __NR64ATRF0_coredump               "%p"
#define __NR64ATRA0_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,curr_state
#define __NR64ATRF1_coredump               "%p"
#define __NR64ATRA1_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,orig_state
#define __NR64ATRF2_coredump               "%p"
#define __NR64ATRA2_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,traceback_vector
#define __NR64ATRF3_coredump               "%" PRIuSIZ
#define __NR64ATRA3_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,traceback_length
#define __NR64ATRF4_coredump               "%p"
#define __NR64ATRA4_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,exception
#define __NR64ATRF5_coredump               "%#" PRIxSIZ
#define __NR64ATRA5_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,(uintptr_t)(unwind_error)
#define __NR64ATRF0_kreaddir               "%d"
#define __NR64ATRA0_kreaddir(fd, buf, bufsize, mode) ,(int)(fd)
#define __NR64ATRF1_kreaddir               "%p"
#define __NR64ATRA1_kreaddir(fd, buf, bufsize, mode) ,buf
#define __NR64ATRF2_kreaddir               "%" PRIuSIZ
#define __NR64ATRA2_kreaddir(fd, buf, bufsize, mode) ,bufsize
#define __NR64ATRF3_kreaddir               "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR64ATRA3_kreaddir(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                     ,((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "",(mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                     ,((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK)) ? "|" : "",(mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                     ,((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK|READDIR_SKIPREL)) ? "|" : "",(mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NR64ATRF0_fchdirat               "%d"
#define __NR64ATRA0_fchdirat(dirfd, path, flags) ,(int)(dirfd)
#define __NR64ATRF1_fchdirat               "%q"
#define __NR64ATRA1_fchdirat(dirfd, path, flags) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF2_fchdirat               "%#" PRIxSIZ "=%s"
#define __NR64ATRA2_fchdirat(dirfd, path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_fsmode                 "%" PRIu64
#define __NR64ATRA0_fsmode(mode)           ,mode
#define __NR64ATRF0_maplibrary             "%p"
#define __NR64ATRA0_maplibrary(addr, flags, fd, hdrv, hdrc) ,addr
#define __NR64ATRF1_maplibrary             "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA1_maplibrary(addr, flags, fd, hdrv, hdrc) ,(uintptr_t)(flags),(flags) & MAP_FIXED ? "MAP_FIXED" : "" \
                                                            ,((flags) & MAP_LOCKED) && ((flags) & (MAP_FIXED)) ? "|" : "",(flags) & MAP_LOCKED ? "MAP_LOCKED" : "" \
                                                            ,((flags) & MAP_NONBLOCK) && ((flags) & (MAP_FIXED|MAP_LOCKED)) ? "|" : "",(flags) & MAP_NONBLOCK ? "MAP_NONBLOCK" : "" \
                                                            ,((flags) & MAP_NORESERVE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK)) ? "|" : "",(flags) & MAP_NORESERVE ? "MAP_NORESERVE" : "" \
                                                            ,((flags) & MAP_POPULATE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE)) ? "|" : "",(flags) & MAP_POPULATE ? "MAP_POPULATE" : "" \
                                                            ,((flags) & MAP_SYNC) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE)) ? "|" : "",(flags) & MAP_SYNC ? "MAP_SYNC" : "" \
                                                            ,((flags) & MAP_DONT_MAP) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_SYNC)) ? "|" : "",(flags) & MAP_DONT_MAP ? "MAP_DONT_MAP" : "" \
                                                            ,((flags) & MAP_DONT_OVERRIDE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP)) ? "|" : "",(flags) & MAP_DONT_OVERRIDE ? "MAP_DONT_OVERRIDE" : ""
#define __NR64ATRF2_maplibrary             "%d"
#define __NR64ATRA2_maplibrary(addr, flags, fd, hdrv, hdrc) ,(int)(fd)
#define __NR64ATRF3_maplibrary             "%p"
#define __NR64ATRA3_maplibrary(addr, flags, fd, hdrv, hdrc) ,hdrv
#define __NR64ATRF4_maplibrary             "%" PRIuSIZ
#define __NR64ATRA4_maplibrary(addr, flags, fd, hdrv, hdrc) ,hdrc
#define __NR64ATRF0_kreaddirf              "%d"
#define __NR64ATRA0_kreaddirf(fd, buf, bufsize, mode, iomode) ,(int)(fd)
#define __NR64ATRF1_kreaddirf              "%p"
#define __NR64ATRA1_kreaddirf(fd, buf, bufsize, mode, iomode) ,buf
#define __NR64ATRF2_kreaddirf              "%" PRIuSIZ
#define __NR64ATRA2_kreaddirf(fd, buf, bufsize, mode, iomode) ,bufsize
#define __NR64ATRF3_kreaddirf              "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR64ATRA3_kreaddirf(fd, buf, bufsize, mode, iomode) ,(uintptr_t)(mode),(mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                              ,((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "",(mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                              ,((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK)) ? "|" : "",(mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                              ,((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK|READDIR_SKIPREL)) ? "|" : "",(mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NR64ATRF4_kreaddirf              "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA4_kreaddirf(fd, buf, bufsize, mode, iomode) ,(uintptr_t)(iomode),(iomode) & IO_WRONLY ? "IO_WRONLY" : (iomode) ? "" : "IO_RDONLY" \
                                                              ,((iomode) & IO_RDWR) && ((iomode) & (IO_WRONLY)) ? "|" : "",(iomode) & IO_RDWR ? "IO_RDWR" : "" \
                                                              ,((iomode) & IO_CLOEXEC) && ((iomode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(iomode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                              ,((iomode) & IO_CLOFORK) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(iomode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                              ,((iomode) & IO_APPEND) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(iomode) & IO_APPEND ? "IO_APPEND" : "" \
                                                              ,((iomode) & IO_NONBLOCK) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(iomode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                              ,((iomode) & IO_SYNC) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(iomode) & IO_SYNC ? "IO_SYNC" : "" \
                                                              ,((iomode) & IO_ASYNC) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(iomode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                              ,((iomode) & IO_DIRECT) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(iomode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF0_fmkdirat               "%d"
#define __NR64ATRA0_fmkdirat(dirfd, pathname, mode, flags) ,(int)(dirfd)
#define __NR64ATRF1_fmkdirat               "%q"
#define __NR64ATRA1_fmkdirat(dirfd, pathname, mode, flags) ,(validate_readable_opt(pathname,1),pathname)
#define __NR64ATRF2_fmkdirat               "%#" PRIoSIZ
#define __NR64ATRA2_fmkdirat(dirfd, pathname, mode, flags) ,(uintptr_t)(mode)
#define __NR64ATRF3_fmkdirat               "%#" PRIxSIZ "=%s"
#define __NR64ATRA3_fmkdirat(dirfd, pathname, mode, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_fmknodat               "%d"
#define __NR64ATRA0_fmknodat(dirfd, nodename, mode, dev, flags) ,(int)(dirfd)
#define __NR64ATRF1_fmknodat               "%q"
#define __NR64ATRA1_fmknodat(dirfd, nodename, mode, dev, flags) ,(validate_readable_opt(nodename,1),nodename)
#define __NR64ATRF2_fmknodat               "%#" PRIoSIZ
#define __NR64ATRA2_fmknodat(dirfd, nodename, mode, dev, flags) ,(uintptr_t)(mode)
#define __NR64ATRF3_fmknodat               "%.2x:%.2x"
#define __NR64ATRA3_fmknodat(dirfd, nodename, mode, dev, flags) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR64ATRF4_fmknodat               "%#" PRIxSIZ "=%s"
#define __NR64ATRA4_fmknodat(dirfd, nodename, mode, dev, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_kfstatat               "%d"
#define __NR64ATRA0_kfstatat(dirfd, filename, statbuf, flags) ,(int)(dirfd)
#define __NR64ATRF1_kfstatat               "%q"
#define __NR64ATRA1_kfstatat(dirfd, filename, statbuf, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR64ATRF2_kfstatat               "%p"
#define __NR64ATRA2_kfstatat(dirfd, filename, statbuf, flags) ,statbuf
#define __NR64ATRF3_kfstatat               "%#" PRIxSIZ "=%s%s%s"
#define __NR64ATRA3_kfstatat(dirfd, filename, statbuf, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                              ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_frenameat              "%d"
#define __NR64ATRA0_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(int)(oldfd)
#define __NR64ATRF1_frenameat              "%q"
#define __NR64ATRA1_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(validate_readable_opt(oldname,1),oldname)
#define __NR64ATRF2_frenameat              "%d"
#define __NR64ATRA2_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(int)(newfd)
#define __NR64ATRF3_frenameat              "%q"
#define __NR64ATRA3_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NR64ATRF4_frenameat              "%#" PRIxSIZ "=%s"
#define __NR64ATRA4_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_fsymlinkat             "%q"
#define __NR64ATRA0_fsymlinkat(link_text, tofd, target_path, flags) ,(validate_readable_opt(link_text,1),link_text)
#define __NR64ATRF1_fsymlinkat             "%d"
#define __NR64ATRA1_fsymlinkat(link_text, tofd, target_path, flags) ,(int)(tofd)
#define __NR64ATRF2_fsymlinkat             "%q"
#define __NR64ATRA2_fsymlinkat(link_text, tofd, target_path, flags) ,(validate_readable_opt(target_path,1),target_path)
#define __NR64ATRF3_fsymlinkat             "%#" PRIxSIZ "=%s"
#define __NR64ATRA3_fsymlinkat(link_text, tofd, target_path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_freadlinkat            "%d"
#define __NR64ATRA0_freadlinkat(dirfd, path, buf, buflen, flags) ,(int)(dirfd)
#define __NR64ATRF1_freadlinkat            "%q"
#define __NR64ATRA1_freadlinkat(dirfd, path, buf, buflen, flags) ,(validate_readable_opt(path,1),path)
#define __NR64ATRF2_freadlinkat            "%p"
#define __NR64ATRA2_freadlinkat(dirfd, path, buf, buflen, flags) ,buf
#define __NR64ATRF3_freadlinkat            "%" PRIuSIZ
#define __NR64ATRA3_freadlinkat(dirfd, path, buf, buflen, flags) ,buflen
#define __NR64ATRF4_freadlinkat            "%#" PRIxSIZ "=%s%s%s"
#define __NR64ATRA4_freadlinkat(dirfd, path, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR64ATRF0_preadvf                "%d"
#define __NR64ATRA0_preadvf(fd, iovec, count, offset, mode) ,(int)(fd)
#define __NR64ATRF1_preadvf                "%p"
#define __NR64ATRA1_preadvf(fd, iovec, count, offset, mode) ,iovec
#define __NR64ATRF2_preadvf                "%" PRIuSIZ
#define __NR64ATRA2_preadvf(fd, iovec, count, offset, mode) ,count
#define __NR64ATRF3_preadvf                "%" PRIu64
#define __NR64ATRA3_preadvf(fd, iovec, count, offset, mode) ,offset
#define __NR64ATRF4_preadvf                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA4_preadvf(fd, iovec, count, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                            ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                            ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                            ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                            ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                            ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                            ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                            ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                            ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR64ATRF0_pwritevf               "%d"
#define __NR64ATRA0_pwritevf(fd, iovec, count, offset, mode) ,(int)(fd)
#define __NR64ATRF1_pwritevf               "%p"
#define __NR64ATRA1_pwritevf(fd, iovec, count, offset, mode) ,iovec
#define __NR64ATRF2_pwritevf               "%" PRIuSIZ
#define __NR64ATRA2_pwritevf(fd, iovec, count, offset, mode) ,count
#define __NR64ATRF3_pwritevf               "%" PRIu64
#define __NR64ATRA3_pwritevf(fd, iovec, count, offset, mode) ,offset
#define __NR64ATRF4_pwritevf               "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR64ATRA4_pwritevf(fd, iovec, count, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                             ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                             ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                             ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                             ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                             ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                             ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                             ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                             ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#endif /* !__NR64FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT */
#endif /* __WANT_SYSCALL_ARGUMENT_FORMAT */

