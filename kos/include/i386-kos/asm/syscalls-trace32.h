/* HASH CRC-32:0x7b9c1d77 */
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

/************************************************************************/
/* SYSCALL ARGUMENT NAMES                                               */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_NAMES
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_NAMES 1
#define __NRAN0_exit                    status
#define __NRAN0_read                    fd
#define __NRAN1_read                    buf
#define __NRAN2_read                    bufsize
#define __NRAN0_write                   fd
#define __NRAN1_write                   buf
#define __NRAN2_write                   bufsize
#define __NRAN0_open                    filename
#define __NRAN1_open                    oflags
#define __NRAN2_open                    mode
#define __NRAN0_close                   fd
#define __NRAN0_waitpid                 pid
#define __NRAN1_waitpid                 stat_loc
#define __NRAN2_waitpid                 options
#define __NRAN0_creat                   filename
#define __NRAN1_creat                   mode
#define __NRAN0_link                    existing_file
#define __NRAN1_link                    link_file
#define __NRAN0_unlink                  filename
#define __NRAN0_execve                  path
#define __NRAN1_execve                  argv
#define __NRAN2_execve                  envp
#define __NRAN0_chdir                   path
#define __NRAN0_time                    timer
#define __NRAN0_mknod                   nodename
#define __NRAN1_mknod                   mode
#define __NRAN2_mknod                   dev
#define __NRAN0_chmod                   filename
#define __NRAN1_chmod                   mode
#define __NRAN0_lchown                  filename
#define __NRAN1_lchown                  owner
#define __NRAN2_lchown                  group
#define __NRAN0_linux_oldstat           filename
#define __NRAN1_linux_oldstat           statbuf
#define __NRAN0_lseek                   fd
#define __NRAN1_lseek                   offset
#define __NRAN2_lseek                   whence
#define __NRAN0_mount                   special_file
#define __NRAN1_mount                   dir
#define __NRAN2_mount                   fstype
#define __NRAN3_mount                   rwflag
#define __NRAN4_mount                   data
#define __NRAN0_umount                  special_file
#define __NRAN0_setuid                  uid
#define __NRAN0_stime                   t
#define __NRAN0_ptrace                  request
#define __NRAN1_ptrace                  pid
#define __NRAN2_ptrace                  addr
#define __NRAN3_ptrace                  data
#define __NRAN0_alarm                   seconds
#define __NRAN0_linux_oldfstat          fd
#define __NRAN1_linux_oldfstat          statbuf
#define __NRAN0_utime                   filename
#define __NRAN1_utime                   times
#define __NRAN0_access                  filename
#define __NRAN1_access                  type
#define __NRAN0_nice                    inc
#define __NRAN0_ftime                   tp
#define __NRAN0_kill                    pid
#define __NRAN1_kill                    signo
#define __NRAN0_rename                  oldname
#define __NRAN1_rename                  newname_or_path
#define __NRAN0_mkdir                   pathname
#define __NRAN1_mkdir                   mode
#define __NRAN0_rmdir                   path
#define __NRAN0_dup                     fd
#define __NRAN0_pipe                    pipedes
#define __NRAN0_times                   buf
#define __NRAN0_brk                     addr
#define __NRAN0_setgid                  gid
#define __NRAN0_signal                  signo
#define __NRAN1_signal                  handler
#define __NRAN0_acct                    filename
#define __NRAN0_umount2                 special_file
#define __NRAN1_umount2                 flags
#define __NRAN0_ioctl                   fd
#define __NRAN1_ioctl                   request
#define __NRAN2_ioctl                   arg
#define __NRAN0_fcntl                   fd
#define __NRAN1_fcntl                   cmd
#define __NRAN2_fcntl                   arg
#define __NRAN0_setpgid                 pid
#define __NRAN1_setpgid                 pgid
#define __NRAN0_oldolduname             name
#define __NRAN0_umask                   mode
#define __NRAN0_chroot                  path
#define __NRAN0_ustat                   dev
#define __NRAN1_ustat                   ubuf
#define __NRAN0_dup2                    oldfd
#define __NRAN1_dup2                    newfd
#define __NRAN0_sigaction               signo
#define __NRAN1_sigaction               act
#define __NRAN2_sigaction               oact
#define __NRAN0_ssetmask                sigmask
#define __NRAN0_setreuid                ruid
#define __NRAN1_setreuid                euid
#define __NRAN0_setregid                rgid
#define __NRAN1_setregid                egid
#define __NRAN0_sigsuspend              set
#define __NRAN0_sigpending              set
#define __NRAN0_sethostname             name
#define __NRAN1_sethostname             len
#define __NRAN0_setrlimit               resource
#define __NRAN1_setrlimit               rlimits
#define __NRAN0_getrlimit               resource
#define __NRAN1_getrlimit               rlimits
#define __NRAN0_getrusage               who
#define __NRAN1_getrusage               tv
#define __NRAN0_gettimeofday            tv
#define __NRAN1_gettimeofday            tz
#define __NRAN0_settimeofday            tv
#define __NRAN1_settimeofday            tz
#define __NRAN0_getgroups               size
#define __NRAN1_getgroups               list
#define __NRAN0_setgroups               count
#define __NRAN1_setgroups               groups
#define __NRAN0_select                  nfds
#define __NRAN1_select                  readfds
#define __NRAN2_select                  writefds
#define __NRAN3_select                  exceptfds
#define __NRAN4_select                  timeout
#define __NRAN0_symlink                 link_text
#define __NRAN1_symlink                 target_path
#define __NRAN0_linux_oldlstat          filename
#define __NRAN1_linux_oldlstat          statbuf
#define __NRAN0_readlink                path
#define __NRAN1_readlink                buf
#define __NRAN2_readlink                buflen
#define __NRAN0_uselib                  library
#define __NRAN0_swapon                  pathname
#define __NRAN1_swapon                  swapflags
#define __NRAN0_reboot                  how
#define __NRAN0_readdir                 fd
#define __NRAN1_readdir                 dirp
#define __NRAN2_readdir                 count
#define __NRAN0_mmap                    addr
#define __NRAN1_mmap                    len
#define __NRAN2_mmap                    prot
#define __NRAN3_mmap                    flags
#define __NRAN4_mmap                    fd
#define __NRAN5_mmap                    offset
#define __NRAN0_munmap                  addr
#define __NRAN1_munmap                  len
#define __NRAN0_truncate                filename
#define __NRAN1_truncate                length
#define __NRAN0_ftruncate               fd
#define __NRAN1_ftruncate               length
#define __NRAN0_fchmod                  fd
#define __NRAN1_fchmod                  mode
#define __NRAN0_fchown                  fd
#define __NRAN1_fchown                  owner
#define __NRAN2_fchown                  group
#define __NRAN0_getpriority             which
#define __NRAN1_getpriority             who
#define __NRAN0_setpriority             which
#define __NRAN1_setpriority             who
#define __NRAN2_setpriority             value
#define __NRAN0_profil                  sample_buffer
#define __NRAN1_profil                  size
#define __NRAN2_profil                  offset
#define __NRAN3_profil                  scale
#define __NRAN0_statfs                  file
#define __NRAN1_statfs                  buf
#define __NRAN0_fstatfs                 file
#define __NRAN1_fstatfs                 buf
#define __NRAN0_ioperm                  from
#define __NRAN1_ioperm                  num
#define __NRAN2_ioperm                  turn_on
#define __NRAN0_socketcall              call
#define __NRAN1_socketcall              args
#define __NRAN0_syslog                  level
#define __NRAN1_syslog                  str
#define __NRAN2_syslog                  len
#define __NRAN0_setitimer               which
#define __NRAN1_setitimer               newval
#define __NRAN2_setitimer               oldval
#define __NRAN0_getitimer               which
#define __NRAN1_getitimer               curr_value
#define __NRAN0_linux_stat              filename
#define __NRAN1_linux_stat              statbuf
#define __NRAN0_linux_lstat             filename
#define __NRAN1_linux_lstat             statbuf
#define __NRAN0_linux_fstat             fd
#define __NRAN1_linux_fstat             statbuf
#define __NRAN0_olduname                name
#define __NRAN0_iopl                    level
#define __NRAN0_vm86old                 TODO_PROTOTYPE
#define __NRAN0_wait4                   pid
#define __NRAN1_wait4                   stat_loc
#define __NRAN2_wait4                   options
#define __NRAN3_wait4                   usage
#define __NRAN0_swapoff                 pathname
#define __NRAN0_sysinfo                 info
#define __NRAN0_ipc                     TODO_PROTOTYPE
#define __NRAN0_fsync                   fd
#define __NRAN0_sigreturn               restore_fpu
#define __NRAN1_sigreturn               unused1
#define __NRAN2_sigreturn               unused2
#define __NRAN3_sigreturn               restore_sigmask
#define __NRAN4_sigreturn               sc_info
#define __NRAN5_sigreturn               restore_cpu
#define __NRAN0_clone                   flags
#define __NRAN1_clone                   child_stack
#define __NRAN2_clone                   ptid
#define __NRAN3_clone                   newtls
#define __NRAN4_clone                   ctid
#define __NRAN0_setdomainname           name
#define __NRAN1_setdomainname           len
#define __NRAN0_uname                   name
#define __NRAN0_modify_ldt              func
#define __NRAN1_modify_ldt              ptr
#define __NRAN2_modify_ldt              bytecount
#define __NRAN0_adjtimex                TODO_PROTOTYPE
#define __NRAN0_mprotect                addr
#define __NRAN1_mprotect                len
#define __NRAN2_mprotect                prot
#define __NRAN0_sigprocmask             how
#define __NRAN1_sigprocmask             set
#define __NRAN2_sigprocmask             oset
#define __NRAN0_create_module           TODO_PROTOTYPE
#define __NRAN0_init_module             TODO_PROTOTYPE
#define __NRAN0_delete_module           TODO_PROTOTYPE
#define __NRAN0_get_kernel_syms         TODO_PROTOTYPE
#define __NRAN0_quotactl                TODO_PROTOTYPE
#define __NRAN0_getpgid                 pid
#define __NRAN0_fchdir                  fd
#define __NRAN0_bdflush                 TODO_PROTOTYPE
#define __NRAN0_sysfs                   TODO_PROTOTYPE
#define __NRAN0_personality             TODO_PROTOTYPE
#define __NRAN0_afs_syscall             TODO_PROTOTYPE
#define __NRAN0_setfsuid                uid
#define __NRAN0_setfsgid                gid
#define __NRAN0__llseek                 fd
#define __NRAN1__llseek                 offset
#define __NRAN2__llseek                 result
#define __NRAN3__llseek                 whence
#define __NRAN0_getdents                fd
#define __NRAN1_getdents                dirp
#define __NRAN2_getdents                count
#define __NRAN0__newselect              TODO_PROTOTYPE
#define __NRAN0_flock                   fd
#define __NRAN1_flock                   operation
#define __NRAN0_msync                   addr
#define __NRAN1_msync                   len
#define __NRAN2_msync                   flags
#define __NRAN0_readv                   fd
#define __NRAN1_readv                   iovec
#define __NRAN2_readv                   count
#define __NRAN0_writev                  fd
#define __NRAN1_writev                  iovec
#define __NRAN2_writev                  count
#define __NRAN0_getsid                  pid
#define __NRAN0_fdatasync               fd
#define __NRAN0__sysctl                 TODO_PROTOTYPE
#define __NRAN0_mlock                   addr
#define __NRAN1_mlock                   len
#define __NRAN0_munlock                 addr
#define __NRAN1_munlock                 len
#define __NRAN0_mlockall                flags
#define __NRAN0_sched_setparam          pid
#define __NRAN1_sched_setparam          param
#define __NRAN0_sched_getparam          pid
#define __NRAN1_sched_getparam          param
#define __NRAN0_sched_setscheduler      pid
#define __NRAN1_sched_setscheduler      policy
#define __NRAN2_sched_setscheduler      param
#define __NRAN0_sched_getscheduler      pid
#define __NRAN0_sched_get_priority_max  algorithm
#define __NRAN0_sched_get_priority_min  algorithm
#define __NRAN0_sched_rr_get_interval   pid
#define __NRAN1_sched_rr_get_interval   tms
#define __NRAN0_nanosleep               req
#define __NRAN1_nanosleep               rem
#define __NRAN0_mremap                  addr
#define __NRAN1_mremap                  old_len
#define __NRAN2_mremap                  new_len
#define __NRAN3_mremap                  flags
#define __NRAN4_mremap                  new_address
#define __NRAN0_setresuid               ruid
#define __NRAN1_setresuid               euid
#define __NRAN2_setresuid               suid
#define __NRAN0_getresuid               ruid
#define __NRAN1_getresuid               euid
#define __NRAN2_getresuid               suid
#define __NRAN0_vm86                    TODO_PROTOTYPE
#define __NRAN0_query_module            TODO_PROTOTYPE
#define __NRAN0_poll                    fds
#define __NRAN1_poll                    nfds
#define __NRAN2_poll                    timeout
#define __NRAN0_nfsservctl              TODO_PROTOTYPE
#define __NRAN0_setresgid               rgid
#define __NRAN1_setresgid               egid
#define __NRAN2_setresgid               sgid
#define __NRAN0_getresgid               rgid
#define __NRAN1_getresgid               egid
#define __NRAN2_getresgid               sgid
#define __NRAN0_prctl                   TODO_PROTOTYPE
#define __NRAN0_rt_sigreturn            restore_fpu
#define __NRAN1_rt_sigreturn            restore_sigmask
#define __NRAN2_rt_sigreturn            sc_info
#define __NRAN3_rt_sigreturn            restore_cpu
#define __NRAN0_rt_sigaction            signo
#define __NRAN1_rt_sigaction            act
#define __NRAN2_rt_sigaction            oact
#define __NRAN3_rt_sigaction            sigsetsize
#define __NRAN0_rt_sigprocmask          how
#define __NRAN1_rt_sigprocmask          set
#define __NRAN2_rt_sigprocmask          oset
#define __NRAN3_rt_sigprocmask          sigsetsize
#define __NRAN0_rt_sigpending           set
#define __NRAN1_rt_sigpending           sigsetsize
#define __NRAN0_rt_sigtimedwait         set
#define __NRAN1_rt_sigtimedwait         info
#define __NRAN2_rt_sigtimedwait         timeout
#define __NRAN3_rt_sigtimedwait         sigsetsize
#define __NRAN0_rt_sigqueueinfo         tgid
#define __NRAN1_rt_sigqueueinfo         signo
#define __NRAN2_rt_sigqueueinfo         uinfo
#define __NRAN0_rt_sigsuspend           set
#define __NRAN1_rt_sigsuspend           sigsetsize
#define __NRAN0_pread64                 fd
#define __NRAN1_pread64                 buf
#define __NRAN2_pread64                 bufsize
#define __NRAN3_pread64                 offset
#define __NRAN0_pwrite64                fd
#define __NRAN1_pwrite64                buf
#define __NRAN2_pwrite64                bufsize
#define __NRAN3_pwrite64                offset
#define __NRAN0_chown                   filename
#define __NRAN1_chown                   owner
#define __NRAN2_chown                   group
#define __NRAN0_getcwd                  buf
#define __NRAN1_getcwd                  size
#define __NRAN0_capget                  TODO_PROTOTYPE
#define __NRAN0_capset                  TODO_PROTOTYPE
#define __NRAN0_sigaltstack             ss
#define __NRAN1_sigaltstack             oss
#define __NRAN0_sendfile                out_fd
#define __NRAN1_sendfile                in_fd
#define __NRAN2_sendfile                pin_offset
#define __NRAN3_sendfile                num_bytes
#define __NRAN0_getpmsg                 TODO_PROTOTYPE
#define __NRAN0_putpmsg                 TODO_PROTOTYPE
#define __NRAN0_ugetrlimit              TODO_PROTOTYPE
#define __NRAN0_mmap2                   addr
#define __NRAN1_mmap2                   len
#define __NRAN2_mmap2                   prot
#define __NRAN3_mmap2                   flags
#define __NRAN4_mmap2                   fd
#define __NRAN5_mmap2                   pgoffset
#define __NRAN0_truncate64              filename
#define __NRAN1_truncate64              length
#define __NRAN0_ftruncate64             fd
#define __NRAN1_ftruncate64             length
#define __NRAN0_linux_stat64            filename
#define __NRAN1_linux_stat64            statbuf
#define __NRAN0_linux_lstat64           filename
#define __NRAN1_linux_lstat64           statbuf
#define __NRAN0_linux_fstat64           fd
#define __NRAN1_linux_fstat64           statbuf
#define __NRAN0_lchown32                filename
#define __NRAN1_lchown32                owner
#define __NRAN2_lchown32                group
#define __NRAN0_setreuid32              ruid
#define __NRAN1_setreuid32              euid
#define __NRAN0_setregid32              rgid
#define __NRAN1_setregid32              egid
#define __NRAN0_getgroups32             size
#define __NRAN1_getgroups32             list
#define __NRAN0_setgroups32             count
#define __NRAN1_setgroups32             groups
#define __NRAN0_fchown32                fd
#define __NRAN1_fchown32                owner
#define __NRAN2_fchown32                group
#define __NRAN0_setresuid32             ruid
#define __NRAN1_setresuid32             euid
#define __NRAN2_setresuid32             suid
#define __NRAN0_getresuid32             ruid
#define __NRAN1_getresuid32             euid
#define __NRAN2_getresuid32             suid
#define __NRAN0_setresgid32             rgid
#define __NRAN1_setresgid32             egid
#define __NRAN2_setresgid32             sgid
#define __NRAN0_getresgid32             rgid
#define __NRAN1_getresgid32             egid
#define __NRAN2_getresgid32             sgid
#define __NRAN0_chown32                 filename
#define __NRAN1_chown32                 owner
#define __NRAN2_chown32                 group
#define __NRAN0_setuid32                uid
#define __NRAN0_setgid32                gid
#define __NRAN0_setfsuid32              uid
#define __NRAN0_setfsgid32              gid
#define __NRAN0_pivot_root              TODO_PROTOTYPE
#define __NRAN0_mincore                 start
#define __NRAN1_mincore                 len
#define __NRAN2_mincore                 vec
#define __NRAN0_madvise                 addr
#define __NRAN1_madvise                 len
#define __NRAN2_madvise                 advice
#define __NRAN0_getdents64              fd
#define __NRAN1_getdents64              dirp
#define __NRAN2_getdents64              count
#define __NRAN0_fcntl64                 fd
#define __NRAN1_fcntl64                 command
#define __NRAN2_fcntl64                 arg
#define __NRAN0_readahead               fd
#define __NRAN1_readahead               offset
#define __NRAN2_readahead               count
#define __NRAN0_setxattr                path
#define __NRAN1_setxattr                name
#define __NRAN2_setxattr                buf
#define __NRAN3_setxattr                bufsize
#define __NRAN4_setxattr                flags
#define __NRAN0_lsetxattr               path
#define __NRAN1_lsetxattr               name
#define __NRAN2_lsetxattr               buf
#define __NRAN3_lsetxattr               bufsize
#define __NRAN4_lsetxattr               flags
#define __NRAN0_fsetxattr               fd
#define __NRAN1_fsetxattr               name
#define __NRAN2_fsetxattr               buf
#define __NRAN3_fsetxattr               bufsize
#define __NRAN4_fsetxattr               flags
#define __NRAN0_getxattr                path
#define __NRAN1_getxattr                name
#define __NRAN2_getxattr                buf
#define __NRAN3_getxattr                bufsize
#define __NRAN0_lgetxattr               path
#define __NRAN1_lgetxattr               name
#define __NRAN2_lgetxattr               buf
#define __NRAN3_lgetxattr               bufsize
#define __NRAN0_fgetxattr               fd
#define __NRAN1_fgetxattr               name
#define __NRAN2_fgetxattr               buf
#define __NRAN3_fgetxattr               bufsize
#define __NRAN0_listxattr               path
#define __NRAN1_listxattr               listbuf
#define __NRAN2_listxattr               listbufsize
#define __NRAN0_llistxattr              path
#define __NRAN1_llistxattr              listbuf
#define __NRAN2_llistxattr              listbufsize
#define __NRAN0_flistxattr              fd
#define __NRAN1_flistxattr              listbuf
#define __NRAN2_flistxattr              listbufsize
#define __NRAN0_removexattr             path
#define __NRAN1_removexattr             name
#define __NRAN0_lremovexattr            path
#define __NRAN1_lremovexattr            name
#define __NRAN0_fremovexattr            fd
#define __NRAN1_fremovexattr            name
#define __NRAN0_tkill                   tid
#define __NRAN1_tkill                   signo
#define __NRAN0_sendfile64              out_fd
#define __NRAN1_sendfile64              in_fd
#define __NRAN2_sendfile64              pin_offset
#define __NRAN3_sendfile64              num_bytes
#define __NRAN0_futex                   uaddr
#define __NRAN1_futex                   futex_op
#define __NRAN2_futex                   val
#define __NRAN3_futex                   timeout_or_val2
#define __NRAN4_futex                   uaddr2
#define __NRAN5_futex                   val3
#define __NRAN0_sched_setaffinity       pid
#define __NRAN1_sched_setaffinity       cpusetsize
#define __NRAN2_sched_setaffinity       cpuset
#define __NRAN0_sched_getaffinity       pid
#define __NRAN1_sched_getaffinity       cpusetsize
#define __NRAN2_sched_getaffinity       cpuset
#define __NRAN0_set_thread_area         TODO_PROTOTYPE
#define __NRAN0_get_thread_area         TODO_PROTOTYPE
#define __NRAN0_io_setup                TODO_PROTOTYPE
#define __NRAN0_io_destroy              TODO_PROTOTYPE
#define __NRAN0_io_getevents            TODO_PROTOTYPE
#define __NRAN0_io_submit               TODO_PROTOTYPE
#define __NRAN0_io_cancel               TODO_PROTOTYPE
#define __NRAN0_fadvise64               TODO_PROTOTYPE
#define __NRAN0_exit_group              exit_code
#define __NRAN0_lookup_dcookie          TODO_PROTOTYPE
#define __NRAN0_epoll_create            size
#define __NRAN0_epoll_ctl               epfd
#define __NRAN1_epoll_ctl               op
#define __NRAN2_epoll_ctl               fd
#define __NRAN3_epoll_ctl               event
#define __NRAN0_epoll_wait              epfd
#define __NRAN1_epoll_wait              events
#define __NRAN2_epoll_wait              maxevents
#define __NRAN3_epoll_wait              timeout
#define __NRAN0_remap_file_pages        start
#define __NRAN1_remap_file_pages        size
#define __NRAN2_remap_file_pages        prot
#define __NRAN3_remap_file_pages        pgoff
#define __NRAN4_remap_file_pages        flags
#define __NRAN0_set_tid_address         tidptr
#define __NRAN0_timer_create            clock_id
#define __NRAN1_timer_create            evp
#define __NRAN2_timer_create            timerid
#define __NRAN0_timer_settime           timerid
#define __NRAN1_timer_settime           flags
#define __NRAN2_timer_settime           value
#define __NRAN3_timer_settime           ovalue
#define __NRAN0_timer_gettime           timerid
#define __NRAN1_timer_gettime           value
#define __NRAN0_timer_getoverrun        timerid
#define __NRAN0_timer_delete            timerid
#define __NRAN0_clock_settime           clock_id
#define __NRAN1_clock_settime           tp
#define __NRAN0_clock_gettime           clock_id
#define __NRAN1_clock_gettime           tp
#define __NRAN0_clock_getres            clock_id
#define __NRAN1_clock_getres            res
#define __NRAN0_clock_nanosleep         clock_id
#define __NRAN1_clock_nanosleep         flags
#define __NRAN2_clock_nanosleep         requested_time
#define __NRAN3_clock_nanosleep         remaining
#define __NRAN0_statfs64                file
#define __NRAN1_statfs64                buf
#define __NRAN0_fstatfs64               file
#define __NRAN1_fstatfs64               buf
#define __NRAN0_tgkill                  tgid
#define __NRAN1_tgkill                  tid
#define __NRAN2_tgkill                  signo
#define __NRAN0_utimes                  filename
#define __NRAN1_utimes                  times
#define __NRAN0_fadvise64_64            TODO_PROTOTYPE
#define __NRAN0_vserver                 TODO_PROTOTYPE
#define __NRAN0_mbind                   TODO_PROTOTYPE
#define __NRAN0_get_mempolicy           TODO_PROTOTYPE
#define __NRAN0_set_mempolicy           TODO_PROTOTYPE
#define __NRAN0_mq_open                 name
#define __NRAN1_mq_open                 oflags
#define __NRAN2_mq_open                 mode
#define __NRAN0_mq_unlink               name
#define __NRAN0_mq_timedsend            mqdes
#define __NRAN1_mq_timedsend            msg_ptr
#define __NRAN2_mq_timedsend            msg_len
#define __NRAN3_mq_timedsend            msg_prio
#define __NRAN4_mq_timedsend            abs_timeout
#define __NRAN0_mq_timedreceive         mqdes
#define __NRAN1_mq_timedreceive         msg_ptr
#define __NRAN2_mq_timedreceive         msg_len
#define __NRAN3_mq_timedreceive         pmsg_prio
#define __NRAN4_mq_timedreceive         abs_timeout
#define __NRAN0_mq_notify               mqdes
#define __NRAN1_mq_notify               notification
#define __NRAN0_mq_getsetattr           mqdes
#define __NRAN1_mq_getsetattr           newattr
#define __NRAN2_mq_getsetattr           oldattr
#define __NRAN0_kexec_load              TODO_PROTOTYPE
#define __NRAN0_waitid                  idtype
#define __NRAN1_waitid                  id
#define __NRAN2_waitid                  infop
#define __NRAN3_waitid                  options
#define __NRAN4_waitid                  ru
#define __NRAN0_add_key                 TODO_PROTOTYPE
#define __NRAN0_request_key             TODO_PROTOTYPE
#define __NRAN0_keyctl                  TODO_PROTOTYPE
#define __NRAN0_ioprio_set              which
#define __NRAN1_ioprio_set              who
#define __NRAN2_ioprio_set              ioprio
#define __NRAN0_ioprio_get              which
#define __NRAN1_ioprio_get              who
#define __NRAN0_inotify_init            TODO_PROTOTYPE
#define __NRAN0_inotify_add_watch       TODO_PROTOTYPE
#define __NRAN0_inotify_rm_watch        TODO_PROTOTYPE
#define __NRAN0_migrate_pages           TODO_PROTOTYPE
#define __NRAN0_openat                  dirfd
#define __NRAN1_openat                  filename
#define __NRAN2_openat                  oflags
#define __NRAN3_openat                  mode
#define __NRAN0_mkdirat                 dirfd
#define __NRAN1_mkdirat                 pathname
#define __NRAN2_mkdirat                 mode
#define __NRAN0_mknodat                 dirfd
#define __NRAN1_mknodat                 nodename
#define __NRAN2_mknodat                 mode
#define __NRAN3_mknodat                 dev
#define __NRAN0_fchownat                dirfd
#define __NRAN1_fchownat                filename
#define __NRAN2_fchownat                owner
#define __NRAN3_fchownat                group
#define __NRAN4_fchownat                flags
#define __NRAN0_futimesat               dirfd
#define __NRAN1_futimesat               filename
#define __NRAN2_futimesat               times
#define __NRAN0_linux_fstatat64         dirfd
#define __NRAN1_linux_fstatat64         filename
#define __NRAN2_linux_fstatat64         statbuf
#define __NRAN3_linux_fstatat64         flags
#define __NRAN0_unlinkat                dirfd
#define __NRAN1_unlinkat                name
#define __NRAN2_unlinkat                flags
#define __NRAN0_renameat                oldfd
#define __NRAN1_renameat                oldname
#define __NRAN2_renameat                newfd
#define __NRAN3_renameat                newname_or_path
#define __NRAN0_linkat                  fromfd
#define __NRAN1_linkat                  existing_file
#define __NRAN2_linkat                  tofd
#define __NRAN3_linkat                  target_path
#define __NRAN4_linkat                  flags
#define __NRAN0_symlinkat               link_text
#define __NRAN1_symlinkat               tofd
#define __NRAN2_symlinkat               target_path
#define __NRAN0_readlinkat              dirfd
#define __NRAN1_readlinkat              path
#define __NRAN2_readlinkat              buf
#define __NRAN3_readlinkat              buflen
#define __NRAN0_fchmodat                dirfd
#define __NRAN1_fchmodat                filename
#define __NRAN2_fchmodat                mode
#define __NRAN3_fchmodat                flags
#define __NRAN0_faccessat               dirfd
#define __NRAN1_faccessat               filename
#define __NRAN2_faccessat               type
#define __NRAN3_faccessat               flags
#define __NRAN0_pselect6                nfds
#define __NRAN1_pselect6                readfds
#define __NRAN2_pselect6                writefds
#define __NRAN3_pselect6                exceptfds
#define __NRAN4_pselect6                timeout
#define __NRAN5_pselect6                sigmask_sigset_and_len
#define __NRAN0_ppoll                   fds
#define __NRAN1_ppoll                   nfds
#define __NRAN2_ppoll                   timeout_ts
#define __NRAN3_ppoll                   sigmask
#define __NRAN4_ppoll                   sigsetsize
#define __NRAN0_unshare                 flags
#define __NRAN0_set_robust_list         TODO_PROTOTYPE
#define __NRAN0_get_robust_list         TODO_PROTOTYPE
#define __NRAN0_splice                  fdin
#define __NRAN1_splice                  offin
#define __NRAN2_splice                  fdout
#define __NRAN3_splice                  offout
#define __NRAN4_splice                  length
#define __NRAN5_splice                  flags
#define __NRAN0_sync_file_range         fd
#define __NRAN1_sync_file_range         offset
#define __NRAN2_sync_file_range         count
#define __NRAN3_sync_file_range         flags
#define __NRAN0_tee                     fdin
#define __NRAN1_tee                     fdout
#define __NRAN2_tee                     length
#define __NRAN3_tee                     flags
#define __NRAN0_vmsplice                fdout
#define __NRAN1_vmsplice                iov
#define __NRAN2_vmsplice                count
#define __NRAN3_vmsplice                flags
#define __NRAN0_move_pages              TODO_PROTOTYPE
#define __NRAN0_getcpu                  cpu
#define __NRAN1_getcpu                  node
#define __NRAN2_getcpu                  tcache
#define __NRAN0_epoll_pwait             epfd
#define __NRAN1_epoll_pwait             events
#define __NRAN2_epoll_pwait             maxevents
#define __NRAN3_epoll_pwait             timeout
#define __NRAN4_epoll_pwait             ss
#define __NRAN0_utimensat               dirfd
#define __NRAN1_utimensat               filename
#define __NRAN2_utimensat               times
#define __NRAN3_utimensat               flags
#define __NRAN0_signalfd                fd
#define __NRAN1_signalfd                sigmask
#define __NRAN2_signalfd                sigsetsize
#define __NRAN0_timerfd_create          clock_id
#define __NRAN1_timerfd_create          flags
#define __NRAN0_eventfd                 initval
#define __NRAN0_fallocate               fd
#define __NRAN1_fallocate               mode
#define __NRAN2_fallocate               offset
#define __NRAN3_fallocate               length
#define __NRAN0_timerfd_settime         ufd
#define __NRAN1_timerfd_settime         flags
#define __NRAN2_timerfd_settime         utmr
#define __NRAN3_timerfd_settime         otmr
#define __NRAN0_timerfd_gettime         ufd
#define __NRAN1_timerfd_gettime         otmr
#define __NRAN0_signalfd4               fd
#define __NRAN1_signalfd4               sigmask
#define __NRAN2_signalfd4               sigsetsize
#define __NRAN3_signalfd4               flags
#define __NRAN0_eventfd2                initval
#define __NRAN1_eventfd2                flags
#define __NRAN0_epoll_create1           flags
#define __NRAN0_dup3                    oldfd
#define __NRAN1_dup3                    newfd
#define __NRAN2_dup3                    flags
#define __NRAN0_pipe2                   pipedes
#define __NRAN1_pipe2                   flags
#define __NRAN0_inotify_init1           TODO_PROTOTYPE
#define __NRAN0_preadv                  fd
#define __NRAN1_preadv                  iovec
#define __NRAN2_preadv                  count
#define __NRAN3_preadv                  offset
#define __NRAN0_pwritev                 fd
#define __NRAN1_pwritev                 iovec
#define __NRAN2_pwritev                 count
#define __NRAN3_pwritev                 offset
#define __NRAN0_rt_tgsigqueueinfo       tgid
#define __NRAN1_rt_tgsigqueueinfo       tid
#define __NRAN2_rt_tgsigqueueinfo       signo
#define __NRAN3_rt_tgsigqueueinfo       uinfo
#define __NRAN0_perf_event_open         TODO_PROTOTYPE
#define __NRAN0_recvmmsg                sockfd
#define __NRAN1_recvmmsg                vmessages
#define __NRAN2_recvmmsg                vlen
#define __NRAN3_recvmmsg                flags
#define __NRAN4_recvmmsg                tmo
#define __NRAN0_fanotify_init           TODO_PROTOTYPE
#define __NRAN0_fanotify_mark           TODO_PROTOTYPE
#define __NRAN0_prlimit64               pid
#define __NRAN1_prlimit64               resource
#define __NRAN2_prlimit64               new_limit
#define __NRAN3_prlimit64               old_limit
#define __NRAN0_name_to_handle_at       dirfd
#define __NRAN1_name_to_handle_at       name
#define __NRAN2_name_to_handle_at       handle
#define __NRAN3_name_to_handle_at       mnt_id
#define __NRAN4_name_to_handle_at       flags
#define __NRAN0_open_by_handle_at       mountdirfd
#define __NRAN1_open_by_handle_at       handle
#define __NRAN2_open_by_handle_at       flags
#define __NRAN0_clock_adjtime           TODO_PROTOTYPE
#define __NRAN0_syncfs                  fd
#define __NRAN0_sendmmsg                sockfd
#define __NRAN1_sendmmsg                vmessages
#define __NRAN2_sendmmsg                vlen
#define __NRAN3_sendmmsg                flags
#define __NRAN0_setns                   fd
#define __NRAN1_setns                   nstype
#define __NRAN0_process_vm_readv        pid
#define __NRAN1_process_vm_readv        local_iov
#define __NRAN2_process_vm_readv        liovcnt
#define __NRAN3_process_vm_readv        remote_iov
#define __NRAN4_process_vm_readv        riovcnt
#define __NRAN5_process_vm_readv        flags
#define __NRAN0_process_vm_writev       pid
#define __NRAN1_process_vm_writev       local_iov
#define __NRAN2_process_vm_writev       liovcnt
#define __NRAN3_process_vm_writev       remote_iov
#define __NRAN4_process_vm_writev       riovcnt
#define __NRAN5_process_vm_writev       flags
#define __NRAN0_kcmp                    pid1
#define __NRAN1_kcmp                    pid2
#define __NRAN2_kcmp                    type
#define __NRAN3_kcmp                    idx1
#define __NRAN4_kcmp                    idx2
#define __NRAN0_finit_module            TODO_PROTOTYPE
#define __NRAN0_sched_setattr           TODO_PROTOTYPE
#define __NRAN0_sched_getattr           TODO_PROTOTYPE
#define __NRAN0_renameat2               olddirfd
#define __NRAN1_renameat2               oldpath
#define __NRAN2_renameat2               newdirfd
#define __NRAN3_renameat2               newpath
#define __NRAN4_renameat2               flags
#define __NRAN0_seccomp                 TODO_PROTOTYPE
#define __NRAN0_getrandom               buf
#define __NRAN1_getrandom               num_bytes
#define __NRAN2_getrandom               flags
#define __NRAN0_memfd_create            name
#define __NRAN1_memfd_create            flags
#define __NRAN0_bpf                     TODO_PROTOTYPE
#define __NRAN0_execveat                dirfd
#define __NRAN1_execveat                pathname
#define __NRAN2_execveat                argv
#define __NRAN3_execveat                envp
#define __NRAN4_execveat                flags
#define __NRAN0_socket                  domain
#define __NRAN1_socket                  type
#define __NRAN2_socket                  protocol
#define __NRAN0_socketpair              domain
#define __NRAN1_socketpair              type
#define __NRAN2_socketpair              protocol
#define __NRAN3_socketpair              fds
#define __NRAN0_bind                    sockfd
#define __NRAN1_bind                    addr
#define __NRAN2_bind                    addr_len
#define __NRAN0_connect                 sockfd
#define __NRAN1_connect                 addr
#define __NRAN2_connect                 addr_len
#define __NRAN0_listen                  sockfd
#define __NRAN1_listen                  max_backlog
#define __NRAN0_accept4                 sockfd
#define __NRAN1_accept4                 addr
#define __NRAN2_accept4                 addr_len
#define __NRAN3_accept4                 sock_flags
#define __NRAN0_getsockopt              sockfd
#define __NRAN1_getsockopt              level
#define __NRAN2_getsockopt              optname
#define __NRAN3_getsockopt              optval
#define __NRAN4_getsockopt              optlen
#define __NRAN0_setsockopt              sockfd
#define __NRAN1_setsockopt              level
#define __NRAN2_setsockopt              optname
#define __NRAN3_setsockopt              optval
#define __NRAN4_setsockopt              optlen
#define __NRAN0_getsockname             sockfd
#define __NRAN1_getsockname             addr
#define __NRAN2_getsockname             addr_len
#define __NRAN0_getpeername             sockfd
#define __NRAN1_getpeername             addr
#define __NRAN2_getpeername             addr_len
#define __NRAN0_sendto                  sockfd
#define __NRAN1_sendto                  buf
#define __NRAN2_sendto                  bufsize
#define __NRAN3_sendto                  msg_flags
#define __NRAN4_sendto                  addr
#define __NRAN5_sendto                  addr_len
#define __NRAN0_sendmsg                 sockfd
#define __NRAN1_sendmsg                 message
#define __NRAN2_sendmsg                 msg_flags
#define __NRAN0_recvfrom                sockfd
#define __NRAN1_recvfrom                buf
#define __NRAN2_recvfrom                bufsize
#define __NRAN3_recvfrom                msg_flags
#define __NRAN4_recvfrom                addr
#define __NRAN5_recvfrom                addr_len
#define __NRAN0_recvmsg                 sockfd
#define __NRAN1_recvmsg                 message
#define __NRAN2_recvmsg                 msg_flags
#define __NRAN0_shutdown                sockfd
#define __NRAN1_shutdown                how
#define __NRAN0_userfaultfd             TODO_PROTOTYPE
#define __NRAN0_membarrier              TODO_PROTOTYPE
#define __NRAN0_mlock2                  TODO_PROTOTYPE
#define __NRAN0_recvmmsg64              sockfd
#define __NRAN1_recvmmsg64              vmessages
#define __NRAN2_recvmmsg64              vlen
#define __NRAN3_recvmmsg64              flags
#define __NRAN4_recvmmsg64              tmo
#define __NRAN0_pwritevf                fd
#define __NRAN1_pwritevf                iovec
#define __NRAN2_pwritevf                count
#define __NRAN3_pwritevf                offset
#define __NRAN4_pwritevf                mode
#define __NRAN0_preadvf                 fd
#define __NRAN1_preadvf                 iovec
#define __NRAN2_preadvf                 count
#define __NRAN3_preadvf                 offset
#define __NRAN4_preadvf                 mode
#define __NRAN0_timerfd_gettime64       ufd
#define __NRAN1_timerfd_gettime64       otmr
#define __NRAN0_timerfd_settime64       ufd
#define __NRAN1_timerfd_settime64       flags
#define __NRAN2_timerfd_settime64       utmr
#define __NRAN3_timerfd_settime64       otmr
#define __NRAN0_fallocate64             fd
#define __NRAN1_fallocate64             mode
#define __NRAN2_fallocate64             offset
#define __NRAN3_fallocate64             length
#define __NRAN0_utimensat64             dirfd
#define __NRAN1_utimensat64             filename
#define __NRAN2_utimensat64             times
#define __NRAN3_utimensat64             flags
#define __NRAN0_ppoll64                 fds
#define __NRAN1_ppoll64                 nfds
#define __NRAN2_ppoll64                 timeout_ts
#define __NRAN3_ppoll64                 sigmask
#define __NRAN4_ppoll64                 sigsetsize
#define __NRAN0_pselect6_64             nfds
#define __NRAN1_pselect6_64             readfds
#define __NRAN2_pselect6_64             writefds
#define __NRAN3_pselect6_64             exceptfds
#define __NRAN4_pselect6_64             timeout
#define __NRAN5_pselect6_64             sigmask_sigset_and_len
#define __NRAN0_freadlinkat             dirfd
#define __NRAN1_freadlinkat             path
#define __NRAN2_freadlinkat             buf
#define __NRAN3_freadlinkat             buflen
#define __NRAN4_freadlinkat             flags
#define __NRAN0_fsymlinkat              link_text
#define __NRAN1_fsymlinkat              tofd
#define __NRAN2_fsymlinkat              target_path
#define __NRAN3_fsymlinkat              flags
#define __NRAN0_frenameat               oldfd
#define __NRAN1_frenameat               oldname
#define __NRAN2_frenameat               newfd
#define __NRAN3_frenameat               newname_or_path
#define __NRAN4_frenameat               flags
#define __NRAN0_kfstatat                dirfd
#define __NRAN1_kfstatat                filename
#define __NRAN2_kfstatat                statbuf
#define __NRAN3_kfstatat                flags
#define __NRAN0_futimesat64             dirfd
#define __NRAN1_futimesat64             filename
#define __NRAN2_futimesat64             times
#define __NRAN0_fmknodat                dirfd
#define __NRAN1_fmknodat                nodename
#define __NRAN2_fmknodat                mode
#define __NRAN3_fmknodat                dev
#define __NRAN4_fmknodat                flags
#define __NRAN0_fmkdirat                dirfd
#define __NRAN1_fmkdirat                pathname
#define __NRAN2_fmkdirat                mode
#define __NRAN3_fmkdirat                flags
#define __NRAN0_waitid64                idtype
#define __NRAN1_waitid64                id
#define __NRAN2_waitid64                infop
#define __NRAN3_waitid64                options
#define __NRAN4_waitid64                ru
#define __NRAN0_mq_timedreceive64       mqdes
#define __NRAN1_mq_timedreceive64       msg_ptr
#define __NRAN2_mq_timedreceive64       msg_len
#define __NRAN3_mq_timedreceive64       pmsg_prio
#define __NRAN4_mq_timedreceive64       abs_timeout
#define __NRAN0_mq_timedsend64          mqdes
#define __NRAN1_mq_timedsend64          msg_ptr
#define __NRAN2_mq_timedsend64          msg_len
#define __NRAN3_mq_timedsend64          msg_prio
#define __NRAN4_mq_timedsend64          abs_timeout
#define __NRAN0_utimes64                filename
#define __NRAN1_utimes64                times
#define __NRAN0_clock_nanosleep64       clock_id
#define __NRAN1_clock_nanosleep64       flags
#define __NRAN2_clock_nanosleep64       requested_time
#define __NRAN3_clock_nanosleep64       remaining
#define __NRAN0_clock_getres64          clock_id
#define __NRAN1_clock_getres64          res
#define __NRAN0_clock_gettime64         clock_id
#define __NRAN1_clock_gettime64         tp
#define __NRAN0_clock_settime64         clock_id
#define __NRAN1_clock_settime64         tp
#define __NRAN0_timer_gettime64         timerid
#define __NRAN1_timer_gettime64         value
#define __NRAN0_timer_settime64         timerid
#define __NRAN1_timer_settime64         flags
#define __NRAN2_timer_settime64         value
#define __NRAN3_timer_settime64         ovalue
#define __NRAN0_kreaddirf               fd
#define __NRAN1_kreaddirf               buf
#define __NRAN2_kreaddirf               bufsize
#define __NRAN3_kreaddirf               mode
#define __NRAN4_kreaddirf               iomode
#define __NRAN0_kfstat                  fd
#define __NRAN1_kfstat                  statbuf
#define __NRAN0_klstat                  filename
#define __NRAN1_klstat                  statbuf
#define __NRAN0_kstat                   filename
#define __NRAN1_kstat                   statbuf
#define __NRAN0_pwrite64f               fd
#define __NRAN1_pwrite64f               buf
#define __NRAN2_pwrite64f               bufsize
#define __NRAN3_pwrite64f               offset
#define __NRAN4_pwrite64f               mode
#define __NRAN0_pread64f                fd
#define __NRAN1_pread64f                buf
#define __NRAN2_pread64f                bufsize
#define __NRAN3_pread64f                offset
#define __NRAN4_pread64f                mode
#define __NRAN0_rt_sigtimedwait64       set
#define __NRAN1_rt_sigtimedwait64       info
#define __NRAN2_rt_sigtimedwait64       timeout
#define __NRAN3_rt_sigtimedwait64       sigsetsize
#define __NRAN0_nanosleep64             req
#define __NRAN1_nanosleep64             rem
#define __NRAN0_sched_rr_get_interval64 pid
#define __NRAN1_sched_rr_get_interval64 tms
#define __NRAN0_ksysctl                 command
#define __NRAN1_ksysctl                 arg
#define __NRAN0_writevf                 fd
#define __NRAN1_writevf                 iovec
#define __NRAN2_writevf                 count
#define __NRAN3_writevf                 mode
#define __NRAN0_readvf                  fd
#define __NRAN1_readvf                  iovec
#define __NRAN2_readvf                  count
#define __NRAN3_readvf                  mode
#define __NRAN0_kreaddir                fd
#define __NRAN1_kreaddir                buf
#define __NRAN2_kreaddir                bufsize
#define __NRAN3_kreaddir                mode
#define __NRAN0_wait4_64                pid
#define __NRAN1_wait4_64                stat_loc
#define __NRAN2_wait4_64                options
#define __NRAN3_wait4_64                usage
#define __NRAN0_getitimer64             which
#define __NRAN1_getitimer64             curr_value
#define __NRAN0_setitimer64             which
#define __NRAN1_setitimer64             newval
#define __NRAN2_setitimer64             oldval
#define __NRAN0_maplibrary              addr
#define __NRAN1_maplibrary              flags
#define __NRAN2_maplibrary              fd
#define __NRAN3_maplibrary              hdrv
#define __NRAN4_maplibrary              hdrc
#define __NRAN0_select64                nfds
#define __NRAN1_select64                readfds
#define __NRAN2_select64                writefds
#define __NRAN3_select64                exceptfds
#define __NRAN4_select64                timeout
#define __NRAN0_settimeofday64          tv
#define __NRAN1_settimeofday64          tz
#define __NRAN0_gettimeofday64          tv
#define __NRAN1_gettimeofday64          tz
#define __NRAN0_getrusage64             who
#define __NRAN1_getrusage64             tv
#define __NRAN0_fsmode                  mode
#define __NRAN0_ioctlf                  fd
#define __NRAN1_ioctlf                  command
#define __NRAN2_ioctlf                  mode
#define __NRAN3_ioctlf                  arg
#define __NRAN0_ftime64                 tp
#define __NRAN0_utime64                 filename
#define __NRAN1_utime64                 times
#define __NRAN0_userviofd               initial_size
#define __NRAN1_userviofd               flags
#define __NRAN0_process_spawnveat       dirfd
#define __NRAN1_process_spawnveat       pathname
#define __NRAN2_process_spawnveat       argv
#define __NRAN3_process_spawnveat       envp
#define __NRAN4_process_spawnveat       flags
#define __NRAN5_process_spawnveat       actions
#define __NRAN0_stime64                 t
#define __NRAN0_coredump                curr_state
#define __NRAN1_coredump                orig_state
#define __NRAN2_coredump                traceback_vector
#define __NRAN3_coredump                traceback_length
#define __NRAN4_coredump                exception
#define __NRAN5_coredump                unwind_error
#define __NRAN0_raiseat                 state
#define __NRAN1_raiseat                 si
#define __NRAN0_mktty                   keyboard
#define __NRAN1_mktty                   display
#define __NRAN2_mktty                   name
#define __NRAN3_mktty                   rsvd
#define __NRAN0_lfutexlockexpr          ulockaddr
#define __NRAN1_lfutexlockexpr          base
#define __NRAN2_lfutexlockexpr          exprc
#define __NRAN3_lfutexlockexpr          exprv
#define __NRAN4_lfutexlockexpr          timeout
#define __NRAN5_lfutexlockexpr          timeout_flags
#define __NRAN0_lfutexexpr              base
#define __NRAN1_lfutexexpr              exprc
#define __NRAN2_lfutexexpr              exprv
#define __NRAN3_lfutexexpr              timeout
#define __NRAN4_lfutexexpr              timeout_flags
#define __NRAN0_lseek64                 fd
#define __NRAN1_lseek64                 offset
#define __NRAN2_lseek64                 whence
#define __NRAN0_lfutex                  uaddr
#define __NRAN1_lfutex                  futex_op
#define __NRAN2_lfutex                  val
#define __NRAN3_lfutex                  timeout
#define __NRAN4_lfutex                  val2
#define __NRAN0_debugtrap               state
#define __NRAN1_debugtrap               reason
#define __NRAN0_set_library_listdef     listdef
#define __NRAN0_get_exception_handler   pmode
#define __NRAN1_get_exception_handler   phandler
#define __NRAN2_get_exception_handler   phandler_sp
#define __NRAN0_set_exception_handler   mode
#define __NRAN1_set_exception_handler   handler
#define __NRAN2_set_exception_handler   handler_sp
#define __NRAN0_time64                  timer
#define __NRAN0_fchdirat                dirfd
#define __NRAN1_fchdirat                path
#define __NRAN2_fchdirat                flags
#define __NRAN0_openpty                 amaster
#define __NRAN1_openpty                 aslave
#define __NRAN2_openpty                 name
#define __NRAN3_openpty                 termp
#define __NRAN4_openpty                 winp
#define __NRAN0_rpc_schedule            target
#define __NRAN1_rpc_schedule            flags
#define __NRAN2_rpc_schedule            program
#define __NRAN3_rpc_schedule            arguments
#define __NRAN0_frealpathat             dirfd
#define __NRAN1_frealpathat             filename
#define __NRAN2_frealpathat             buf
#define __NRAN3_frealpathat             buflen
#define __NRAN4_frealpathat             flags
#define __NRAN0_frealpath4              fd
#define __NRAN1_frealpath4              resolved
#define __NRAN2_frealpath4              buflen
#define __NRAN3_frealpath4              flags
#define __NRAN0_detach                  pid
#define __NRAN0_writef                  fd
#define __NRAN1_writef                  buf
#define __NRAN2_writef                  bufsize
#define __NRAN3_writef                  mode
#define __NRAN0_readf                   fd
#define __NRAN1_readf                   buf
#define __NRAN2_readf                   bufsize
#define __NRAN3_readf                   mode
#define __NRAN0_hopf                    fd
#define __NRAN1_hopf                    command
#define __NRAN2_hopf                    mode
#define __NRAN3_hopf                    arg
#define __NRAN0_hop                     fd
#define __NRAN1_hop                     command
#define __NRAN2_hop                     arg
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_NAMES */
#endif /* __WANT_SYSCALL_ARGUMENT_NAMES */


/************************************************************************/
/* SYSCALL ARGUMENT FORMAT                                              */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_FORMAT
#ifndef __NRFEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#define __NRFEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT 1
#define __NRATRF0_exit                    "%" PRIuSIZ
#define __NRATRA0_exit(status)            , (uintptr_t)(status)
#define __NRATRF0_read                    "%d"
#define __NRATRA0_read(fd, buf, bufsize)  , (int)(fd)
#define __NRATRF1_read                    "%p"
#define __NRATRA1_read(fd, buf, bufsize)  , buf
#define __NRATRF2_read                    "%" PRIuSIZ
#define __NRATRA2_read(fd, buf, bufsize)  , bufsize
#define __NRATRF0_write                   "%d"
#define __NRATRA0_write(fd, buf, bufsize) , (int)(fd)
#define __NRATRF1_write                   "%p"
#define __NRATRA1_write(fd, buf, bufsize) , buf
#define __NRATRF2_write                   "%" PRIuSIZ
#define __NRATRA2_write(fd, buf, bufsize) , bufsize
#define __NRATRF0_open                    "%q"
#define __NRATRA0_open(filename, oflags, mode) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_open                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA1_open(filename, oflags, mode) , (uintptr_t)(oflags), (oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
                                               , ((oflags) & O_RDWR) && ((oflags) & (O_WRONLY)) ? "|" : "", (oflags) & O_RDWR ? "O_RDWR" : "" \
                                               , ((oflags) & O_CREAT) && ((oflags) & (O_WRONLY | O_RDWR)) ? "|" : "", (oflags) & O_CREAT ? "O_CREAT" : "" \
                                               , ((oflags) & O_EXCL) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT)) ? "|" : "", (oflags) & O_EXCL ? "O_EXCL" : "" \
                                               , ((oflags) & O_NOCTTY) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL)) ? "|" : "", (oflags) & O_NOCTTY ? "O_NOCTTY" : "" \
                                               , ((oflags) & O_TRUNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY)) ? "|" : "", (oflags) & O_TRUNC ? "O_TRUNC" : "" \
                                               , ((oflags) & O_APPEND) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC)) ? "|" : "", (oflags) & O_APPEND ? "O_APPEND" : "" \
                                               , ((oflags) & O_NONBLOCK) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND)) ? "|" : "", (oflags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                               , ((oflags) & O_SYNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK)) ? "|" : "", (oflags) & O_SYNC ? "O_SYNC" : "" \
                                               , ((oflags) & O_DSYNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC)) ? "|" : "", (oflags) & O_DSYNC ? "O_DSYNC" : "" \
                                               , ((oflags) & O_ASYNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC)) ? "|" : "", (oflags) & O_ASYNC ? "O_ASYNC" : "" \
                                               , ((oflags) & O_DIRECT) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC)) ? "|" : "", (oflags) & O_DIRECT ? "O_DIRECT" : "" \
                                               , ((oflags) & O_LARGEFILE) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT)) ? "|" : "", (oflags) & O_LARGEFILE ? "O_LARGEFILE" : "" \
                                               , ((oflags) & O_DIRECTORY) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE)) ? "|" : "", (oflags) & O_DIRECTORY ? "O_DIRECTORY" : "" \
                                               , ((oflags) & O_NOFOLLOW) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY)) ? "|" : "", (oflags) & O_NOFOLLOW ? "O_NOFOLLOW" : "" \
                                               , ((oflags) & O_NOATIME) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW)) ? "|" : "", (oflags) & O_NOATIME ? "O_NOATIME" : "" \
                                               , ((oflags) & O_CLOEXEC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME)) ? "|" : "", (oflags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                               , ((oflags) & O_CLOFORK) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC)) ? "|" : "", (oflags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                               , ((oflags) & O_PATH) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK)) ? "|" : "", (oflags) & O_PATH ? "O_PATH" : "" \
                                               , ((oflags) & 0x0400000) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH)) ? "|" : "", (oflags) & 0x0400000 ? "O_TMPFILE" : "" \
                                               , ((oflags) & O_SYMLINK) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | 0x0400000)) ? "|" : "", (oflags) & O_SYMLINK ? "O_SYMLINK" : "" \
                                               , ((oflags) & O_DOSPATH) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | 0x0400000 | O_SYMLINK)) ? "|" : "", (oflags) & O_DOSPATH ? "O_DOSPATH" : ""
#define __NRATRF2_open                    "%#" PRIoSIZ
#define __NRATRA2_open(filename, oflags, mode) , (uintptr_t)(mode)
#define __NRATRF0_close                   "%d"
#define __NRATRA0_close(fd)               , (int)(fd)
#define __NRATRF0_waitpid                 "%" PRIdSIZ
#define __NRATRA0_waitpid(pid, stat_loc, options) , (intptr_t)(pid)
#define __NRATRF1_waitpid                 "%p"
#define __NRATRA1_waitpid(pid, stat_loc, options) , stat_loc
#define __NRATRF2_waitpid                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NRATRA2_waitpid(pid, stat_loc, options) , (uintptr_t)(options), (options) & WNOHANG ? "WNOHANG" : "" \
                                                  , ((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "", (options) & WUNTRACED ? "WUNTRACED" : "" \
                                                  , ((options) & WCONTINUED) && ((options) & (WNOHANG | WUNTRACED)) ? "|" : "", (options) & WCONTINUED ? "WCONTINUED" : "" \
                                                  , ((options) & WNOWAIT) && ((options) & (WNOHANG | WUNTRACED | WCONTINUED)) ? "|" : "", (options) & WNOWAIT ? "WNOWAIT" : ""
#define __NRATRF0_creat                   "%q"
#define __NRATRA0_creat(filename, mode)   , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_creat                   "%#" PRIoSIZ
#define __NRATRA1_creat(filename, mode)   , (uintptr_t)(mode)
#define __NRATRF0_link                    "%q"
#define __NRATRA0_link(existing_file, link_file) , (validate_readable_opt(existing_file,1),existing_file)
#define __NRATRF1_link                    "%q"
#define __NRATRA1_link(existing_file, link_file) , (validate_readable_opt(link_file,1),link_file)
#define __NRATRF0_unlink                  "%q"
#define __NRATRA0_unlink(filename)        , (validate_readable_opt(filename,1),filename)
#define __NRATRF0_execve                  "%q"
#define __NRATRA0_execve(path, argv, envp) , (validate_readable_opt(path,1),path)
#define __NRATRF1_execve                  "%p"
#define __NRATRA1_execve(path, argv, envp) , argv
#define __NRATRF2_execve                  "%p"
#define __NRATRA2_execve(path, argv, envp) , envp
#define __NRATRF0_chdir                   "%q"
#define __NRATRA0_chdir(path)             , (validate_readable_opt(path,1),path)
#define __NRATRF0_time                    "%p"
#define __NRATRA0_time(timer)             , timer
#define __NRATRF0_mknod                   "%q"
#define __NRATRA0_mknod(nodename, mode, dev) , (validate_readable_opt(nodename,1),nodename)
#define __NRATRF1_mknod                   "%#" PRIoSIZ
#define __NRATRA1_mknod(nodename, mode, dev) , (uintptr_t)(mode)
#define __NRATRF2_mknod                   "%.2x:%.2x"
#define __NRATRA2_mknod(nodename, mode, dev) , (unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NRATRF0_chmod                   "%q"
#define __NRATRA0_chmod(filename, mode)   , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_chmod                   "%#" PRIoSIZ
#define __NRATRA1_chmod(filename, mode)   , (uintptr_t)(mode)
#define __NRATRF0_lchown                  "%q"
#define __NRATRA0_lchown(filename, owner, group) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_lchown                  "%" PRIu16
#define __NRATRA1_lchown(filename, owner, group) , owner
#define __NRATRF2_lchown                  "%" PRIu16
#define __NRATRA2_lchown(filename, owner, group) , group
#define __NRATRF0_linux_oldstat           "%q"
#define __NRATRA0_linux_oldstat(filename, statbuf) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_oldstat           "%p"
#define __NRATRA1_linux_oldstat(filename, statbuf) , statbuf
#define __NRATRF0_lseek                   "%d"
#define __NRATRA0_lseek(fd, offset, whence) , (int)(fd)
#define __NRATRF1_lseek                   "%" PRIdSIZ
#define __NRATRA1_lseek(fd, offset, whence) , (intptr_t)(offset)
#define __NRATRF2_lseek                   "%#Ix=%s"
#define __NRATRA2_lseek(fd, offset, whence) , (whence), (whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NRATRF0_mount                   "%q"
#define __NRATRA0_mount(special_file, dir, fstype, rwflag, data) , (validate_readable_opt(special_file,1),special_file)
#define __NRATRF1_mount                   "%q"
#define __NRATRA1_mount(special_file, dir, fstype, rwflag, data) , (validate_readable_opt(dir,1),dir)
#define __NRATRF2_mount                   "%q"
#define __NRATRA2_mount(special_file, dir, fstype, rwflag, data) , (validate_readable_opt(fstype,1),fstype)
#define __NRATRF3_mount                   "%#" PRIxSIZ
#define __NRATRA3_mount(special_file, dir, fstype, rwflag, data) , (uintptr_t)(rwflag)
#define __NRATRF4_mount                   "%p"
#define __NRATRA4_mount(special_file, dir, fstype, rwflag, data) , data
#define __NRATRF0_umount                  "%q"
#define __NRATRA0_umount(special_file)    , (validate_readable_opt(special_file,1),special_file)
#define __NRATRF0_setuid                  "%" PRIu16
#define __NRATRA0_setuid(uid)             , uid
#define __NRATRF0_stime                   "%p"
#define __NRATRA0_stime(t)                , t
#define __NRATRF0_ptrace                  "%#" PRIxSIZ
#define __NRATRA0_ptrace(request, pid, addr, data) , (uintptr_t)(request)
#define __NRATRF1_ptrace                  "%" PRIdSIZ
#define __NRATRA1_ptrace(request, pid, addr, data) , (intptr_t)(pid)
#define __NRATRF2_ptrace                  "%p"
#define __NRATRA2_ptrace(request, pid, addr, data) , addr
#define __NRATRF3_ptrace                  "%p"
#define __NRATRA3_ptrace(request, pid, addr, data) , data
#define __NRATRF0_alarm                   "%#" PRIxSIZ
#define __NRATRA0_alarm(seconds)          , (uintptr_t)(seconds)
#define __NRATRF0_linux_oldfstat          "%d"
#define __NRATRA0_linux_oldfstat(fd, statbuf) , (int)(fd)
#define __NRATRF1_linux_oldfstat          "%p"
#define __NRATRA1_linux_oldfstat(fd, statbuf) , statbuf
#define __NRATRF0_utime                   "%q"
#define __NRATRA0_utime(filename, times)  , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_utime                   "%p"
#define __NRATRA1_utime(filename, times)  , times
#define __NRATRF0_access                  "%q"
#define __NRATRA0_access(filename, type)  , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_access                  "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA1_access(filename, type)  , (uintptr_t)(type), (type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                          , ((type) & W_OK) && ((type) & (R_OK)) ? "|" : "", (type) & W_OK ? "W_OK" : "" \
                                          , ((type) & X_OK) && ((type) & (R_OK | W_OK)) ? "|" : "", (type) & X_OK ? "X_OK" : ""
#define __NRATRF0_nice                    "%" PRIdSIZ
#define __NRATRA0_nice(inc)               , (intptr_t)(inc)
#define __NRATRF0_ftime                   "%p"
#define __NRATRA0_ftime(tp)               , tp
#define __NRATRF0_kill                    "%" PRIdSIZ
#define __NRATRA0_kill(pid, signo)        , (intptr_t)(pid)
#define __NRATRF1_kill                    "%#" PRIxSIZ
#define __NRATRA1_kill(pid, signo)        , (uintptr_t)(signo)
#define __NRATRF0_rename                  "%q"
#define __NRATRA0_rename(oldname, newname_or_path) , (validate_readable_opt(oldname,1),oldname)
#define __NRATRF1_rename                  "%q"
#define __NRATRA1_rename(oldname, newname_or_path) , (validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NRATRF0_mkdir                   "%q"
#define __NRATRA0_mkdir(pathname, mode)   , (validate_readable_opt(pathname,1),pathname)
#define __NRATRF1_mkdir                   "%#" PRIoSIZ
#define __NRATRA1_mkdir(pathname, mode)   , (uintptr_t)(mode)
#define __NRATRF0_rmdir                   "%q"
#define __NRATRA0_rmdir(path)             , (validate_readable_opt(path,1),path)
#define __NRATRF0_dup                     "%d"
#define __NRATRA0_dup(fd)                 , (int)(fd)
#define __NRATRF0_pipe                    "%p"
#define __NRATRA0_pipe(pipedes)           , pipedes
#define __NRATRF0_times                   "%p"
#define __NRATRA0_times(buf)              , buf
#define __NRATRF0_brk                     "%p"
#define __NRATRA0_brk(addr)               , addr
#define __NRATRF0_setgid                  "%" PRIu16
#define __NRATRA0_setgid(gid)             , gid
#define __NRATRF0_signal                  "%#" PRIxSIZ
#define __NRATRA0_signal(signo, handler)  , (uintptr_t)(signo)
#define __NRATRF1_signal                  "%p"
#define __NRATRA1_signal(signo, handler)  , handler
#define __NRATRF0_acct                    "%q"
#define __NRATRA0_acct(filename)          , (validate_readable_opt(filename,1),filename)
#define __NRATRF0_umount2                 "%q"
#define __NRATRA0_umount2(special_file, flags) , (validate_readable_opt(special_file,1),special_file)
#define __NRATRF1_umount2                 "%#" PRIxSIZ
#define __NRATRA1_umount2(special_file, flags) , (uintptr_t)(flags)
#define __NRATRF0_ioctl                   "%d"
#define __NRATRA0_ioctl(fd, request, arg) , (int)(fd)
#define __NRATRF1_ioctl                   "%#" PRIxSIZ
#define __NRATRA1_ioctl(fd, request, arg) , (uintptr_t)(request)
#define __NRATRF2_ioctl                   "%p"
#define __NRATRA2_ioctl(fd, request, arg) , arg
#define __NRATRF0_fcntl                   "%d"
#define __NRATRA0_fcntl(fd, cmd, arg)     , (int)(fd)
#define __NRATRF1_fcntl                   "%#" PRIxSIZ
#define __NRATRA1_fcntl(fd, cmd, arg)     , (uintptr_t)(cmd)
#define __NRATRF2_fcntl                   "%p"
#define __NRATRA2_fcntl(fd, cmd, arg)     , arg
#define __NRATRF0_setpgid                 "%" PRIdSIZ
#define __NRATRA0_setpgid(pid, pgid)      , (intptr_t)(pid)
#define __NRATRF1_setpgid                 "%" PRIdSIZ
#define __NRATRA1_setpgid(pid, pgid)      , (intptr_t)(pgid)
#define __NRATRF0_oldolduname             "%p"
#define __NRATRA0_oldolduname(name)       , name
#define __NRATRF0_umask                   "%#" PRIoSIZ
#define __NRATRA0_umask(mode)             , (uintptr_t)(mode)
#define __NRATRF0_chroot                  "%q"
#define __NRATRA0_chroot(path)            , (validate_readable_opt(path,1),path)
#define __NRATRF0_ustat                   "%.2x:%.2x"
#define __NRATRA0_ustat(dev, ubuf)        , (unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NRATRF1_ustat                   "%p"
#define __NRATRA1_ustat(dev, ubuf)        , ubuf
#define __NRATRF0_dup2                    "%d"
#define __NRATRA0_dup2(oldfd, newfd)      , (int)(oldfd)
#define __NRATRF1_dup2                    "%d"
#define __NRATRA1_dup2(oldfd, newfd)      , (int)(newfd)
#define __NRATRF0_sigaction               "%#" PRIxSIZ
#define __NRATRA0_sigaction(signo, act, oact) , (uintptr_t)(signo)
#define __NRATRF1_sigaction               "%p"
#define __NRATRA1_sigaction(signo, act, oact) , act
#define __NRATRF2_sigaction               "%p"
#define __NRATRA2_sigaction(signo, act, oact) , oact
#define __NRATRF0_ssetmask                "%#" PRIxSIZ
#define __NRATRA0_ssetmask(sigmask)       , (uintptr_t)(sigmask)
#define __NRATRF0_setreuid                "%" PRIu16
#define __NRATRA0_setreuid(ruid, euid)    , ruid
#define __NRATRF1_setreuid                "%" PRIu16
#define __NRATRA1_setreuid(ruid, euid)    , euid
#define __NRATRF0_setregid                "%" PRIu16
#define __NRATRA0_setregid(rgid, egid)    , rgid
#define __NRATRF1_setregid                "%" PRIu16
#define __NRATRA1_setregid(rgid, egid)    , egid
#define __NRATRF0_sigsuspend              "%p"
#define __NRATRA0_sigsuspend(set)         , set
#define __NRATRF0_sigpending              "%p"
#define __NRATRA0_sigpending(set)         , set
#define __NRATRF0_sethostname             "%q"
#define __NRATRA0_sethostname(name, len)  , (validate_readable_opt(name,1),name)
#define __NRATRF1_sethostname             "%" PRIuSIZ
#define __NRATRA1_sethostname(name, len)  , len
#define __NRATRF0_setrlimit               "%#" PRIxSIZ
#define __NRATRA0_setrlimit(resource, rlimits) , (uintptr_t)(resource)
#define __NRATRF1_setrlimit               "%p"
#define __NRATRA1_setrlimit(resource, rlimits) , rlimits
#define __NRATRF0_getrlimit               "%#" PRIxSIZ
#define __NRATRA0_getrlimit(resource, rlimits) , (uintptr_t)(resource)
#define __NRATRF1_getrlimit               "%p"
#define __NRATRA1_getrlimit(resource, rlimits) , rlimits
#define __NRATRF0_getrusage               "%" PRIdSIZ
#define __NRATRA0_getrusage(who, tv)      , (intptr_t)(who)
#define __NRATRF1_getrusage               "%p"
#define __NRATRA1_getrusage(who, tv)      , tv
#define __NRATRF0_gettimeofday            "%p"
#define __NRATRA0_gettimeofday(tv, tz)    , tv
#define __NRATRF1_gettimeofday            "%p"
#define __NRATRA1_gettimeofday(tv, tz)    , tz
#define __NRATRF0_settimeofday            "%p"
#define __NRATRA0_settimeofday(tv, tz)    , tv
#define __NRATRF1_settimeofday            "%p"
#define __NRATRA1_settimeofday(tv, tz)    , tz
#define __NRATRF0_getgroups               "%" PRIuSIZ
#define __NRATRA0_getgroups(size, list)   , size
#define __NRATRF1_getgroups               "%p"
#define __NRATRA1_getgroups(size, list)   , list
#define __NRATRF0_setgroups               "%" PRIuSIZ
#define __NRATRA0_setgroups(count, groups) , count
#define __NRATRF1_setgroups               "%p"
#define __NRATRA1_setgroups(count, groups) , groups
#define __NRATRF0_select                  "%" PRIuSIZ
#define __NRATRA0_select(nfds, readfds, writefds, exceptfds, timeout) , nfds
#define __NRATRF1_select                  "%p"
#define __NRATRA1_select(nfds, readfds, writefds, exceptfds, timeout) , readfds
#define __NRATRF2_select                  "%p"
#define __NRATRA2_select(nfds, readfds, writefds, exceptfds, timeout) , writefds
#define __NRATRF3_select                  "%p"
#define __NRATRA3_select(nfds, readfds, writefds, exceptfds, timeout) , exceptfds
#define __NRATRF4_select                  "%p"
#define __NRATRA4_select(nfds, readfds, writefds, exceptfds, timeout) , timeout
#define __NRATRF0_symlink                 "%q"
#define __NRATRA0_symlink(link_text, target_path) , (validate_readable_opt(link_text,1),link_text)
#define __NRATRF1_symlink                 "%q"
#define __NRATRA1_symlink(link_text, target_path) , (validate_readable_opt(target_path,1),target_path)
#define __NRATRF0_linux_oldlstat          "%q"
#define __NRATRA0_linux_oldlstat(filename, statbuf) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_oldlstat          "%p"
#define __NRATRA1_linux_oldlstat(filename, statbuf) , statbuf
#define __NRATRF0_readlink                "%q"
#define __NRATRA0_readlink(path, buf, buflen) , (validate_readable_opt(path,1),path)
#define __NRATRF1_readlink                "%p"
#define __NRATRA1_readlink(path, buf, buflen) , buf
#define __NRATRF2_readlink                "%" PRIuSIZ
#define __NRATRA2_readlink(path, buf, buflen) , buflen
#define __NRATRF0_uselib                  "%q"
#define __NRATRA0_uselib(library)         , (validate_readable_opt(library,1),library)
#define __NRATRF0_swapon                  "%q"
#define __NRATRA0_swapon(pathname, swapflags) , (validate_readable_opt(pathname,1),pathname)
#define __NRATRF1_swapon                  "%#" PRIxSIZ "=%s%s%s"
#define __NRATRA1_swapon(pathname, swapflags) , (uintptr_t)(swapflags), (swapflags) & SWAP_FLAG_PREFER ? "SWAP_FLAG_PREFER" : "" \
                                              , ((swapflags) & SWAP_FLAG_DISCARD) && ((swapflags) & (SWAP_FLAG_PREFER)) ? "|" : "", (swapflags) & SWAP_FLAG_DISCARD ? "SWAP_FLAG_DISCARD" : ""
#define __NRATRF0_reboot                  "%#" PRIxSIZ
#define __NRATRA0_reboot(how)             , (uintptr_t)(how)
#define __NRATRF0_readdir                 "%d"
#define __NRATRA0_readdir(fd, dirp, count) , (int)(fd)
#define __NRATRF1_readdir                 "%p"
#define __NRATRA1_readdir(fd, dirp, count) , dirp
#define __NRATRF2_readdir                 "%" PRIuSIZ
#define __NRATRA2_readdir(fd, dirp, count) , count
#define __NRATRF0_mmap                    "%p"
#define __NRATRA0_mmap(addr, len, prot, flags, fd, offset) , addr
#define __NRATRF1_mmap                    "%" PRIuSIZ
#define __NRATRA1_mmap(addr, len, prot, flags, fd, offset) , len
#define __NRATRF2_mmap                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_mmap(addr, len, prot, flags, fd, offset) , (uintptr_t)(prot), (prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                                           , ((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "", (prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                                           , ((prot) & PROT_READ) && ((prot) & (PROT_EXEC | PROT_WRITE)) ? "|" : "", (prot) & PROT_READ ? "PROT_READ" : "" \
                                                           , ((prot) & PROT_SEM) && ((prot) & (PROT_EXEC | PROT_WRITE | PROT_READ)) ? "|" : "", (prot) & PROT_SEM ? "PROT_SEM" : "" \
                                                           , ((prot) & PROT_LOOSE) && ((prot) & (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM)) ? "|" : "", (prot) & PROT_LOOSE ? "PROT_LOOSE" : "" \
                                                           , ((prot) & PROT_SHARED) && ((prot) & (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE)) ? "|" : "", (prot) & PROT_SHARED ? "PROT_SHARED" : ""
#define __NRATRF3_mmap                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_mmap(addr, len, prot, flags, fd, offset) , (uintptr_t)(flags), (flags) & MAP_SHARED ? "MAP_SHARED" : (flags) ? "" : "MAP_AUTOMATIC" \
                                                           , ((flags) & MAP_PRIVATE) && ((flags) & (MAP_SHARED)) ? "|" : "", (flags) & MAP_PRIVATE ? "MAP_PRIVATE" : "" \
                                                           , ((flags) & MAP_FIXED) && ((flags) & (MAP_SHARED | MAP_PRIVATE)) ? "|" : "", (flags) & MAP_FIXED ? "MAP_FIXED" : "" \
                                                           , ((flags) & MAP_ANON) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED)) ? "|" : "", (flags) & MAP_ANON ? "MAP_ANON" : "" \
                                                           , ((flags) & MAP_32BIT) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON)) ? "|" : "", (flags) & MAP_32BIT ? "MAP_32BIT" : "" \
                                                           , ((flags) & MAP_GROWSDOWN) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT)) ? "|" : "", (flags) & MAP_GROWSDOWN ? "MAP_GROWSDOWN" : "" \
                                                           , ((flags) & MAP_GROWSUP) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN)) ? "|" : "", (flags) & MAP_GROWSUP ? "MAP_GROWSUP" : "" \
                                                           , ((flags) & MAP_LOCKED) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP)) ? "|" : "", (flags) & MAP_LOCKED ? "MAP_LOCKED" : "" \
                                                           , ((flags) & MAP_NORESERVE) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_LOCKED)) ? "|" : "", (flags) & MAP_NORESERVE ? "MAP_NORESERVE" : "" \
                                                           , ((flags) & MAP_POPULATE) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_LOCKED | MAP_NORESERVE)) ? "|" : "", (flags) & MAP_POPULATE ? "MAP_POPULATE" : "" \
                                                           , ((flags) & MAP_NONBLOCK) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_LOCKED | MAP_NORESERVE | MAP_POPULATE)) ? "|" : "", (flags) & MAP_NONBLOCK ? "MAP_NONBLOCK" : "" \
                                                           , ((flags) & MAP_STACK) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_LOCKED | MAP_NORESERVE | MAP_POPULATE | MAP_NONBLOCK)) ? "|" : "", (flags) & MAP_STACK ? "MAP_STACK" : "" \
                                                           , ((flags) & MAP_UNINITIALIZED) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_LOCKED | MAP_NORESERVE | MAP_POPULATE | MAP_NONBLOCK | MAP_STACK)) ? "|" : "", (flags) & MAP_UNINITIALIZED ? "MAP_UNINITIALIZED" : "" \
                                                           , ((flags) & MAP_DONT_MAP) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_LOCKED | MAP_NORESERVE | MAP_POPULATE | MAP_NONBLOCK | MAP_STACK | MAP_UNINITIALIZED)) ? "|" : "", (flags) & MAP_DONT_MAP ? "MAP_DONT_MAP" : "" \
                                                           , ((flags) & MAP_DONT_OVERRIDE) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_LOCKED | MAP_NORESERVE | MAP_POPULATE | MAP_NONBLOCK | MAP_STACK | MAP_UNINITIALIZED | MAP_DONT_MAP)) ? "|" : "", (flags) & MAP_DONT_OVERRIDE ? "MAP_DONT_OVERRIDE" : "" \
                                                           , ((flags) & MAP_OFFSET64_POINTER) && ((flags) & (MAP_SHARED | MAP_PRIVATE | MAP_FIXED | MAP_ANON | MAP_32BIT | MAP_GROWSDOWN | MAP_GROWSUP | MAP_LOCKED | MAP_NORESERVE | MAP_POPULATE | MAP_NONBLOCK | MAP_STACK | MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE)) ? "|" : "", (flags) & MAP_OFFSET64_POINTER ? "MAP_OFFSET64_POINTER" : ""
#define __NRATRF4_mmap                    "%d"
#define __NRATRA4_mmap(addr, len, prot, flags, fd, offset) , (int)(fd)
#define __NRATRF5_mmap                    "%#" PRIxSIZ
#define __NRATRA5_mmap(addr, len, prot, flags, fd, offset) , (uintptr_t)(offset)
#define __NRATRF0_munmap                  "%p"
#define __NRATRA0_munmap(addr, len)       , addr
#define __NRATRF1_munmap                  "%" PRIuSIZ
#define __NRATRA1_munmap(addr, len)       , len
#define __NRATRF0_truncate                "%q"
#define __NRATRA0_truncate(filename, length) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_truncate                "%#" PRIxSIZ
#define __NRATRA1_truncate(filename, length) , (uintptr_t)(length)
#define __NRATRF0_ftruncate               "%d"
#define __NRATRA0_ftruncate(fd, length)   , (int)(fd)
#define __NRATRF1_ftruncate               "%#" PRIxSIZ
#define __NRATRA1_ftruncate(fd, length)   , (uintptr_t)(length)
#define __NRATRF0_fchmod                  "%d"
#define __NRATRA0_fchmod(fd, mode)        , (int)(fd)
#define __NRATRF1_fchmod                  "%#" PRIoSIZ
#define __NRATRA1_fchmod(fd, mode)        , (uintptr_t)(mode)
#define __NRATRF0_fchown                  "%d"
#define __NRATRA0_fchown(fd, owner, group) , (int)(fd)
#define __NRATRF1_fchown                  "%" PRIu16
#define __NRATRA1_fchown(fd, owner, group) , owner
#define __NRATRF2_fchown                  "%" PRIu16
#define __NRATRA2_fchown(fd, owner, group) , group
#define __NRATRF0_getpriority             "%#" PRIxSIZ
#define __NRATRA0_getpriority(which, who) , (uintptr_t)(which)
#define __NRATRF1_getpriority             "%" PRIuSIZ
#define __NRATRA1_getpriority(which, who) , (uintptr_t)(who)
#define __NRATRF0_setpriority             "%#" PRIxSIZ
#define __NRATRA0_setpriority(which, who, value) , (uintptr_t)(which)
#define __NRATRF1_setpriority             "%" PRIuSIZ
#define __NRATRA1_setpriority(which, who, value) , (uintptr_t)(who)
#define __NRATRF2_setpriority             "%#" PRIxSIZ
#define __NRATRA2_setpriority(which, who, value) , (uintptr_t)(value)
#define __NRATRF0_profil                  "%p"
#define __NRATRA0_profil(sample_buffer, size, offset, scale) , sample_buffer
#define __NRATRF1_profil                  "%" PRIuSIZ
#define __NRATRA1_profil(sample_buffer, size, offset, scale) , size
#define __NRATRF2_profil                  "%" PRIuSIZ
#define __NRATRA2_profil(sample_buffer, size, offset, scale) , offset
#define __NRATRF3_profil                  "%#" PRIxSIZ
#define __NRATRA3_profil(sample_buffer, size, offset, scale) , (uintptr_t)(scale)
#define __NRATRF0_statfs                  "%q"
#define __NRATRA0_statfs(file, buf)       , (validate_readable_opt(file,1),file)
#define __NRATRF1_statfs                  "%p"
#define __NRATRA1_statfs(file, buf)       , buf
#define __NRATRF0_fstatfs                 "%d"
#define __NRATRA0_fstatfs(file, buf)      , (int)(file)
#define __NRATRF1_fstatfs                 "%p"
#define __NRATRA1_fstatfs(file, buf)      , buf
#define __NRATRF0_ioperm                  "%#" PRIxSIZ
#define __NRATRA0_ioperm(from, num, turn_on) , (uintptr_t)(from)
#define __NRATRF1_ioperm                  "%#" PRIxSIZ
#define __NRATRA1_ioperm(from, num, turn_on) , (uintptr_t)(num)
#define __NRATRF2_ioperm                  "%#" PRIxSIZ
#define __NRATRA2_ioperm(from, num, turn_on) , (uintptr_t)(turn_on)
#define __NRATRF0_socketcall              "%d"
#define __NRATRA0_socketcall(call, args)  , call
#define __NRATRF1_socketcall              "%p"
#define __NRATRA1_socketcall(call, args)  , args
#define __NRATRF0_syslog                  "%" PRIuSIZ
#define __NRATRA0_syslog(level, str, len) , (uintptr_t)(level)
#define __NRATRF1_syslog                  "%$q"
#define __NRATRA1_syslog(level, str, len) , len,(validate_readable(str,len),str)
#define __NRATRF2_syslog                  "%" PRIuSIZ
#define __NRATRA2_syslog(level, str, len) , len
#define __NRATRF0_setitimer               "%#" PRIxSIZ
#define __NRATRA0_setitimer(which, newval, oldval) , (uintptr_t)(which)
#define __NRATRF1_setitimer               "%p"
#define __NRATRA1_setitimer(which, newval, oldval) , newval
#define __NRATRF2_setitimer               "%p"
#define __NRATRA2_setitimer(which, newval, oldval) , oldval
#define __NRATRF0_getitimer               "%#" PRIxSIZ
#define __NRATRA0_getitimer(which, curr_value) , (uintptr_t)(which)
#define __NRATRF1_getitimer               "%p"
#define __NRATRA1_getitimer(which, curr_value) , curr_value
#define __NRATRF0_linux_stat              "%q"
#define __NRATRA0_linux_stat(filename, statbuf) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_stat              "%p"
#define __NRATRA1_linux_stat(filename, statbuf) , statbuf
#define __NRATRF0_linux_lstat             "%q"
#define __NRATRA0_linux_lstat(filename, statbuf) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_lstat             "%p"
#define __NRATRA1_linux_lstat(filename, statbuf) , statbuf
#define __NRATRF0_linux_fstat             "%d"
#define __NRATRA0_linux_fstat(fd, statbuf) , (int)(fd)
#define __NRATRF1_linux_fstat             "%p"
#define __NRATRA1_linux_fstat(fd, statbuf) , statbuf
#define __NRATRF0_olduname                "%p"
#define __NRATRA0_olduname(name)          , name
#define __NRATRF0_iopl                    "%#" PRIxSIZ
#define __NRATRA0_iopl(level)             , (uintptr_t)(level)
#define __NRATRF0_vm86old                 "%d"
#define __NRATRA0_vm86old(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_wait4                   "%" PRIdSIZ
#define __NRATRA0_wait4(pid, stat_loc, options, usage) , (intptr_t)(pid)
#define __NRATRF1_wait4                   "%p"
#define __NRATRA1_wait4(pid, stat_loc, options, usage) , stat_loc
#define __NRATRF2_wait4                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NRATRA2_wait4(pid, stat_loc, options, usage) , (uintptr_t)(options), (options) & WNOHANG ? "WNOHANG" : "" \
                                                       , ((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "", (options) & WUNTRACED ? "WUNTRACED" : "" \
                                                       , ((options) & WCONTINUED) && ((options) & (WNOHANG | WUNTRACED)) ? "|" : "", (options) & WCONTINUED ? "WCONTINUED" : "" \
                                                       , ((options) & WNOWAIT) && ((options) & (WNOHANG | WUNTRACED | WCONTINUED)) ? "|" : "", (options) & WNOWAIT ? "WNOWAIT" : ""
#define __NRATRF3_wait4                   "%p"
#define __NRATRA3_wait4(pid, stat_loc, options, usage) , usage
#define __NRATRF0_swapoff                 "%q"
#define __NRATRA0_swapoff(pathname)       , (validate_readable_opt(pathname,1),pathname)
#define __NRATRF0_sysinfo                 "%p"
#define __NRATRA0_sysinfo(info)           , info
#define __NRATRF0_ipc                     "%d"
#define __NRATRA0_ipc(TODO_PROTOTYPE)     , TODO_PROTOTYPE
#define __NRATRF0_fsync                   "%d"
#define __NRATRA0_fsync(fd)               , (int)(fd)
#define __NRATRF0_sigreturn               "%p"
#define __NRATRA0_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) , restore_fpu
#define __NRATRF1_sigreturn               "%#" PRIxSIZ
#define __NRATRA1_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) , (uintptr_t)(unused1)
#define __NRATRF2_sigreturn               "%#" PRIxSIZ
#define __NRATRA2_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) , (uintptr_t)(unused2)
#define __NRATRF3_sigreturn               "%p"
#define __NRATRA3_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) , restore_sigmask
#define __NRATRF4_sigreturn               "%p"
#define __NRATRA4_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) , sc_info
#define __NRATRF5_sigreturn               "%p"
#define __NRATRA5_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) , restore_cpu
#define __NRATRF0_clone                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA0_clone(flags, child_stack, ptid, newtls, ctid) , (uintptr_t)(flags), (flags) & CLONE_VM ? "CLONE_VM" : "" \
                                                                , ((flags) & CLONE_FS) && ((flags) & (CLONE_VM)) ? "|" : "", (flags) & CLONE_FS ? "CLONE_FS" : "" \
                                                                , ((flags) & CLONE_FILES) && ((flags) & (CLONE_VM | CLONE_FS)) ? "|" : "", (flags) & CLONE_FILES ? "CLONE_FILES" : "" \
                                                                , ((flags) & CLONE_SIGHAND) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES)) ? "|" : "", (flags) & CLONE_SIGHAND ? "CLONE_SIGHAND" : "" \
                                                                , ((flags) & CLONE_PTRACE) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND)) ? "|" : "", (flags) & CLONE_PTRACE ? "CLONE_PTRACE" : "" \
                                                                , ((flags) & CLONE_VFORK) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE)) ? "|" : "", (flags) & CLONE_VFORK ? "CLONE_VFORK" : "" \
                                                                , ((flags) & CLONE_PARENT) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK)) ? "|" : "", (flags) & CLONE_PARENT ? "CLONE_PARENT" : "" \
                                                                , ((flags) & CLONE_THREAD) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT)) ? "|" : "", (flags) & CLONE_THREAD ? "CLONE_THREAD" : "" \
                                                                , ((flags) & CLONE_NEWNS) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD)) ? "|" : "", (flags) & CLONE_NEWNS ? "CLONE_NEWNS" : "" \
                                                                , ((flags) & CLONE_SYSVSEM) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS)) ? "|" : "", (flags) & CLONE_SYSVSEM ? "CLONE_SYSVSEM" : "" \
                                                                , ((flags) & CLONE_SETTLS) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM)) ? "|" : "", (flags) & CLONE_SETTLS ? "CLONE_SETTLS" : "" \
                                                                , ((flags) & CLONE_PARENT_SETTID) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS)) ? "|" : "", (flags) & CLONE_PARENT_SETTID ? "CLONE_PARENT_SETTID" : "" \
                                                                , ((flags) & CLONE_CHILD_CLEARTID) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID)) ? "|" : "", (flags) & CLONE_CHILD_CLEARTID ? "CLONE_CHILD_CLEARTID" : "" \
                                                                , ((flags) & CLONE_DETACHED) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID)) ? "|" : "", (flags) & CLONE_DETACHED ? "CLONE_DETACHED" : "" \
                                                                , ((flags) & CLONE_UNTRACED) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED)) ? "|" : "", (flags) & CLONE_UNTRACED ? "CLONE_UNTRACED" : "" \
                                                                , ((flags) & CLONE_CHILD_SETTID) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED)) ? "|" : "", (flags) & CLONE_CHILD_SETTID ? "CLONE_CHILD_SETTID" : "" \
                                                                , ((flags) & CLONE_NEWUTS) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID)) ? "|" : "", (flags) & CLONE_NEWUTS ? "CLONE_NEWUTS" : "" \
                                                                , ((flags) & CLONE_NEWIPC) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS)) ? "|" : "", (flags) & CLONE_NEWIPC ? "CLONE_NEWIPC" : "" \
                                                                , ((flags) & CLONE_NEWUSER) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS | CLONE_NEWIPC)) ? "|" : "", (flags) & CLONE_NEWUSER ? "CLONE_NEWUSER" : "" \
                                                                , ((flags) & CLONE_NEWPID) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWUSER)) ? "|" : "", (flags) & CLONE_NEWPID ? "CLONE_NEWPID" : "" \
                                                                , ((flags) & CLONE_NEWNET) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWUSER | CLONE_NEWPID)) ? "|" : "", (flags) & CLONE_NEWNET ? "CLONE_NEWNET" : "" \
                                                                , ((flags) & CLONE_IO) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWUSER | CLONE_NEWPID | CLONE_NEWNET)) ? "|" : "", (flags) & CLONE_IO ? "CLONE_IO" : ""
#define __NRATRF1_clone                   "%p"
#define __NRATRA1_clone(flags, child_stack, ptid, newtls, ctid) , child_stack
#define __NRATRF2_clone                   "%p"
#define __NRATRA2_clone(flags, child_stack, ptid, newtls, ctid) , ptid
#define __NRATRF3_clone                   "%p"
#define __NRATRA3_clone(flags, child_stack, ptid, newtls, ctid) , newtls
#define __NRATRF4_clone                   "%p"
#define __NRATRA4_clone(flags, child_stack, ptid, newtls, ctid) , ctid
#define __NRATRF0_setdomainname           "%q"
#define __NRATRA0_setdomainname(name, len) , (validate_readable_opt(name,1),name)
#define __NRATRF1_setdomainname           "%" PRIuSIZ
#define __NRATRA1_setdomainname(name, len) , len
#define __NRATRF0_uname                   "%p"
#define __NRATRA0_uname(name)             , name
#define __NRATRF0_modify_ldt              "%#" PRIxSIZ
#define __NRATRA0_modify_ldt(func, ptr, bytecount) , (uintptr_t)(func)
#define __NRATRF1_modify_ldt              "%p"
#define __NRATRA1_modify_ldt(func, ptr, bytecount) , ptr
#define __NRATRF2_modify_ldt              "%#" PRIxSIZ
#define __NRATRA2_modify_ldt(func, ptr, bytecount) , (uintptr_t)(bytecount)
#define __NRATRF0_adjtimex                "%d"
#define __NRATRA0_adjtimex(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_mprotect                "%p"
#define __NRATRA0_mprotect(addr, len, prot) , addr
#define __NRATRF1_mprotect                "%" PRIuSIZ
#define __NRATRA1_mprotect(addr, len, prot) , len
#define __NRATRF2_mprotect                "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NRATRA2_mprotect(addr, len, prot) , (uintptr_t)(prot), (prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                            , ((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "", (prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                            , ((prot) & PROT_READ) && ((prot) & (PROT_EXEC | PROT_WRITE)) ? "|" : "", (prot) & PROT_READ ? "PROT_READ" : "" \
                                            , ((prot) & PROT_SEM) && ((prot) & (PROT_EXEC | PROT_WRITE | PROT_READ)) ? "|" : "", (prot) & PROT_SEM ? "PROT_SEM" : ""
#define __NRATRF0_sigprocmask             "%#" PRIxSIZ
#define __NRATRA0_sigprocmask(how, set, oset) , (uintptr_t)(how)
#define __NRATRF1_sigprocmask             "%p"
#define __NRATRA1_sigprocmask(how, set, oset) , set
#define __NRATRF2_sigprocmask             "%p"
#define __NRATRA2_sigprocmask(how, set, oset) , oset
#define __NRATRF0_create_module           "%d"
#define __NRATRA0_create_module(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_init_module             "%d"
#define __NRATRA0_init_module(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_delete_module           "%d"
#define __NRATRA0_delete_module(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_get_kernel_syms         "%d"
#define __NRATRA0_get_kernel_syms(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_quotactl                "%d"
#define __NRATRA0_quotactl(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_getpgid                 "%" PRIdSIZ
#define __NRATRA0_getpgid(pid)            , (intptr_t)(pid)
#define __NRATRF0_fchdir                  "%d"
#define __NRATRA0_fchdir(fd)              , (int)(fd)
#define __NRATRF0_bdflush                 "%d"
#define __NRATRA0_bdflush(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_sysfs                   "%d"
#define __NRATRA0_sysfs(TODO_PROTOTYPE)   , TODO_PROTOTYPE
#define __NRATRF0_personality             "%d"
#define __NRATRA0_personality(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_afs_syscall             "%d"
#define __NRATRA0_afs_syscall(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_setfsuid                "%" PRIu16
#define __NRATRA0_setfsuid(uid)           , uid
#define __NRATRF0_setfsgid                "%" PRIu16
#define __NRATRA0_setfsgid(gid)           , gid
#define __NRATRF0__llseek                 "%d"
#define __NRATRA0__llseek(fd, offset, result, whence) , (int)(fd)
#define __NRATRF1__llseek                 "%" PRId64
#define __NRATRA1__llseek(fd, offset, result, whence) , offset
#define __NRATRF2__llseek                 "%p"
#define __NRATRA2__llseek(fd, offset, result, whence) , result
#define __NRATRF3__llseek                 "%#Ix=%s"
#define __NRATRA3__llseek(fd, offset, result, whence) , (whence), (whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NRATRF0_getdents                "%d"
#define __NRATRA0_getdents(fd, dirp, count) , (int)(fd)
#define __NRATRF1_getdents                "%p"
#define __NRATRA1_getdents(fd, dirp, count) , dirp
#define __NRATRF2_getdents                "%" PRIuSIZ
#define __NRATRA2_getdents(fd, dirp, count) , count
#define __NRATRF0__newselect              "%d"
#define __NRATRA0__newselect(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_flock                   "%d"
#define __NRATRA0_flock(fd, operation)    , (int)(fd)
#define __NRATRF1_flock                   "%#" PRIxSIZ
#define __NRATRA1_flock(fd, operation)    , (uintptr_t)(operation)
#define __NRATRF0_msync                   "%p"
#define __NRATRA0_msync(addr, len, flags) , addr
#define __NRATRF1_msync                   "%" PRIuSIZ
#define __NRATRA1_msync(addr, len, flags) , len
#define __NRATRF2_msync                   "%#" PRIxSIZ
#define __NRATRA2_msync(addr, len, flags) , (uintptr_t)(flags)
#define __NRATRF0_readv                   "%d"
#define __NRATRA0_readv(fd, iovec, count) , (int)(fd)
#define __NRATRF1_readv                   "%p"
#define __NRATRA1_readv(fd, iovec, count) , iovec
#define __NRATRF2_readv                   "%" PRIuSIZ
#define __NRATRA2_readv(fd, iovec, count) , count
#define __NRATRF0_writev                  "%d"
#define __NRATRA0_writev(fd, iovec, count) , (int)(fd)
#define __NRATRF1_writev                  "%p"
#define __NRATRA1_writev(fd, iovec, count) , iovec
#define __NRATRF2_writev                  "%" PRIuSIZ
#define __NRATRA2_writev(fd, iovec, count) , count
#define __NRATRF0_getsid                  "%" PRIdSIZ
#define __NRATRA0_getsid(pid)             , (intptr_t)(pid)
#define __NRATRF0_fdatasync               "%d"
#define __NRATRA0_fdatasync(fd)           , (int)(fd)
#define __NRATRF0__sysctl                 "%d"
#define __NRATRA0__sysctl(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_mlock                   "%p"
#define __NRATRA0_mlock(addr, len)        , addr
#define __NRATRF1_mlock                   "%" PRIuSIZ
#define __NRATRA1_mlock(addr, len)        , len
#define __NRATRF0_munlock                 "%p"
#define __NRATRA0_munlock(addr, len)      , addr
#define __NRATRF1_munlock                 "%" PRIuSIZ
#define __NRATRA1_munlock(addr, len)      , len
#define __NRATRF0_mlockall                "%#" PRIxSIZ
#define __NRATRA0_mlockall(flags)         , (uintptr_t)(flags)
#define __NRATRF0_sched_setparam          "%" PRIdSIZ
#define __NRATRA0_sched_setparam(pid, param) , (intptr_t)(pid)
#define __NRATRF1_sched_setparam          "%p"
#define __NRATRA1_sched_setparam(pid, param) , param
#define __NRATRF0_sched_getparam          "%" PRIdSIZ
#define __NRATRA0_sched_getparam(pid, param) , (intptr_t)(pid)
#define __NRATRF1_sched_getparam          "%p"
#define __NRATRA1_sched_getparam(pid, param) , param
#define __NRATRF0_sched_setscheduler      "%" PRIdSIZ
#define __NRATRA0_sched_setscheduler(pid, policy, param) , (intptr_t)(pid)
#define __NRATRF1_sched_setscheduler      "%#" PRIxSIZ
#define __NRATRA1_sched_setscheduler(pid, policy, param) , (uintptr_t)(policy)
#define __NRATRF2_sched_setscheduler      "%p"
#define __NRATRA2_sched_setscheduler(pid, policy, param) , param
#define __NRATRF0_sched_getscheduler      "%" PRIdSIZ
#define __NRATRA0_sched_getscheduler(pid) , (intptr_t)(pid)
#define __NRATRF0_sched_get_priority_max  "%#" PRIxSIZ
#define __NRATRA0_sched_get_priority_max(algorithm) , (uintptr_t)(algorithm)
#define __NRATRF0_sched_get_priority_min  "%#" PRIxSIZ
#define __NRATRA0_sched_get_priority_min(algorithm) , (uintptr_t)(algorithm)
#define __NRATRF0_sched_rr_get_interval   "%" PRIdSIZ
#define __NRATRA0_sched_rr_get_interval(pid, tms) , (intptr_t)(pid)
#define __NRATRF1_sched_rr_get_interval   "%p"
#define __NRATRA1_sched_rr_get_interval(pid, tms) , tms
#define __NRATRF0_nanosleep               "%p"
#define __NRATRA0_nanosleep(req, rem)     , req
#define __NRATRF1_nanosleep               "%p"
#define __NRATRA1_nanosleep(req, rem)     , rem
#define __NRATRF0_mremap                  "%p"
#define __NRATRA0_mremap(addr, old_len, new_len, flags, new_address) , addr
#define __NRATRF1_mremap                  "%" PRIuSIZ
#define __NRATRA1_mremap(addr, old_len, new_len, flags, new_address) , old_len
#define __NRATRF2_mremap                  "%" PRIuSIZ
#define __NRATRA2_mremap(addr, old_len, new_len, flags, new_address) , new_len
#define __NRATRF3_mremap                  "%#" PRIxSIZ "=%s%s%s"
#define __NRATRA3_mremap(addr, old_len, new_len, flags, new_address) , (uintptr_t)(flags), (flags) & MREMAP_MAYMOVE ? "MREMAP_MAYMOVE" : "" \
                                                                     , ((flags) & MREMAP_FIXED) && ((flags) & (MREMAP_MAYMOVE)) ? "|" : "", (flags) & MREMAP_FIXED ? "MREMAP_FIXED" : ""
#define __NRATRF4_mremap                  "%p"
#define __NRATRA4_mremap(addr, old_len, new_len, flags, new_address) , new_address
#define __NRATRF0_setresuid               "%" PRIu16
#define __NRATRA0_setresuid(ruid, euid, suid) , ruid
#define __NRATRF1_setresuid               "%" PRIu16
#define __NRATRA1_setresuid(ruid, euid, suid) , euid
#define __NRATRF2_setresuid               "%" PRIu16
#define __NRATRA2_setresuid(ruid, euid, suid) , suid
#define __NRATRF0_getresuid               "%p"
#define __NRATRA0_getresuid(ruid, euid, suid) , ruid
#define __NRATRF1_getresuid               "%p"
#define __NRATRA1_getresuid(ruid, euid, suid) , euid
#define __NRATRF2_getresuid               "%p"
#define __NRATRA2_getresuid(ruid, euid, suid) , suid
#define __NRATRF0_vm86                    "%d"
#define __NRATRA0_vm86(TODO_PROTOTYPE)    , TODO_PROTOTYPE
#define __NRATRF0_query_module            "%d"
#define __NRATRA0_query_module(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_poll                    "%p"
#define __NRATRA0_poll(fds, nfds, timeout) , fds
#define __NRATRF1_poll                    "%" PRIuSIZ
#define __NRATRA1_poll(fds, nfds, timeout) , nfds
#define __NRATRF2_poll                    "%" PRIdSIZ
#define __NRATRA2_poll(fds, nfds, timeout) , (intptr_t)(timeout)
#define __NRATRF0_nfsservctl              "%d"
#define __NRATRA0_nfsservctl(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_setresgid               "%" PRIu16
#define __NRATRA0_setresgid(rgid, egid, sgid) , rgid
#define __NRATRF1_setresgid               "%" PRIu16
#define __NRATRA1_setresgid(rgid, egid, sgid) , egid
#define __NRATRF2_setresgid               "%" PRIu16
#define __NRATRA2_setresgid(rgid, egid, sgid) , sgid
#define __NRATRF0_getresgid               "%p"
#define __NRATRA0_getresgid(rgid, egid, sgid) , rgid
#define __NRATRF1_getresgid               "%p"
#define __NRATRA1_getresgid(rgid, egid, sgid) , egid
#define __NRATRF2_getresgid               "%p"
#define __NRATRA2_getresgid(rgid, egid, sgid) , sgid
#define __NRATRF0_prctl                   "%d"
#define __NRATRA0_prctl(TODO_PROTOTYPE)   , TODO_PROTOTYPE
#define __NRATRF0_rt_sigreturn            "%p"
#define __NRATRA0_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) , restore_fpu
#define __NRATRF1_rt_sigreturn            "%p"
#define __NRATRA1_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) , restore_sigmask
#define __NRATRF2_rt_sigreturn            "%p"
#define __NRATRA2_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) , sc_info
#define __NRATRF3_rt_sigreturn            "%p"
#define __NRATRA3_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) , restore_cpu
#define __NRATRF0_rt_sigaction            "%#" PRIxSIZ
#define __NRATRA0_rt_sigaction(signo, act, oact, sigsetsize) , (uintptr_t)(signo)
#define __NRATRF1_rt_sigaction            "%p"
#define __NRATRA1_rt_sigaction(signo, act, oact, sigsetsize) , act
#define __NRATRF2_rt_sigaction            "%p"
#define __NRATRA2_rt_sigaction(signo, act, oact, sigsetsize) , oact
#define __NRATRF3_rt_sigaction            "%" PRIuSIZ
#define __NRATRA3_rt_sigaction(signo, act, oact, sigsetsize) , sigsetsize
#define __NRATRF0_rt_sigprocmask          "%#" PRIxSIZ
#define __NRATRA0_rt_sigprocmask(how, set, oset, sigsetsize) , (uintptr_t)(how)
#define __NRATRF1_rt_sigprocmask          "%p"
#define __NRATRA1_rt_sigprocmask(how, set, oset, sigsetsize) , set
#define __NRATRF2_rt_sigprocmask          "%p"
#define __NRATRA2_rt_sigprocmask(how, set, oset, sigsetsize) , oset
#define __NRATRF3_rt_sigprocmask          "%" PRIuSIZ
#define __NRATRA3_rt_sigprocmask(how, set, oset, sigsetsize) , sigsetsize
#define __NRATRF0_rt_sigpending           "%p"
#define __NRATRA0_rt_sigpending(set, sigsetsize) , set
#define __NRATRF1_rt_sigpending           "%" PRIuSIZ
#define __NRATRA1_rt_sigpending(set, sigsetsize) , sigsetsize
#define __NRATRF0_rt_sigtimedwait         "%p"
#define __NRATRA0_rt_sigtimedwait(set, info, timeout, sigsetsize) , set
#define __NRATRF1_rt_sigtimedwait         "%p"
#define __NRATRA1_rt_sigtimedwait(set, info, timeout, sigsetsize) , info
#define __NRATRF2_rt_sigtimedwait         "%p"
#define __NRATRA2_rt_sigtimedwait(set, info, timeout, sigsetsize) , timeout
#define __NRATRF3_rt_sigtimedwait         "%" PRIuSIZ
#define __NRATRA3_rt_sigtimedwait(set, info, timeout, sigsetsize) , sigsetsize
#define __NRATRF0_rt_sigqueueinfo         "%" PRIdSIZ
#define __NRATRA0_rt_sigqueueinfo(tgid, signo, uinfo) , (intptr_t)(tgid)
#define __NRATRF1_rt_sigqueueinfo         "%#" PRIxSIZ
#define __NRATRA1_rt_sigqueueinfo(tgid, signo, uinfo) , (uintptr_t)(signo)
#define __NRATRF2_rt_sigqueueinfo         "%p"
#define __NRATRA2_rt_sigqueueinfo(tgid, signo, uinfo) , uinfo
#define __NRATRF0_rt_sigsuspend           "%p"
#define __NRATRA0_rt_sigsuspend(set, sigsetsize) , set
#define __NRATRF1_rt_sigsuspend           "%" PRIuSIZ
#define __NRATRA1_rt_sigsuspend(set, sigsetsize) , sigsetsize
#define __NRATRF0_pread64                 "%d"
#define __NRATRA0_pread64(fd, buf, bufsize, offset) , (int)(fd)
#define __NRATRF1_pread64                 "%p"
#define __NRATRA1_pread64(fd, buf, bufsize, offset) , buf
#define __NRATRF2_pread64                 "%" PRIuSIZ
#define __NRATRA2_pread64(fd, buf, bufsize, offset) , bufsize
#define __NRATRF3_pread64                 "%" PRIu64
#define __NRATRA3_pread64(fd, buf, bufsize, offset) , offset
#define __NRATRF0_pwrite64                "%d"
#define __NRATRA0_pwrite64(fd, buf, bufsize, offset) , (int)(fd)
#define __NRATRF1_pwrite64                "%p"
#define __NRATRA1_pwrite64(fd, buf, bufsize, offset) , buf
#define __NRATRF2_pwrite64                "%" PRIuSIZ
#define __NRATRA2_pwrite64(fd, buf, bufsize, offset) , bufsize
#define __NRATRF3_pwrite64                "%" PRIu64
#define __NRATRA3_pwrite64(fd, buf, bufsize, offset) , offset
#define __NRATRF0_chown                   "%q"
#define __NRATRA0_chown(filename, owner, group) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_chown                   "%" PRIu16
#define __NRATRA1_chown(filename, owner, group) , owner
#define __NRATRF2_chown                   "%" PRIu16
#define __NRATRA2_chown(filename, owner, group) , group
#define __NRATRF0_getcwd                  "%p"
#define __NRATRA0_getcwd(buf, size)       , buf
#define __NRATRF1_getcwd                  "%" PRIuSIZ
#define __NRATRA1_getcwd(buf, size)       , size
#define __NRATRF0_capget                  "%d"
#define __NRATRA0_capget(TODO_PROTOTYPE)  , TODO_PROTOTYPE
#define __NRATRF0_capset                  "%d"
#define __NRATRA0_capset(TODO_PROTOTYPE)  , TODO_PROTOTYPE
#define __NRATRF0_sigaltstack             "%p"
#define __NRATRA0_sigaltstack(ss, oss)    , ss
#define __NRATRF1_sigaltstack             "%p"
#define __NRATRA1_sigaltstack(ss, oss)    , oss
#define __NRATRF0_sendfile                "%d"
#define __NRATRA0_sendfile(out_fd, in_fd, pin_offset, num_bytes) , (int)(out_fd)
#define __NRATRF1_sendfile                "%d"
#define __NRATRA1_sendfile(out_fd, in_fd, pin_offset, num_bytes) , (int)(in_fd)
#define __NRATRF2_sendfile                "%p"
#define __NRATRA2_sendfile(out_fd, in_fd, pin_offset, num_bytes) , pin_offset
#define __NRATRF3_sendfile                "%" PRIuSIZ
#define __NRATRA3_sendfile(out_fd, in_fd, pin_offset, num_bytes) , num_bytes
#define __NRATRF0_getpmsg                 "%d"
#define __NRATRA0_getpmsg(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_putpmsg                 "%d"
#define __NRATRA0_putpmsg(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_ugetrlimit              "%d"
#define __NRATRA0_ugetrlimit(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_mmap2                   "%p"
#define __NRATRA0_mmap2(addr, len, prot, flags, fd, pgoffset) , addr
#define __NRATRF1_mmap2                   "%" PRIuSIZ
#define __NRATRA1_mmap2(addr, len, prot, flags, fd, pgoffset) , len
#define __NRATRF2_mmap2                   "%#" PRIxSIZ
#define __NRATRA2_mmap2(addr, len, prot, flags, fd, pgoffset) , (uintptr_t)(prot)
#define __NRATRF3_mmap2                   "%#" PRIxSIZ
#define __NRATRA3_mmap2(addr, len, prot, flags, fd, pgoffset) , (uintptr_t)(flags)
#define __NRATRF4_mmap2                   "%d"
#define __NRATRA4_mmap2(addr, len, prot, flags, fd, pgoffset) , (int)(fd)
#define __NRATRF5_mmap2                   "%#" PRIxSIZ
#define __NRATRA5_mmap2(addr, len, prot, flags, fd, pgoffset) , (uintptr_t)(pgoffset)
#define __NRATRF0_truncate64              "%q"
#define __NRATRA0_truncate64(filename, length) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_truncate64              "%" PRIu64
#define __NRATRA1_truncate64(filename, length) , length
#define __NRATRF0_ftruncate64             "%d"
#define __NRATRA0_ftruncate64(fd, length) , (int)(fd)
#define __NRATRF1_ftruncate64             "%" PRIu64
#define __NRATRA1_ftruncate64(fd, length) , length
#define __NRATRF0_linux_stat64            "%q"
#define __NRATRA0_linux_stat64(filename, statbuf) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_stat64            "%p"
#define __NRATRA1_linux_stat64(filename, statbuf) , statbuf
#define __NRATRF0_linux_lstat64           "%q"
#define __NRATRA0_linux_lstat64(filename, statbuf) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_linux_lstat64           "%p"
#define __NRATRA1_linux_lstat64(filename, statbuf) , statbuf
#define __NRATRF0_linux_fstat64           "%d"
#define __NRATRA0_linux_fstat64(fd, statbuf) , (int)(fd)
#define __NRATRF1_linux_fstat64           "%p"
#define __NRATRA1_linux_fstat64(fd, statbuf) , statbuf
#define __NRATRF0_lchown32                "%q"
#define __NRATRA0_lchown32(filename, owner, group) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_lchown32                "%" PRIu32
#define __NRATRA1_lchown32(filename, owner, group) , owner
#define __NRATRF2_lchown32                "%" PRIu32
#define __NRATRA2_lchown32(filename, owner, group) , group
#define __NRATRF0_setreuid32              "%" PRIu32
#define __NRATRA0_setreuid32(ruid, euid)  , ruid
#define __NRATRF1_setreuid32              "%" PRIu32
#define __NRATRA1_setreuid32(ruid, euid)  , euid
#define __NRATRF0_setregid32              "%" PRIu32
#define __NRATRA0_setregid32(rgid, egid)  , rgid
#define __NRATRF1_setregid32              "%" PRIu32
#define __NRATRA1_setregid32(rgid, egid)  , egid
#define __NRATRF0_getgroups32             "%" PRIuSIZ
#define __NRATRA0_getgroups32(size, list) , size
#define __NRATRF1_getgroups32             "%p"
#define __NRATRA1_getgroups32(size, list) , list
#define __NRATRF0_setgroups32             "%" PRIuSIZ
#define __NRATRA0_setgroups32(count, groups) , count
#define __NRATRF1_setgroups32             "%p"
#define __NRATRA1_setgroups32(count, groups) , groups
#define __NRATRF0_fchown32                "%d"
#define __NRATRA0_fchown32(fd, owner, group) , (int)(fd)
#define __NRATRF1_fchown32                "%" PRIu32
#define __NRATRA1_fchown32(fd, owner, group) , owner
#define __NRATRF2_fchown32                "%" PRIu32
#define __NRATRA2_fchown32(fd, owner, group) , group
#define __NRATRF0_setresuid32             "%" PRIu32
#define __NRATRA0_setresuid32(ruid, euid, suid) , ruid
#define __NRATRF1_setresuid32             "%" PRIu32
#define __NRATRA1_setresuid32(ruid, euid, suid) , euid
#define __NRATRF2_setresuid32             "%" PRIu32
#define __NRATRA2_setresuid32(ruid, euid, suid) , suid
#define __NRATRF0_getresuid32             "%p"
#define __NRATRA0_getresuid32(ruid, euid, suid) , ruid
#define __NRATRF1_getresuid32             "%p"
#define __NRATRA1_getresuid32(ruid, euid, suid) , euid
#define __NRATRF2_getresuid32             "%p"
#define __NRATRA2_getresuid32(ruid, euid, suid) , suid
#define __NRATRF0_setresgid32             "%" PRIu32
#define __NRATRA0_setresgid32(rgid, egid, sgid) , rgid
#define __NRATRF1_setresgid32             "%" PRIu32
#define __NRATRA1_setresgid32(rgid, egid, sgid) , egid
#define __NRATRF2_setresgid32             "%" PRIu32
#define __NRATRA2_setresgid32(rgid, egid, sgid) , sgid
#define __NRATRF0_getresgid32             "%p"
#define __NRATRA0_getresgid32(rgid, egid, sgid) , rgid
#define __NRATRF1_getresgid32             "%p"
#define __NRATRA1_getresgid32(rgid, egid, sgid) , egid
#define __NRATRF2_getresgid32             "%p"
#define __NRATRA2_getresgid32(rgid, egid, sgid) , sgid
#define __NRATRF0_chown32                 "%q"
#define __NRATRA0_chown32(filename, owner, group) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_chown32                 "%" PRIu32
#define __NRATRA1_chown32(filename, owner, group) , owner
#define __NRATRF2_chown32                 "%" PRIu32
#define __NRATRA2_chown32(filename, owner, group) , group
#define __NRATRF0_setuid32                "%" PRIu32
#define __NRATRA0_setuid32(uid)           , uid
#define __NRATRF0_setgid32                "%" PRIu32
#define __NRATRA0_setgid32(gid)           , gid
#define __NRATRF0_setfsuid32              "%" PRIu32
#define __NRATRA0_setfsuid32(uid)         , uid
#define __NRATRF0_setfsgid32              "%" PRIu32
#define __NRATRA0_setfsgid32(gid)         , gid
#define __NRATRF0_pivot_root              "%d"
#define __NRATRA0_pivot_root(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_mincore                 "%p"
#define __NRATRA0_mincore(start, len, vec) , start
#define __NRATRF1_mincore                 "%" PRIuSIZ
#define __NRATRA1_mincore(start, len, vec) , len
#define __NRATRF2_mincore                 "%p"
#define __NRATRA2_mincore(start, len, vec) , vec
#define __NRATRF0_madvise                 "%p"
#define __NRATRA0_madvise(addr, len, advice) , addr
#define __NRATRF1_madvise                 "%" PRIuSIZ
#define __NRATRA1_madvise(addr, len, advice) , len
#define __NRATRF2_madvise                 "%#" PRIxSIZ
#define __NRATRA2_madvise(addr, len, advice) , (uintptr_t)(advice)
#define __NRATRF0_getdents64              "%d"
#define __NRATRA0_getdents64(fd, dirp, count) , (int)(fd)
#define __NRATRF1_getdents64              "%p"
#define __NRATRA1_getdents64(fd, dirp, count) , dirp
#define __NRATRF2_getdents64              "%" PRIuSIZ
#define __NRATRA2_getdents64(fd, dirp, count) , count
#define __NRATRF0_fcntl64                 "%d"
#define __NRATRA0_fcntl64(fd, command, arg) , (int)(fd)
#define __NRATRF1_fcntl64                 "%#" PRIxSIZ
#define __NRATRA1_fcntl64(fd, command, arg) , (uintptr_t)(command)
#define __NRATRF2_fcntl64                 "%p"
#define __NRATRA2_fcntl64(fd, command, arg) , arg
#define __NRATRF0_readahead               "%d"
#define __NRATRA0_readahead(fd, offset, count) , (int)(fd)
#define __NRATRF1_readahead               "%" PRIu64
#define __NRATRA1_readahead(fd, offset, count) , offset
#define __NRATRF2_readahead               "%" PRIuSIZ
#define __NRATRA2_readahead(fd, offset, count) , count
#define __NRATRF0_setxattr                "%q"
#define __NRATRA0_setxattr(path, name, buf, bufsize, flags) , (validate_readable_opt(path,1),path)
#define __NRATRF1_setxattr                "%q"
#define __NRATRA1_setxattr(path, name, buf, bufsize, flags) , (validate_readable_opt(name,1),name)
#define __NRATRF2_setxattr                "%p"
#define __NRATRA2_setxattr(path, name, buf, bufsize, flags) , buf
#define __NRATRF3_setxattr                "%" PRIuSIZ
#define __NRATRA3_setxattr(path, name, buf, bufsize, flags) , bufsize
#define __NRATRF4_setxattr                "%#" PRIxSIZ
#define __NRATRA4_setxattr(path, name, buf, bufsize, flags) , (uintptr_t)(flags)
#define __NRATRF0_lsetxattr               "%q"
#define __NRATRA0_lsetxattr(path, name, buf, bufsize, flags) , (validate_readable_opt(path,1),path)
#define __NRATRF1_lsetxattr               "%q"
#define __NRATRA1_lsetxattr(path, name, buf, bufsize, flags) , (validate_readable_opt(name,1),name)
#define __NRATRF2_lsetxattr               "%p"
#define __NRATRA2_lsetxattr(path, name, buf, bufsize, flags) , buf
#define __NRATRF3_lsetxattr               "%" PRIuSIZ
#define __NRATRA3_lsetxattr(path, name, buf, bufsize, flags) , bufsize
#define __NRATRF4_lsetxattr               "%#" PRIxSIZ
#define __NRATRA4_lsetxattr(path, name, buf, bufsize, flags) , (uintptr_t)(flags)
#define __NRATRF0_fsetxattr               "%d"
#define __NRATRA0_fsetxattr(fd, name, buf, bufsize, flags) , (int)(fd)
#define __NRATRF1_fsetxattr               "%q"
#define __NRATRA1_fsetxattr(fd, name, buf, bufsize, flags) , (validate_readable_opt(name,1),name)
#define __NRATRF2_fsetxattr               "%p"
#define __NRATRA2_fsetxattr(fd, name, buf, bufsize, flags) , buf
#define __NRATRF3_fsetxattr               "%" PRIuSIZ
#define __NRATRA3_fsetxattr(fd, name, buf, bufsize, flags) , bufsize
#define __NRATRF4_fsetxattr               "%#" PRIxSIZ
#define __NRATRA4_fsetxattr(fd, name, buf, bufsize, flags) , (uintptr_t)(flags)
#define __NRATRF0_getxattr                "%q"
#define __NRATRA0_getxattr(path, name, buf, bufsize) , (validate_readable_opt(path,1),path)
#define __NRATRF1_getxattr                "%q"
#define __NRATRA1_getxattr(path, name, buf, bufsize) , (validate_readable_opt(name,1),name)
#define __NRATRF2_getxattr                "%p"
#define __NRATRA2_getxattr(path, name, buf, bufsize) , buf
#define __NRATRF3_getxattr                "%" PRIuSIZ
#define __NRATRA3_getxattr(path, name, buf, bufsize) , bufsize
#define __NRATRF0_lgetxattr               "%q"
#define __NRATRA0_lgetxattr(path, name, buf, bufsize) , (validate_readable_opt(path,1),path)
#define __NRATRF1_lgetxattr               "%q"
#define __NRATRA1_lgetxattr(path, name, buf, bufsize) , (validate_readable_opt(name,1),name)
#define __NRATRF2_lgetxattr               "%p"
#define __NRATRA2_lgetxattr(path, name, buf, bufsize) , buf
#define __NRATRF3_lgetxattr               "%" PRIuSIZ
#define __NRATRA3_lgetxattr(path, name, buf, bufsize) , bufsize
#define __NRATRF0_fgetxattr               "%d"
#define __NRATRA0_fgetxattr(fd, name, buf, bufsize) , (int)(fd)
#define __NRATRF1_fgetxattr               "%q"
#define __NRATRA1_fgetxattr(fd, name, buf, bufsize) , (validate_readable_opt(name,1),name)
#define __NRATRF2_fgetxattr               "%p"
#define __NRATRA2_fgetxattr(fd, name, buf, bufsize) , buf
#define __NRATRF3_fgetxattr               "%" PRIuSIZ
#define __NRATRA3_fgetxattr(fd, name, buf, bufsize) , bufsize
#define __NRATRF0_listxattr               "%q"
#define __NRATRA0_listxattr(path, listbuf, listbufsize) , (validate_readable_opt(path,1),path)
#define __NRATRF1_listxattr               "%p"
#define __NRATRA1_listxattr(path, listbuf, listbufsize) , listbuf
#define __NRATRF2_listxattr               "%" PRIuSIZ
#define __NRATRA2_listxattr(path, listbuf, listbufsize) , listbufsize
#define __NRATRF0_llistxattr              "%q"
#define __NRATRA0_llistxattr(path, listbuf, listbufsize) , (validate_readable_opt(path,1),path)
#define __NRATRF1_llistxattr              "%p"
#define __NRATRA1_llistxattr(path, listbuf, listbufsize) , listbuf
#define __NRATRF2_llistxattr              "%" PRIuSIZ
#define __NRATRA2_llistxattr(path, listbuf, listbufsize) , listbufsize
#define __NRATRF0_flistxattr              "%d"
#define __NRATRA0_flistxattr(fd, listbuf, listbufsize) , (int)(fd)
#define __NRATRF1_flistxattr              "%p"
#define __NRATRA1_flistxattr(fd, listbuf, listbufsize) , listbuf
#define __NRATRF2_flistxattr              "%" PRIuSIZ
#define __NRATRA2_flistxattr(fd, listbuf, listbufsize) , listbufsize
#define __NRATRF0_removexattr             "%q"
#define __NRATRA0_removexattr(path, name) , (validate_readable_opt(path,1),path)
#define __NRATRF1_removexattr             "%q"
#define __NRATRA1_removexattr(path, name) , (validate_readable_opt(name,1),name)
#define __NRATRF0_lremovexattr            "%q"
#define __NRATRA0_lremovexattr(path, name) , (validate_readable_opt(path,1),path)
#define __NRATRF1_lremovexattr            "%q"
#define __NRATRA1_lremovexattr(path, name) , (validate_readable_opt(name,1),name)
#define __NRATRF0_fremovexattr            "%d"
#define __NRATRA0_fremovexattr(fd, name)  , fd
#define __NRATRF1_fremovexattr            "%q"
#define __NRATRA1_fremovexattr(fd, name)  , (validate_readable_opt(name,1),name)
#define __NRATRF0_tkill                   "%" PRIdSIZ
#define __NRATRA0_tkill(tid, signo)       , (intptr_t)(tid)
#define __NRATRF1_tkill                   "%#" PRIxSIZ
#define __NRATRA1_tkill(tid, signo)       , (uintptr_t)(signo)
#define __NRATRF0_sendfile64              "%d"
#define __NRATRA0_sendfile64(out_fd, in_fd, pin_offset, num_bytes) , (int)(out_fd)
#define __NRATRF1_sendfile64              "%d"
#define __NRATRA1_sendfile64(out_fd, in_fd, pin_offset, num_bytes) , (int)(in_fd)
#define __NRATRF2_sendfile64              "%p"
#define __NRATRA2_sendfile64(out_fd, in_fd, pin_offset, num_bytes) , pin_offset
#define __NRATRF3_sendfile64              "%" PRIuSIZ
#define __NRATRA3_sendfile64(out_fd, in_fd, pin_offset, num_bytes) , num_bytes
#define __NRATRF0_futex                   "%p"
#define __NRATRA0_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) , uaddr
#define __NRATRF1_futex                   "%#" PRIxSIZ
#define __NRATRA1_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) , (uintptr_t)(futex_op)
#define __NRATRF2_futex                   "%" PRIu32
#define __NRATRA2_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) , val
#define __NRATRF3_futex                   "%p"
#define __NRATRA3_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) , timeout_or_val2
#define __NRATRF4_futex                   "%p"
#define __NRATRA4_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) , uaddr2
#define __NRATRF5_futex                   "%" PRIu32
#define __NRATRA5_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) , val3
#define __NRATRF0_sched_setaffinity       "%" PRIdSIZ
#define __NRATRA0_sched_setaffinity(pid, cpusetsize, cpuset) , (intptr_t)(pid)
#define __NRATRF1_sched_setaffinity       "%" PRIuSIZ
#define __NRATRA1_sched_setaffinity(pid, cpusetsize, cpuset) , cpusetsize
#define __NRATRF2_sched_setaffinity       "%p"
#define __NRATRA2_sched_setaffinity(pid, cpusetsize, cpuset) , cpuset
#define __NRATRF0_sched_getaffinity       "%" PRIdSIZ
#define __NRATRA0_sched_getaffinity(pid, cpusetsize, cpuset) , (intptr_t)(pid)
#define __NRATRF1_sched_getaffinity       "%" PRIuSIZ
#define __NRATRA1_sched_getaffinity(pid, cpusetsize, cpuset) , cpusetsize
#define __NRATRF2_sched_getaffinity       "%p"
#define __NRATRA2_sched_getaffinity(pid, cpusetsize, cpuset) , cpuset
#define __NRATRF0_set_thread_area         "%d"
#define __NRATRA0_set_thread_area(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_get_thread_area         "%d"
#define __NRATRA0_get_thread_area(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_io_setup                "%d"
#define __NRATRA0_io_setup(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_io_destroy              "%d"
#define __NRATRA0_io_destroy(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_io_getevents            "%d"
#define __NRATRA0_io_getevents(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_io_submit               "%d"
#define __NRATRA0_io_submit(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_io_cancel               "%d"
#define __NRATRA0_io_cancel(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_fadvise64               "%d"
#define __NRATRA0_fadvise64(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_exit_group              "%" PRIuSIZ
#define __NRATRA0_exit_group(exit_code)   , (uintptr_t)(exit_code)
#define __NRATRF0_lookup_dcookie          "%d"
#define __NRATRA0_lookup_dcookie(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_epoll_create            "%#" PRIxSIZ
#define __NRATRA0_epoll_create(size)      , (uintptr_t)(size)
#define __NRATRF0_epoll_ctl               "%d"
#define __NRATRA0_epoll_ctl(epfd, op, fd, event) , (int)(epfd)
#define __NRATRF1_epoll_ctl               "%#Ix=%s"
#define __NRATRA1_epoll_ctl(epfd, op, fd, event) , (op), (op) == EPOLL_CTL_ADD ? "EPOLL_CTL_ADD" : (op) == EPOLL_CTL_DEL ? "EPOLL_CTL_DEL" : (op) == EPOLL_CTL_MOD ? "EPOLL_CTL_MOD" : "?"
#define __NRATRF2_epoll_ctl               "%d"
#define __NRATRA2_epoll_ctl(epfd, op, fd, event) , (int)(fd)
#define __NRATRF3_epoll_ctl               "%p"
#define __NRATRA3_epoll_ctl(epfd, op, fd, event) , event
#define __NRATRF0_epoll_wait              "%d"
#define __NRATRA0_epoll_wait(epfd, events, maxevents, timeout) , (int)(epfd)
#define __NRATRF1_epoll_wait              "%p"
#define __NRATRA1_epoll_wait(epfd, events, maxevents, timeout) , events
#define __NRATRF2_epoll_wait              "%#" PRIxSIZ
#define __NRATRA2_epoll_wait(epfd, events, maxevents, timeout) , (uintptr_t)(maxevents)
#define __NRATRF3_epoll_wait              "%" PRIdSIZ
#define __NRATRA3_epoll_wait(epfd, events, maxevents, timeout) , (intptr_t)(timeout)
#define __NRATRF0_remap_file_pages        "%p"
#define __NRATRA0_remap_file_pages(start, size, prot, pgoff, flags) , start
#define __NRATRF1_remap_file_pages        "%" PRIuSIZ
#define __NRATRA1_remap_file_pages(start, size, prot, pgoff, flags) , size
#define __NRATRF2_remap_file_pages        "%#" PRIxSIZ
#define __NRATRA2_remap_file_pages(start, size, prot, pgoff, flags) , (uintptr_t)(prot)
#define __NRATRF3_remap_file_pages        "%" PRIuSIZ
#define __NRATRA3_remap_file_pages(start, size, prot, pgoff, flags) , pgoff
#define __NRATRF4_remap_file_pages        "%#" PRIxSIZ
#define __NRATRA4_remap_file_pages(start, size, prot, pgoff, flags) , (uintptr_t)(flags)
#define __NRATRF0_set_tid_address         "%p"
#define __NRATRA0_set_tid_address(tidptr) , tidptr
#define __NRATRF0_timer_create            "%#" PRIxSIZ
#define __NRATRA0_timer_create(clock_id, evp, timerid) , (uintptr_t)(clock_id)
#define __NRATRF1_timer_create            "%p"
#define __NRATRA1_timer_create(clock_id, evp, timerid) , evp
#define __NRATRF2_timer_create            "%p"
#define __NRATRA2_timer_create(clock_id, evp, timerid) , timerid
#define __NRATRF0_timer_settime           "%p"
#define __NRATRA0_timer_settime(timerid, flags, value, ovalue) , timerid
#define __NRATRF1_timer_settime           "%#" PRIxSIZ
#define __NRATRA1_timer_settime(timerid, flags, value, ovalue) , (uintptr_t)(flags)
#define __NRATRF2_timer_settime           "%p"
#define __NRATRA2_timer_settime(timerid, flags, value, ovalue) , value
#define __NRATRF3_timer_settime           "%p"
#define __NRATRA3_timer_settime(timerid, flags, value, ovalue) , ovalue
#define __NRATRF0_timer_gettime           "%p"
#define __NRATRA0_timer_gettime(timerid, value) , timerid
#define __NRATRF1_timer_gettime           "%p"
#define __NRATRA1_timer_gettime(timerid, value) , value
#define __NRATRF0_timer_getoverrun        "%p"
#define __NRATRA0_timer_getoverrun(timerid) , timerid
#define __NRATRF0_timer_delete            "%p"
#define __NRATRA0_timer_delete(timerid)   , timerid
#define __NRATRF0_clock_settime           "%#" PRIxSIZ
#define __NRATRA0_clock_settime(clock_id, tp) , (uintptr_t)(clock_id)
#define __NRATRF1_clock_settime           "%p"
#define __NRATRA1_clock_settime(clock_id, tp) , tp
#define __NRATRF0_clock_gettime           "%#" PRIxSIZ
#define __NRATRA0_clock_gettime(clock_id, tp) , (uintptr_t)(clock_id)
#define __NRATRF1_clock_gettime           "%p"
#define __NRATRA1_clock_gettime(clock_id, tp) , tp
#define __NRATRF0_clock_getres            "%#" PRIxSIZ
#define __NRATRA0_clock_getres(clock_id, res) , (uintptr_t)(clock_id)
#define __NRATRF1_clock_getres            "%p"
#define __NRATRA1_clock_getres(clock_id, res) , res
#define __NRATRF0_clock_nanosleep         "%#" PRIxSIZ
#define __NRATRA0_clock_nanosleep(clock_id, flags, requested_time, remaining) , (uintptr_t)(clock_id)
#define __NRATRF1_clock_nanosleep         "%#" PRIxSIZ
#define __NRATRA1_clock_nanosleep(clock_id, flags, requested_time, remaining) , (uintptr_t)(flags)
#define __NRATRF2_clock_nanosleep         "%p"
#define __NRATRA2_clock_nanosleep(clock_id, flags, requested_time, remaining) , requested_time
#define __NRATRF3_clock_nanosleep         "%p"
#define __NRATRA3_clock_nanosleep(clock_id, flags, requested_time, remaining) , remaining
#define __NRATRF0_statfs64                "%q"
#define __NRATRA0_statfs64(file, buf)     , (validate_readable_opt(file,1),file)
#define __NRATRF1_statfs64                "%p"
#define __NRATRA1_statfs64(file, buf)     , buf
#define __NRATRF0_fstatfs64               "%d"
#define __NRATRA0_fstatfs64(file, buf)    , (int)(file)
#define __NRATRF1_fstatfs64               "%p"
#define __NRATRA1_fstatfs64(file, buf)    , buf
#define __NRATRF0_tgkill                  "%" PRIdSIZ
#define __NRATRA0_tgkill(tgid, tid, signo) , (intptr_t)(tgid)
#define __NRATRF1_tgkill                  "%" PRIdSIZ
#define __NRATRA1_tgkill(tgid, tid, signo) , (intptr_t)(tid)
#define __NRATRF2_tgkill                  "%#" PRIxSIZ
#define __NRATRA2_tgkill(tgid, tid, signo) , (uintptr_t)(signo)
#define __NRATRF0_utimes                  "%q"
#define __NRATRA0_utimes(filename, times) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_utimes                  "%p"
#define __NRATRA1_utimes(filename, times) , times
#define __NRATRF0_fadvise64_64            "%d"
#define __NRATRA0_fadvise64_64(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_vserver                 "%d"
#define __NRATRA0_vserver(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_mbind                   "%d"
#define __NRATRA0_mbind(TODO_PROTOTYPE)   , TODO_PROTOTYPE
#define __NRATRF0_get_mempolicy           "%d"
#define __NRATRA0_get_mempolicy(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_set_mempolicy           "%d"
#define __NRATRA0_set_mempolicy(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_mq_open                 "%q"
#define __NRATRA0_mq_open(name, oflags, mode) , (validate_readable_opt(name,1),name)
#define __NRATRF1_mq_open                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA1_mq_open(name, oflags, mode) , (uintptr_t)(oflags), (oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
                                              , ((oflags) & O_RDWR) && ((oflags) & (O_WRONLY)) ? "|" : "", (oflags) & O_RDWR ? "O_RDWR" : "" \
                                              , ((oflags) & O_CREAT) && ((oflags) & (O_WRONLY | O_RDWR)) ? "|" : "", (oflags) & O_CREAT ? "O_CREAT" : "" \
                                              , ((oflags) & O_EXCL) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT)) ? "|" : "", (oflags) & O_EXCL ? "O_EXCL" : "" \
                                              , ((oflags) & O_NOCTTY) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL)) ? "|" : "", (oflags) & O_NOCTTY ? "O_NOCTTY" : "" \
                                              , ((oflags) & O_TRUNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY)) ? "|" : "", (oflags) & O_TRUNC ? "O_TRUNC" : "" \
                                              , ((oflags) & O_APPEND) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC)) ? "|" : "", (oflags) & O_APPEND ? "O_APPEND" : "" \
                                              , ((oflags) & O_NONBLOCK) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND)) ? "|" : "", (oflags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                              , ((oflags) & O_SYNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK)) ? "|" : "", (oflags) & O_SYNC ? "O_SYNC" : "" \
                                              , ((oflags) & O_DSYNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC)) ? "|" : "", (oflags) & O_DSYNC ? "O_DSYNC" : "" \
                                              , ((oflags) & O_ASYNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC)) ? "|" : "", (oflags) & O_ASYNC ? "O_ASYNC" : "" \
                                              , ((oflags) & O_DIRECT) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC)) ? "|" : "", (oflags) & O_DIRECT ? "O_DIRECT" : "" \
                                              , ((oflags) & O_LARGEFILE) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT)) ? "|" : "", (oflags) & O_LARGEFILE ? "O_LARGEFILE" : "" \
                                              , ((oflags) & O_DIRECTORY) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE)) ? "|" : "", (oflags) & O_DIRECTORY ? "O_DIRECTORY" : "" \
                                              , ((oflags) & O_NOFOLLOW) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY)) ? "|" : "", (oflags) & O_NOFOLLOW ? "O_NOFOLLOW" : "" \
                                              , ((oflags) & O_NOATIME) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW)) ? "|" : "", (oflags) & O_NOATIME ? "O_NOATIME" : "" \
                                              , ((oflags) & O_CLOEXEC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME)) ? "|" : "", (oflags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                              , ((oflags) & O_CLOFORK) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC)) ? "|" : "", (oflags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                              , ((oflags) & O_PATH) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK)) ? "|" : "", (oflags) & O_PATH ? "O_PATH" : "" \
                                              , ((oflags) & 0x0400000) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH)) ? "|" : "", (oflags) & 0x0400000 ? "O_TMPFILE" : "" \
                                              , ((oflags) & O_SYMLINK) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | 0x0400000)) ? "|" : "", (oflags) & O_SYMLINK ? "O_SYMLINK" : "" \
                                              , ((oflags) & O_DOSPATH) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | 0x0400000 | O_SYMLINK)) ? "|" : "", (oflags) & O_DOSPATH ? "O_DOSPATH" : ""
#define __NRATRF2_mq_open                 "%#" PRIoSIZ
#define __NRATRA2_mq_open(name, oflags, mode) , (uintptr_t)(mode)
#define __NRATRF0_mq_unlink               "%q"
#define __NRATRA0_mq_unlink(name)         , (validate_readable_opt(name,1),name)
#define __NRATRF0_mq_timedsend            "%d"
#define __NRATRA0_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , (int)(mqdes)
#define __NRATRF1_mq_timedsend            "%q"
#define __NRATRA1_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , (validate_readable_opt(msg_ptr,1),msg_ptr)
#define __NRATRF2_mq_timedsend            "%" PRIuSIZ
#define __NRATRA2_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , msg_len
#define __NRATRF3_mq_timedsend            "%" PRIu32
#define __NRATRA3_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , msg_prio
#define __NRATRF4_mq_timedsend            "%p"
#define __NRATRA4_mq_timedsend(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , abs_timeout
#define __NRATRF0_mq_timedreceive         "%d"
#define __NRATRA0_mq_timedreceive(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , (int)(mqdes)
#define __NRATRF1_mq_timedreceive         "%p"
#define __NRATRA1_mq_timedreceive(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , msg_ptr
#define __NRATRF2_mq_timedreceive         "%" PRIuSIZ
#define __NRATRA2_mq_timedreceive(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , msg_len
#define __NRATRF3_mq_timedreceive         "%p"
#define __NRATRA3_mq_timedreceive(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , pmsg_prio
#define __NRATRF4_mq_timedreceive         "%p"
#define __NRATRA4_mq_timedreceive(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , abs_timeout
#define __NRATRF0_mq_notify               "%d"
#define __NRATRA0_mq_notify(mqdes, notification) , (int)(mqdes)
#define __NRATRF1_mq_notify               "%p"
#define __NRATRA1_mq_notify(mqdes, notification) , notification
#define __NRATRF0_mq_getsetattr           "%d"
#define __NRATRA0_mq_getsetattr(mqdes, newattr, oldattr) , (int)(mqdes)
#define __NRATRF1_mq_getsetattr           "%p"
#define __NRATRA1_mq_getsetattr(mqdes, newattr, oldattr) , newattr
#define __NRATRF2_mq_getsetattr           "%p"
#define __NRATRA2_mq_getsetattr(mqdes, newattr, oldattr) , oldattr
#define __NRATRF0_kexec_load              "%d"
#define __NRATRA0_kexec_load(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_waitid                  "%#Ix=%s"
#define __NRATRA0_waitid(idtype, id, infop, options, ru) , (idtype), (idtype) == P_ALL ? "P_ALL" : (idtype) == P_PID ? "P_PID" : (idtype) == P_PGID ? "P_PGID" : "?"
#define __NRATRF1_waitid                  "%" PRIuSIZ
#define __NRATRA1_waitid(idtype, id, infop, options, ru) , (uintptr_t)(id)
#define __NRATRF2_waitid                  "%p"
#define __NRATRA2_waitid(idtype, id, infop, options, ru) , infop
#define __NRATRF3_waitid                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_waitid(idtype, id, infop, options, ru) , (uintptr_t)(options), (options) & WEXITED ? "WEXITED" : "" \
                                                         , ((options) & WSTOPPED) && ((options) & (WEXITED)) ? "|" : "", (options) & WSTOPPED ? "WSTOPPED" : "" \
                                                         , ((options) & WCONTINUED) && ((options) & (WEXITED | WSTOPPED)) ? "|" : "", (options) & WCONTINUED ? "WCONTINUED" : "" \
                                                         , ((options) & WNOHANG) && ((options) & (WEXITED | WSTOPPED | WCONTINUED)) ? "|" : "", (options) & WNOHANG ? "WNOHANG" : "" \
                                                         , ((options) & WNOWAIT) && ((options) & (WEXITED | WSTOPPED | WCONTINUED | WNOHANG)) ? "|" : "", (options) & WNOWAIT ? "WNOWAIT" : ""
#define __NRATRF4_waitid                  "%p"
#define __NRATRA4_waitid(idtype, id, infop, options, ru) , ru
#define __NRATRF0_add_key                 "%d"
#define __NRATRA0_add_key(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_request_key             "%d"
#define __NRATRA0_request_key(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_keyctl                  "%d"
#define __NRATRA0_keyctl(TODO_PROTOTYPE)  , TODO_PROTOTYPE
#define __NRATRF0_ioprio_set              "%#" PRIxSIZ
#define __NRATRA0_ioprio_set(which, who, ioprio) , (uintptr_t)(which)
#define __NRATRF1_ioprio_set              "%#" PRIxSIZ
#define __NRATRA1_ioprio_set(which, who, ioprio) , (uintptr_t)(who)
#define __NRATRF2_ioprio_set              "%#" PRIxSIZ
#define __NRATRA2_ioprio_set(which, who, ioprio) , (uintptr_t)(ioprio)
#define __NRATRF0_ioprio_get              "%#" PRIxSIZ
#define __NRATRA0_ioprio_get(which, who)  , (uintptr_t)(which)
#define __NRATRF1_ioprio_get              "%#" PRIxSIZ
#define __NRATRA1_ioprio_get(which, who)  , (uintptr_t)(who)
#define __NRATRF0_inotify_init            "%d"
#define __NRATRA0_inotify_init(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_inotify_add_watch       "%d"
#define __NRATRA0_inotify_add_watch(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_inotify_rm_watch        "%d"
#define __NRATRA0_inotify_rm_watch(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_migrate_pages           "%d"
#define __NRATRA0_migrate_pages(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_openat                  "%d"
#define __NRATRA0_openat(dirfd, filename, oflags, mode) , (int)(dirfd)
#define __NRATRF1_openat                  "%q"
#define __NRATRA1_openat(dirfd, filename, oflags, mode) , (validate_readable_opt(filename,1),filename)
#define __NRATRF2_openat                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_openat(dirfd, filename, oflags, mode) , (uintptr_t)(oflags), (oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
                                                        , ((oflags) & O_RDWR) && ((oflags) & (O_WRONLY)) ? "|" : "", (oflags) & O_RDWR ? "O_RDWR" : "" \
                                                        , ((oflags) & O_CREAT) && ((oflags) & (O_WRONLY | O_RDWR)) ? "|" : "", (oflags) & O_CREAT ? "O_CREAT" : "" \
                                                        , ((oflags) & O_EXCL) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT)) ? "|" : "", (oflags) & O_EXCL ? "O_EXCL" : "" \
                                                        , ((oflags) & O_NOCTTY) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL)) ? "|" : "", (oflags) & O_NOCTTY ? "O_NOCTTY" : "" \
                                                        , ((oflags) & O_TRUNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY)) ? "|" : "", (oflags) & O_TRUNC ? "O_TRUNC" : "" \
                                                        , ((oflags) & O_APPEND) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC)) ? "|" : "", (oflags) & O_APPEND ? "O_APPEND" : "" \
                                                        , ((oflags) & O_NONBLOCK) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND)) ? "|" : "", (oflags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                                        , ((oflags) & O_SYNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK)) ? "|" : "", (oflags) & O_SYNC ? "O_SYNC" : "" \
                                                        , ((oflags) & O_DSYNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC)) ? "|" : "", (oflags) & O_DSYNC ? "O_DSYNC" : "" \
                                                        , ((oflags) & O_ASYNC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC)) ? "|" : "", (oflags) & O_ASYNC ? "O_ASYNC" : "" \
                                                        , ((oflags) & O_DIRECT) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC)) ? "|" : "", (oflags) & O_DIRECT ? "O_DIRECT" : "" \
                                                        , ((oflags) & O_LARGEFILE) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT)) ? "|" : "", (oflags) & O_LARGEFILE ? "O_LARGEFILE" : "" \
                                                        , ((oflags) & O_DIRECTORY) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE)) ? "|" : "", (oflags) & O_DIRECTORY ? "O_DIRECTORY" : "" \
                                                        , ((oflags) & O_NOFOLLOW) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY)) ? "|" : "", (oflags) & O_NOFOLLOW ? "O_NOFOLLOW" : "" \
                                                        , ((oflags) & O_NOATIME) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW)) ? "|" : "", (oflags) & O_NOATIME ? "O_NOATIME" : "" \
                                                        , ((oflags) & O_CLOEXEC) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME)) ? "|" : "", (oflags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                                        , ((oflags) & O_CLOFORK) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC)) ? "|" : "", (oflags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                                        , ((oflags) & O_PATH) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK)) ? "|" : "", (oflags) & O_PATH ? "O_PATH" : "" \
                                                        , ((oflags) & 0x0400000) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH)) ? "|" : "", (oflags) & 0x0400000 ? "O_TMPFILE" : "" \
                                                        , ((oflags) & O_SYMLINK) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | 0x0400000)) ? "|" : "", (oflags) & O_SYMLINK ? "O_SYMLINK" : "" \
                                                        , ((oflags) & O_DOSPATH) && ((oflags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | 0x0400000 | O_SYMLINK)) ? "|" : "", (oflags) & O_DOSPATH ? "O_DOSPATH" : ""
#define __NRATRF3_openat                  "%#" PRIoSIZ
#define __NRATRA3_openat(dirfd, filename, oflags, mode) , (uintptr_t)(mode)
#define __NRATRF0_mkdirat                 "%d"
#define __NRATRA0_mkdirat(dirfd, pathname, mode) , (int)(dirfd)
#define __NRATRF1_mkdirat                 "%q"
#define __NRATRA1_mkdirat(dirfd, pathname, mode) , (validate_readable_opt(pathname,1),pathname)
#define __NRATRF2_mkdirat                 "%#" PRIoSIZ
#define __NRATRA2_mkdirat(dirfd, pathname, mode) , (uintptr_t)(mode)
#define __NRATRF0_mknodat                 "%d"
#define __NRATRA0_mknodat(dirfd, nodename, mode, dev) , (int)(dirfd)
#define __NRATRF1_mknodat                 "%q"
#define __NRATRA1_mknodat(dirfd, nodename, mode, dev) , (validate_readable_opt(nodename,1),nodename)
#define __NRATRF2_mknodat                 "%#" PRIoSIZ
#define __NRATRA2_mknodat(dirfd, nodename, mode, dev) , (uintptr_t)(mode)
#define __NRATRF3_mknodat                 "%.2x:%.2x"
#define __NRATRA3_mknodat(dirfd, nodename, mode, dev) , (unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NRATRF0_fchownat                "%d"
#define __NRATRA0_fchownat(dirfd, filename, owner, group, flags) , (int)(dirfd)
#define __NRATRF1_fchownat                "%q"
#define __NRATRA1_fchownat(dirfd, filename, owner, group, flags) , (validate_readable_opt(filename,1),filename)
#define __NRATRF2_fchownat                "%" PRIu32
#define __NRATRA2_fchownat(dirfd, filename, owner, group, flags) , (uint32_t)(owner)
#define __NRATRF3_fchownat                "%" PRIu32
#define __NRATRA3_fchownat(dirfd, filename, owner, group, flags) , (uint32_t)(group)
#define __NRATRF4_fchownat                "%#" PRIxSIZ "=%s%s%s"
#define __NRATRA4_fchownat(dirfd, filename, owner, group, flags) , (uintptr_t)(flags), (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                 , ((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_futimesat               "%d"
#define __NRATRA0_futimesat(dirfd, filename, times) , (int)(dirfd)
#define __NRATRF1_futimesat               "%p"
#define __NRATRA1_futimesat(dirfd, filename, times) , filename
#define __NRATRF2_futimesat               "%p"
#define __NRATRA2_futimesat(dirfd, filename, times) , times
#define __NRATRF0_linux_fstatat64         "%d"
#define __NRATRA0_linux_fstatat64(dirfd, filename, statbuf, flags) , (int)(dirfd)
#define __NRATRF1_linux_fstatat64         "%q"
#define __NRATRA1_linux_fstatat64(dirfd, filename, statbuf, flags) , (validate_readable_opt(filename,1),filename)
#define __NRATRF2_linux_fstatat64         "%p"
#define __NRATRA2_linux_fstatat64(dirfd, filename, statbuf, flags) , statbuf
#define __NRATRF3_linux_fstatat64         "%#" PRIxSIZ "=%s%s%s"
#define __NRATRA3_linux_fstatat64(dirfd, filename, statbuf, flags) , (uintptr_t)(flags), (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                   , ((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_unlinkat                "%d"
#define __NRATRA0_unlinkat(dirfd, name, flags) , (int)(dirfd)
#define __NRATRF1_unlinkat                "%q"
#define __NRATRA1_unlinkat(dirfd, name, flags) , (validate_readable_opt(name,1),name)
#define __NRATRF2_unlinkat                "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA2_unlinkat(dirfd, name, flags) , (uintptr_t)(flags), (flags) & AT_REMOVEDIR ? "AT_REMOVEDIR" : "" \
                                               , ((flags) & AT_REMOVEREG) && ((flags) & (AT_REMOVEDIR)) ? "|" : "", (flags) & AT_REMOVEREG ? "AT_REMOVEREG" : "" \
                                               , ((flags) & AT_DOSPATH) && ((flags) & (AT_REMOVEDIR | AT_REMOVEREG)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_renameat                "%d"
#define __NRATRA0_renameat(oldfd, oldname, newfd, newname_or_path) , (int)(oldfd)
#define __NRATRF1_renameat                "%q"
#define __NRATRA1_renameat(oldfd, oldname, newfd, newname_or_path) , (validate_readable_opt(oldname,1),oldname)
#define __NRATRF2_renameat                "%d"
#define __NRATRA2_renameat(oldfd, oldname, newfd, newname_or_path) , (int)(newfd)
#define __NRATRF3_renameat                "%q"
#define __NRATRA3_renameat(oldfd, oldname, newfd, newname_or_path) , (validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NRATRF0_linkat                  "%d"
#define __NRATRA0_linkat(fromfd, existing_file, tofd, target_path, flags) , (int)(fromfd)
#define __NRATRF1_linkat                  "%q"
#define __NRATRA1_linkat(fromfd, existing_file, tofd, target_path, flags) , (validate_readable_opt(existing_file,1),existing_file)
#define __NRATRF2_linkat                  "%d"
#define __NRATRA2_linkat(fromfd, existing_file, tofd, target_path, flags) , (int)(tofd)
#define __NRATRF3_linkat                  "%q"
#define __NRATRA3_linkat(fromfd, existing_file, tofd, target_path, flags) , (validate_readable_opt(target_path,1),target_path)
#define __NRATRF4_linkat                  "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA4_linkat(fromfd, existing_file, tofd, target_path, flags) , (uintptr_t)(flags), (flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                                          , ((flags) & AT_SYMLINK_FOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "", (flags) & AT_SYMLINK_FOLLOW ? "AT_SYMLINK_FOLLOW" : "" \
                                                                          , ((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH | AT_SYMLINK_FOLLOW)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_symlinkat               "%q"
#define __NRATRA0_symlinkat(link_text, tofd, target_path) , (validate_readable_opt(link_text,1),link_text)
#define __NRATRF1_symlinkat               "%d"
#define __NRATRA1_symlinkat(link_text, tofd, target_path) , (int)(tofd)
#define __NRATRF2_symlinkat               "%q"
#define __NRATRA2_symlinkat(link_text, tofd, target_path) , (validate_readable_opt(target_path,1),target_path)
#define __NRATRF0_readlinkat              "%d"
#define __NRATRA0_readlinkat(dirfd, path, buf, buflen) , (int)(dirfd)
#define __NRATRF1_readlinkat              "%q"
#define __NRATRA1_readlinkat(dirfd, path, buf, buflen) , (validate_readable_opt(path,1),path)
#define __NRATRF2_readlinkat              "%p"
#define __NRATRA2_readlinkat(dirfd, path, buf, buflen) , buf
#define __NRATRF3_readlinkat              "%" PRIuSIZ
#define __NRATRA3_readlinkat(dirfd, path, buf, buflen) , buflen
#define __NRATRF0_fchmodat                "%d"
#define __NRATRA0_fchmodat(dirfd, filename, mode, flags) , (int)(dirfd)
#define __NRATRF1_fchmodat                "%q"
#define __NRATRA1_fchmodat(dirfd, filename, mode, flags) , (validate_readable_opt(filename,1),filename)
#define __NRATRF2_fchmodat                "%#" PRIoSIZ
#define __NRATRA2_fchmodat(dirfd, filename, mode, flags) , (uintptr_t)(mode)
#define __NRATRF3_fchmodat                "%#" PRIxSIZ "=%s%s%s"
#define __NRATRA3_fchmodat(dirfd, filename, mode, flags) , (uintptr_t)(flags), (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                         , ((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_faccessat               "%d"
#define __NRATRA0_faccessat(dirfd, filename, type, flags) , (int)(dirfd)
#define __NRATRF1_faccessat               "%q"
#define __NRATRA1_faccessat(dirfd, filename, type, flags) , (validate_readable_opt(filename,1),filename)
#define __NRATRF2_faccessat               "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA2_faccessat(dirfd, filename, type, flags) , (uintptr_t)(type), (type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                                          , ((type) & W_OK) && ((type) & (R_OK)) ? "|" : "", (type) & W_OK ? "W_OK" : "" \
                                                          , ((type) & X_OK) && ((type) & (R_OK | W_OK)) ? "|" : "", (type) & X_OK ? "X_OK" : ""
#define __NRATRF3_faccessat               "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA3_faccessat(dirfd, filename, type, flags) , (uintptr_t)(flags), (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                          , ((flags) & AT_EACCESS) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_EACCESS ? "AT_EACCESS" : "" \
                                                          , ((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW | AT_EACCESS)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_pselect6                "%" PRIuSIZ
#define __NRATRA0_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , nfds
#define __NRATRF1_pselect6                "%p"
#define __NRATRA1_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , readfds
#define __NRATRF2_pselect6                "%p"
#define __NRATRA2_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , writefds
#define __NRATRF3_pselect6                "%p"
#define __NRATRA3_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , exceptfds
#define __NRATRF4_pselect6                "%p"
#define __NRATRA4_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , timeout
#define __NRATRF5_pselect6                "%p"
#define __NRATRA5_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , sigmask_sigset_and_len
#define __NRATRF0_ppoll                   "%p"
#define __NRATRA0_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) , fds
#define __NRATRF1_ppoll                   "%" PRIuSIZ
#define __NRATRA1_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) , nfds
#define __NRATRF2_ppoll                   "%p"
#define __NRATRA2_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) , timeout_ts
#define __NRATRF3_ppoll                   "%p"
#define __NRATRA3_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) , sigmask
#define __NRATRF4_ppoll                   "%" PRIuSIZ
#define __NRATRA4_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) , sigsetsize
#define __NRATRF0_unshare                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA0_unshare(flags)          , (uintptr_t)(flags), (flags) & CLONE_VM ? "CLONE_VM" : "" \
                                          , ((flags) & CLONE_FS) && ((flags) & (CLONE_VM)) ? "|" : "", (flags) & CLONE_FS ? "CLONE_FS" : "" \
                                          , ((flags) & CLONE_FILES) && ((flags) & (CLONE_VM | CLONE_FS)) ? "|" : "", (flags) & CLONE_FILES ? "CLONE_FILES" : "" \
                                          , ((flags) & CLONE_SIGHAND) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES)) ? "|" : "", (flags) & CLONE_SIGHAND ? "CLONE_SIGHAND" : "" \
                                          , ((flags) & CLONE_PTRACE) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND)) ? "|" : "", (flags) & CLONE_PTRACE ? "CLONE_PTRACE" : "" \
                                          , ((flags) & CLONE_VFORK) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE)) ? "|" : "", (flags) & CLONE_VFORK ? "CLONE_VFORK" : "" \
                                          , ((flags) & CLONE_PARENT) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK)) ? "|" : "", (flags) & CLONE_PARENT ? "CLONE_PARENT" : "" \
                                          , ((flags) & CLONE_THREAD) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT)) ? "|" : "", (flags) & CLONE_THREAD ? "CLONE_THREAD" : "" \
                                          , ((flags) & CLONE_NEWNS) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD)) ? "|" : "", (flags) & CLONE_NEWNS ? "CLONE_NEWNS" : "" \
                                          , ((flags) & CLONE_SYSVSEM) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS)) ? "|" : "", (flags) & CLONE_SYSVSEM ? "CLONE_SYSVSEM" : "" \
                                          , ((flags) & CLONE_SETTLS) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM)) ? "|" : "", (flags) & CLONE_SETTLS ? "CLONE_SETTLS" : "" \
                                          , ((flags) & CLONE_PARENT_SETTID) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS)) ? "|" : "", (flags) & CLONE_PARENT_SETTID ? "CLONE_PARENT_SETTID" : "" \
                                          , ((flags) & CLONE_CHILD_CLEARTID) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID)) ? "|" : "", (flags) & CLONE_CHILD_CLEARTID ? "CLONE_CHILD_CLEARTID" : "" \
                                          , ((flags) & CLONE_DETACHED) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID)) ? "|" : "", (flags) & CLONE_DETACHED ? "CLONE_DETACHED" : "" \
                                          , ((flags) & CLONE_UNTRACED) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED)) ? "|" : "", (flags) & CLONE_UNTRACED ? "CLONE_UNTRACED" : "" \
                                          , ((flags) & CLONE_CHILD_SETTID) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED)) ? "|" : "", (flags) & CLONE_CHILD_SETTID ? "CLONE_CHILD_SETTID" : "" \
                                          , ((flags) & CLONE_NEWUTS) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID)) ? "|" : "", (flags) & CLONE_NEWUTS ? "CLONE_NEWUTS" : "" \
                                          , ((flags) & CLONE_NEWIPC) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS)) ? "|" : "", (flags) & CLONE_NEWIPC ? "CLONE_NEWIPC" : "" \
                                          , ((flags) & CLONE_NEWUSER) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS | CLONE_NEWIPC)) ? "|" : "", (flags) & CLONE_NEWUSER ? "CLONE_NEWUSER" : "" \
                                          , ((flags) & CLONE_NEWPID) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWUSER)) ? "|" : "", (flags) & CLONE_NEWPID ? "CLONE_NEWPID" : "" \
                                          , ((flags) & CLONE_NEWNET) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWUSER | CLONE_NEWPID)) ? "|" : "", (flags) & CLONE_NEWNET ? "CLONE_NEWNET" : "" \
                                          , ((flags) & CLONE_IO) && ((flags) & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_PTRACE | CLONE_VFORK | CLONE_PARENT | CLONE_THREAD | CLONE_NEWNS | CLONE_SYSVSEM | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED | CLONE_UNTRACED | CLONE_CHILD_SETTID | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWUSER | CLONE_NEWPID | CLONE_NEWNET)) ? "|" : "", (flags) & CLONE_IO ? "CLONE_IO" : ""
#define __NRATRF0_set_robust_list         "%d"
#define __NRATRA0_set_robust_list(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_get_robust_list         "%d"
#define __NRATRA0_get_robust_list(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_splice                  "%d"
#define __NRATRA0_splice(fdin, offin, fdout, offout, length, flags) , (int)(fdin)
#define __NRATRF1_splice                  "%p"
#define __NRATRA1_splice(fdin, offin, fdout, offout, length, flags) , offin
#define __NRATRF2_splice                  "%d"
#define __NRATRA2_splice(fdin, offin, fdout, offout, length, flags) , (int)(fdout)
#define __NRATRF3_splice                  "%p"
#define __NRATRA3_splice(fdin, offin, fdout, offout, length, flags) , offout
#define __NRATRF4_splice                  "%" PRIuSIZ
#define __NRATRA4_splice(fdin, offin, fdout, offout, length, flags) , length
#define __NRATRF5_splice                  "%#" PRIxSIZ
#define __NRATRA5_splice(fdin, offin, fdout, offout, length, flags) , (uintptr_t)(flags)
#define __NRATRF0_sync_file_range         "%d"
#define __NRATRA0_sync_file_range(fd, offset, count, flags) , (int)(fd)
#define __NRATRF1_sync_file_range         "%" PRIu64
#define __NRATRA1_sync_file_range(fd, offset, count, flags) , offset
#define __NRATRF2_sync_file_range         "%" PRIu64
#define __NRATRA2_sync_file_range(fd, offset, count, flags) , count
#define __NRATRF3_sync_file_range         "%#" PRIxSIZ
#define __NRATRA3_sync_file_range(fd, offset, count, flags) , (uintptr_t)(flags)
#define __NRATRF0_tee                     "%d"
#define __NRATRA0_tee(fdin, fdout, length, flags) , (int)(fdin)
#define __NRATRF1_tee                     "%d"
#define __NRATRA1_tee(fdin, fdout, length, flags) , (int)(fdout)
#define __NRATRF2_tee                     "%" PRIuSIZ
#define __NRATRA2_tee(fdin, fdout, length, flags) , length
#define __NRATRF3_tee                     "%#" PRIxSIZ
#define __NRATRA3_tee(fdin, fdout, length, flags) , (uintptr_t)(flags)
#define __NRATRF0_vmsplice                "%d"
#define __NRATRA0_vmsplice(fdout, iov, count, flags) , (int)(fdout)
#define __NRATRF1_vmsplice                "%p"
#define __NRATRA1_vmsplice(fdout, iov, count, flags) , iov
#define __NRATRF2_vmsplice                "%" PRIuSIZ
#define __NRATRA2_vmsplice(fdout, iov, count, flags) , count
#define __NRATRF3_vmsplice                "%#" PRIxSIZ
#define __NRATRA3_vmsplice(fdout, iov, count, flags) , (uintptr_t)(flags)
#define __NRATRF0_move_pages              "%d"
#define __NRATRA0_move_pages(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_getcpu                  "%p"
#define __NRATRA0_getcpu(cpu, node, tcache) , cpu
#define __NRATRF1_getcpu                  "%p"
#define __NRATRA1_getcpu(cpu, node, tcache) , node
#define __NRATRF2_getcpu                  "%p"
#define __NRATRA2_getcpu(cpu, node, tcache) , tcache
#define __NRATRF0_epoll_pwait             "%d"
#define __NRATRA0_epoll_pwait(epfd, events, maxevents, timeout, ss) , (int)(epfd)
#define __NRATRF1_epoll_pwait             "%p"
#define __NRATRA1_epoll_pwait(epfd, events, maxevents, timeout, ss) , events
#define __NRATRF2_epoll_pwait             "%#" PRIxSIZ
#define __NRATRA2_epoll_pwait(epfd, events, maxevents, timeout, ss) , (uintptr_t)(maxevents)
#define __NRATRF3_epoll_pwait             "%" PRIdSIZ
#define __NRATRA3_epoll_pwait(epfd, events, maxevents, timeout, ss) , (intptr_t)(timeout)
#define __NRATRF4_epoll_pwait             "%p"
#define __NRATRA4_epoll_pwait(epfd, events, maxevents, timeout, ss) , ss
#define __NRATRF0_utimensat               "%d"
#define __NRATRA0_utimensat(dirfd, filename, times, flags) , (int)(dirfd)
#define __NRATRF1_utimensat               "%q"
#define __NRATRA1_utimensat(dirfd, filename, times, flags) , (validate_readable_opt(filename,1),filename)
#define __NRATRF2_utimensat               "%p"
#define __NRATRA2_utimensat(dirfd, filename, times, flags) , times
#define __NRATRF3_utimensat               "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA3_utimensat(dirfd, filename, times, flags) , (uintptr_t)(flags), (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                           , ((flags) & AT_CHANGE_CTIME) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_CHANGE_CTIME ? "AT_CHANGE_CTIME" : "" \
                                                           , ((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_signalfd                "%d"
#define __NRATRA0_signalfd(fd, sigmask, sigsetsize) , (int)(fd)
#define __NRATRF1_signalfd                "%p"
#define __NRATRA1_signalfd(fd, sigmask, sigsetsize) , sigmask
#define __NRATRF2_signalfd                "%" PRIuSIZ
#define __NRATRA2_signalfd(fd, sigmask, sigsetsize) , sigsetsize
#define __NRATRF0_timerfd_create          "%#" PRIxSIZ
#define __NRATRA0_timerfd_create(clock_id, flags) , (uintptr_t)(clock_id)
#define __NRATRF1_timerfd_create          "%#" PRIxSIZ
#define __NRATRA1_timerfd_create(clock_id, flags) , (uintptr_t)(flags)
#define __NRATRF0_eventfd                 "%#" PRIxSIZ
#define __NRATRA0_eventfd(initval)        , (uintptr_t)(initval)
#define __NRATRF0_fallocate               "%d"
#define __NRATRA0_fallocate(fd, mode, offset, length) , (int)(fd)
#define __NRATRF1_fallocate               "%#" PRIxSIZ
#define __NRATRA1_fallocate(fd, mode, offset, length) , (uintptr_t)(mode)
#define __NRATRF2_fallocate               "%#" PRIxSIZ
#define __NRATRA2_fallocate(fd, mode, offset, length) , (uintptr_t)(offset)
#define __NRATRF3_fallocate               "%#" PRIxSIZ
#define __NRATRA3_fallocate(fd, mode, offset, length) , (uintptr_t)(length)
#define __NRATRF0_timerfd_settime         "%d"
#define __NRATRA0_timerfd_settime(ufd, flags, utmr, otmr) , (int)(ufd)
#define __NRATRF1_timerfd_settime         "%#" PRIxSIZ
#define __NRATRA1_timerfd_settime(ufd, flags, utmr, otmr) , (uintptr_t)(flags)
#define __NRATRF2_timerfd_settime         "%p"
#define __NRATRA2_timerfd_settime(ufd, flags, utmr, otmr) , utmr
#define __NRATRF3_timerfd_settime         "%p"
#define __NRATRA3_timerfd_settime(ufd, flags, utmr, otmr) , otmr
#define __NRATRF0_timerfd_gettime         "%d"
#define __NRATRA0_timerfd_gettime(ufd, otmr) , (int)(ufd)
#define __NRATRF1_timerfd_gettime         "%p"
#define __NRATRA1_timerfd_gettime(ufd, otmr) , otmr
#define __NRATRF0_signalfd4               "%d"
#define __NRATRA0_signalfd4(fd, sigmask, sigsetsize, flags) , (int)(fd)
#define __NRATRF1_signalfd4               "%p"
#define __NRATRA1_signalfd4(fd, sigmask, sigsetsize, flags) , sigmask
#define __NRATRF2_signalfd4               "%" PRIuSIZ
#define __NRATRA2_signalfd4(fd, sigmask, sigsetsize, flags) , sigsetsize
#define __NRATRF3_signalfd4               "%#" PRIxSIZ "=%s%s%s"
#define __NRATRA3_signalfd4(fd, sigmask, sigsetsize, flags) , (uintptr_t)(flags), (flags) & SFD_NONBLOCK ? "SFD_NONBLOCK" : "" \
                                                            , ((flags) & SFD_CLOEXEC) && ((flags) & (SFD_NONBLOCK)) ? "|" : "", (flags) & SFD_CLOEXEC ? "SFD_CLOEXEC" : ""
#define __NRATRF0_eventfd2                "%#" PRIxSIZ
#define __NRATRA0_eventfd2(initval, flags) , (uintptr_t)(initval)
#define __NRATRF1_eventfd2                "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA1_eventfd2(initval, flags) , (uintptr_t)(flags), (flags) & EFD_SEMAPHORE ? "EFD_SEMAPHORE" : "" \
                                           , ((flags) & EFD_NONBLOCK) && ((flags) & (EFD_SEMAPHORE)) ? "|" : "", (flags) & EFD_NONBLOCK ? "EFD_NONBLOCK" : "" \
                                           , ((flags) & EFD_CLOEXEC) && ((flags) & (EFD_SEMAPHORE | EFD_NONBLOCK)) ? "|" : "", (flags) & EFD_CLOEXEC ? "EFD_CLOEXEC" : ""
#define __NRATRF0_epoll_create1           "%#" PRIxSIZ
#define __NRATRA0_epoll_create1(flags)    , (uintptr_t)(flags)
#define __NRATRF0_dup3                    "%d"
#define __NRATRA0_dup3(oldfd, newfd, flags) , (int)(oldfd)
#define __NRATRF1_dup3                    "%d"
#define __NRATRA1_dup3(oldfd, newfd, flags) , (int)(newfd)
#define __NRATRF2_dup3                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_dup3(oldfd, newfd, flags) , (uintptr_t)(flags), (flags) & O_WRONLY ? "O_WRONLY" : (flags) ? "" : "O_RDONLY" \
                                            , ((flags) & O_RDWR) && ((flags) & (O_WRONLY)) ? "|" : "", (flags) & O_RDWR ? "O_RDWR" : "" \
                                            , ((flags) & O_CREAT) && ((flags) & (O_WRONLY | O_RDWR)) ? "|" : "", (flags) & O_CREAT ? "O_CREAT" : "" \
                                            , ((flags) & O_EXCL) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT)) ? "|" : "", (flags) & O_EXCL ? "O_EXCL" : "" \
                                            , ((flags) & O_NOCTTY) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL)) ? "|" : "", (flags) & O_NOCTTY ? "O_NOCTTY" : "" \
                                            , ((flags) & O_TRUNC) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY)) ? "|" : "", (flags) & O_TRUNC ? "O_TRUNC" : "" \
                                            , ((flags) & O_APPEND) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC)) ? "|" : "", (flags) & O_APPEND ? "O_APPEND" : "" \
                                            , ((flags) & O_NONBLOCK) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND)) ? "|" : "", (flags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                            , ((flags) & O_SYNC) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK)) ? "|" : "", (flags) & O_SYNC ? "O_SYNC" : "" \
                                            , ((flags) & O_DSYNC) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC)) ? "|" : "", (flags) & O_DSYNC ? "O_DSYNC" : "" \
                                            , ((flags) & O_ASYNC) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC)) ? "|" : "", (flags) & O_ASYNC ? "O_ASYNC" : "" \
                                            , ((flags) & O_DIRECT) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC)) ? "|" : "", (flags) & O_DIRECT ? "O_DIRECT" : "" \
                                            , ((flags) & O_LARGEFILE) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT)) ? "|" : "", (flags) & O_LARGEFILE ? "O_LARGEFILE" : "" \
                                            , ((flags) & O_DIRECTORY) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE)) ? "|" : "", (flags) & O_DIRECTORY ? "O_DIRECTORY" : "" \
                                            , ((flags) & O_NOFOLLOW) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY)) ? "|" : "", (flags) & O_NOFOLLOW ? "O_NOFOLLOW" : "" \
                                            , ((flags) & O_NOATIME) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW)) ? "|" : "", (flags) & O_NOATIME ? "O_NOATIME" : "" \
                                            , ((flags) & O_CLOEXEC) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME)) ? "|" : "", (flags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                            , ((flags) & O_CLOFORK) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC)) ? "|" : "", (flags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                            , ((flags) & O_PATH) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK)) ? "|" : "", (flags) & O_PATH ? "O_PATH" : "" \
                                            , ((flags) & 0x0400000) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH)) ? "|" : "", (flags) & 0x0400000 ? "O_TMPFILE" : "" \
                                            , ((flags) & O_SYMLINK) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | 0x0400000)) ? "|" : "", (flags) & O_SYMLINK ? "O_SYMLINK" : "" \
                                            , ((flags) & O_DOSPATH) && ((flags) & (O_WRONLY | O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | 0x0400000 | O_SYMLINK)) ? "|" : "", (flags) & O_DOSPATH ? "O_DOSPATH" : ""
#define __NRATRF0_pipe2                   "%p"
#define __NRATRA0_pipe2(pipedes, flags)   , pipedes
#define __NRATRF1_pipe2                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NRATRA1_pipe2(pipedes, flags)   , (uintptr_t)(flags), (flags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                          , ((flags) & O_CLOFORK) && ((flags) & (O_CLOEXEC)) ? "|" : "", (flags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                          , ((flags) & O_NONBLOCK) && ((flags) & (O_CLOEXEC | O_CLOFORK)) ? "|" : "", (flags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                          , ((flags) & O_DIRECT) && ((flags) & (O_CLOEXEC | O_CLOFORK | O_NONBLOCK)) ? "|" : "", (flags) & O_DIRECT ? "O_DIRECT" : ""
#define __NRATRF0_inotify_init1           "%d"
#define __NRATRA0_inotify_init1(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_preadv                  "%d"
#define __NRATRA0_preadv(fd, iovec, count, offset) , (int)(fd)
#define __NRATRF1_preadv                  "%p"
#define __NRATRA1_preadv(fd, iovec, count, offset) , iovec
#define __NRATRF2_preadv                  "%" PRIuSIZ
#define __NRATRA2_preadv(fd, iovec, count, offset) , count
#define __NRATRF3_preadv                  "%" PRIu64
#define __NRATRA3_preadv(fd, iovec, count, offset) , offset
#define __NRATRF0_pwritev                 "%d"
#define __NRATRA0_pwritev(fd, iovec, count, offset) , (int)(fd)
#define __NRATRF1_pwritev                 "%p"
#define __NRATRA1_pwritev(fd, iovec, count, offset) , iovec
#define __NRATRF2_pwritev                 "%" PRIuSIZ
#define __NRATRA2_pwritev(fd, iovec, count, offset) , count
#define __NRATRF3_pwritev                 "%" PRIu64
#define __NRATRA3_pwritev(fd, iovec, count, offset) , offset
#define __NRATRF0_rt_tgsigqueueinfo       "%" PRIdSIZ
#define __NRATRA0_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) , (intptr_t)(tgid)
#define __NRATRF1_rt_tgsigqueueinfo       "%" PRIdSIZ
#define __NRATRA1_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) , (intptr_t)(tid)
#define __NRATRF2_rt_tgsigqueueinfo       "%#" PRIxSIZ
#define __NRATRA2_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) , (uintptr_t)(signo)
#define __NRATRF3_rt_tgsigqueueinfo       "%p"
#define __NRATRA3_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) , uinfo
#define __NRATRF0_perf_event_open         "%d"
#define __NRATRA0_perf_event_open(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_recvmmsg                "%d"
#define __NRATRA0_recvmmsg(sockfd, vmessages, vlen, flags, tmo) , (int)(sockfd)
#define __NRATRF1_recvmmsg                "%p"
#define __NRATRA1_recvmmsg(sockfd, vmessages, vlen, flags, tmo) , vmessages
#define __NRATRF2_recvmmsg                "%" PRIuSIZ
#define __NRATRA2_recvmmsg(sockfd, vmessages, vlen, flags, tmo) , vlen
#define __NRATRF3_recvmmsg                "%#" PRIxSIZ
#define __NRATRA3_recvmmsg(sockfd, vmessages, vlen, flags, tmo) , (uintptr_t)(flags)
#define __NRATRF4_recvmmsg                "%p"
#define __NRATRA4_recvmmsg(sockfd, vmessages, vlen, flags, tmo) , tmo
#define __NRATRF0_fanotify_init           "%d"
#define __NRATRA0_fanotify_init(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_fanotify_mark           "%d"
#define __NRATRA0_fanotify_mark(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_prlimit64               "%" PRIdSIZ
#define __NRATRA0_prlimit64(pid, resource, new_limit, old_limit) , (intptr_t)(pid)
#define __NRATRF1_prlimit64               "%#" PRIxSIZ
#define __NRATRA1_prlimit64(pid, resource, new_limit, old_limit) , (uintptr_t)(resource)
#define __NRATRF2_prlimit64               "%p"
#define __NRATRA2_prlimit64(pid, resource, new_limit, old_limit) , new_limit
#define __NRATRF3_prlimit64               "%p"
#define __NRATRA3_prlimit64(pid, resource, new_limit, old_limit) , old_limit
#define __NRATRF0_name_to_handle_at       "%d"
#define __NRATRA0_name_to_handle_at(dirfd, name, handle, mnt_id, flags) , (int)(dirfd)
#define __NRATRF1_name_to_handle_at       "%q"
#define __NRATRA1_name_to_handle_at(dirfd, name, handle, mnt_id, flags) , (validate_readable_opt(name,1),name)
#define __NRATRF2_name_to_handle_at       "%p"
#define __NRATRA2_name_to_handle_at(dirfd, name, handle, mnt_id, flags) , handle
#define __NRATRF3_name_to_handle_at       "%p"
#define __NRATRA3_name_to_handle_at(dirfd, name, handle, mnt_id, flags) , mnt_id
#define __NRATRF4_name_to_handle_at       "%#" PRIxSIZ
#define __NRATRA4_name_to_handle_at(dirfd, name, handle, mnt_id, flags) , (uintptr_t)(flags)
#define __NRATRF0_open_by_handle_at       "%d"
#define __NRATRA0_open_by_handle_at(mountdirfd, handle, flags) , (int)(mountdirfd)
#define __NRATRF1_open_by_handle_at       "%p"
#define __NRATRA1_open_by_handle_at(mountdirfd, handle, flags) , handle
#define __NRATRF2_open_by_handle_at       "%#" PRIxSIZ
#define __NRATRA2_open_by_handle_at(mountdirfd, handle, flags) , (uintptr_t)(flags)
#define __NRATRF0_clock_adjtime           "%d"
#define __NRATRA0_clock_adjtime(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_syncfs                  "%d"
#define __NRATRA0_syncfs(fd)              , (int)(fd)
#define __NRATRF0_sendmmsg                "%d"
#define __NRATRA0_sendmmsg(sockfd, vmessages, vlen, flags) , (int)(sockfd)
#define __NRATRF1_sendmmsg                "%p"
#define __NRATRA1_sendmmsg(sockfd, vmessages, vlen, flags) , vmessages
#define __NRATRF2_sendmmsg                "%" PRIuSIZ
#define __NRATRA2_sendmmsg(sockfd, vmessages, vlen, flags) , vlen
#define __NRATRF3_sendmmsg                "%#" PRIxSIZ
#define __NRATRA3_sendmmsg(sockfd, vmessages, vlen, flags) , (uintptr_t)(flags)
#define __NRATRF0_setns                   "%d"
#define __NRATRA0_setns(fd, nstype)       , (int)(fd)
#define __NRATRF1_setns                   "%#" PRIxSIZ
#define __NRATRA1_setns(fd, nstype)       , (uintptr_t)(nstype)
#define __NRATRF0_process_vm_readv        "%" PRIdSIZ
#define __NRATRA0_process_vm_readv(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , (intptr_t)(pid)
#define __NRATRF1_process_vm_readv        "%p"
#define __NRATRA1_process_vm_readv(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , local_iov
#define __NRATRF2_process_vm_readv        "%" PRIuSIZ
#define __NRATRA2_process_vm_readv(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , liovcnt
#define __NRATRF3_process_vm_readv        "%p"
#define __NRATRA3_process_vm_readv(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , remote_iov
#define __NRATRF4_process_vm_readv        "%" PRIuSIZ
#define __NRATRA4_process_vm_readv(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , riovcnt
#define __NRATRF5_process_vm_readv        "%#" PRIxSIZ
#define __NRATRA5_process_vm_readv(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , (uintptr_t)(flags)
#define __NRATRF0_process_vm_writev       "%" PRIdSIZ
#define __NRATRA0_process_vm_writev(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , (intptr_t)(pid)
#define __NRATRF1_process_vm_writev       "%p"
#define __NRATRA1_process_vm_writev(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , local_iov
#define __NRATRF2_process_vm_writev       "%" PRIuSIZ
#define __NRATRA2_process_vm_writev(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , liovcnt
#define __NRATRF3_process_vm_writev       "%p"
#define __NRATRA3_process_vm_writev(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , remote_iov
#define __NRATRF4_process_vm_writev       "%" PRIuSIZ
#define __NRATRA4_process_vm_writev(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , riovcnt
#define __NRATRF5_process_vm_writev       "%#" PRIxSIZ
#define __NRATRA5_process_vm_writev(pid, local_iov, liovcnt, remote_iov, riovcnt, flags) , (uintptr_t)(flags)
#define __NRATRF0_kcmp                    "%" PRIdSIZ
#define __NRATRA0_kcmp(pid1, pid2, type, idx1, idx2) , (intptr_t)(pid1)
#define __NRATRF1_kcmp                    "%" PRIdSIZ
#define __NRATRA1_kcmp(pid1, pid2, type, idx1, idx2) , (intptr_t)(pid2)
#define __NRATRF2_kcmp                    "%#" PRIxSIZ
#define __NRATRA2_kcmp(pid1, pid2, type, idx1, idx2) , (uintptr_t)(type)
#define __NRATRF3_kcmp                    "%#" PRIxSIZ
#define __NRATRA3_kcmp(pid1, pid2, type, idx1, idx2) , (uintptr_t)(idx1)
#define __NRATRF4_kcmp                    "%#" PRIxSIZ
#define __NRATRA4_kcmp(pid1, pid2, type, idx1, idx2) , (uintptr_t)(idx2)
#define __NRATRF0_finit_module            "%d"
#define __NRATRA0_finit_module(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_sched_setattr           "%d"
#define __NRATRA0_sched_setattr(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_sched_getattr           "%d"
#define __NRATRA0_sched_getattr(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_renameat2               "%d"
#define __NRATRA0_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) , (int)(olddirfd)
#define __NRATRF1_renameat2               "%q"
#define __NRATRA1_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) , (validate_readable_opt(oldpath,1),oldpath)
#define __NRATRF2_renameat2               "%d"
#define __NRATRA2_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) , (int)(newdirfd)
#define __NRATRF3_renameat2               "%q"
#define __NRATRA3_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) , (validate_readable_opt(newpath,1),newpath)
#define __NRATRF4_renameat2               "%#" PRIxSIZ
#define __NRATRA4_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) , (uintptr_t)(flags)
#define __NRATRF0_seccomp                 "%d"
#define __NRATRA0_seccomp(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_getrandom               "%p"
#define __NRATRA0_getrandom(buf, num_bytes, flags) , buf
#define __NRATRF1_getrandom               "%" PRIuSIZ
#define __NRATRA1_getrandom(buf, num_bytes, flags) , num_bytes
#define __NRATRF2_getrandom               "%#" PRIxSIZ
#define __NRATRA2_getrandom(buf, num_bytes, flags) , (uintptr_t)(flags)
#define __NRATRF0_memfd_create            "%q"
#define __NRATRA0_memfd_create(name, flags) , (validate_readable_opt(name,1),name)
#define __NRATRF1_memfd_create            "%#" PRIxSIZ "=%s%s%s"
#define __NRATRA1_memfd_create(name, flags) , (uintptr_t)(flags), (flags) & MFD_CLOEXEC ? "MFD_CLOEXEC" : "" \
                                            , ((flags) & MFD_ALLOW_SEALING) && ((flags) & (MFD_CLOEXEC)) ? "|" : "", (flags) & MFD_ALLOW_SEALING ? "MFD_ALLOW_SEALING" : ""
#define __NRATRF0_bpf                     "%d"
#define __NRATRA0_bpf(TODO_PROTOTYPE)     , TODO_PROTOTYPE
#define __NRATRF0_execveat                "%d"
#define __NRATRA0_execveat(dirfd, pathname, argv, envp, flags) , (int)(dirfd)
#define __NRATRF1_execveat                "%q"
#define __NRATRA1_execveat(dirfd, pathname, argv, envp, flags) , (validate_readable_opt(pathname,1),pathname)
#define __NRATRF2_execveat                "%p"
#define __NRATRA2_execveat(dirfd, pathname, argv, envp, flags) , argv
#define __NRATRF3_execveat                "%p"
#define __NRATRA3_execveat(dirfd, pathname, argv, envp, flags) , envp
#define __NRATRF4_execveat                "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA4_execveat(dirfd, pathname, argv, envp, flags) , (uintptr_t)(flags), (flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                               , ((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "", (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                               , ((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_socket                  "%#" PRIxSIZ
#define __NRATRA0_socket(domain, type, protocol) , (uintptr_t)(domain)
#define __NRATRF1_socket                  "%#" PRIxSIZ
#define __NRATRA1_socket(domain, type, protocol) , (uintptr_t)(type)
#define __NRATRF2_socket                  "%#" PRIxSIZ
#define __NRATRA2_socket(domain, type, protocol) , (uintptr_t)(protocol)
#define __NRATRF0_socketpair              "%#" PRIxSIZ
#define __NRATRA0_socketpair(domain, type, protocol, fds) , (uintptr_t)(domain)
#define __NRATRF1_socketpair              "%#" PRIxSIZ
#define __NRATRA1_socketpair(domain, type, protocol, fds) , (uintptr_t)(type)
#define __NRATRF2_socketpair              "%#" PRIxSIZ
#define __NRATRA2_socketpair(domain, type, protocol, fds) , (uintptr_t)(protocol)
#define __NRATRF3_socketpair              "%p"
#define __NRATRA3_socketpair(domain, type, protocol, fds) , fds
#define __NRATRF0_bind                    "%d"
#define __NRATRA0_bind(sockfd, addr, addr_len) , (int)(sockfd)
#define __NRATRF1_bind                    "%p"
#define __NRATRA1_bind(sockfd, addr, addr_len) , addr
#define __NRATRF2_bind                    "%" PRIuSIZ
#define __NRATRA2_bind(sockfd, addr, addr_len) , (uintptr_t)(addr_len)
#define __NRATRF0_connect                 "%d"
#define __NRATRA0_connect(sockfd, addr, addr_len) , (int)(sockfd)
#define __NRATRF1_connect                 "%p"
#define __NRATRA1_connect(sockfd, addr, addr_len) , addr
#define __NRATRF2_connect                 "%" PRIuSIZ
#define __NRATRA2_connect(sockfd, addr, addr_len) , (uintptr_t)(addr_len)
#define __NRATRF0_listen                  "%d"
#define __NRATRA0_listen(sockfd, max_backlog) , (int)(sockfd)
#define __NRATRF1_listen                  "%#" PRIxSIZ
#define __NRATRA1_listen(sockfd, max_backlog) , (uintptr_t)(max_backlog)
#define __NRATRF0_accept4                 "%d"
#define __NRATRA0_accept4(sockfd, addr, addr_len, sock_flags) , (int)(sockfd)
#define __NRATRF1_accept4                 "%p"
#define __NRATRA1_accept4(sockfd, addr, addr_len, sock_flags) , addr
#define __NRATRF2_accept4                 "%p"
#define __NRATRA2_accept4(sockfd, addr, addr_len, sock_flags) , addr_len
#define __NRATRF3_accept4                 "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA3_accept4(sockfd, addr, addr_len, sock_flags) , (uintptr_t)(sock_flags), (sock_flags) & SOCK_NONBLOCK ? "SOCK_NONBLOCK" : "" \
                                                              , ((sock_flags) & SOCK_CLOEXEC) && ((sock_flags) & (SOCK_NONBLOCK)) ? "|" : "", (sock_flags) & SOCK_CLOEXEC ? "SOCK_CLOEXEC" : "" \
                                                              , ((sock_flags) & SOCK_CLOFORK) && ((sock_flags) & (SOCK_NONBLOCK | SOCK_CLOEXEC)) ? "|" : "", (sock_flags) & SOCK_CLOFORK ? "SOCK_CLOFORK" : ""
#define __NRATRF0_getsockopt              "%d"
#define __NRATRA0_getsockopt(sockfd, level, optname, optval, optlen) , (int)(sockfd)
#define __NRATRF1_getsockopt              "%#Ix=%s"
#define __NRATRA1_getsockopt(sockfd, level, optname, optval, optlen) , (level), (level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NRATRF2_getsockopt              "%#" PRIxSIZ
#define __NRATRA2_getsockopt(sockfd, level, optname, optval, optlen) , (uintptr_t)(optname)
#define __NRATRF3_getsockopt              "%p"
#define __NRATRA3_getsockopt(sockfd, level, optname, optval, optlen) , optval
#define __NRATRF4_getsockopt              "%p"
#define __NRATRA4_getsockopt(sockfd, level, optname, optval, optlen) , optlen
#define __NRATRF0_setsockopt              "%d"
#define __NRATRA0_setsockopt(sockfd, level, optname, optval, optlen) , (int)(sockfd)
#define __NRATRF1_setsockopt              "%#Ix=%s"
#define __NRATRA1_setsockopt(sockfd, level, optname, optval, optlen) , (level), (level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NRATRF2_setsockopt              "%#" PRIxSIZ
#define __NRATRA2_setsockopt(sockfd, level, optname, optval, optlen) , (uintptr_t)(optname)
#define __NRATRF3_setsockopt              "%p"
#define __NRATRA3_setsockopt(sockfd, level, optname, optval, optlen) , optval
#define __NRATRF4_setsockopt              "%" PRIuSIZ
#define __NRATRA4_setsockopt(sockfd, level, optname, optval, optlen) , (uintptr_t)(optlen)
#define __NRATRF0_getsockname             "%d"
#define __NRATRA0_getsockname(sockfd, addr, addr_len) , (int)(sockfd)
#define __NRATRF1_getsockname             "%p"
#define __NRATRA1_getsockname(sockfd, addr, addr_len) , addr
#define __NRATRF2_getsockname             "%p"
#define __NRATRA2_getsockname(sockfd, addr, addr_len) , addr_len
#define __NRATRF0_getpeername             "%d"
#define __NRATRA0_getpeername(sockfd, addr, addr_len) , (int)(sockfd)
#define __NRATRF1_getpeername             "%p"
#define __NRATRA1_getpeername(sockfd, addr, addr_len) , addr
#define __NRATRF2_getpeername             "%p"
#define __NRATRA2_getpeername(sockfd, addr, addr_len) , addr_len
#define __NRATRF0_sendto                  "%d"
#define __NRATRA0_sendto(sockfd, buf, bufsize, msg_flags, addr, addr_len) , (int)(sockfd)
#define __NRATRF1_sendto                  "%p"
#define __NRATRA1_sendto(sockfd, buf, bufsize, msg_flags, addr, addr_len) , buf
#define __NRATRF2_sendto                  "%" PRIuSIZ
#define __NRATRA2_sendto(sockfd, buf, bufsize, msg_flags, addr, addr_len) , bufsize
#define __NRATRF3_sendto                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_sendto(sockfd, buf, bufsize, msg_flags, addr, addr_len) , (uintptr_t)(msg_flags), (msg_flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                                          , ((msg_flags) & MSG_DONTROUTE) && ((msg_flags) & (MSG_CONFIRM)) ? "|" : "", (msg_flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                                          , ((msg_flags) & MSG_DONTWAIT) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE)) ? "|" : "", (msg_flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                          , ((msg_flags) & MSG_EOR) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT)) ? "|" : "", (msg_flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                                          , ((msg_flags) & MSG_MORE) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR)) ? "|" : "", (msg_flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                                          , ((msg_flags) & MSG_NOSIGNAL) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE)) ? "|" : "", (msg_flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                                          , ((msg_flags) & MSG_OOB) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL)) ? "|" : "", (msg_flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NRATRF4_sendto                  "%p"
#define __NRATRA4_sendto(sockfd, buf, bufsize, msg_flags, addr, addr_len) , addr
#define __NRATRF5_sendto                  "%" PRIuSIZ
#define __NRATRA5_sendto(sockfd, buf, bufsize, msg_flags, addr, addr_len) , (uintptr_t)(addr_len)
#define __NRATRF0_sendmsg                 "%d"
#define __NRATRA0_sendmsg(sockfd, message, msg_flags) , (int)(sockfd)
#define __NRATRF1_sendmsg                 "%p"
#define __NRATRA1_sendmsg(sockfd, message, msg_flags) , message
#define __NRATRF2_sendmsg                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_sendmsg(sockfd, message, msg_flags) , (uintptr_t)(msg_flags), (msg_flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                      , ((msg_flags) & MSG_DONTROUTE) && ((msg_flags) & (MSG_CONFIRM)) ? "|" : "", (msg_flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                      , ((msg_flags) & MSG_DONTWAIT) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE)) ? "|" : "", (msg_flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                      , ((msg_flags) & MSG_EOR) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT)) ? "|" : "", (msg_flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                      , ((msg_flags) & MSG_MORE) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR)) ? "|" : "", (msg_flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                      , ((msg_flags) & MSG_NOSIGNAL) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE)) ? "|" : "", (msg_flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                      , ((msg_flags) & MSG_OOB) && ((msg_flags) & (MSG_CONFIRM | MSG_DONTROUTE | MSG_DONTWAIT | MSG_EOR | MSG_MORE | MSG_NOSIGNAL)) ? "|" : "", (msg_flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NRATRF0_recvfrom                "%d"
#define __NRATRA0_recvfrom(sockfd, buf, bufsize, msg_flags, addr, addr_len) , (int)(sockfd)
#define __NRATRF1_recvfrom                "%p"
#define __NRATRA1_recvfrom(sockfd, buf, bufsize, msg_flags, addr, addr_len) , buf
#define __NRATRF2_recvfrom                "%" PRIuSIZ
#define __NRATRA2_recvfrom(sockfd, buf, bufsize, msg_flags, addr, addr_len) , bufsize
#define __NRATRF3_recvfrom                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_recvfrom(sockfd, buf, bufsize, msg_flags, addr, addr_len) , (uintptr_t)(msg_flags), (msg_flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                            , ((msg_flags) & MSG_ERRQUEUE) && ((msg_flags) & (MSG_DONTWAIT)) ? "|" : "", (msg_flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                                            , ((msg_flags) & MSG_OOB) && ((msg_flags) & (MSG_DONTWAIT | MSG_ERRQUEUE)) ? "|" : "", (msg_flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                                            , ((msg_flags) & MSG_PEEK) && ((msg_flags) & (MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB)) ? "|" : "", (msg_flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                                            , ((msg_flags) & MSG_TRUNC) && ((msg_flags) & (MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB | MSG_PEEK)) ? "|" : "", (msg_flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                                            , ((msg_flags) & MSG_WAITALL) && ((msg_flags) & (MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC)) ? "|" : "", (msg_flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NRATRF4_recvfrom                "%p"
#define __NRATRA4_recvfrom(sockfd, buf, bufsize, msg_flags, addr, addr_len) , addr
#define __NRATRF5_recvfrom                "%p"
#define __NRATRA5_recvfrom(sockfd, buf, bufsize, msg_flags, addr, addr_len) , addr_len
#define __NRATRF0_recvmsg                 "%d"
#define __NRATRA0_recvmsg(sockfd, message, msg_flags) , (int)(sockfd)
#define __NRATRF1_recvmsg                 "%p"
#define __NRATRA1_recvmsg(sockfd, message, msg_flags) , message
#define __NRATRF2_recvmsg                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_recvmsg(sockfd, message, msg_flags) , (uintptr_t)(msg_flags), (msg_flags) & MSG_CMSG_CLOEXEC ? "MSG_CMSG_CLOEXEC" : "" \
                                                      , ((msg_flags) & MSG_CMSG_CLOFORK) && ((msg_flags) & (MSG_CMSG_CLOEXEC)) ? "|" : "", (msg_flags) & MSG_CMSG_CLOFORK ? "MSG_CMSG_CLOFORK" : "" \
                                                      , ((msg_flags) & MSG_DONTWAIT) && ((msg_flags) & (MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK)) ? "|" : "", (msg_flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                      , ((msg_flags) & MSG_ERRQUEUE) && ((msg_flags) & (MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK | MSG_DONTWAIT)) ? "|" : "", (msg_flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                      , ((msg_flags) & MSG_OOB) && ((msg_flags) & (MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK | MSG_DONTWAIT | MSG_ERRQUEUE)) ? "|" : "", (msg_flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                      , ((msg_flags) & MSG_PEEK) && ((msg_flags) & (MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK | MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB)) ? "|" : "", (msg_flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                      , ((msg_flags) & MSG_TRUNC) && ((msg_flags) & (MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK | MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB | MSG_PEEK)) ? "|" : "", (msg_flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                      , ((msg_flags) & MSG_WAITALL) && ((msg_flags) & (MSG_CMSG_CLOEXEC | MSG_CMSG_CLOFORK | MSG_DONTWAIT | MSG_ERRQUEUE | MSG_OOB | MSG_PEEK | MSG_TRUNC)) ? "|" : "", (msg_flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NRATRF0_shutdown                "%d"
#define __NRATRA0_shutdown(sockfd, how)   , (int)(sockfd)
#define __NRATRF1_shutdown                "%#Ix=%s"
#define __NRATRA1_shutdown(sockfd, how)   , (how), (how) == SHUT_RD ? "SHUT_RD" : (how) == SHUT_WR ? "SHUT_WR" : (how) == SHUT_RDWR ? "SHUT_RDWR" : "?"
#define __NRATRF0_userfaultfd             "%d"
#define __NRATRA0_userfaultfd(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_membarrier              "%d"
#define __NRATRA0_membarrier(TODO_PROTOTYPE) , TODO_PROTOTYPE
#define __NRATRF0_mlock2                  "%d"
#define __NRATRA0_mlock2(TODO_PROTOTYPE)  , TODO_PROTOTYPE
#define __NRATRF0_recvmmsg64              "%d"
#define __NRATRA0_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) , (int)(sockfd)
#define __NRATRF1_recvmmsg64              "%p"
#define __NRATRA1_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) , vmessages
#define __NRATRF2_recvmmsg64              "%" PRIuSIZ
#define __NRATRA2_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) , vlen
#define __NRATRF3_recvmmsg64              "%#" PRIxSIZ
#define __NRATRA3_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) , (uintptr_t)(flags)
#define __NRATRF4_recvmmsg64              "%p"
#define __NRATRA4_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) , tmo
#define __NRATRF0_pwritevf                "%d"
#define __NRATRA0_pwritevf(fd, iovec, count, offset, mode) , (int)(fd)
#define __NRATRF1_pwritevf                "%p"
#define __NRATRA1_pwritevf(fd, iovec, count, offset, mode) , iovec
#define __NRATRF2_pwritevf                "%" PRIuSIZ
#define __NRATRA2_pwritevf(fd, iovec, count, offset, mode) , count
#define __NRATRF3_pwritevf                "%" PRIu64
#define __NRATRA3_pwritevf(fd, iovec, count, offset, mode) , offset
#define __NRATRF4_pwritevf                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_pwritevf(fd, iovec, count, offset, mode) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                           , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                           , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                           , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                           , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                           , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                           , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                           , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                           , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_preadvf                 "%d"
#define __NRATRA0_preadvf(fd, iovec, count, offset, mode) , (int)(fd)
#define __NRATRF1_preadvf                 "%p"
#define __NRATRA1_preadvf(fd, iovec, count, offset, mode) , iovec
#define __NRATRF2_preadvf                 "%" PRIuSIZ
#define __NRATRA2_preadvf(fd, iovec, count, offset, mode) , count
#define __NRATRF3_preadvf                 "%" PRIu64
#define __NRATRA3_preadvf(fd, iovec, count, offset, mode) , offset
#define __NRATRF4_preadvf                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_preadvf(fd, iovec, count, offset, mode) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                          , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                          , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                          , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                          , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                          , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                          , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                          , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                          , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_timerfd_gettime64       "%d"
#define __NRATRA0_timerfd_gettime64(ufd, otmr) , (int)(ufd)
#define __NRATRF1_timerfd_gettime64       "%p"
#define __NRATRA1_timerfd_gettime64(ufd, otmr) , otmr
#define __NRATRF0_timerfd_settime64       "%d"
#define __NRATRA0_timerfd_settime64(ufd, flags, utmr, otmr) , (int)(ufd)
#define __NRATRF1_timerfd_settime64       "%#" PRIxSIZ
#define __NRATRA1_timerfd_settime64(ufd, flags, utmr, otmr) , (uintptr_t)(flags)
#define __NRATRF2_timerfd_settime64       "%p"
#define __NRATRA2_timerfd_settime64(ufd, flags, utmr, otmr) , utmr
#define __NRATRF3_timerfd_settime64       "%p"
#define __NRATRA3_timerfd_settime64(ufd, flags, utmr, otmr) , otmr
#define __NRATRF0_fallocate64             "%d"
#define __NRATRA0_fallocate64(fd, mode, offset, length) , (int)(fd)
#define __NRATRF1_fallocate64             "%#" PRIxSIZ
#define __NRATRA1_fallocate64(fd, mode, offset, length) , (uintptr_t)(mode)
#define __NRATRF2_fallocate64             "%" PRIu64
#define __NRATRA2_fallocate64(fd, mode, offset, length) , offset
#define __NRATRF3_fallocate64             "%" PRIu64
#define __NRATRA3_fallocate64(fd, mode, offset, length) , length
#define __NRATRF0_utimensat64             "%d"
#define __NRATRA0_utimensat64(dirfd, filename, times, flags) , (int)(dirfd)
#define __NRATRF1_utimensat64             "%q"
#define __NRATRA1_utimensat64(dirfd, filename, times, flags) , (validate_readable_opt(filename,1),filename)
#define __NRATRF2_utimensat64             "%p"
#define __NRATRA2_utimensat64(dirfd, filename, times, flags) , times
#define __NRATRF3_utimensat64             "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA3_utimensat64(dirfd, filename, times, flags) , (uintptr_t)(flags), (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                             , ((flags) & AT_CHANGE_CTIME) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_CHANGE_CTIME ? "AT_CHANGE_CTIME" : "" \
                                                             , ((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_ppoll64                 "%p"
#define __NRATRA0_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) , fds
#define __NRATRF1_ppoll64                 "%" PRIuSIZ
#define __NRATRA1_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) , nfds
#define __NRATRF2_ppoll64                 "%p"
#define __NRATRA2_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) , timeout_ts
#define __NRATRF3_ppoll64                 "%p"
#define __NRATRA3_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) , sigmask
#define __NRATRF4_ppoll64                 "%" PRIuSIZ
#define __NRATRA4_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) , sigsetsize
#define __NRATRF0_pselect6_64             "%" PRIuSIZ
#define __NRATRA0_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , nfds
#define __NRATRF1_pselect6_64             "%p"
#define __NRATRA1_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , readfds
#define __NRATRF2_pselect6_64             "%p"
#define __NRATRA2_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , writefds
#define __NRATRF3_pselect6_64             "%p"
#define __NRATRA3_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , exceptfds
#define __NRATRF4_pselect6_64             "%p"
#define __NRATRA4_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , timeout
#define __NRATRF5_pselect6_64             "%p"
#define __NRATRA5_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) , sigmask_sigset_and_len
#define __NRATRF0_freadlinkat             "%d"
#define __NRATRA0_freadlinkat(dirfd, path, buf, buflen, flags) , (int)(dirfd)
#define __NRATRF1_freadlinkat             "%q"
#define __NRATRA1_freadlinkat(dirfd, path, buf, buflen, flags) , (validate_readable_opt(path,1),path)
#define __NRATRF2_freadlinkat             "%p"
#define __NRATRA2_freadlinkat(dirfd, path, buf, buflen, flags) , buf
#define __NRATRF3_freadlinkat             "%" PRIuSIZ
#define __NRATRA3_freadlinkat(dirfd, path, buf, buflen, flags) , buflen
#define __NRATRF4_freadlinkat             "%#" PRIxSIZ "=%s%s%s"
#define __NRATRA4_freadlinkat(dirfd, path, buf, buflen, flags) , (uintptr_t)(flags), (flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                               , ((flags) & AT_DOSPATH) && ((flags) & (AT_READLINK_REQSIZE)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_fsymlinkat              "%q"
#define __NRATRA0_fsymlinkat(link_text, tofd, target_path, flags) , (validate_readable_opt(link_text,1),link_text)
#define __NRATRF1_fsymlinkat              "%d"
#define __NRATRA1_fsymlinkat(link_text, tofd, target_path, flags) , (int)(tofd)
#define __NRATRF2_fsymlinkat              "%q"
#define __NRATRA2_fsymlinkat(link_text, tofd, target_path, flags) , (validate_readable_opt(target_path,1),target_path)
#define __NRATRF3_fsymlinkat              "%#" PRIxSIZ "=%s"
#define __NRATRA3_fsymlinkat(link_text, tofd, target_path, flags) , (uintptr_t)(flags), (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_frenameat               "%d"
#define __NRATRA0_frenameat(oldfd, oldname, newfd, newname_or_path, flags) , (int)(oldfd)
#define __NRATRF1_frenameat               "%q"
#define __NRATRA1_frenameat(oldfd, oldname, newfd, newname_or_path, flags) , (validate_readable_opt(oldname,1),oldname)
#define __NRATRF2_frenameat               "%d"
#define __NRATRA2_frenameat(oldfd, oldname, newfd, newname_or_path, flags) , (int)(newfd)
#define __NRATRF3_frenameat               "%q"
#define __NRATRA3_frenameat(oldfd, oldname, newfd, newname_or_path, flags) , (validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NRATRF4_frenameat               "%#" PRIxSIZ "=%s"
#define __NRATRA4_frenameat(oldfd, oldname, newfd, newname_or_path, flags) , (uintptr_t)(flags), (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_kfstatat                "%d"
#define __NRATRA0_kfstatat(dirfd, filename, statbuf, flags) , (int)(dirfd)
#define __NRATRF1_kfstatat                "%q"
#define __NRATRA1_kfstatat(dirfd, filename, statbuf, flags) , (validate_readable_opt(filename,1),filename)
#define __NRATRF2_kfstatat                "%p"
#define __NRATRA2_kfstatat(dirfd, filename, statbuf, flags) , statbuf
#define __NRATRF3_kfstatat                "%#" PRIxSIZ "=%s%s%s"
#define __NRATRA3_kfstatat(dirfd, filename, statbuf, flags) , (uintptr_t)(flags), (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                            , ((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_futimesat64             "%d"
#define __NRATRA0_futimesat64(dirfd, filename, times) , (int)(dirfd)
#define __NRATRF1_futimesat64             "%p"
#define __NRATRA1_futimesat64(dirfd, filename, times) , filename
#define __NRATRF2_futimesat64             "%p"
#define __NRATRA2_futimesat64(dirfd, filename, times) , times
#define __NRATRF0_fmknodat                "%d"
#define __NRATRA0_fmknodat(dirfd, nodename, mode, dev, flags) , (int)(dirfd)
#define __NRATRF1_fmknodat                "%q"
#define __NRATRA1_fmknodat(dirfd, nodename, mode, dev, flags) , (validate_readable_opt(nodename,1),nodename)
#define __NRATRF2_fmknodat                "%#" PRIoSIZ
#define __NRATRA2_fmknodat(dirfd, nodename, mode, dev, flags) , (uintptr_t)(mode)
#define __NRATRF3_fmknodat                "%.2x:%.2x"
#define __NRATRA3_fmknodat(dirfd, nodename, mode, dev, flags) , (unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NRATRF4_fmknodat                "%#" PRIxSIZ "=%s"
#define __NRATRA4_fmknodat(dirfd, nodename, mode, dev, flags) , (uintptr_t)(flags), (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_fmkdirat                "%d"
#define __NRATRA0_fmkdirat(dirfd, pathname, mode, flags) , (int)(dirfd)
#define __NRATRF1_fmkdirat                "%q"
#define __NRATRA1_fmkdirat(dirfd, pathname, mode, flags) , (validate_readable_opt(pathname,1),pathname)
#define __NRATRF2_fmkdirat                "%#" PRIoSIZ
#define __NRATRA2_fmkdirat(dirfd, pathname, mode, flags) , (uintptr_t)(mode)
#define __NRATRF3_fmkdirat                "%#" PRIxSIZ "=%s"
#define __NRATRA3_fmkdirat(dirfd, pathname, mode, flags) , (uintptr_t)(flags), (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_waitid64                "%#Ix=%s"
#define __NRATRA0_waitid64(idtype, id, infop, options, ru) , (idtype), (idtype) == P_ALL ? "P_ALL" : (idtype) == P_PID ? "P_PID" : (idtype) == P_PGID ? "P_PGID" : "?"
#define __NRATRF1_waitid64                "%" PRIuSIZ
#define __NRATRA1_waitid64(idtype, id, infop, options, ru) , (uintptr_t)(id)
#define __NRATRF2_waitid64                "%p"
#define __NRATRA2_waitid64(idtype, id, infop, options, ru) , infop
#define __NRATRF3_waitid64                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_waitid64(idtype, id, infop, options, ru) , (uintptr_t)(options), (options) & WEXITED ? "WEXITED" : "" \
                                                           , ((options) & WSTOPPED) && ((options) & (WEXITED)) ? "|" : "", (options) & WSTOPPED ? "WSTOPPED" : "" \
                                                           , ((options) & WCONTINUED) && ((options) & (WEXITED | WSTOPPED)) ? "|" : "", (options) & WCONTINUED ? "WCONTINUED" : "" \
                                                           , ((options) & WNOHANG) && ((options) & (WEXITED | WSTOPPED | WCONTINUED)) ? "|" : "", (options) & WNOHANG ? "WNOHANG" : "" \
                                                           , ((options) & WNOWAIT) && ((options) & (WEXITED | WSTOPPED | WCONTINUED | WNOHANG)) ? "|" : "", (options) & WNOWAIT ? "WNOWAIT" : ""
#define __NRATRF4_waitid64                "%p"
#define __NRATRA4_waitid64(idtype, id, infop, options, ru) , ru
#define __NRATRF0_mq_timedreceive64       "%d"
#define __NRATRA0_mq_timedreceive64(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , (int)(mqdes)
#define __NRATRF1_mq_timedreceive64       "%p"
#define __NRATRA1_mq_timedreceive64(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , msg_ptr
#define __NRATRF2_mq_timedreceive64       "%" PRIuSIZ
#define __NRATRA2_mq_timedreceive64(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , msg_len
#define __NRATRF3_mq_timedreceive64       "%p"
#define __NRATRA3_mq_timedreceive64(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , pmsg_prio
#define __NRATRF4_mq_timedreceive64       "%p"
#define __NRATRA4_mq_timedreceive64(mqdes, msg_ptr, msg_len, pmsg_prio, abs_timeout) , abs_timeout
#define __NRATRF0_mq_timedsend64          "%d"
#define __NRATRA0_mq_timedsend64(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , (int)(mqdes)
#define __NRATRF1_mq_timedsend64          "%q"
#define __NRATRA1_mq_timedsend64(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , (validate_readable_opt(msg_ptr,1),msg_ptr)
#define __NRATRF2_mq_timedsend64          "%" PRIuSIZ
#define __NRATRA2_mq_timedsend64(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , msg_len
#define __NRATRF3_mq_timedsend64          "%" PRIu32
#define __NRATRA3_mq_timedsend64(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , msg_prio
#define __NRATRF4_mq_timedsend64          "%p"
#define __NRATRA4_mq_timedsend64(mqdes, msg_ptr, msg_len, msg_prio, abs_timeout) , abs_timeout
#define __NRATRF0_utimes64                "%q"
#define __NRATRA0_utimes64(filename, times) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_utimes64                "%p"
#define __NRATRA1_utimes64(filename, times) , times
#define __NRATRF0_clock_nanosleep64       "%#" PRIxSIZ
#define __NRATRA0_clock_nanosleep64(clock_id, flags, requested_time, remaining) , (uintptr_t)(clock_id)
#define __NRATRF1_clock_nanosleep64       "%#" PRIxSIZ
#define __NRATRA1_clock_nanosleep64(clock_id, flags, requested_time, remaining) , (uintptr_t)(flags)
#define __NRATRF2_clock_nanosleep64       "%p"
#define __NRATRA2_clock_nanosleep64(clock_id, flags, requested_time, remaining) , requested_time
#define __NRATRF3_clock_nanosleep64       "%p"
#define __NRATRA3_clock_nanosleep64(clock_id, flags, requested_time, remaining) , remaining
#define __NRATRF0_clock_getres64          "%#" PRIxSIZ
#define __NRATRA0_clock_getres64(clock_id, res) , (uintptr_t)(clock_id)
#define __NRATRF1_clock_getres64          "%p"
#define __NRATRA1_clock_getres64(clock_id, res) , res
#define __NRATRF0_clock_gettime64         "%#" PRIxSIZ
#define __NRATRA0_clock_gettime64(clock_id, tp) , (uintptr_t)(clock_id)
#define __NRATRF1_clock_gettime64         "%p"
#define __NRATRA1_clock_gettime64(clock_id, tp) , tp
#define __NRATRF0_clock_settime64         "%#" PRIxSIZ
#define __NRATRA0_clock_settime64(clock_id, tp) , (uintptr_t)(clock_id)
#define __NRATRF1_clock_settime64         "%p"
#define __NRATRA1_clock_settime64(clock_id, tp) , tp
#define __NRATRF0_timer_gettime64         "%p"
#define __NRATRA0_timer_gettime64(timerid, value) , timerid
#define __NRATRF1_timer_gettime64         "%p"
#define __NRATRA1_timer_gettime64(timerid, value) , value
#define __NRATRF0_timer_settime64         "%p"
#define __NRATRA0_timer_settime64(timerid, flags, value, ovalue) , timerid
#define __NRATRF1_timer_settime64         "%#" PRIxSIZ
#define __NRATRA1_timer_settime64(timerid, flags, value, ovalue) , (uintptr_t)(flags)
#define __NRATRF2_timer_settime64         "%p"
#define __NRATRA2_timer_settime64(timerid, flags, value, ovalue) , value
#define __NRATRF3_timer_settime64         "%p"
#define __NRATRA3_timer_settime64(timerid, flags, value, ovalue) , ovalue
#define __NRATRF0_kreaddirf               "%d"
#define __NRATRA0_kreaddirf(fd, buf, bufsize, mode, iomode) , (int)(fd)
#define __NRATRF1_kreaddirf               "%p"
#define __NRATRA1_kreaddirf(fd, buf, bufsize, mode, iomode) , buf
#define __NRATRF2_kreaddirf               "%" PRIuSIZ
#define __NRATRA2_kreaddirf(fd, buf, bufsize, mode, iomode) , bufsize
#define __NRATRF3_kreaddirf               "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NRATRA3_kreaddirf(fd, buf, bufsize, mode, iomode) , (uintptr_t)(mode), (mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                            , ((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "", (mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                            , ((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE | READDIR_PEEK)) ? "|" : "", (mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                            , ((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE | READDIR_PEEK | READDIR_SKIPREL)) ? "|" : "", (mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NRATRF4_kreaddirf               "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_kreaddirf(fd, buf, bufsize, mode, iomode) , (uintptr_t)(iomode), (iomode) & IO_WRONLY ? "IO_WRONLY" : (iomode) ? "" : "IO_RDONLY" \
                                                            , ((iomode) & IO_RDWR) && ((iomode) & (IO_WRONLY)) ? "|" : "", (iomode) & IO_RDWR ? "IO_RDWR" : "" \
                                                            , ((iomode) & IO_CLOEXEC) && ((iomode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (iomode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                            , ((iomode) & IO_CLOFORK) && ((iomode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (iomode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                            , ((iomode) & IO_APPEND) && ((iomode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (iomode) & IO_APPEND ? "IO_APPEND" : "" \
                                                            , ((iomode) & IO_NONBLOCK) && ((iomode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (iomode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                            , ((iomode) & IO_SYNC) && ((iomode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (iomode) & IO_SYNC ? "IO_SYNC" : "" \
                                                            , ((iomode) & IO_ASYNC) && ((iomode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (iomode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                            , ((iomode) & IO_DIRECT) && ((iomode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (iomode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_kfstat                  "%d"
#define __NRATRA0_kfstat(fd, statbuf)     , (int)(fd)
#define __NRATRF1_kfstat                  "%p"
#define __NRATRA1_kfstat(fd, statbuf)     , statbuf
#define __NRATRF0_klstat                  "%q"
#define __NRATRA0_klstat(filename, statbuf) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_klstat                  "%p"
#define __NRATRA1_klstat(filename, statbuf) , statbuf
#define __NRATRF0_kstat                   "%q"
#define __NRATRA0_kstat(filename, statbuf) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_kstat                   "%p"
#define __NRATRA1_kstat(filename, statbuf) , statbuf
#define __NRATRF0_pwrite64f               "%d"
#define __NRATRA0_pwrite64f(fd, buf, bufsize, offset, mode) , (int)(fd)
#define __NRATRF1_pwrite64f               "%p"
#define __NRATRA1_pwrite64f(fd, buf, bufsize, offset, mode) , buf
#define __NRATRF2_pwrite64f               "%" PRIuSIZ
#define __NRATRA2_pwrite64f(fd, buf, bufsize, offset, mode) , bufsize
#define __NRATRF3_pwrite64f               "%" PRIu64
#define __NRATRA3_pwrite64f(fd, buf, bufsize, offset, mode) , offset
#define __NRATRF4_pwrite64f               "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_pwrite64f(fd, buf, bufsize, offset, mode) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                            , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                            , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                            , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                            , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                            , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                            , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                            , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                            , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_pread64f                "%d"
#define __NRATRA0_pread64f(fd, buf, bufsize, offset, mode) , (int)(fd)
#define __NRATRF1_pread64f                "%p"
#define __NRATRA1_pread64f(fd, buf, bufsize, offset, mode) , buf
#define __NRATRF2_pread64f                "%" PRIuSIZ
#define __NRATRA2_pread64f(fd, buf, bufsize, offset, mode) , bufsize
#define __NRATRF3_pread64f                "%" PRIu64
#define __NRATRA3_pread64f(fd, buf, bufsize, offset, mode) , offset
#define __NRATRF4_pread64f                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA4_pread64f(fd, buf, bufsize, offset, mode) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                           , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                           , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                           , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                           , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                           , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                           , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                           , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                           , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_rt_sigtimedwait64       "%p"
#define __NRATRA0_rt_sigtimedwait64(set, info, timeout, sigsetsize) , set
#define __NRATRF1_rt_sigtimedwait64       "%p"
#define __NRATRA1_rt_sigtimedwait64(set, info, timeout, sigsetsize) , info
#define __NRATRF2_rt_sigtimedwait64       "%p"
#define __NRATRA2_rt_sigtimedwait64(set, info, timeout, sigsetsize) , timeout
#define __NRATRF3_rt_sigtimedwait64       "%" PRIuSIZ
#define __NRATRA3_rt_sigtimedwait64(set, info, timeout, sigsetsize) , sigsetsize
#define __NRATRF0_nanosleep64             "%p"
#define __NRATRA0_nanosleep64(req, rem)   , req
#define __NRATRF1_nanosleep64             "%p"
#define __NRATRA1_nanosleep64(req, rem)   , rem
#define __NRATRF0_sched_rr_get_interval64 "%" PRIdSIZ
#define __NRATRA0_sched_rr_get_interval64(pid, tms) , (intptr_t)(pid)
#define __NRATRF1_sched_rr_get_interval64 "%p"
#define __NRATRA1_sched_rr_get_interval64(pid, tms) , tms
#define __NRATRF0_ksysctl                 "%#" PRIxSIZ
#define __NRATRA0_ksysctl(command, arg)   , (uintptr_t)(command)
#define __NRATRF1_ksysctl                 "%p"
#define __NRATRA1_ksysctl(command, arg)   , arg
#define __NRATRF0_writevf                 "%d"
#define __NRATRA0_writevf(fd, iovec, count, mode) , (int)(fd)
#define __NRATRF1_writevf                 "%p"
#define __NRATRA1_writevf(fd, iovec, count, mode) , iovec
#define __NRATRF2_writevf                 "%" PRIuSIZ
#define __NRATRA2_writevf(fd, iovec, count, mode) , count
#define __NRATRF3_writevf                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_writevf(fd, iovec, count, mode) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                  , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                  , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                  , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                  , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                  , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                  , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                  , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                  , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_readvf                  "%d"
#define __NRATRA0_readvf(fd, iovec, count, mode) , (int)(fd)
#define __NRATRF1_readvf                  "%p"
#define __NRATRA1_readvf(fd, iovec, count, mode) , iovec
#define __NRATRF2_readvf                  "%" PRIuSIZ
#define __NRATRA2_readvf(fd, iovec, count, mode) , count
#define __NRATRF3_readvf                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_readvf(fd, iovec, count, mode) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                 , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                 , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                 , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                 , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                 , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                 , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                 , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                 , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_kreaddir                "%d"
#define __NRATRA0_kreaddir(fd, buf, bufsize, mode) , (int)(fd)
#define __NRATRF1_kreaddir                "%p"
#define __NRATRA1_kreaddir(fd, buf, bufsize, mode) , buf
#define __NRATRF2_kreaddir                "%" PRIuSIZ
#define __NRATRA2_kreaddir(fd, buf, bufsize, mode) , bufsize
#define __NRATRF3_kreaddir                "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NRATRA3_kreaddir(fd, buf, bufsize, mode) , (uintptr_t)(mode), (mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                   , ((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "", (mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                   , ((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE | READDIR_PEEK)) ? "|" : "", (mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                   , ((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE | READDIR_PEEK | READDIR_SKIPREL)) ? "|" : "", (mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NRATRF0_wait4_64                "%" PRIdSIZ
#define __NRATRA0_wait4_64(pid, stat_loc, options, usage) , (intptr_t)(pid)
#define __NRATRF1_wait4_64                "%p"
#define __NRATRA1_wait4_64(pid, stat_loc, options, usage) , stat_loc
#define __NRATRF2_wait4_64                "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NRATRA2_wait4_64(pid, stat_loc, options, usage) , (uintptr_t)(options), (options) & WNOHANG ? "WNOHANG" : "" \
                                                          , ((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "", (options) & WUNTRACED ? "WUNTRACED" : "" \
                                                          , ((options) & WCONTINUED) && ((options) & (WNOHANG | WUNTRACED)) ? "|" : "", (options) & WCONTINUED ? "WCONTINUED" : "" \
                                                          , ((options) & WNOWAIT) && ((options) & (WNOHANG | WUNTRACED | WCONTINUED)) ? "|" : "", (options) & WNOWAIT ? "WNOWAIT" : ""
#define __NRATRF3_wait4_64                "%p"
#define __NRATRA3_wait4_64(pid, stat_loc, options, usage) , usage
#define __NRATRF0_getitimer64             "%#" PRIxSIZ
#define __NRATRA0_getitimer64(which, curr_value) , (uintptr_t)(which)
#define __NRATRF1_getitimer64             "%p"
#define __NRATRA1_getitimer64(which, curr_value) , curr_value
#define __NRATRF0_setitimer64             "%#" PRIxSIZ
#define __NRATRA0_setitimer64(which, newval, oldval) , (uintptr_t)(which)
#define __NRATRF1_setitimer64             "%p"
#define __NRATRA1_setitimer64(which, newval, oldval) , newval
#define __NRATRF2_setitimer64             "%p"
#define __NRATRA2_setitimer64(which, newval, oldval) , oldval
#define __NRATRF0_maplibrary              "%p"
#define __NRATRA0_maplibrary(addr, flags, fd, hdrv, hdrc) , addr
#define __NRATRF1_maplibrary              "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA1_maplibrary(addr, flags, fd, hdrv, hdrc) , (uintptr_t)(flags), (flags) & MAP_FIXED ? "MAP_FIXED" : "" \
                                                          , ((flags) & MAP_LOCKED) && ((flags) & (MAP_FIXED)) ? "|" : "", (flags) & MAP_LOCKED ? "MAP_LOCKED" : "" \
                                                          , ((flags) & MAP_NONBLOCK) && ((flags) & (MAP_FIXED | MAP_LOCKED)) ? "|" : "", (flags) & MAP_NONBLOCK ? "MAP_NONBLOCK" : "" \
                                                          , ((flags) & MAP_NORESERVE) && ((flags) & (MAP_FIXED | MAP_LOCKED | MAP_NONBLOCK)) ? "|" : "", (flags) & MAP_NORESERVE ? "MAP_NORESERVE" : "" \
                                                          , ((flags) & MAP_POPULATE) && ((flags) & (MAP_FIXED | MAP_LOCKED | MAP_NONBLOCK | MAP_NORESERVE)) ? "|" : "", (flags) & MAP_POPULATE ? "MAP_POPULATE" : "" \
                                                          , ((flags) & MAP_SYNC) && ((flags) & (MAP_FIXED | MAP_LOCKED | MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE)) ? "|" : "", (flags) & MAP_SYNC ? "MAP_SYNC" : "" \
                                                          , ((flags) & MAP_DONT_MAP) && ((flags) & (MAP_FIXED | MAP_LOCKED | MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_SYNC)) ? "|" : "", (flags) & MAP_DONT_MAP ? "MAP_DONT_MAP" : "" \
                                                          , ((flags) & MAP_DONT_OVERRIDE) && ((flags) & (MAP_FIXED | MAP_LOCKED | MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_SYNC | MAP_DONT_MAP)) ? "|" : "", (flags) & MAP_DONT_OVERRIDE ? "MAP_DONT_OVERRIDE" : ""
#define __NRATRF2_maplibrary              "%d"
#define __NRATRA2_maplibrary(addr, flags, fd, hdrv, hdrc) , (int)(fd)
#define __NRATRF3_maplibrary              "%p"
#define __NRATRA3_maplibrary(addr, flags, fd, hdrv, hdrc) , hdrv
#define __NRATRF4_maplibrary              "%" PRIuSIZ
#define __NRATRA4_maplibrary(addr, flags, fd, hdrv, hdrc) , hdrc
#define __NRATRF0_select64                "%" PRIuSIZ
#define __NRATRA0_select64(nfds, readfds, writefds, exceptfds, timeout) , nfds
#define __NRATRF1_select64                "%p"
#define __NRATRA1_select64(nfds, readfds, writefds, exceptfds, timeout) , readfds
#define __NRATRF2_select64                "%p"
#define __NRATRA2_select64(nfds, readfds, writefds, exceptfds, timeout) , writefds
#define __NRATRF3_select64                "%p"
#define __NRATRA3_select64(nfds, readfds, writefds, exceptfds, timeout) , exceptfds
#define __NRATRF4_select64                "%p"
#define __NRATRA4_select64(nfds, readfds, writefds, exceptfds, timeout) , timeout
#define __NRATRF0_settimeofday64          "%p"
#define __NRATRA0_settimeofday64(tv, tz)  , tv
#define __NRATRF1_settimeofday64          "%p"
#define __NRATRA1_settimeofday64(tv, tz)  , tz
#define __NRATRF0_gettimeofday64          "%p"
#define __NRATRA0_gettimeofday64(tv, tz)  , tv
#define __NRATRF1_gettimeofday64          "%p"
#define __NRATRA1_gettimeofday64(tv, tz)  , tz
#define __NRATRF0_getrusage64             "%" PRIdSIZ
#define __NRATRA0_getrusage64(who, tv)    , (intptr_t)(who)
#define __NRATRF1_getrusage64             "%p"
#define __NRATRA1_getrusage64(who, tv)    , tv
#define __NRATRF0_fsmode                  "%" PRIu64
#define __NRATRA0_fsmode(mode)            , mode
#define __NRATRF0_ioctlf                  "%d"
#define __NRATRA0_ioctlf(fd, command, mode, arg) , (int)(fd)
#define __NRATRF1_ioctlf                  "%#" PRIxSIZ
#define __NRATRA1_ioctlf(fd, command, mode, arg) , (uintptr_t)(command)
#define __NRATRF2_ioctlf                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_ioctlf(fd, command, mode, arg) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                 , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                 , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                 , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                 , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                 , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                 , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                 , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                 , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF3_ioctlf                  "%p"
#define __NRATRA3_ioctlf(fd, command, mode, arg) , arg
#define __NRATRF0_ftime64                 "%p"
#define __NRATRA0_ftime64(tp)             , tp
#define __NRATRF0_utime64                 "%q"
#define __NRATRA0_utime64(filename, times) , (validate_readable_opt(filename,1),filename)
#define __NRATRF1_utime64                 "%p"
#define __NRATRA1_utime64(filename, times) , times
#define __NRATRF0_userviofd               "%" PRIuSIZ
#define __NRATRA0_userviofd(initial_size, flags) , initial_size
#define __NRATRF1_userviofd               "%#" PRIxSIZ
#define __NRATRA1_userviofd(initial_size, flags) , (uintptr_t)(flags)
#define __NRATRF0_process_spawnveat       "%d"
#define __NRATRA0_process_spawnveat(dirfd, pathname, argv, envp, flags, actions) , (int)(dirfd)
#define __NRATRF1_process_spawnveat       "%q"
#define __NRATRA1_process_spawnveat(dirfd, pathname, argv, envp, flags, actions) , (validate_readable_opt(pathname,1),pathname)
#define __NRATRF2_process_spawnveat       "%p"
#define __NRATRA2_process_spawnveat(dirfd, pathname, argv, envp, flags, actions) , argv
#define __NRATRF3_process_spawnveat       "%p"
#define __NRATRA3_process_spawnveat(dirfd, pathname, argv, envp, flags, actions) , envp
#define __NRATRF4_process_spawnveat       "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA4_process_spawnveat(dirfd, pathname, argv, envp, flags, actions) , (uintptr_t)(flags), (flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                                                 , ((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "", (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                                 , ((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF5_process_spawnveat       "%p"
#define __NRATRA5_process_spawnveat(dirfd, pathname, argv, envp, flags, actions) , actions
#define __NRATRF0_stime64                 "%p"
#define __NRATRA0_stime64(t)              , t
#define __NRATRF0_coredump                "%p"
#define __NRATRA0_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) , curr_state
#define __NRATRF1_coredump                "%p"
#define __NRATRA1_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) , orig_state
#define __NRATRF2_coredump                "%p"
#define __NRATRA2_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) , traceback_vector
#define __NRATRF3_coredump                "%" PRIuSIZ
#define __NRATRA3_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) , traceback_length
#define __NRATRF4_coredump                "%p"
#define __NRATRA4_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) , exception
#define __NRATRF5_coredump                "%#" PRIxSIZ
#define __NRATRA5_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) , (uintptr_t)(unwind_error)
#define __NRATRF0_raiseat                 "%p"
#define __NRATRA0_raiseat(state, si)      , state
#define __NRATRF1_raiseat                 "%p"
#define __NRATRA1_raiseat(state, si)      , si
#define __NRATRF0_mktty                   "%d"
#define __NRATRA0_mktty(keyboard, display, name, rsvd) , (int)(keyboard)
#define __NRATRF1_mktty                   "%d"
#define __NRATRA1_mktty(keyboard, display, name, rsvd) , (int)(display)
#define __NRATRF2_mktty                   "%q"
#define __NRATRA2_mktty(keyboard, display, name, rsvd) , (validate_readable_opt(name,1),name)
#define __NRATRF3_mktty                   "%#" PRIxSIZ
#define __NRATRA3_mktty(keyboard, display, name, rsvd) , (uintptr_t)(rsvd)
#define __NRATRF0_lfutexlockexpr          "%p"
#define __NRATRA0_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) , ulockaddr
#define __NRATRF1_lfutexlockexpr          "%p"
#define __NRATRA1_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) , base
#define __NRATRF2_lfutexlockexpr          "%" PRIuSIZ
#define __NRATRA2_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) , exprc
#define __NRATRF3_lfutexlockexpr          "%p"
#define __NRATRA3_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) , exprv
#define __NRATRF4_lfutexlockexpr          "%p"
#define __NRATRA4_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) , timeout
#define __NRATRF5_lfutexlockexpr          "%#" PRIxSIZ
#define __NRATRA5_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) , (uintptr_t)(timeout_flags)
#define __NRATRF0_lfutexexpr              "%p"
#define __NRATRA0_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) , base
#define __NRATRF1_lfutexexpr              "%" PRIuSIZ
#define __NRATRA1_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) , exprc
#define __NRATRF2_lfutexexpr              "%p"
#define __NRATRA2_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) , exprv
#define __NRATRF3_lfutexexpr              "%p"
#define __NRATRA3_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) , timeout
#define __NRATRF4_lfutexexpr              "%#" PRIxSIZ
#define __NRATRA4_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) , (uintptr_t)(timeout_flags)
#define __NRATRF0_lseek64                 "%d"
#define __NRATRA0_lseek64(fd, offset, whence) , (int)(fd)
#define __NRATRF1_lseek64                 "%" PRId64
#define __NRATRA1_lseek64(fd, offset, whence) , offset
#define __NRATRF2_lseek64                 "%#Ix=%s"
#define __NRATRA2_lseek64(fd, offset, whence) , (whence), (whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NRATRF0_lfutex                  "%p"
#define __NRATRA0_lfutex(uaddr, futex_op, val, timeout, val2) , uaddr
#define __NRATRF1_lfutex                  "%#" PRIxSIZ
#define __NRATRA1_lfutex(uaddr, futex_op, val, timeout, val2) , (uintptr_t)(futex_op)
#define __NRATRF2_lfutex                  "%" PRIu32
#define __NRATRA2_lfutex(uaddr, futex_op, val, timeout, val2) , val
#define __NRATRF3_lfutex                  "%p"
#define __NRATRA3_lfutex(uaddr, futex_op, val, timeout, val2) , timeout
#define __NRATRF4_lfutex                  "%" PRIu32
#define __NRATRA4_lfutex(uaddr, futex_op, val, timeout, val2) , val2
#define __NRATRF0_debugtrap               "%p"
#define __NRATRA0_debugtrap(state, reason) , state
#define __NRATRF1_debugtrap               "%p"
#define __NRATRA1_debugtrap(state, reason) , reason
#define __NRATRF0_set_library_listdef     "%p"
#define __NRATRA0_set_library_listdef(listdef) , listdef
#define __NRATRF0_get_exception_handler   "%p"
#define __NRATRA0_get_exception_handler(pmode, phandler, phandler_sp) , pmode
#define __NRATRF1_get_exception_handler   "%p"
#define __NRATRA1_get_exception_handler(pmode, phandler, phandler_sp) , phandler
#define __NRATRF2_get_exception_handler   "%p"
#define __NRATRA2_get_exception_handler(pmode, phandler, phandler_sp) , phandler_sp
#define __NRATRF0_set_exception_handler   "%#" PRIxSIZ
#define __NRATRA0_set_exception_handler(mode, handler, handler_sp) , (uintptr_t)(mode)
#define __NRATRF1_set_exception_handler   "%p"
#define __NRATRA1_set_exception_handler(mode, handler, handler_sp) , handler
#define __NRATRF2_set_exception_handler   "%p"
#define __NRATRA2_set_exception_handler(mode, handler, handler_sp) , handler_sp
#define __NRATRF0_time64                  "%p"
#define __NRATRA0_time64(timer)           , timer
#define __NRATRF0_fchdirat                "%d"
#define __NRATRA0_fchdirat(dirfd, path, flags) , (int)(dirfd)
#define __NRATRF1_fchdirat                "%q"
#define __NRATRA1_fchdirat(dirfd, path, flags) , (validate_readable_opt(path,1),path)
#define __NRATRF2_fchdirat                "%#" PRIxSIZ "=%s"
#define __NRATRA2_fchdirat(dirfd, path, flags) , (uintptr_t)(flags), (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_openpty                 "%p"
#define __NRATRA0_openpty(amaster, aslave, name, termp, winp) , amaster
#define __NRATRF1_openpty                 "%p"
#define __NRATRA1_openpty(amaster, aslave, name, termp, winp) , aslave
#define __NRATRF2_openpty                 "%p"
#define __NRATRA2_openpty(amaster, aslave, name, termp, winp) , name
#define __NRATRF3_openpty                 "%p"
#define __NRATRA3_openpty(amaster, aslave, name, termp, winp) , termp
#define __NRATRF4_openpty                 "%p"
#define __NRATRA4_openpty(amaster, aslave, name, termp, winp) , winp
#define __NRATRF0_rpc_schedule            "%" PRIdSIZ
#define __NRATRA0_rpc_schedule(target, flags, program, arguments) , (intptr_t)(target)
#define __NRATRF1_rpc_schedule            "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA1_rpc_schedule(target, flags, program, arguments) , (uintptr_t)(flags), (flags) & RPC_SCHEDULE_ASYNC ? "RPC_SCHEDULE_ASYNC" : (flags) ? "" : "RPC_SCHEDULE_SYNC" \
                                                                  , ((flags) & RPC_SCHEDULE_FLAG_NONSYSCALL) && ((flags) & (RPC_SCHEDULE_ASYNC)) ? "|" : "", (flags) & RPC_SCHEDULE_FLAG_NONSYSCALL ? "RPC_SCHEDULE_FLAG_NONSYSCALL" : "" \
                                                                  , ((flags) & RPC_SCHEDULE_FLAG_WAITFORSTART) && ((flags) & (RPC_SCHEDULE_ASYNC | RPC_SCHEDULE_FLAG_NONSYSCALL)) ? "|" : "", (flags) & RPC_SCHEDULE_FLAG_WAITFORSTART ? "RPC_SCHEDULE_FLAG_WAITFORSTART" : "" \
                                                                  , ((flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX) && ((flags) & (RPC_SCHEDULE_ASYNC | RPC_SCHEDULE_FLAG_NONSYSCALL | RPC_SCHEDULE_FLAG_WAITFORSTART)) ? "|" : "", (flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX ? "RPC_SCHEDULE_FLAG_STATUSFUTEX" : "" \
                                                                  , ((flags) & RPC_SCHEDULE_FLAG_SYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC | RPC_SCHEDULE_FLAG_NONSYSCALL | RPC_SCHEDULE_FLAG_WAITFORSTART | RPC_SCHEDULE_FLAG_STATUSFUTEX)) ? "|" : "", (flags) & RPC_SCHEDULE_FLAG_SYSRESTART ? "RPC_SCHEDULE_FLAG_SYSRESTART" : "" \
                                                                  , ((flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC | RPC_SCHEDULE_FLAG_NONSYSCALL | RPC_SCHEDULE_FLAG_WAITFORSTART | RPC_SCHEDULE_FLAG_STATUSFUTEX | RPC_SCHEDULE_FLAG_SYSRESTART)) ? "|" : "", (flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART ? "RPC_SCHEDULE_FLAG_NOSYSRESTART" : "" \
                                                                  , ((flags) & RPC_SCHEDULE_FLAG_WAITSMPACK) && ((flags) & (RPC_SCHEDULE_ASYNC | RPC_SCHEDULE_FLAG_NONSYSCALL | RPC_SCHEDULE_FLAG_WAITFORSTART | RPC_SCHEDULE_FLAG_STATUSFUTEX | RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART)) ? "|" : "", (flags) & RPC_SCHEDULE_FLAG_WAITSMPACK ? "RPC_SCHEDULE_FLAG_WAITSMPACK" : "" \
                                                                  , ((flags) & RPC_SCHEDULE_FLAG_DONTWAKE) && ((flags) & (RPC_SCHEDULE_ASYNC | RPC_SCHEDULE_FLAG_NONSYSCALL | RPC_SCHEDULE_FLAG_WAITFORSTART | RPC_SCHEDULE_FLAG_STATUSFUTEX | RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART | RPC_SCHEDULE_FLAG_WAITSMPACK)) ? "|" : "", (flags) & RPC_SCHEDULE_FLAG_DONTWAKE ? "RPC_SCHEDULE_FLAG_DONTWAKE" : "" \
                                                                  , ((flags) & RPC_SCHEDULE_FLAG_HIGHPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC | RPC_SCHEDULE_FLAG_NONSYSCALL | RPC_SCHEDULE_FLAG_WAITFORSTART | RPC_SCHEDULE_FLAG_STATUSFUTEX | RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART | RPC_SCHEDULE_FLAG_WAITSMPACK | RPC_SCHEDULE_FLAG_DONTWAKE)) ? "|" : "", (flags) & RPC_SCHEDULE_FLAG_HIGHPRIO ? "RPC_SCHEDULE_FLAG_HIGHPRIO" : "" \
                                                                  , ((flags) & RPC_SCHEDULE_FLAG_LOWPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC | RPC_SCHEDULE_FLAG_NONSYSCALL | RPC_SCHEDULE_FLAG_WAITFORSTART | RPC_SCHEDULE_FLAG_STATUSFUTEX | RPC_SCHEDULE_FLAG_SYSRESTART | RPC_SCHEDULE_FLAG_NOSYSRESTART | RPC_SCHEDULE_FLAG_WAITSMPACK | RPC_SCHEDULE_FLAG_DONTWAKE | RPC_SCHEDULE_FLAG_HIGHPRIO)) ? "|" : "", (flags) & RPC_SCHEDULE_FLAG_LOWPRIO ? "RPC_SCHEDULE_FLAG_LOWPRIO" : ""
#define __NRATRF2_rpc_schedule            "%p"
#define __NRATRA2_rpc_schedule(target, flags, program, arguments) , program
#define __NRATRF3_rpc_schedule            "%p"
#define __NRATRA3_rpc_schedule(target, flags, program, arguments) , arguments
#define __NRATRF0_frealpathat             "%d"
#define __NRATRA0_frealpathat(dirfd, filename, buf, buflen, flags) , (int)(dirfd)
#define __NRATRF1_frealpathat             "%q"
#define __NRATRA1_frealpathat(dirfd, filename, buf, buflen, flags) , (validate_readable_opt(filename,1),filename)
#define __NRATRF2_frealpathat             "%p"
#define __NRATRA2_frealpathat(dirfd, filename, buf, buflen, flags) , buf
#define __NRATRF3_frealpathat             "%" PRIuSIZ
#define __NRATRA3_frealpathat(dirfd, filename, buf, buflen, flags) , buflen
#define __NRATRF4_frealpathat             "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NRATRA4_frealpathat(dirfd, filename, buf, buflen, flags) , (uintptr_t)(flags), (flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                                   , ((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_ALTPATH)) ? "|" : "", (flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                   , ((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH | AT_SYMLINK_NOFOLLOW)) ? "|" : "", (flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                                   , ((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_READLINK_REQSIZE)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_frealpath4              "%d"
#define __NRATRA0_frealpath4(fd, resolved, buflen, flags) , (int)(fd)
#define __NRATRF1_frealpath4              "%p"
#define __NRATRA1_frealpath4(fd, resolved, buflen, flags) , resolved
#define __NRATRF2_frealpath4              "%" PRIuSIZ
#define __NRATRA2_frealpath4(fd, resolved, buflen, flags) , buflen
#define __NRATRF3_frealpath4              "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NRATRA3_frealpath4(fd, resolved, buflen, flags) , (uintptr_t)(flags), (flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                          , ((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH)) ? "|" : "", (flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                          , ((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH | AT_READLINK_REQSIZE)) ? "|" : "", (flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NRATRF0_detach                  "%" PRIdSIZ
#define __NRATRA0_detach(pid)             , (intptr_t)(pid)
#define __NRATRF0_writef                  "%d"
#define __NRATRA0_writef(fd, buf, bufsize, mode) , (int)(fd)
#define __NRATRF1_writef                  "%p"
#define __NRATRA1_writef(fd, buf, bufsize, mode) , buf
#define __NRATRF2_writef                  "%" PRIuSIZ
#define __NRATRA2_writef(fd, buf, bufsize, mode) , bufsize
#define __NRATRF3_writef                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_writef(fd, buf, bufsize, mode) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                 , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                 , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                 , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                 , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                 , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                 , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                 , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                 , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_readf                   "%d"
#define __NRATRA0_readf(fd, buf, bufsize, mode) , (int)(fd)
#define __NRATRF1_readf                   "%p"
#define __NRATRA1_readf(fd, buf, bufsize, mode) , buf
#define __NRATRF2_readf                   "%" PRIuSIZ
#define __NRATRA2_readf(fd, buf, bufsize, mode) , bufsize
#define __NRATRF3_readf                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA3_readf(fd, buf, bufsize, mode) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF0_hopf                    "%d"
#define __NRATRA0_hopf(fd, command, mode, arg) , (int)(fd)
#define __NRATRF1_hopf                    "%#" PRIxSIZ
#define __NRATRA1_hopf(fd, command, mode, arg) , (uintptr_t)(command)
#define __NRATRF2_hopf                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NRATRA2_hopf(fd, command, mode, arg) , (uintptr_t)(mode), (mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                               , ((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "", (mode) & IO_RDWR ? "IO_RDWR" : "" \
                                               , ((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY | IO_RDWR)) ? "|" : "", (mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                               , ((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC)) ? "|" : "", (mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                               , ((mode) & IO_APPEND) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK)) ? "|" : "", (mode) & IO_APPEND ? "IO_APPEND" : "" \
                                               , ((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND)) ? "|" : "", (mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                               , ((mode) & IO_SYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK)) ? "|" : "", (mode) & IO_SYNC ? "IO_SYNC" : "" \
                                               , ((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC)) ? "|" : "", (mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                               , ((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY | IO_RDWR | IO_CLOEXEC | IO_CLOFORK | IO_APPEND | IO_NONBLOCK | IO_SYNC | IO_ASYNC)) ? "|" : "", (mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NRATRF3_hopf                    "%p"
#define __NRATRA3_hopf(fd, command, mode, arg) , arg
#define __NRATRF0_hop                     "%d"
#define __NRATRA0_hop(fd, command, arg)   , (int)(fd)
#define __NRATRF1_hop                     "%#" PRIxSIZ
#define __NRATRA1_hop(fd, command, arg)   , (uintptr_t)(command)
#define __NRATRF2_hop                     "%p"
#define __NRATRA2_hop(fd, command, arg)   , arg
#endif /* !__NRFEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT */
#endif /* __WANT_SYSCALL_ARGUMENT_FORMAT */

