/* HASH CRC-32:0xe9235550 */
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
#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#define __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES 1
#define __NR32AN0_exit                    status
#define __NR32AN0_read                    fd
#define __NR32AN1_read                    buf
#define __NR32AN2_read                    bufsize
#define __NR32AN0_write                   fd
#define __NR32AN1_write                   buf
#define __NR32AN2_write                   bufsize
#define __NR32AN0_open                    filename
#define __NR32AN1_open                    oflags
#define __NR32AN2_open                    mode
#define __NR32AN0_close                   fd
#define __NR32AN0_waitpid                 pid
#define __NR32AN1_waitpid                 stat_loc
#define __NR32AN2_waitpid                 options
#define __NR32AN0_creat                   filename
#define __NR32AN1_creat                   mode
#define __NR32AN0_link                    existing_file
#define __NR32AN1_link                    link_file
#define __NR32AN0_unlink                  filename
#define __NR32AN0_execve                  path
#define __NR32AN1_execve                  argv
#define __NR32AN2_execve                  envp
#define __NR32AN0_chdir                   path
#define __NR32AN0_time                    timer
#define __NR32AN0_mknod                   nodename
#define __NR32AN1_mknod                   mode
#define __NR32AN2_mknod                   dev
#define __NR32AN0_chmod                   filename
#define __NR32AN1_chmod                   mode
#define __NR32AN0_lchown                  filename
#define __NR32AN1_lchown                  owner
#define __NR32AN2_lchown                  group
#define __NR32AN0_linux_oldstat           filename
#define __NR32AN1_linux_oldstat           statbuf
#define __NR32AN0_lseek                   fd
#define __NR32AN1_lseek                   offset
#define __NR32AN2_lseek                   whence
#define __NR32AN0_mount                   special_file
#define __NR32AN1_mount                   dir
#define __NR32AN2_mount                   fstype
#define __NR32AN3_mount                   rwflag
#define __NR32AN4_mount                   data
#define __NR32AN0_umount                  special_file
#define __NR32AN0_setuid                  uid
#define __NR32AN0_stime                   t
#define __NR32AN0_ptrace                  request
#define __NR32AN1_ptrace                  pid
#define __NR32AN2_ptrace                  addr
#define __NR32AN3_ptrace                  data
#define __NR32AN0_alarm                   seconds
#define __NR32AN0_linux_oldfstat          fd
#define __NR32AN1_linux_oldfstat          statbuf
#define __NR32AN0_utime                   filename
#define __NR32AN1_utime                   times
#define __NR32AN0_access                  filename
#define __NR32AN1_access                  type
#define __NR32AN0_nice                    inc
#define __NR32AN0_ftime                   tp
#define __NR32AN0_kill                    pid
#define __NR32AN1_kill                    signo
#define __NR32AN0_rename                  oldname
#define __NR32AN1_rename                  newname_or_path
#define __NR32AN0_mkdir                   pathname
#define __NR32AN1_mkdir                   mode
#define __NR32AN0_rmdir                   path
#define __NR32AN0_dup                     fd
#define __NR32AN0_pipe                    pipedes
#define __NR32AN0_times                   buf
#define __NR32AN0_brk                     addr
#define __NR32AN0_setgid                  gid
#define __NR32AN0_signal                  signo
#define __NR32AN1_signal                  handler
#define __NR32AN0_acct                    filename
#define __NR32AN0_umount2                 special_file
#define __NR32AN1_umount2                 flags
#define __NR32AN0_ioctl                   fd
#define __NR32AN1_ioctl                   request
#define __NR32AN2_ioctl                   arg
#define __NR32AN0_fcntl                   fd
#define __NR32AN1_fcntl                   cmd
#define __NR32AN2_fcntl                   arg
#define __NR32AN0_setpgid                 pid
#define __NR32AN1_setpgid                 pgid
#define __NR32AN0_oldolduname             name
#define __NR32AN0_umask                   mode
#define __NR32AN0_chroot                  path
#define __NR32AN0_ustat                   dev
#define __NR32AN1_ustat                   ubuf
#define __NR32AN0_dup2                    oldfd
#define __NR32AN1_dup2                    newfd
#define __NR32AN0_sigaction               signo
#define __NR32AN1_sigaction               act
#define __NR32AN2_sigaction               oact
#define __NR32AN0_ssetmask                sigmask
#define __NR32AN0_setreuid                ruid
#define __NR32AN1_setreuid                euid
#define __NR32AN0_setregid                rgid
#define __NR32AN1_setregid                egid
#define __NR32AN0_sigsuspend              set
#define __NR32AN0_sigpending              set
#define __NR32AN0_sethostname             name
#define __NR32AN1_sethostname             len
#define __NR32AN0_setrlimit               resource
#define __NR32AN1_setrlimit               rlimits
#define __NR32AN0_getrlimit               resource
#define __NR32AN1_getrlimit               rlimits
#define __NR32AN0_getrusage               who
#define __NR32AN1_getrusage               usage
#define __NR32AN0_gettimeofday            tv
#define __NR32AN1_gettimeofday            tz
#define __NR32AN0_settimeofday            tv
#define __NR32AN1_settimeofday            tz
#define __NR32AN0_getgroups               size
#define __NR32AN1_getgroups               list
#define __NR32AN0_setgroups               count
#define __NR32AN1_setgroups               groups
#define __NR32AN0_select                  nfds
#define __NR32AN1_select                  readfds
#define __NR32AN2_select                  writefds
#define __NR32AN3_select                  exceptfds
#define __NR32AN4_select                  timeout
#define __NR32AN0_symlink                 link_text
#define __NR32AN1_symlink                 target_path
#define __NR32AN0_linux_oldlstat          filename
#define __NR32AN1_linux_oldlstat          statbuf
#define __NR32AN0_readlink                path
#define __NR32AN1_readlink                buf
#define __NR32AN2_readlink                buflen
#define __NR32AN0_uselib                  library
#define __NR32AN0_swapon                  pathname
#define __NR32AN1_swapon                  swapflags
#define __NR32AN0_reboot                  how
#define __NR32AN0_readdir                 fd
#define __NR32AN1_readdir                 dirp
#define __NR32AN2_readdir                 count
#define __NR32AN0_mmap                    addr
#define __NR32AN1_mmap                    len
#define __NR32AN2_mmap                    prot
#define __NR32AN3_mmap                    flags
#define __NR32AN4_mmap                    fd
#define __NR32AN5_mmap                    offset
#define __NR32AN0_munmap                  addr
#define __NR32AN1_munmap                  len
#define __NR32AN0_truncate                filename
#define __NR32AN1_truncate                length
#define __NR32AN0_ftruncate               fd
#define __NR32AN1_ftruncate               length
#define __NR32AN0_fchmod                  fd
#define __NR32AN1_fchmod                  mode
#define __NR32AN0_fchown                  fd
#define __NR32AN1_fchown                  owner
#define __NR32AN2_fchown                  group
#define __NR32AN0_getpriority             which
#define __NR32AN1_getpriority             who
#define __NR32AN0_setpriority             which
#define __NR32AN1_setpriority             who
#define __NR32AN2_setpriority             value
#define __NR32AN0_profil                  sample_buffer
#define __NR32AN1_profil                  size
#define __NR32AN2_profil                  offset
#define __NR32AN3_profil                  scale
#define __NR32AN0_statfs                  file
#define __NR32AN1_statfs                  buf
#define __NR32AN0_fstatfs                 file
#define __NR32AN1_fstatfs                 buf
#define __NR32AN0_ioperm                  from
#define __NR32AN1_ioperm                  num
#define __NR32AN2_ioperm                  turn_on
#define __NR32AN0_socketcall              call
#define __NR32AN1_socketcall              args
#define __NR32AN0_syslog                  level
#define __NR32AN1_syslog                  str
#define __NR32AN2_syslog                  len
#define __NR32AN0_setitimer               which
#define __NR32AN1_setitimer               newval
#define __NR32AN2_setitimer               oldval
#define __NR32AN0_getitimer               which
#define __NR32AN1_getitimer               curr_value
#define __NR32AN0_linux_stat32            filename
#define __NR32AN1_linux_stat32            statbuf
#define __NR32AN0_linux_lstat32           filename
#define __NR32AN1_linux_lstat32           statbuf
#define __NR32AN0_linux_fstat32           fd
#define __NR32AN1_linux_fstat32           statbuf
#define __NR32AN0_olduname                name
#define __NR32AN0_iopl                    level
#define __NR32AN0_vm86old                 TODO_PROTOTYPE
#define __NR32AN0_wait4                   pid
#define __NR32AN1_wait4                   stat_loc
#define __NR32AN2_wait4                   options
#define __NR32AN3_wait4                   usage
#define __NR32AN0_swapoff                 pathname
#define __NR32AN0_sysinfo                 info
#define __NR32AN0_ipc                     TODO_PROTOTYPE
#define __NR32AN0_fsync                   fd
#define __NR32AN0_sigreturn               restore_fpu
#define __NR32AN1_sigreturn               unused1
#define __NR32AN2_sigreturn               unused2
#define __NR32AN3_sigreturn               restore_sigmask
#define __NR32AN4_sigreturn               sc_info
#define __NR32AN5_sigreturn               restore_cpu
#define __NR32AN0_clone                   flags
#define __NR32AN1_clone                   child_stack
#define __NR32AN2_clone                   ptid
#define __NR32AN3_clone                   newtls
#define __NR32AN4_clone                   ctid
#define __NR32AN0_setdomainname           name
#define __NR32AN1_setdomainname           len
#define __NR32AN0_uname                   name
#define __NR32AN0_modify_ldt              func
#define __NR32AN1_modify_ldt              ptr
#define __NR32AN2_modify_ldt              bytecount
#define __NR32AN0_adjtimex                TODO_PROTOTYPE
#define __NR32AN0_mprotect                addr
#define __NR32AN1_mprotect                len
#define __NR32AN2_mprotect                prot
#define __NR32AN0_sigprocmask             how
#define __NR32AN1_sigprocmask             set
#define __NR32AN2_sigprocmask             oset
#define __NR32AN0_create_module           TODO_PROTOTYPE
#define __NR32AN0_init_module             TODO_PROTOTYPE
#define __NR32AN0_delete_module           TODO_PROTOTYPE
#define __NR32AN0_get_kernel_syms         TODO_PROTOTYPE
#define __NR32AN0_quotactl                TODO_PROTOTYPE
#define __NR32AN0_getpgid                 pid
#define __NR32AN0_fchdir                  fd
#define __NR32AN0_bdflush                 TODO_PROTOTYPE
#define __NR32AN0_sysfs                   TODO_PROTOTYPE
#define __NR32AN0_personality             TODO_PROTOTYPE
#define __NR32AN0_afs_syscall             TODO_PROTOTYPE
#define __NR32AN0_setfsuid                uid
#define __NR32AN0_setfsgid                gid
#define __NR32AN0__llseek                 fd
#define __NR32AN1__llseek                 offset
#define __NR32AN2__llseek                 result
#define __NR32AN3__llseek                 whence
#define __NR32AN0_getdents                fd
#define __NR32AN1_getdents                dirp
#define __NR32AN2_getdents                count
#define __NR32AN0__newselect              TODO_PROTOTYPE
#define __NR32AN0_flock                   fd
#define __NR32AN1_flock                   operation
#define __NR32AN0_msync                   addr
#define __NR32AN1_msync                   len
#define __NR32AN2_msync                   flags
#define __NR32AN0_readv                   fd
#define __NR32AN1_readv                   iovec
#define __NR32AN2_readv                   count
#define __NR32AN0_writev                  fd
#define __NR32AN1_writev                  iovec
#define __NR32AN2_writev                  count
#define __NR32AN0_getsid                  pid
#define __NR32AN0_fdatasync               fd
#define __NR32AN0__sysctl                 TODO_PROTOTYPE
#define __NR32AN0_mlock                   addr
#define __NR32AN1_mlock                   len
#define __NR32AN0_munlock                 addr
#define __NR32AN1_munlock                 len
#define __NR32AN0_mlockall                flags
#define __NR32AN0_sched_setparam          pid
#define __NR32AN1_sched_setparam          param
#define __NR32AN0_sched_getparam          pid
#define __NR32AN1_sched_getparam          param
#define __NR32AN0_sched_setscheduler      pid
#define __NR32AN1_sched_setscheduler      policy
#define __NR32AN2_sched_setscheduler      param
#define __NR32AN0_sched_getscheduler      pid
#define __NR32AN0_sched_get_priority_max  algorithm
#define __NR32AN0_sched_get_priority_min  algorithm
#define __NR32AN0_sched_rr_get_interval   pid
#define __NR32AN1_sched_rr_get_interval   tms
#define __NR32AN0_nanosleep               req
#define __NR32AN1_nanosleep               rem
#define __NR32AN0_mremap                  addr
#define __NR32AN1_mremap                  old_len
#define __NR32AN2_mremap                  new_len
#define __NR32AN3_mremap                  flags
#define __NR32AN4_mremap                  new_address
#define __NR32AN0_setresuid               ruid
#define __NR32AN1_setresuid               euid
#define __NR32AN2_setresuid               suid
#define __NR32AN0_getresuid               ruid
#define __NR32AN1_getresuid               euid
#define __NR32AN2_getresuid               suid
#define __NR32AN0_vm86                    TODO_PROTOTYPE
#define __NR32AN0_query_module            TODO_PROTOTYPE
#define __NR32AN0_poll                    fds
#define __NR32AN1_poll                    nfds
#define __NR32AN2_poll                    timeout
#define __NR32AN0_nfsservctl              TODO_PROTOTYPE
#define __NR32AN0_setresgid               rgid
#define __NR32AN1_setresgid               egid
#define __NR32AN2_setresgid               sgid
#define __NR32AN0_getresgid               rgid
#define __NR32AN1_getresgid               egid
#define __NR32AN2_getresgid               sgid
#define __NR32AN0_prctl                   TODO_PROTOTYPE
#define __NR32AN0_rt_sigreturn            restore_fpu
#define __NR32AN1_rt_sigreturn            restore_sigmask
#define __NR32AN2_rt_sigreturn            sc_info
#define __NR32AN3_rt_sigreturn            restore_cpu
#define __NR32AN0_rt_sigaction            signo
#define __NR32AN1_rt_sigaction            act
#define __NR32AN2_rt_sigaction            oact
#define __NR32AN3_rt_sigaction            sigsetsize
#define __NR32AN0_rt_sigprocmask          how
#define __NR32AN1_rt_sigprocmask          set
#define __NR32AN2_rt_sigprocmask          oset
#define __NR32AN3_rt_sigprocmask          sigsetsize
#define __NR32AN0_rt_sigpending           set
#define __NR32AN1_rt_sigpending           sigsetsize
#define __NR32AN0_rt_sigtimedwait         set
#define __NR32AN1_rt_sigtimedwait         info
#define __NR32AN2_rt_sigtimedwait         timeout
#define __NR32AN3_rt_sigtimedwait         sigsetsize
#define __NR32AN0_rt_sigqueueinfo         tgid
#define __NR32AN1_rt_sigqueueinfo         signo
#define __NR32AN2_rt_sigqueueinfo         uinfo
#define __NR32AN0_rt_sigsuspend           set
#define __NR32AN1_rt_sigsuspend           sigsetsize
#define __NR32AN0_pread64                 fd
#define __NR32AN1_pread64                 buf
#define __NR32AN2_pread64                 bufsize
#define __NR32AN3_pread64                 offset
#define __NR32AN0_pwrite64                fd
#define __NR32AN1_pwrite64                buf
#define __NR32AN2_pwrite64                bufsize
#define __NR32AN3_pwrite64                offset
#define __NR32AN0_chown                   filename
#define __NR32AN1_chown                   owner
#define __NR32AN2_chown                   group
#define __NR32AN0_getcwd                  buf
#define __NR32AN1_getcwd                  size
#define __NR32AN0_capget                  TODO_PROTOTYPE
#define __NR32AN0_capset                  TODO_PROTOTYPE
#define __NR32AN0_sigaltstack             ss
#define __NR32AN1_sigaltstack             oss
#define __NR32AN0_sendfile                out_fd
#define __NR32AN1_sendfile                in_fd
#define __NR32AN2_sendfile                offset
#define __NR32AN3_sendfile                count
#define __NR32AN0_getpmsg                 TODO_PROTOTYPE
#define __NR32AN0_putpmsg                 TODO_PROTOTYPE
#define __NR32AN0_ugetrlimit              TODO_PROTOTYPE
#define __NR32AN0_mmap2                   addr
#define __NR32AN1_mmap2                   len
#define __NR32AN2_mmap2                   prot
#define __NR32AN3_mmap2                   flags
#define __NR32AN4_mmap2                   fd
#define __NR32AN5_mmap2                   pgoffset
#define __NR32AN0_truncate64              filename
#define __NR32AN1_truncate64              length
#define __NR32AN0_ftruncate64             fd
#define __NR32AN1_ftruncate64             length
#define __NR32AN0_linux_stat64            filename
#define __NR32AN1_linux_stat64            statbuf
#define __NR32AN0_linux_lstat64           filename
#define __NR32AN1_linux_lstat64           statbuf
#define __NR32AN0_linux_fstat64           fd
#define __NR32AN1_linux_fstat64           statbuf
#define __NR32AN0_lchown32                filename
#define __NR32AN1_lchown32                owner
#define __NR32AN2_lchown32                group
#define __NR32AN0_setreuid32              ruid
#define __NR32AN1_setreuid32              euid
#define __NR32AN0_setregid32              rgid
#define __NR32AN1_setregid32              egid
#define __NR32AN0_getgroups32             size
#define __NR32AN1_getgroups32             list
#define __NR32AN0_setgroups32             count
#define __NR32AN1_setgroups32             groups
#define __NR32AN0_fchown32                fd
#define __NR32AN1_fchown32                owner
#define __NR32AN2_fchown32                group
#define __NR32AN0_setresuid32             ruid
#define __NR32AN1_setresuid32             euid
#define __NR32AN2_setresuid32             suid
#define __NR32AN0_getresuid32             ruid
#define __NR32AN1_getresuid32             euid
#define __NR32AN2_getresuid32             suid
#define __NR32AN0_setresgid32             rgid
#define __NR32AN1_setresgid32             egid
#define __NR32AN2_setresgid32             sgid
#define __NR32AN0_getresgid32             rgid
#define __NR32AN1_getresgid32             egid
#define __NR32AN2_getresgid32             sgid
#define __NR32AN0_chown32                 filename
#define __NR32AN1_chown32                 owner
#define __NR32AN2_chown32                 group
#define __NR32AN0_setuid32                uid
#define __NR32AN0_setgid32                gid
#define __NR32AN0_setfsuid32              uid
#define __NR32AN0_setfsgid32              gid
#define __NR32AN0_pivot_root              TODO_PROTOTYPE
#define __NR32AN0_mincore                 start
#define __NR32AN1_mincore                 len
#define __NR32AN2_mincore                 vec
#define __NR32AN0_madvise                 addr
#define __NR32AN1_madvise                 len
#define __NR32AN2_madvise                 advice
#define __NR32AN0_getdents64              fd
#define __NR32AN1_getdents64              dirp
#define __NR32AN2_getdents64              count
#define __NR32AN0_fcntl64                 fd
#define __NR32AN1_fcntl64                 command
#define __NR32AN2_fcntl64                 arg
#define __NR32AN0_readahead               fd
#define __NR32AN1_readahead               offset
#define __NR32AN2_readahead               count
#define __NR32AN0_setxattr                path
#define __NR32AN1_setxattr                name
#define __NR32AN2_setxattr                buf
#define __NR32AN3_setxattr                bufsize
#define __NR32AN4_setxattr                flags
#define __NR32AN0_lsetxattr               path
#define __NR32AN1_lsetxattr               name
#define __NR32AN2_lsetxattr               buf
#define __NR32AN3_lsetxattr               bufsize
#define __NR32AN4_lsetxattr               flags
#define __NR32AN0_fsetxattr               fd
#define __NR32AN1_fsetxattr               name
#define __NR32AN2_fsetxattr               buf
#define __NR32AN3_fsetxattr               bufsize
#define __NR32AN4_fsetxattr               flags
#define __NR32AN0_getxattr                path
#define __NR32AN1_getxattr                name
#define __NR32AN2_getxattr                buf
#define __NR32AN3_getxattr                bufsize
#define __NR32AN0_lgetxattr               path
#define __NR32AN1_lgetxattr               name
#define __NR32AN2_lgetxattr               buf
#define __NR32AN3_lgetxattr               bufsize
#define __NR32AN0_fgetxattr               fd
#define __NR32AN1_fgetxattr               name
#define __NR32AN2_fgetxattr               buf
#define __NR32AN3_fgetxattr               bufsize
#define __NR32AN0_listxattr               path
#define __NR32AN1_listxattr               listbuf
#define __NR32AN2_listxattr               listbufsize
#define __NR32AN0_llistxattr              path
#define __NR32AN1_llistxattr              listbuf
#define __NR32AN2_llistxattr              listbufsize
#define __NR32AN0_flistxattr              fd
#define __NR32AN1_flistxattr              listbuf
#define __NR32AN2_flistxattr              listbufsize
#define __NR32AN0_removexattr             path
#define __NR32AN1_removexattr             name
#define __NR32AN0_lremovexattr            path
#define __NR32AN1_lremovexattr            name
#define __NR32AN0_fremovexattr            fd
#define __NR32AN1_fremovexattr            name
#define __NR32AN0_tkill                   tid
#define __NR32AN1_tkill                   signo
#define __NR32AN0_sendfile64              out_fd
#define __NR32AN1_sendfile64              in_fd
#define __NR32AN2_sendfile64              offset
#define __NR32AN3_sendfile64              count
#define __NR32AN0_futex                   uaddr
#define __NR32AN1_futex                   futex_op
#define __NR32AN2_futex                   val
#define __NR32AN3_futex                   timeout_or_val2
#define __NR32AN4_futex                   uaddr2
#define __NR32AN5_futex                   val3
#define __NR32AN0_sched_setaffinity       pid
#define __NR32AN1_sched_setaffinity       cpusetsize
#define __NR32AN2_sched_setaffinity       cpuset
#define __NR32AN0_sched_getaffinity       pid
#define __NR32AN1_sched_getaffinity       cpusetsize
#define __NR32AN2_sched_getaffinity       cpuset
#define __NR32AN0_set_thread_area         TODO_PROTOTYPE
#define __NR32AN0_get_thread_area         TODO_PROTOTYPE
#define __NR32AN0_io_setup                TODO_PROTOTYPE
#define __NR32AN0_io_destroy              TODO_PROTOTYPE
#define __NR32AN0_io_getevents            TODO_PROTOTYPE
#define __NR32AN0_io_submit               TODO_PROTOTYPE
#define __NR32AN0_io_cancel               TODO_PROTOTYPE
#define __NR32AN0_fadvise64               TODO_PROTOTYPE
#define __NR32AN0_exit_group              exit_code
#define __NR32AN0_lookup_dcookie          TODO_PROTOTYPE
#define __NR32AN0_epoll_create            size
#define __NR32AN0_epoll_ctl               epfd
#define __NR32AN1_epoll_ctl               op
#define __NR32AN2_epoll_ctl               fd
#define __NR32AN3_epoll_ctl               event
#define __NR32AN0_epoll_wait              epfd
#define __NR32AN1_epoll_wait              events
#define __NR32AN2_epoll_wait              maxevents
#define __NR32AN3_epoll_wait              timeout
#define __NR32AN0_remap_file_pages        start
#define __NR32AN1_remap_file_pages        size
#define __NR32AN2_remap_file_pages        prot
#define __NR32AN3_remap_file_pages        pgoff
#define __NR32AN4_remap_file_pages        flags
#define __NR32AN0_set_tid_address         tidptr
#define __NR32AN0_timer_create            clock_id
#define __NR32AN1_timer_create            evp
#define __NR32AN2_timer_create            timerid
#define __NR32AN0_timer_settime           timerid
#define __NR32AN1_timer_settime           flags
#define __NR32AN2_timer_settime           value
#define __NR32AN3_timer_settime           ovalue
#define __NR32AN0_timer_gettime           timerid
#define __NR32AN1_timer_gettime           value
#define __NR32AN0_timer_getoverrun        timerid
#define __NR32AN0_timer_delete            timerid
#define __NR32AN0_clock_settime           clock_id
#define __NR32AN1_clock_settime           tp
#define __NR32AN0_clock_gettime           clock_id
#define __NR32AN1_clock_gettime           tp
#define __NR32AN0_clock_getres            clock_id
#define __NR32AN1_clock_getres            res
#define __NR32AN0_clock_nanosleep         clock_id
#define __NR32AN1_clock_nanosleep         flags
#define __NR32AN2_clock_nanosleep         requested_time
#define __NR32AN3_clock_nanosleep         remaining
#define __NR32AN0_statfs64                file
#define __NR32AN1_statfs64                buf
#define __NR32AN0_fstatfs64               file
#define __NR32AN1_fstatfs64               buf
#define __NR32AN0_tgkill                  tgid
#define __NR32AN1_tgkill                  tid
#define __NR32AN2_tgkill                  signo
#define __NR32AN0_utimes                  filename
#define __NR32AN1_utimes                  times
#define __NR32AN0_fadvise64_64            TODO_PROTOTYPE
#define __NR32AN0_vserver                 TODO_PROTOTYPE
#define __NR32AN0_mbind                   TODO_PROTOTYPE
#define __NR32AN0_get_mempolicy           TODO_PROTOTYPE
#define __NR32AN0_set_mempolicy           TODO_PROTOTYPE
#define __NR32AN0_mq_open                 TODO_PROTOTYPE
#define __NR32AN0_mq_unlink               TODO_PROTOTYPE
#define __NR32AN0_mq_timedsend            TODO_PROTOTYPE
#define __NR32AN0_mq_timedreceive         TODO_PROTOTYPE
#define __NR32AN0_mq_notify               TODO_PROTOTYPE
#define __NR32AN0_mq_getsetattr           TODO_PROTOTYPE
#define __NR32AN0_kexec_load              TODO_PROTOTYPE
#define __NR32AN0_waitid                  idtype
#define __NR32AN1_waitid                  id
#define __NR32AN2_waitid                  infop
#define __NR32AN3_waitid                  options
#define __NR32AN4_waitid                  ru
#define __NR32AN0_add_key                 TODO_PROTOTYPE
#define __NR32AN0_request_key             TODO_PROTOTYPE
#define __NR32AN0_keyctl                  TODO_PROTOTYPE
#define __NR32AN0_ioprio_set              which
#define __NR32AN1_ioprio_set              who
#define __NR32AN2_ioprio_set              ioprio
#define __NR32AN0_ioprio_get              which
#define __NR32AN1_ioprio_get              who
#define __NR32AN0_inotify_init            TODO_PROTOTYPE
#define __NR32AN0_inotify_add_watch       TODO_PROTOTYPE
#define __NR32AN0_inotify_rm_watch        TODO_PROTOTYPE
#define __NR32AN0_migrate_pages           TODO_PROTOTYPE
#define __NR32AN0_openat                  dirfd
#define __NR32AN1_openat                  filename
#define __NR32AN2_openat                  oflags
#define __NR32AN3_openat                  mode
#define __NR32AN0_mkdirat                 dirfd
#define __NR32AN1_mkdirat                 pathname
#define __NR32AN2_mkdirat                 mode
#define __NR32AN0_mknodat                 dirfd
#define __NR32AN1_mknodat                 nodename
#define __NR32AN2_mknodat                 mode
#define __NR32AN3_mknodat                 dev
#define __NR32AN0_fchownat                dirfd
#define __NR32AN1_fchownat                filename
#define __NR32AN2_fchownat                owner
#define __NR32AN3_fchownat                group
#define __NR32AN4_fchownat                flags
#define __NR32AN0_futimesat               dirfd
#define __NR32AN1_futimesat               filename
#define __NR32AN2_futimesat               times
#define __NR32AN0_linux_fstatat64         dirfd
#define __NR32AN1_linux_fstatat64         filename
#define __NR32AN2_linux_fstatat64         statbuf
#define __NR32AN3_linux_fstatat64         flags
#define __NR32AN0_unlinkat                dirfd
#define __NR32AN1_unlinkat                name
#define __NR32AN2_unlinkat                flags
#define __NR32AN0_renameat                oldfd
#define __NR32AN1_renameat                oldname
#define __NR32AN2_renameat                newfd
#define __NR32AN3_renameat                newname_or_path
#define __NR32AN0_linkat                  fromfd
#define __NR32AN1_linkat                  existing_file
#define __NR32AN2_linkat                  tofd
#define __NR32AN3_linkat                  target_path
#define __NR32AN4_linkat                  flags
#define __NR32AN0_symlinkat               link_text
#define __NR32AN1_symlinkat               tofd
#define __NR32AN2_symlinkat               target_path
#define __NR32AN0_readlinkat              dirfd
#define __NR32AN1_readlinkat              path
#define __NR32AN2_readlinkat              buf
#define __NR32AN3_readlinkat              buflen
#define __NR32AN0_fchmodat                dirfd
#define __NR32AN1_fchmodat                filename
#define __NR32AN2_fchmodat                mode
#define __NR32AN3_fchmodat                flags
#define __NR32AN0_faccessat               dirfd
#define __NR32AN1_faccessat               filename
#define __NR32AN2_faccessat               type
#define __NR32AN3_faccessat               flags
#define __NR32AN0_pselect6                nfds
#define __NR32AN1_pselect6                readfds
#define __NR32AN2_pselect6                writefds
#define __NR32AN3_pselect6                exceptfds
#define __NR32AN4_pselect6                timeout
#define __NR32AN5_pselect6                sigmask_sigset_and_len
#define __NR32AN0_ppoll                   fds
#define __NR32AN1_ppoll                   nfds
#define __NR32AN2_ppoll                   timeout_ts
#define __NR32AN3_ppoll                   sigmask
#define __NR32AN4_ppoll                   sigsetsize
#define __NR32AN0_unshare                 flags
#define __NR32AN0_set_robust_list         TODO_PROTOTYPE
#define __NR32AN0_get_robust_list         TODO_PROTOTYPE
#define __NR32AN0_splice                  fdin
#define __NR32AN1_splice                  offin
#define __NR32AN2_splice                  fdout
#define __NR32AN3_splice                  offout
#define __NR32AN4_splice                  length
#define __NR32AN5_splice                  flags
#define __NR32AN0_sync_file_range         fd
#define __NR32AN1_sync_file_range         offset
#define __NR32AN2_sync_file_range         count
#define __NR32AN3_sync_file_range         flags
#define __NR32AN0_tee                     fdin
#define __NR32AN1_tee                     fdout
#define __NR32AN2_tee                     length
#define __NR32AN3_tee                     flags
#define __NR32AN0_vmsplice                fdout
#define __NR32AN1_vmsplice                iov
#define __NR32AN2_vmsplice                count
#define __NR32AN3_vmsplice                flags
#define __NR32AN0_move_pages              TODO_PROTOTYPE
#define __NR32AN0_getcpu                  cpu
#define __NR32AN1_getcpu                  node
#define __NR32AN2_getcpu                  tcache
#define __NR32AN0_epoll_pwait             epfd
#define __NR32AN1_epoll_pwait             events
#define __NR32AN2_epoll_pwait             maxevents
#define __NR32AN3_epoll_pwait             timeout
#define __NR32AN4_epoll_pwait             ss
#define __NR32AN0_utimensat               dirfd
#define __NR32AN1_utimensat               filename
#define __NR32AN2_utimensat               times
#define __NR32AN3_utimensat               flags
#define __NR32AN0_signalfd                fd
#define __NR32AN1_signalfd                sigmask
#define __NR32AN2_signalfd                sigsetsize
#define __NR32AN0_timerfd_create          clock_id
#define __NR32AN1_timerfd_create          flags
#define __NR32AN0_eventfd                 initval
#define __NR32AN0_fallocate               fd
#define __NR32AN1_fallocate               mode
#define __NR32AN2_fallocate               offset
#define __NR32AN3_fallocate               length
#define __NR32AN0_timerfd_settime         ufd
#define __NR32AN1_timerfd_settime         flags
#define __NR32AN2_timerfd_settime         utmr
#define __NR32AN3_timerfd_settime         otmr
#define __NR32AN0_timerfd_gettime         ufd
#define __NR32AN1_timerfd_gettime         otmr
#define __NR32AN0_signalfd4               fd
#define __NR32AN1_signalfd4               sigmask
#define __NR32AN2_signalfd4               sigsetsize
#define __NR32AN3_signalfd4               flags
#define __NR32AN0_eventfd2                initval
#define __NR32AN1_eventfd2                flags
#define __NR32AN0_epoll_create1           flags
#define __NR32AN0_dup3                    oldfd
#define __NR32AN1_dup3                    newfd
#define __NR32AN2_dup3                    flags
#define __NR32AN0_pipe2                   pipedes
#define __NR32AN1_pipe2                   flags
#define __NR32AN0_inotify_init1           TODO_PROTOTYPE
#define __NR32AN0_preadv                  fd
#define __NR32AN1_preadv                  iovec
#define __NR32AN2_preadv                  count
#define __NR32AN3_preadv                  offset
#define __NR32AN0_pwritev                 fd
#define __NR32AN1_pwritev                 iovec
#define __NR32AN2_pwritev                 count
#define __NR32AN3_pwritev                 offset
#define __NR32AN0_rt_tgsigqueueinfo       tgid
#define __NR32AN1_rt_tgsigqueueinfo       tid
#define __NR32AN2_rt_tgsigqueueinfo       signo
#define __NR32AN3_rt_tgsigqueueinfo       uinfo
#define __NR32AN0_perf_event_open         TODO_PROTOTYPE
#define __NR32AN0_recvmmsg                sockfd
#define __NR32AN1_recvmmsg                vmessages
#define __NR32AN2_recvmmsg                vlen
#define __NR32AN3_recvmmsg                flags
#define __NR32AN4_recvmmsg                tmo
#define __NR32AN0_fanotify_init           TODO_PROTOTYPE
#define __NR32AN0_fanotify_mark           TODO_PROTOTYPE
#define __NR32AN0_prlimit64               pid
#define __NR32AN1_prlimit64               resource
#define __NR32AN2_prlimit64               new_limit
#define __NR32AN3_prlimit64               old_limit
#define __NR32AN0_name_to_handle_at       dirfd
#define __NR32AN1_name_to_handle_at       name
#define __NR32AN2_name_to_handle_at       handle
#define __NR32AN3_name_to_handle_at       mnt_id
#define __NR32AN4_name_to_handle_at       flags
#define __NR32AN0_open_by_handle_at       mountdirfd
#define __NR32AN1_open_by_handle_at       handle
#define __NR32AN2_open_by_handle_at       flags
#define __NR32AN0_clock_adjtime           TODO_PROTOTYPE
#define __NR32AN0_syncfs                  fd
#define __NR32AN0_sendmmsg                sockfd
#define __NR32AN1_sendmmsg                vmessages
#define __NR32AN2_sendmmsg                vlen
#define __NR32AN3_sendmmsg                flags
#define __NR32AN0_setns                   fd
#define __NR32AN1_setns                   nstype
#define __NR32AN0_process_vm_readv        pid
#define __NR32AN1_process_vm_readv        lvec
#define __NR32AN2_process_vm_readv        liovcnt
#define __NR32AN3_process_vm_readv        rvec
#define __NR32AN4_process_vm_readv        riovcnt
#define __NR32AN5_process_vm_readv        flags
#define __NR32AN0_process_vm_writev       pid
#define __NR32AN1_process_vm_writev       lvec
#define __NR32AN2_process_vm_writev       liovcnt
#define __NR32AN3_process_vm_writev       rvec
#define __NR32AN4_process_vm_writev       riovcnt
#define __NR32AN5_process_vm_writev       flags
#define __NR32AN0_kcmp                    pid1
#define __NR32AN1_kcmp                    pid2
#define __NR32AN2_kcmp                    type
#define __NR32AN3_kcmp                    idx1
#define __NR32AN4_kcmp                    idx2
#define __NR32AN0_finit_module            TODO_PROTOTYPE
#define __NR32AN0_sched_setattr           TODO_PROTOTYPE
#define __NR32AN0_sched_getattr           TODO_PROTOTYPE
#define __NR32AN0_renameat2               olddirfd
#define __NR32AN1_renameat2               oldpath
#define __NR32AN2_renameat2               newdirfd
#define __NR32AN3_renameat2               newpath
#define __NR32AN4_renameat2               flags
#define __NR32AN0_seccomp                 TODO_PROTOTYPE
#define __NR32AN0_getrandom               TODO_PROTOTYPE
#define __NR32AN0_memfd_create            TODO_PROTOTYPE
#define __NR32AN0_bpf                     TODO_PROTOTYPE
#define __NR32AN0_execveat                dirfd
#define __NR32AN1_execveat                pathname
#define __NR32AN2_execveat                argv
#define __NR32AN3_execveat                envp
#define __NR32AN4_execveat                flags
#define __NR32AN0_socket                  domain
#define __NR32AN1_socket                  type
#define __NR32AN2_socket                  protocol
#define __NR32AN0_socketpair              domain
#define __NR32AN1_socketpair              type
#define __NR32AN2_socketpair              protocol
#define __NR32AN3_socketpair              fds
#define __NR32AN0_bind                    sockfd
#define __NR32AN1_bind                    addr
#define __NR32AN2_bind                    addr_len
#define __NR32AN0_connect                 sockfd
#define __NR32AN1_connect                 addr
#define __NR32AN2_connect                 addr_len
#define __NR32AN0_listen                  sockfd
#define __NR32AN1_listen                  max_backlog
#define __NR32AN0_accept4                 sockfd
#define __NR32AN1_accept4                 addr
#define __NR32AN2_accept4                 addr_len
#define __NR32AN3_accept4                 flags
#define __NR32AN0_getsockopt              sockfd
#define __NR32AN1_getsockopt              level
#define __NR32AN2_getsockopt              optname
#define __NR32AN3_getsockopt              optval
#define __NR32AN4_getsockopt              optlen
#define __NR32AN0_setsockopt              sockfd
#define __NR32AN1_setsockopt              level
#define __NR32AN2_setsockopt              optname
#define __NR32AN3_setsockopt              optval
#define __NR32AN4_setsockopt              optlen
#define __NR32AN0_getsockname             sockfd
#define __NR32AN1_getsockname             addr
#define __NR32AN2_getsockname             addr_len
#define __NR32AN0_getpeername             sockfd
#define __NR32AN1_getpeername             addr
#define __NR32AN2_getpeername             addr_len
#define __NR32AN0_sendto                  sockfd
#define __NR32AN1_sendto                  buf
#define __NR32AN2_sendto                  bufsize
#define __NR32AN3_sendto                  flags
#define __NR32AN4_sendto                  addr
#define __NR32AN5_sendto                  addr_len
#define __NR32AN0_sendmsg                 sockfd
#define __NR32AN1_sendmsg                 message
#define __NR32AN2_sendmsg                 flags
#define __NR32AN0_recvfrom                sockfd
#define __NR32AN1_recvfrom                buf
#define __NR32AN2_recvfrom                bufsize
#define __NR32AN3_recvfrom                flags
#define __NR32AN4_recvfrom                addr
#define __NR32AN5_recvfrom                addr_len
#define __NR32AN0_recvmsg                 sockfd
#define __NR32AN1_recvmsg                 message
#define __NR32AN2_recvmsg                 flags
#define __NR32AN0_shutdown                sockfd
#define __NR32AN1_shutdown                how
#define __NR32AN0_userfaultfd             TODO_PROTOTYPE
#define __NR32AN0_membarrier              TODO_PROTOTYPE
#define __NR32AN0_mlock2                  TODO_PROTOTYPE
#define __NR32AN0_hop                     fd
#define __NR32AN1_hop                     command
#define __NR32AN2_hop                     arg
#define __NR32AN0_hopf                    fd
#define __NR32AN1_hopf                    command
#define __NR32AN2_hopf                    mode
#define __NR32AN3_hopf                    arg
#define __NR32AN0_readf                   fd
#define __NR32AN1_readf                   buf
#define __NR32AN2_readf                   bufsize
#define __NR32AN3_readf                   mode
#define __NR32AN0_writef                  fd
#define __NR32AN1_writef                  buf
#define __NR32AN2_writef                  bufsize
#define __NR32AN3_writef                  mode
#define __NR32AN0_detach                  pid
#define __NR32AN0_frealpath4              fd
#define __NR32AN1_frealpath4              buf
#define __NR32AN2_frealpath4              buflen
#define __NR32AN3_frealpath4              flags
#define __NR32AN0_frealpathat             dirfd
#define __NR32AN1_frealpathat             filename
#define __NR32AN2_frealpathat             buf
#define __NR32AN3_frealpathat             buflen
#define __NR32AN4_frealpathat             flags
#define __NR32AN0_rpc_schedule            target
#define __NR32AN1_rpc_schedule            flags
#define __NR32AN2_rpc_schedule            program
#define __NR32AN3_rpc_schedule            arguments
#define __NR32AN0_sysctl                  command
#define __NR32AN1_sysctl                  arg
#define __NR32AN0_openpty                 amaster
#define __NR32AN1_openpty                 aslave
#define __NR32AN2_openpty                 name
#define __NR32AN3_openpty                 termp
#define __NR32AN4_openpty                 winp
#define __NR32AN0_fchdirat                dirfd
#define __NR32AN1_fchdirat                path
#define __NR32AN2_fchdirat                flags
#define __NR32AN0_time64                  timer
#define __NR32AN0_set_exception_handler   mode
#define __NR32AN1_set_exception_handler   handler
#define __NR32AN2_set_exception_handler   handler_sp
#define __NR32AN0_get_exception_handler   pmode
#define __NR32AN1_get_exception_handler   phandler
#define __NR32AN2_get_exception_handler   phandler_sp
#define __NR32AN0_set_library_listdef     listdef
#define __NR32AN0_debugtrap               state
#define __NR32AN1_debugtrap               reason
#define __NR32AN0_lfutex                  uaddr
#define __NR32AN1_lfutex                  futex_op
#define __NR32AN2_lfutex                  val
#define __NR32AN3_lfutex                  timeout
#define __NR32AN4_lfutex                  val2
#define __NR32AN0_lseek64                 fd
#define __NR32AN1_lseek64                 offset
#define __NR32AN2_lseek64                 whence
#define __NR32AN0_lfutexexpr              base
#define __NR32AN1_lfutexexpr              exprc
#define __NR32AN2_lfutexexpr              exprv
#define __NR32AN3_lfutexexpr              timeout
#define __NR32AN4_lfutexexpr              timeout_flags
#define __NR32AN0_lfutexlockexpr          ulockaddr
#define __NR32AN1_lfutexlockexpr          base
#define __NR32AN2_lfutexlockexpr          exprc
#define __NR32AN3_lfutexlockexpr          exprv
#define __NR32AN4_lfutexlockexpr          timeout
#define __NR32AN5_lfutexlockexpr          timeout_flags
#define __NR32AN0_mktty                   keyboard
#define __NR32AN1_mktty                   display
#define __NR32AN2_mktty                   name
#define __NR32AN3_mktty                   rsvd
#define __NR32AN0_raiseat                 state
#define __NR32AN1_raiseat                 si
#define __NR32AN0_coredump                curr_state
#define __NR32AN1_coredump                orig_state
#define __NR32AN2_coredump                traceback_vector
#define __NR32AN3_coredump                traceback_length
#define __NR32AN4_coredump                exception
#define __NR32AN5_coredump                unwind_error
#define __NR32AN0_stime64                 t
#define __NR32AN0_utime64                 filename
#define __NR32AN1_utime64                 times
#define __NR32AN0_ioctlf                  fd
#define __NR32AN1_ioctlf                  command
#define __NR32AN2_ioctlf                  mode
#define __NR32AN3_ioctlf                  arg
#define __NR32AN0_fsmode                  mode
#define __NR32AN0_gettimeofday64          tv
#define __NR32AN1_gettimeofday64          tz
#define __NR32AN0_settimeofday64          tv
#define __NR32AN1_settimeofday64          tz
#define __NR32AN0_select64                nfds
#define __NR32AN1_select64                readfds
#define __NR32AN2_select64                writefds
#define __NR32AN3_select64                exceptfds
#define __NR32AN4_select64                timeout
#define __NR32AN0_maplibrary              addr
#define __NR32AN1_maplibrary              flags
#define __NR32AN2_maplibrary              fd
#define __NR32AN3_maplibrary              hdrv
#define __NR32AN4_maplibrary              hdrc
#define __NR32AN0_setitimer64             which
#define __NR32AN1_setitimer64             newval
#define __NR32AN2_setitimer64             oldval
#define __NR32AN0_getitimer64             which
#define __NR32AN1_getitimer64             curr_value
#define __NR32AN0_kreaddir                fd
#define __NR32AN1_kreaddir                buf
#define __NR32AN2_kreaddir                bufsize
#define __NR32AN3_kreaddir                mode
#define __NR32AN0_readvf                  fd
#define __NR32AN1_readvf                  iovec
#define __NR32AN2_readvf                  count
#define __NR32AN3_readvf                  mode
#define __NR32AN0_writevf                 fd
#define __NR32AN1_writevf                 iovec
#define __NR32AN2_writevf                 count
#define __NR32AN3_writevf                 mode
#define __NR32AN0_sched_rr_get_interval64 pid
#define __NR32AN1_sched_rr_get_interval64 tms
#define __NR32AN0_nanosleep64             req
#define __NR32AN1_nanosleep64             rem
#define __NR32AN0_rt_sigtimedwait64       set
#define __NR32AN1_rt_sigtimedwait64       info
#define __NR32AN2_rt_sigtimedwait64       timeout
#define __NR32AN3_rt_sigtimedwait64       sigsetsize
#define __NR32AN0_pread64f                fd
#define __NR32AN1_pread64f                buf
#define __NR32AN2_pread64f                bufsize
#define __NR32AN3_pread64f                offset
#define __NR32AN4_pread64f                mode
#define __NR32AN0_pwrite64f               fd
#define __NR32AN1_pwrite64f               buf
#define __NR32AN2_pwrite64f               bufsize
#define __NR32AN3_pwrite64f               offset
#define __NR32AN4_pwrite64f               mode
#define __NR32AN0_kstat                   filename
#define __NR32AN1_kstat                   statbuf
#define __NR32AN0_klstat                  filename
#define __NR32AN1_klstat                  statbuf
#define __NR32AN0_kfstat                  fd
#define __NR32AN1_kfstat                  statbuf
#define __NR32AN0_kreaddirf               fd
#define __NR32AN1_kreaddirf               buf
#define __NR32AN2_kreaddirf               bufsize
#define __NR32AN3_kreaddirf               mode
#define __NR32AN4_kreaddirf               iomode
#define __NR32AN0_timer_settime64         timerid
#define __NR32AN1_timer_settime64         flags
#define __NR32AN2_timer_settime64         value
#define __NR32AN3_timer_settime64         ovalue
#define __NR32AN0_timer_gettime64         timerid
#define __NR32AN1_timer_gettime64         value
#define __NR32AN0_clock_settime64         clock_id
#define __NR32AN1_clock_settime64         tp
#define __NR32AN0_clock_gettime64         clock_id
#define __NR32AN1_clock_gettime64         tp
#define __NR32AN0_clock_getres64          clock_id
#define __NR32AN1_clock_getres64          res
#define __NR32AN0_clock_nanosleep64       clock_id
#define __NR32AN1_clock_nanosleep64       flags
#define __NR32AN2_clock_nanosleep64       requested_time
#define __NR32AN3_clock_nanosleep64       remaining
#define __NR32AN0_utimes64                filename
#define __NR32AN1_utimes64                times
#define __NR32AN0_fmkdirat                dirfd
#define __NR32AN1_fmkdirat                pathname
#define __NR32AN2_fmkdirat                mode
#define __NR32AN3_fmkdirat                flags
#define __NR32AN0_fmknodat                dirfd
#define __NR32AN1_fmknodat                nodename
#define __NR32AN2_fmknodat                mode
#define __NR32AN3_fmknodat                dev
#define __NR32AN4_fmknodat                flags
#define __NR32AN0_futimesat64             dirfd
#define __NR32AN1_futimesat64             filename
#define __NR32AN2_futimesat64             times
#define __NR32AN0_kfstatat                dirfd
#define __NR32AN1_kfstatat                filename
#define __NR32AN2_kfstatat                statbuf
#define __NR32AN3_kfstatat                flags
#define __NR32AN0_frenameat               oldfd
#define __NR32AN1_frenameat               oldname
#define __NR32AN2_frenameat               newfd
#define __NR32AN3_frenameat               newname_or_path
#define __NR32AN4_frenameat               flags
#define __NR32AN0_fsymlinkat              link_text
#define __NR32AN1_fsymlinkat              tofd
#define __NR32AN2_fsymlinkat              target_path
#define __NR32AN3_fsymlinkat              flags
#define __NR32AN0_freadlinkat             dirfd
#define __NR32AN1_freadlinkat             path
#define __NR32AN2_freadlinkat             buf
#define __NR32AN3_freadlinkat             buflen
#define __NR32AN4_freadlinkat             flags
#define __NR32AN0_pselect6_64             nfds
#define __NR32AN1_pselect6_64             readfds
#define __NR32AN2_pselect6_64             writefds
#define __NR32AN3_pselect6_64             exceptfds
#define __NR32AN4_pselect6_64             timeout
#define __NR32AN5_pselect6_64             sigmask_sigset_and_len
#define __NR32AN0_ppoll64                 fds
#define __NR32AN1_ppoll64                 nfds
#define __NR32AN2_ppoll64                 timeout_ts
#define __NR32AN3_ppoll64                 sigmask
#define __NR32AN4_ppoll64                 sigsetsize
#define __NR32AN0_utimensat64             dirfd
#define __NR32AN1_utimensat64             filename
#define __NR32AN2_utimensat64             times
#define __NR32AN3_utimensat64             flags
#define __NR32AN0_fallocate64             fd
#define __NR32AN1_fallocate64             mode
#define __NR32AN2_fallocate64             offset
#define __NR32AN3_fallocate64             length
#define __NR32AN0_timerfd_settime64       ufd
#define __NR32AN1_timerfd_settime64       flags
#define __NR32AN2_timerfd_settime64       utmr
#define __NR32AN3_timerfd_settime64       otmr
#define __NR32AN0_timerfd_gettime64       ufd
#define __NR32AN1_timerfd_gettime64       otmr
#define __NR32AN0_preadvf                 fd
#define __NR32AN1_preadvf                 iovec
#define __NR32AN2_preadvf                 count
#define __NR32AN3_preadvf                 offset
#define __NR32AN4_preadvf                 mode
#define __NR32AN0_pwritevf                fd
#define __NR32AN1_pwritevf                iovec
#define __NR32AN2_pwritevf                count
#define __NR32AN3_pwritevf                offset
#define __NR32AN4_pwritevf                mode
#define __NR32AN0_recvmmsg64              sockfd
#define __NR32AN1_recvmmsg64              vmessages
#define __NR32AN2_recvmmsg64              vlen
#define __NR32AN3_recvmmsg64              flags
#define __NR32AN4_recvmmsg64              tmo
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES */
#endif /* __WANT_SYSCALL_ARGUMENT_NAMES */


/************************************************************************/
/* SYSCALL ARGUMENT FORMAT                                              */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_FORMAT
#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#define __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT 1
#define __NR32ATRF0_exit                    "%" PRIuSIZ
#define __NR32ATRA0_exit(status)            ,(uintptr_t)(status)
#define __NR32ATRF0_read                    "%d"
#define __NR32ATRA0_read(fd, buf, bufsize)  ,(int)(fd)
#define __NR32ATRF1_read                    "%p"
#define __NR32ATRA1_read(fd, buf, bufsize)  ,buf
#define __NR32ATRF2_read                    "%" PRIuSIZ
#define __NR32ATRA2_read(fd, buf, bufsize)  ,bufsize
#define __NR32ATRF0_write                   "%d"
#define __NR32ATRA0_write(fd, buf, bufsize) ,(int)(fd)
#define __NR32ATRF1_write                   "%p"
#define __NR32ATRA1_write(fd, buf, bufsize) ,buf
#define __NR32ATRF2_write                   "%" PRIuSIZ
#define __NR32ATRA2_write(fd, buf, bufsize) ,bufsize
#define __NR32ATRF0_open                    "%q"
#define __NR32ATRA0_open(filename, oflags, mode) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_open                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA1_open(filename, oflags, mode) ,(uintptr_t)(oflags),(oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
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
#define __NR32ATRF2_open                    "%#" PRIoSIZ
#define __NR32ATRA2_open(filename, oflags, mode) ,(uintptr_t)(mode)
#define __NR32ATRF0_close                   "%d"
#define __NR32ATRA0_close(fd)               ,(int)(fd)
#define __NR32ATRF0_waitpid                 "%" PRIdSIZ
#define __NR32ATRA0_waitpid(pid, stat_loc, options) ,(intptr_t)(pid)
#define __NR32ATRF1_waitpid                 "%p"
#define __NR32ATRA1_waitpid(pid, stat_loc, options) ,stat_loc
#define __NR32ATRF2_waitpid                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR32ATRA2_waitpid(pid, stat_loc, options) ,(uintptr_t)(options),(options) & WNOHANG ? "WNOHANG" : "" \
                                                    ,((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "",(options) & WUNTRACED ? "WUNTRACED" : "" \
                                                    ,((options) & WCONTINUED) && ((options) & (WNOHANG|WUNTRACED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                    ,((options) & WNOWAIT) && ((options) & (WNOHANG|WUNTRACED|WCONTINUED)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NR32ATRF0_creat                   "%q"
#define __NR32ATRA0_creat(filename, mode)   ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_creat                   "%#" PRIoSIZ
#define __NR32ATRA1_creat(filename, mode)   ,(uintptr_t)(mode)
#define __NR32ATRF0_link                    "%q"
#define __NR32ATRA0_link(existing_file, link_file) ,(validate_readable_opt(existing_file,1),existing_file)
#define __NR32ATRF1_link                    "%q"
#define __NR32ATRA1_link(existing_file, link_file) ,(validate_readable_opt(link_file,1),link_file)
#define __NR32ATRF0_unlink                  "%q"
#define __NR32ATRA0_unlink(filename)        ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF0_execve                  "%q"
#define __NR32ATRA0_execve(path, argv, envp) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_execve                  "%p"
#define __NR32ATRA1_execve(path, argv, envp) ,argv
#define __NR32ATRF2_execve                  "%p"
#define __NR32ATRA2_execve(path, argv, envp) ,envp
#define __NR32ATRF0_chdir                   "%q"
#define __NR32ATRA0_chdir(path)             ,(validate_readable_opt(path,1),path)
#define __NR32ATRF0_time                    "%p"
#define __NR32ATRA0_time(timer)             ,timer
#define __NR32ATRF0_mknod                   "%q"
#define __NR32ATRA0_mknod(nodename, mode, dev) ,(validate_readable_opt(nodename,1),nodename)
#define __NR32ATRF1_mknod                   "%#" PRIoSIZ
#define __NR32ATRA1_mknod(nodename, mode, dev) ,(uintptr_t)(mode)
#define __NR32ATRF2_mknod                   "%.2x:%.2x"
#define __NR32ATRA2_mknod(nodename, mode, dev) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR32ATRF0_chmod                   "%q"
#define __NR32ATRA0_chmod(filename, mode)   ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_chmod                   "%#" PRIoSIZ
#define __NR32ATRA1_chmod(filename, mode)   ,(uintptr_t)(mode)
#define __NR32ATRF0_lchown                  "%q"
#define __NR32ATRA0_lchown(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_lchown                  "%" PRIu16
#define __NR32ATRA1_lchown(filename, owner, group) ,owner
#define __NR32ATRF2_lchown                  "%" PRIu16
#define __NR32ATRA2_lchown(filename, owner, group) ,group
#define __NR32ATRF0_linux_oldstat           "%q"
#define __NR32ATRA0_linux_oldstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_oldstat           "%p"
#define __NR32ATRA1_linux_oldstat(filename, statbuf) ,statbuf
#define __NR32ATRF0_lseek                   "%d"
#define __NR32ATRA0_lseek(fd, offset, whence) ,(int)(fd)
#define __NR32ATRF1_lseek                   "%" PRIdSIZ
#define __NR32ATRA1_lseek(fd, offset, whence) ,(intptr_t)(offset)
#define __NR32ATRF2_lseek                   "%#Ix=%s"
#define __NR32ATRA2_lseek(fd, offset, whence) ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NR32ATRF0_mount                   "%q"
#define __NR32ATRA0_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(special_file,1),special_file)
#define __NR32ATRF1_mount                   "%q"
#define __NR32ATRA1_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(dir,1),dir)
#define __NR32ATRF2_mount                   "%q"
#define __NR32ATRA2_mount(special_file, dir, fstype, rwflag, data) ,(validate_readable_opt(fstype,1),fstype)
#define __NR32ATRF3_mount                   "%#" PRIxSIZ
#define __NR32ATRA3_mount(special_file, dir, fstype, rwflag, data) ,(uintptr_t)(rwflag)
#define __NR32ATRF4_mount                   "%p"
#define __NR32ATRA4_mount(special_file, dir, fstype, rwflag, data) ,data
#define __NR32ATRF0_umount                  "%q"
#define __NR32ATRA0_umount(special_file)    ,(validate_readable_opt(special_file,1),special_file)
#define __NR32ATRF0_setuid                  "%" PRIu16
#define __NR32ATRA0_setuid(uid)             ,uid
#define __NR32ATRF0_stime                   "%p"
#define __NR32ATRA0_stime(t)                ,t
#define __NR32ATRF0_ptrace                  "%#" PRIxSIZ
#define __NR32ATRA0_ptrace(request, pid, addr, data) ,(uintptr_t)(request)
#define __NR32ATRF1_ptrace                  "%" PRIdSIZ
#define __NR32ATRA1_ptrace(request, pid, addr, data) ,(intptr_t)(pid)
#define __NR32ATRF2_ptrace                  "%p"
#define __NR32ATRA2_ptrace(request, pid, addr, data) ,addr
#define __NR32ATRF3_ptrace                  "%p"
#define __NR32ATRA3_ptrace(request, pid, addr, data) ,data
#define __NR32ATRF0_alarm                   "%#" PRIxSIZ
#define __NR32ATRA0_alarm(seconds)          ,(uintptr_t)(seconds)
#define __NR32ATRF0_linux_oldfstat          "%d"
#define __NR32ATRA0_linux_oldfstat(fd, statbuf) ,(int)(fd)
#define __NR32ATRF1_linux_oldfstat          "%p"
#define __NR32ATRA1_linux_oldfstat(fd, statbuf) ,statbuf
#define __NR32ATRF0_utime                   "%q"
#define __NR32ATRA0_utime(filename, times)  ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_utime                   "%p"
#define __NR32ATRA1_utime(filename, times)  ,times
#define __NR32ATRF0_access                  "%q"
#define __NR32ATRA0_access(filename, type)  ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_access                  "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA1_access(filename, type)  ,(uintptr_t)(type),(type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                            ,((type) & W_OK) && ((type) & (R_OK)) ? "|" : "",(type) & W_OK ? "W_OK" : "" \
                                            ,((type) & X_OK) && ((type) & (R_OK|W_OK)) ? "|" : "",(type) & X_OK ? "X_OK" : ""
#define __NR32ATRF0_nice                    "%" PRIdSIZ
#define __NR32ATRA0_nice(inc)               ,(intptr_t)(inc)
#define __NR32ATRF0_ftime                   "%p"
#define __NR32ATRA0_ftime(tp)               ,tp
#define __NR32ATRF0_kill                    "%" PRIdSIZ
#define __NR32ATRA0_kill(pid, signo)        ,(intptr_t)(pid)
#define __NR32ATRF1_kill                    "%#" PRIxSIZ
#define __NR32ATRA1_kill(pid, signo)        ,(uintptr_t)(signo)
#define __NR32ATRF0_rename                  "%q"
#define __NR32ATRA0_rename(oldname, newname_or_path) ,(validate_readable_opt(oldname,1),oldname)
#define __NR32ATRF1_rename                  "%q"
#define __NR32ATRA1_rename(oldname, newname_or_path) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NR32ATRF0_mkdir                   "%q"
#define __NR32ATRA0_mkdir(pathname, mode)   ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF1_mkdir                   "%#" PRIoSIZ
#define __NR32ATRA1_mkdir(pathname, mode)   ,(uintptr_t)(mode)
#define __NR32ATRF0_rmdir                   "%q"
#define __NR32ATRA0_rmdir(path)             ,(validate_readable_opt(path,1),path)
#define __NR32ATRF0_dup                     "%d"
#define __NR32ATRA0_dup(fd)                 ,(int)(fd)
#define __NR32ATRF0_pipe                    "%p"
#define __NR32ATRA0_pipe(pipedes)           ,pipedes
#define __NR32ATRF0_times                   "%p"
#define __NR32ATRA0_times(buf)              ,buf
#define __NR32ATRF0_brk                     "%p"
#define __NR32ATRA0_brk(addr)               ,addr
#define __NR32ATRF0_setgid                  "%" PRIu16
#define __NR32ATRA0_setgid(gid)             ,gid
#define __NR32ATRF0_signal                  "%#" PRIxSIZ
#define __NR32ATRA0_signal(signo, handler)  ,(uintptr_t)(signo)
#define __NR32ATRF1_signal                  "%p"
#define __NR32ATRA1_signal(signo, handler)  ,handler
#define __NR32ATRF0_acct                    "%q"
#define __NR32ATRA0_acct(filename)          ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF0_umount2                 "%q"
#define __NR32ATRA0_umount2(special_file, flags) ,(validate_readable_opt(special_file,1),special_file)
#define __NR32ATRF1_umount2                 "%#" PRIxSIZ
#define __NR32ATRA1_umount2(special_file, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_ioctl                   "%d"
#define __NR32ATRA0_ioctl(fd, request, arg) ,(int)(fd)
#define __NR32ATRF1_ioctl                   "%#" PRIxSIZ
#define __NR32ATRA1_ioctl(fd, request, arg) ,(uintptr_t)(request)
#define __NR32ATRF2_ioctl                   "%p"
#define __NR32ATRA2_ioctl(fd, request, arg) ,arg
#define __NR32ATRF0_fcntl                   "%d"
#define __NR32ATRA0_fcntl(fd, cmd, arg)     ,(int)(fd)
#define __NR32ATRF1_fcntl                   "%#" PRIxSIZ
#define __NR32ATRA1_fcntl(fd, cmd, arg)     ,(uintptr_t)(cmd)
#define __NR32ATRF2_fcntl                   "%p"
#define __NR32ATRA2_fcntl(fd, cmd, arg)     ,arg
#define __NR32ATRF0_setpgid                 "%" PRIdSIZ
#define __NR32ATRA0_setpgid(pid, pgid)      ,(intptr_t)(pid)
#define __NR32ATRF1_setpgid                 "%" PRIdSIZ
#define __NR32ATRA1_setpgid(pid, pgid)      ,(intptr_t)(pgid)
#define __NR32ATRF0_oldolduname             "%p"
#define __NR32ATRA0_oldolduname(name)       ,name
#define __NR32ATRF0_umask                   "%#" PRIoSIZ
#define __NR32ATRA0_umask(mode)             ,(uintptr_t)(mode)
#define __NR32ATRF0_chroot                  "%q"
#define __NR32ATRA0_chroot(path)            ,(validate_readable_opt(path,1),path)
#define __NR32ATRF0_ustat                   "%.2x:%.2x"
#define __NR32ATRA0_ustat(dev, ubuf)        ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR32ATRF1_ustat                   "%p"
#define __NR32ATRA1_ustat(dev, ubuf)        ,ubuf
#define __NR32ATRF0_dup2                    "%d"
#define __NR32ATRA0_dup2(oldfd, newfd)      ,(int)(oldfd)
#define __NR32ATRF1_dup2                    "%d"
#define __NR32ATRA1_dup2(oldfd, newfd)      ,(int)(newfd)
#define __NR32ATRF0_sigaction               "%#" PRIxSIZ
#define __NR32ATRA0_sigaction(signo, act, oact) ,(uintptr_t)(signo)
#define __NR32ATRF1_sigaction               "%p"
#define __NR32ATRA1_sigaction(signo, act, oact) ,act
#define __NR32ATRF2_sigaction               "%p"
#define __NR32ATRA2_sigaction(signo, act, oact) ,oact
#define __NR32ATRF0_ssetmask                "%#" PRIxSIZ
#define __NR32ATRA0_ssetmask(sigmask)       ,(uintptr_t)(sigmask)
#define __NR32ATRF0_setreuid                "%" PRIu16
#define __NR32ATRA0_setreuid(ruid, euid)    ,ruid
#define __NR32ATRF1_setreuid                "%" PRIu16
#define __NR32ATRA1_setreuid(ruid, euid)    ,euid
#define __NR32ATRF0_setregid                "%" PRIu16
#define __NR32ATRA0_setregid(rgid, egid)    ,rgid
#define __NR32ATRF1_setregid                "%" PRIu16
#define __NR32ATRA1_setregid(rgid, egid)    ,egid
#define __NR32ATRF0_sigsuspend              "%p"
#define __NR32ATRA0_sigsuspend(set)         ,set
#define __NR32ATRF0_sigpending              "%p"
#define __NR32ATRA0_sigpending(set)         ,set
#define __NR32ATRF0_sethostname             "%q"
#define __NR32ATRA0_sethostname(name, len)  ,(validate_readable_opt(name,1),name)
#define __NR32ATRF1_sethostname             "%" PRIuSIZ
#define __NR32ATRA1_sethostname(name, len)  ,len
#define __NR32ATRF0_setrlimit               "%#" PRIxSIZ
#define __NR32ATRA0_setrlimit(resource, rlimits) ,(uintptr_t)(resource)
#define __NR32ATRF1_setrlimit               "%p"
#define __NR32ATRA1_setrlimit(resource, rlimits) ,rlimits
#define __NR32ATRF0_getrlimit               "%#" PRIxSIZ
#define __NR32ATRA0_getrlimit(resource, rlimits) ,(uintptr_t)(resource)
#define __NR32ATRF1_getrlimit               "%p"
#define __NR32ATRA1_getrlimit(resource, rlimits) ,rlimits
#define __NR32ATRF0_getrusage               "%" PRIdSIZ
#define __NR32ATRA0_getrusage(who, usage)   ,(intptr_t)(who)
#define __NR32ATRF1_getrusage               "%p"
#define __NR32ATRA1_getrusage(who, usage)   ,usage
#define __NR32ATRF0_gettimeofday            "%p"
#define __NR32ATRA0_gettimeofday(tv, tz)    ,tv
#define __NR32ATRF1_gettimeofday            "%p"
#define __NR32ATRA1_gettimeofday(tv, tz)    ,tz
#define __NR32ATRF0_settimeofday            "%p"
#define __NR32ATRA0_settimeofday(tv, tz)    ,tv
#define __NR32ATRF1_settimeofday            "%p"
#define __NR32ATRA1_settimeofday(tv, tz)    ,tz
#define __NR32ATRF0_getgroups               "%" PRIuSIZ
#define __NR32ATRA0_getgroups(size, list)   ,size
#define __NR32ATRF1_getgroups               "%p"
#define __NR32ATRA1_getgroups(size, list)   ,list
#define __NR32ATRF0_setgroups               "%" PRIuSIZ
#define __NR32ATRA0_setgroups(count, groups) ,count
#define __NR32ATRF1_setgroups               "%p"
#define __NR32ATRA1_setgroups(count, groups) ,groups
#define __NR32ATRF0_select                  "%" PRIuSIZ
#define __NR32ATRA0_select(nfds, readfds, writefds, exceptfds, timeout) ,nfds
#define __NR32ATRF1_select                  "%p"
#define __NR32ATRA1_select(nfds, readfds, writefds, exceptfds, timeout) ,readfds
#define __NR32ATRF2_select                  "%p"
#define __NR32ATRA2_select(nfds, readfds, writefds, exceptfds, timeout) ,writefds
#define __NR32ATRF3_select                  "%p"
#define __NR32ATRA3_select(nfds, readfds, writefds, exceptfds, timeout) ,exceptfds
#define __NR32ATRF4_select                  "%p"
#define __NR32ATRA4_select(nfds, readfds, writefds, exceptfds, timeout) ,timeout
#define __NR32ATRF0_symlink                 "%q"
#define __NR32ATRA0_symlink(link_text, target_path) ,(validate_readable_opt(link_text,1),link_text)
#define __NR32ATRF1_symlink                 "%q"
#define __NR32ATRA1_symlink(link_text, target_path) ,(validate_readable_opt(target_path,1),target_path)
#define __NR32ATRF0_linux_oldlstat          "%q"
#define __NR32ATRA0_linux_oldlstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_oldlstat          "%p"
#define __NR32ATRA1_linux_oldlstat(filename, statbuf) ,statbuf
#define __NR32ATRF0_readlink                "%q"
#define __NR32ATRA0_readlink(path, buf, buflen) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_readlink                "%p"
#define __NR32ATRA1_readlink(path, buf, buflen) ,buf
#define __NR32ATRF2_readlink                "%" PRIuSIZ
#define __NR32ATRA2_readlink(path, buf, buflen) ,buflen
#define __NR32ATRF0_uselib                  "%q"
#define __NR32ATRA0_uselib(library)         ,(validate_readable_opt(library,1),library)
#define __NR32ATRF0_swapon                  "%q"
#define __NR32ATRA0_swapon(pathname, swapflags) ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF1_swapon                  "%#" PRIxSIZ "=%s%s%s"
#define __NR32ATRA1_swapon(pathname, swapflags) ,(uintptr_t)(swapflags),(swapflags) & SWAP_FLAG_PREFER ? "SWAP_FLAG_PREFER" : "" \
                                                ,((swapflags) & SWAP_FLAG_DISCARD) && ((swapflags) & (SWAP_FLAG_PREFER)) ? "|" : "",(swapflags) & SWAP_FLAG_DISCARD ? "SWAP_FLAG_DISCARD" : ""
#define __NR32ATRF0_reboot                  "%#" PRIxSIZ
#define __NR32ATRA0_reboot(how)             ,(uintptr_t)(how)
#define __NR32ATRF0_readdir                 "%d"
#define __NR32ATRA0_readdir(fd, dirp, count) ,(int)(fd)
#define __NR32ATRF1_readdir                 "%p"
#define __NR32ATRA1_readdir(fd, dirp, count) ,dirp
#define __NR32ATRF2_readdir                 "%" PRIuSIZ
#define __NR32ATRA2_readdir(fd, dirp, count) ,count
#define __NR32ATRF0_mmap                    "%p"
#define __NR32ATRA0_mmap(addr, len, prot, flags, fd, offset) ,addr
#define __NR32ATRF1_mmap                    "%" PRIuSIZ
#define __NR32ATRA1_mmap(addr, len, prot, flags, fd, offset) ,len
#define __NR32ATRF2_mmap                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(prot),(prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                                             ,((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "",(prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                                             ,((prot) & PROT_READ) && ((prot) & (PROT_EXEC|PROT_WRITE)) ? "|" : "",(prot) & PROT_READ ? "PROT_READ" : "" \
                                                             ,((prot) & PROT_SEM) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ)) ? "|" : "",(prot) & PROT_SEM ? "PROT_SEM" : "" \
                                                             ,((prot) & PROT_LOOSE) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM)) ? "|" : "",(prot) & PROT_LOOSE ? "PROT_LOOSE" : "" \
                                                             ,((prot) & PROT_SHARED) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE)) ? "|" : "",(prot) & PROT_SHARED ? "PROT_SHARED" : ""
#define __NR32ATRF3_mmap                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(flags),(flags) & MAP_SHARED ? "MAP_SHARED" : (flags) ? "" : "MAP_AUTOMATIC" \
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
                                                             ,((flags) & MAP_DONT_OVERRIDE) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE|MAP_POPULATE|MAP_NONBLOCK|MAP_STACK|MAP_UNINITIALIZED|MAP_DONT_MAP)) ? "|" : "",(flags) & MAP_DONT_OVERRIDE ? "MAP_DONT_OVERRIDE" : "" \
                                                             ,((flags) & MAP_OFFSET64_POINTER) && ((flags) & (MAP_SHARED|MAP_PRIVATE|MAP_FIXED|MAP_ANON|MAP_32BIT|MAP_GROWSDOWN|MAP_GROWSUP|MAP_LOCKED|MAP_NORESERVE|MAP_POPULATE|MAP_NONBLOCK|MAP_STACK|MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE)) ? "|" : "",(flags) & MAP_OFFSET64_POINTER ? "MAP_OFFSET64_POINTER" : ""
#define __NR32ATRF4_mmap                    "%d"
#define __NR32ATRA4_mmap(addr, len, prot, flags, fd, offset) ,(int)(fd)
#define __NR32ATRF5_mmap                    "%#" PRIxSIZ
#define __NR32ATRA5_mmap(addr, len, prot, flags, fd, offset) ,(uintptr_t)(offset)
#define __NR32ATRF0_munmap                  "%p"
#define __NR32ATRA0_munmap(addr, len)       ,addr
#define __NR32ATRF1_munmap                  "%" PRIuSIZ
#define __NR32ATRA1_munmap(addr, len)       ,len
#define __NR32ATRF0_truncate                "%q"
#define __NR32ATRA0_truncate(filename, length) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_truncate                "%#" PRIxSIZ
#define __NR32ATRA1_truncate(filename, length) ,(uintptr_t)(length)
#define __NR32ATRF0_ftruncate               "%d"
#define __NR32ATRA0_ftruncate(fd, length)   ,(int)(fd)
#define __NR32ATRF1_ftruncate               "%#" PRIxSIZ
#define __NR32ATRA1_ftruncate(fd, length)   ,(uintptr_t)(length)
#define __NR32ATRF0_fchmod                  "%d"
#define __NR32ATRA0_fchmod(fd, mode)        ,(int)(fd)
#define __NR32ATRF1_fchmod                  "%#" PRIoSIZ
#define __NR32ATRA1_fchmod(fd, mode)        ,(uintptr_t)(mode)
#define __NR32ATRF0_fchown                  "%d"
#define __NR32ATRA0_fchown(fd, owner, group) ,(int)(fd)
#define __NR32ATRF1_fchown                  "%" PRIu16
#define __NR32ATRA1_fchown(fd, owner, group) ,owner
#define __NR32ATRF2_fchown                  "%" PRIu16
#define __NR32ATRA2_fchown(fd, owner, group) ,group
#define __NR32ATRF0_getpriority             "%#" PRIxSIZ
#define __NR32ATRA0_getpriority(which, who) ,(uintptr_t)(which)
#define __NR32ATRF1_getpriority             "%" PRIuSIZ
#define __NR32ATRA1_getpriority(which, who) ,(uintptr_t)(who)
#define __NR32ATRF0_setpriority             "%#" PRIxSIZ
#define __NR32ATRA0_setpriority(which, who, value) ,(uintptr_t)(which)
#define __NR32ATRF1_setpriority             "%" PRIuSIZ
#define __NR32ATRA1_setpriority(which, who, value) ,(uintptr_t)(who)
#define __NR32ATRF2_setpriority             "%#" PRIxSIZ
#define __NR32ATRA2_setpriority(which, who, value) ,(uintptr_t)(value)
#define __NR32ATRF0_profil                  "%p"
#define __NR32ATRA0_profil(sample_buffer, size, offset, scale) ,sample_buffer
#define __NR32ATRF1_profil                  "%" PRIuSIZ
#define __NR32ATRA1_profil(sample_buffer, size, offset, scale) ,size
#define __NR32ATRF2_profil                  "%" PRIuSIZ
#define __NR32ATRA2_profil(sample_buffer, size, offset, scale) ,offset
#define __NR32ATRF3_profil                  "%#" PRIxSIZ
#define __NR32ATRA3_profil(sample_buffer, size, offset, scale) ,(uintptr_t)(scale)
#define __NR32ATRF0_statfs                  "%q"
#define __NR32ATRA0_statfs(file, buf)       ,(validate_readable_opt(file,1),file)
#define __NR32ATRF1_statfs                  "%p"
#define __NR32ATRA1_statfs(file, buf)       ,buf
#define __NR32ATRF0_fstatfs                 "%d"
#define __NR32ATRA0_fstatfs(file, buf)      ,(int)(file)
#define __NR32ATRF1_fstatfs                 "%p"
#define __NR32ATRA1_fstatfs(file, buf)      ,buf
#define __NR32ATRF0_ioperm                  "%#" PRIxSIZ
#define __NR32ATRA0_ioperm(from, num, turn_on) ,(uintptr_t)(from)
#define __NR32ATRF1_ioperm                  "%#" PRIxSIZ
#define __NR32ATRA1_ioperm(from, num, turn_on) ,(uintptr_t)(num)
#define __NR32ATRF2_ioperm                  "%#" PRIxSIZ
#define __NR32ATRA2_ioperm(from, num, turn_on) ,(uintptr_t)(turn_on)
#define __NR32ATRF0_socketcall              "%d"
#define __NR32ATRA0_socketcall(call, args)  ,call
#define __NR32ATRF1_socketcall              "%p"
#define __NR32ATRA1_socketcall(call, args)  ,args
#define __NR32ATRF0_syslog                  "%" PRIuSIZ
#define __NR32ATRA0_syslog(level, str, len) ,(uintptr_t)(level)
#define __NR32ATRF1_syslog                  "%$q"
#define __NR32ATRA1_syslog(level, str, len) ,len,(validate_readable(str,len),str)
#define __NR32ATRF2_syslog                  "%" PRIuSIZ
#define __NR32ATRA2_syslog(level, str, len) ,len
#define __NR32ATRF0_setitimer               "%#" PRIxSIZ
#define __NR32ATRA0_setitimer(which, newval, oldval) ,(uintptr_t)(which)
#define __NR32ATRF1_setitimer               "%p"
#define __NR32ATRA1_setitimer(which, newval, oldval) ,newval
#define __NR32ATRF2_setitimer               "%p"
#define __NR32ATRA2_setitimer(which, newval, oldval) ,oldval
#define __NR32ATRF0_getitimer               "%#" PRIxSIZ
#define __NR32ATRA0_getitimer(which, curr_value) ,(uintptr_t)(which)
#define __NR32ATRF1_getitimer               "%p"
#define __NR32ATRA1_getitimer(which, curr_value) ,curr_value
#define __NR32ATRF0_linux_stat32            "%q"
#define __NR32ATRA0_linux_stat32(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_stat32            "%p"
#define __NR32ATRA1_linux_stat32(filename, statbuf) ,statbuf
#define __NR32ATRF0_linux_lstat32           "%q"
#define __NR32ATRA0_linux_lstat32(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_lstat32           "%p"
#define __NR32ATRA1_linux_lstat32(filename, statbuf) ,statbuf
#define __NR32ATRF0_linux_fstat32           "%d"
#define __NR32ATRA0_linux_fstat32(fd, statbuf) ,(int)(fd)
#define __NR32ATRF1_linux_fstat32           "%p"
#define __NR32ATRA1_linux_fstat32(fd, statbuf) ,statbuf
#define __NR32ATRF0_olduname                "%p"
#define __NR32ATRA0_olduname(name)          ,name
#define __NR32ATRF0_iopl                    "%#" PRIxSIZ
#define __NR32ATRA0_iopl(level)             ,(uintptr_t)(level)
#define __NR32ATRF0_vm86old                 "%d"
#define __NR32ATRA0_vm86old(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_wait4                   "%" PRIdSIZ
#define __NR32ATRA0_wait4(pid, stat_loc, options, usage) ,(intptr_t)(pid)
#define __NR32ATRF1_wait4                   "%p"
#define __NR32ATRA1_wait4(pid, stat_loc, options, usage) ,stat_loc
#define __NR32ATRF2_wait4                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR32ATRA2_wait4(pid, stat_loc, options, usage) ,(uintptr_t)(options),(options) & WNOHANG ? "WNOHANG" : "" \
                                                         ,((options) & WUNTRACED) && ((options) & (WNOHANG)) ? "|" : "",(options) & WUNTRACED ? "WUNTRACED" : "" \
                                                         ,((options) & WCONTINUED) && ((options) & (WNOHANG|WUNTRACED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                         ,((options) & WNOWAIT) && ((options) & (WNOHANG|WUNTRACED|WCONTINUED)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NR32ATRF3_wait4                   "%p"
#define __NR32ATRA3_wait4(pid, stat_loc, options, usage) ,usage
#define __NR32ATRF0_swapoff                 "%q"
#define __NR32ATRA0_swapoff(pathname)       ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF0_sysinfo                 "%p"
#define __NR32ATRA0_sysinfo(info)           ,info
#define __NR32ATRF0_ipc                     "%d"
#define __NR32ATRA0_ipc(TODO_PROTOTYPE)     ,TODO_PROTOTYPE
#define __NR32ATRF0_fsync                   "%d"
#define __NR32ATRA0_fsync(fd)               ,(int)(fd)
#define __NR32ATRF0_sigreturn               "%p"
#define __NR32ATRA0_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,restore_fpu
#define __NR32ATRF1_sigreturn               "%#" PRIxSIZ
#define __NR32ATRA1_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,(uintptr_t)(unused1)
#define __NR32ATRF2_sigreturn               "%#" PRIxSIZ
#define __NR32ATRA2_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,(uintptr_t)(unused2)
#define __NR32ATRF3_sigreturn               "%p"
#define __NR32ATRA3_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,restore_sigmask
#define __NR32ATRF4_sigreturn               "%p"
#define __NR32ATRA4_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,sc_info
#define __NR32ATRF5_sigreturn               "%p"
#define __NR32ATRA5_sigreturn(restore_fpu, unused1, unused2, restore_sigmask, sc_info, restore_cpu) ,restore_cpu
#define __NR32ATRF0_clone                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA0_clone(flags, child_stack, ptid, newtls, ctid) ,(uintptr_t)(flags),(flags) & CLONE_VM ? "CLONE_VM" : "" \
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
#define __NR32ATRF1_clone                   "%p"
#define __NR32ATRA1_clone(flags, child_stack, ptid, newtls, ctid) ,child_stack
#define __NR32ATRF2_clone                   "%p"
#define __NR32ATRA2_clone(flags, child_stack, ptid, newtls, ctid) ,ptid
#define __NR32ATRF3_clone                   "%p"
#define __NR32ATRA3_clone(flags, child_stack, ptid, newtls, ctid) ,newtls
#define __NR32ATRF4_clone                   "%p"
#define __NR32ATRA4_clone(flags, child_stack, ptid, newtls, ctid) ,ctid
#define __NR32ATRF0_setdomainname           "%q"
#define __NR32ATRA0_setdomainname(name, len) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF1_setdomainname           "%" PRIuSIZ
#define __NR32ATRA1_setdomainname(name, len) ,len
#define __NR32ATRF0_uname                   "%p"
#define __NR32ATRA0_uname(name)             ,name
#define __NR32ATRF0_modify_ldt              "%#" PRIxSIZ
#define __NR32ATRA0_modify_ldt(func, ptr, bytecount) ,(uintptr_t)(func)
#define __NR32ATRF1_modify_ldt              "%p"
#define __NR32ATRA1_modify_ldt(func, ptr, bytecount) ,ptr
#define __NR32ATRF2_modify_ldt              "%#" PRIxSIZ
#define __NR32ATRA2_modify_ldt(func, ptr, bytecount) ,(uintptr_t)(bytecount)
#define __NR32ATRF0_adjtimex                "%d"
#define __NR32ATRA0_adjtimex(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mprotect                "%p"
#define __NR32ATRA0_mprotect(addr, len, prot) ,addr
#define __NR32ATRF1_mprotect                "%" PRIuSIZ
#define __NR32ATRA1_mprotect(addr, len, prot) ,len
#define __NR32ATRF2_mprotect                "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR32ATRA2_mprotect(addr, len, prot) ,(uintptr_t)(prot),(prot) & PROT_EXEC ? "PROT_EXEC" : (prot) ? "" : "PROT_NONE" \
                                              ,((prot) & PROT_WRITE) && ((prot) & (PROT_EXEC)) ? "|" : "",(prot) & PROT_WRITE ? "PROT_WRITE" : "" \
                                              ,((prot) & PROT_READ) && ((prot) & (PROT_EXEC|PROT_WRITE)) ? "|" : "",(prot) & PROT_READ ? "PROT_READ" : "" \
                                              ,((prot) & PROT_SEM) && ((prot) & (PROT_EXEC|PROT_WRITE|PROT_READ)) ? "|" : "",(prot) & PROT_SEM ? "PROT_SEM" : ""
#define __NR32ATRF0_sigprocmask             "%#" PRIxSIZ
#define __NR32ATRA0_sigprocmask(how, set, oset) ,(uintptr_t)(how)
#define __NR32ATRF1_sigprocmask             "%p"
#define __NR32ATRA1_sigprocmask(how, set, oset) ,set
#define __NR32ATRF2_sigprocmask             "%p"
#define __NR32ATRA2_sigprocmask(how, set, oset) ,oset
#define __NR32ATRF0_create_module           "%d"
#define __NR32ATRA0_create_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_init_module             "%d"
#define __NR32ATRA0_init_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_delete_module           "%d"
#define __NR32ATRA0_delete_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_get_kernel_syms         "%d"
#define __NR32ATRA0_get_kernel_syms(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_quotactl                "%d"
#define __NR32ATRA0_quotactl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_getpgid                 "%" PRIdSIZ
#define __NR32ATRA0_getpgid(pid)            ,(intptr_t)(pid)
#define __NR32ATRF0_fchdir                  "%d"
#define __NR32ATRA0_fchdir(fd)              ,(int)(fd)
#define __NR32ATRF0_bdflush                 "%d"
#define __NR32ATRA0_bdflush(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_sysfs                   "%d"
#define __NR32ATRA0_sysfs(TODO_PROTOTYPE)   ,TODO_PROTOTYPE
#define __NR32ATRF0_personality             "%d"
#define __NR32ATRA0_personality(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_afs_syscall             "%d"
#define __NR32ATRA0_afs_syscall(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_setfsuid                "%" PRIu16
#define __NR32ATRA0_setfsuid(uid)           ,uid
#define __NR32ATRF0_setfsgid                "%" PRIu16
#define __NR32ATRA0_setfsgid(gid)           ,gid
#define __NR32ATRF0__llseek                 "%d"
#define __NR32ATRA0__llseek(fd, offset, result, whence) ,(int)(fd)
#define __NR32ATRF1__llseek                 "%" PRId64
#define __NR32ATRA1__llseek(fd, offset, result, whence) ,offset
#define __NR32ATRF2__llseek                 "%p"
#define __NR32ATRA2__llseek(fd, offset, result, whence) ,result
#define __NR32ATRF3__llseek                 "%#Ix=%s"
#define __NR32ATRA3__llseek(fd, offset, result, whence) ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NR32ATRF0_getdents                "%d"
#define __NR32ATRA0_getdents(fd, dirp, count) ,(int)(fd)
#define __NR32ATRF1_getdents                "%p"
#define __NR32ATRA1_getdents(fd, dirp, count) ,dirp
#define __NR32ATRF2_getdents                "%" PRIuSIZ
#define __NR32ATRA2_getdents(fd, dirp, count) ,count
#define __NR32ATRF0__newselect              "%d"
#define __NR32ATRA0__newselect(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_flock                   "%d"
#define __NR32ATRA0_flock(fd, operation)    ,(int)(fd)
#define __NR32ATRF1_flock                   "%#" PRIxSIZ
#define __NR32ATRA1_flock(fd, operation)    ,(uintptr_t)(operation)
#define __NR32ATRF0_msync                   "%p"
#define __NR32ATRA0_msync(addr, len, flags) ,addr
#define __NR32ATRF1_msync                   "%" PRIuSIZ
#define __NR32ATRA1_msync(addr, len, flags) ,len
#define __NR32ATRF2_msync                   "%#" PRIxSIZ
#define __NR32ATRA2_msync(addr, len, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_readv                   "%d"
#define __NR32ATRA0_readv(fd, iovec, count) ,(int)(fd)
#define __NR32ATRF1_readv                   "%p"
#define __NR32ATRA1_readv(fd, iovec, count) ,iovec
#define __NR32ATRF2_readv                   "%" PRIuSIZ
#define __NR32ATRA2_readv(fd, iovec, count) ,count
#define __NR32ATRF0_writev                  "%d"
#define __NR32ATRA0_writev(fd, iovec, count) ,(int)(fd)
#define __NR32ATRF1_writev                  "%p"
#define __NR32ATRA1_writev(fd, iovec, count) ,iovec
#define __NR32ATRF2_writev                  "%" PRIuSIZ
#define __NR32ATRA2_writev(fd, iovec, count) ,count
#define __NR32ATRF0_getsid                  "%" PRIdSIZ
#define __NR32ATRA0_getsid(pid)             ,(intptr_t)(pid)
#define __NR32ATRF0_fdatasync               "%d"
#define __NR32ATRA0_fdatasync(fd)           ,(int)(fd)
#define __NR32ATRF0__sysctl                 "%d"
#define __NR32ATRA0__sysctl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mlock                   "%p"
#define __NR32ATRA0_mlock(addr, len)        ,addr
#define __NR32ATRF1_mlock                   "%" PRIuSIZ
#define __NR32ATRA1_mlock(addr, len)        ,len
#define __NR32ATRF0_munlock                 "%p"
#define __NR32ATRA0_munlock(addr, len)      ,addr
#define __NR32ATRF1_munlock                 "%" PRIuSIZ
#define __NR32ATRA1_munlock(addr, len)      ,len
#define __NR32ATRF0_mlockall                "%#" PRIxSIZ
#define __NR32ATRA0_mlockall(flags)         ,(uintptr_t)(flags)
#define __NR32ATRF0_sched_setparam          "%" PRIdSIZ
#define __NR32ATRA0_sched_setparam(pid, param) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_setparam          "%p"
#define __NR32ATRA1_sched_setparam(pid, param) ,param
#define __NR32ATRF0_sched_getparam          "%" PRIdSIZ
#define __NR32ATRA0_sched_getparam(pid, param) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_getparam          "%p"
#define __NR32ATRA1_sched_getparam(pid, param) ,param
#define __NR32ATRF0_sched_setscheduler      "%" PRIdSIZ
#define __NR32ATRA0_sched_setscheduler(pid, policy, param) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_setscheduler      "%#" PRIxSIZ
#define __NR32ATRA1_sched_setscheduler(pid, policy, param) ,(uintptr_t)(policy)
#define __NR32ATRF2_sched_setscheduler      "%p"
#define __NR32ATRA2_sched_setscheduler(pid, policy, param) ,param
#define __NR32ATRF0_sched_getscheduler      "%" PRIdSIZ
#define __NR32ATRA0_sched_getscheduler(pid) ,(intptr_t)(pid)
#define __NR32ATRF0_sched_get_priority_max  "%#" PRIxSIZ
#define __NR32ATRA0_sched_get_priority_max(algorithm) ,(uintptr_t)(algorithm)
#define __NR32ATRF0_sched_get_priority_min  "%#" PRIxSIZ
#define __NR32ATRA0_sched_get_priority_min(algorithm) ,(uintptr_t)(algorithm)
#define __NR32ATRF0_sched_rr_get_interval   "%" PRIdSIZ
#define __NR32ATRA0_sched_rr_get_interval(pid, tms) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_rr_get_interval   "%p"
#define __NR32ATRA1_sched_rr_get_interval(pid, tms) ,tms
#define __NR32ATRF0_nanosleep               "%p"
#define __NR32ATRA0_nanosleep(req, rem)     ,req
#define __NR32ATRF1_nanosleep               "%p"
#define __NR32ATRA1_nanosleep(req, rem)     ,rem
#define __NR32ATRF0_mremap                  "%p"
#define __NR32ATRA0_mremap(addr, old_len, new_len, flags, new_address) ,addr
#define __NR32ATRF1_mremap                  "%" PRIuSIZ
#define __NR32ATRA1_mremap(addr, old_len, new_len, flags, new_address) ,old_len
#define __NR32ATRF2_mremap                  "%" PRIuSIZ
#define __NR32ATRA2_mremap(addr, old_len, new_len, flags, new_address) ,new_len
#define __NR32ATRF3_mremap                  "%#" PRIxSIZ "=%s%s%s"
#define __NR32ATRA3_mremap(addr, old_len, new_len, flags, new_address) ,(uintptr_t)(flags),(flags) & MREMAP_MAYMOVE ? "MREMAP_MAYMOVE" : "" \
                                                                       ,((flags) & MREMAP_FIXED) && ((flags) & (MREMAP_MAYMOVE)) ? "|" : "",(flags) & MREMAP_FIXED ? "MREMAP_FIXED" : ""
#define __NR32ATRF4_mremap                  "%p"
#define __NR32ATRA4_mremap(addr, old_len, new_len, flags, new_address) ,new_address
#define __NR32ATRF0_setresuid               "%" PRIu16
#define __NR32ATRA0_setresuid(ruid, euid, suid) ,ruid
#define __NR32ATRF1_setresuid               "%" PRIu16
#define __NR32ATRA1_setresuid(ruid, euid, suid) ,euid
#define __NR32ATRF2_setresuid               "%" PRIu16
#define __NR32ATRA2_setresuid(ruid, euid, suid) ,suid
#define __NR32ATRF0_getresuid               "%p"
#define __NR32ATRA0_getresuid(ruid, euid, suid) ,ruid
#define __NR32ATRF1_getresuid               "%p"
#define __NR32ATRA1_getresuid(ruid, euid, suid) ,euid
#define __NR32ATRF2_getresuid               "%p"
#define __NR32ATRA2_getresuid(ruid, euid, suid) ,suid
#define __NR32ATRF0_vm86                    "%d"
#define __NR32ATRA0_vm86(TODO_PROTOTYPE)    ,TODO_PROTOTYPE
#define __NR32ATRF0_query_module            "%d"
#define __NR32ATRA0_query_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_poll                    "%p"
#define __NR32ATRA0_poll(fds, nfds, timeout) ,fds
#define __NR32ATRF1_poll                    "%" PRIuSIZ
#define __NR32ATRA1_poll(fds, nfds, timeout) ,nfds
#define __NR32ATRF2_poll                    "%" PRIdSIZ
#define __NR32ATRA2_poll(fds, nfds, timeout) ,(intptr_t)(timeout)
#define __NR32ATRF0_nfsservctl              "%d"
#define __NR32ATRA0_nfsservctl(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_setresgid               "%" PRIu16
#define __NR32ATRA0_setresgid(rgid, egid, sgid) ,rgid
#define __NR32ATRF1_setresgid               "%" PRIu16
#define __NR32ATRA1_setresgid(rgid, egid, sgid) ,egid
#define __NR32ATRF2_setresgid               "%" PRIu16
#define __NR32ATRA2_setresgid(rgid, egid, sgid) ,sgid
#define __NR32ATRF0_getresgid               "%p"
#define __NR32ATRA0_getresgid(rgid, egid, sgid) ,rgid
#define __NR32ATRF1_getresgid               "%p"
#define __NR32ATRA1_getresgid(rgid, egid, sgid) ,egid
#define __NR32ATRF2_getresgid               "%p"
#define __NR32ATRA2_getresgid(rgid, egid, sgid) ,sgid
#define __NR32ATRF0_prctl                   "%d"
#define __NR32ATRA0_prctl(TODO_PROTOTYPE)   ,TODO_PROTOTYPE
#define __NR32ATRF0_rt_sigreturn            "%p"
#define __NR32ATRA0_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) ,restore_fpu
#define __NR32ATRF1_rt_sigreturn            "%p"
#define __NR32ATRA1_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) ,restore_sigmask
#define __NR32ATRF2_rt_sigreturn            "%p"
#define __NR32ATRA2_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) ,sc_info
#define __NR32ATRF3_rt_sigreturn            "%p"
#define __NR32ATRA3_rt_sigreturn(restore_fpu, restore_sigmask, sc_info, restore_cpu) ,restore_cpu
#define __NR32ATRF0_rt_sigaction            "%#" PRIxSIZ
#define __NR32ATRA0_rt_sigaction(signo, act, oact, sigsetsize) ,(uintptr_t)(signo)
#define __NR32ATRF1_rt_sigaction            "%p"
#define __NR32ATRA1_rt_sigaction(signo, act, oact, sigsetsize) ,act
#define __NR32ATRF2_rt_sigaction            "%p"
#define __NR32ATRA2_rt_sigaction(signo, act, oact, sigsetsize) ,oact
#define __NR32ATRF3_rt_sigaction            "%" PRIuSIZ
#define __NR32ATRA3_rt_sigaction(signo, act, oact, sigsetsize) ,sigsetsize
#define __NR32ATRF0_rt_sigprocmask          "%#" PRIxSIZ
#define __NR32ATRA0_rt_sigprocmask(how, set, oset, sigsetsize) ,(uintptr_t)(how)
#define __NR32ATRF1_rt_sigprocmask          "%p"
#define __NR32ATRA1_rt_sigprocmask(how, set, oset, sigsetsize) ,set
#define __NR32ATRF2_rt_sigprocmask          "%p"
#define __NR32ATRA2_rt_sigprocmask(how, set, oset, sigsetsize) ,oset
#define __NR32ATRF3_rt_sigprocmask          "%" PRIuSIZ
#define __NR32ATRA3_rt_sigprocmask(how, set, oset, sigsetsize) ,sigsetsize
#define __NR32ATRF0_rt_sigpending           "%p"
#define __NR32ATRA0_rt_sigpending(set, sigsetsize) ,set
#define __NR32ATRF1_rt_sigpending           "%" PRIuSIZ
#define __NR32ATRA1_rt_sigpending(set, sigsetsize) ,sigsetsize
#define __NR32ATRF0_rt_sigtimedwait         "%p"
#define __NR32ATRA0_rt_sigtimedwait(set, info, timeout, sigsetsize) ,set
#define __NR32ATRF1_rt_sigtimedwait         "%p"
#define __NR32ATRA1_rt_sigtimedwait(set, info, timeout, sigsetsize) ,info
#define __NR32ATRF2_rt_sigtimedwait         "%p"
#define __NR32ATRA2_rt_sigtimedwait(set, info, timeout, sigsetsize) ,timeout
#define __NR32ATRF3_rt_sigtimedwait         "%" PRIuSIZ
#define __NR32ATRA3_rt_sigtimedwait(set, info, timeout, sigsetsize) ,sigsetsize
#define __NR32ATRF0_rt_sigqueueinfo         "%" PRIdSIZ
#define __NR32ATRA0_rt_sigqueueinfo(tgid, signo, uinfo) ,(intptr_t)(tgid)
#define __NR32ATRF1_rt_sigqueueinfo         "%#" PRIxSIZ
#define __NR32ATRA1_rt_sigqueueinfo(tgid, signo, uinfo) ,(uintptr_t)(signo)
#define __NR32ATRF2_rt_sigqueueinfo         "%p"
#define __NR32ATRA2_rt_sigqueueinfo(tgid, signo, uinfo) ,uinfo
#define __NR32ATRF0_rt_sigsuspend           "%p"
#define __NR32ATRA0_rt_sigsuspend(set, sigsetsize) ,set
#define __NR32ATRF1_rt_sigsuspend           "%" PRIuSIZ
#define __NR32ATRA1_rt_sigsuspend(set, sigsetsize) ,sigsetsize
#define __NR32ATRF0_pread64                 "%d"
#define __NR32ATRA0_pread64(fd, buf, bufsize, offset) ,(int)(fd)
#define __NR32ATRF1_pread64                 "%p"
#define __NR32ATRA1_pread64(fd, buf, bufsize, offset) ,buf
#define __NR32ATRF2_pread64                 "%" PRIuSIZ
#define __NR32ATRA2_pread64(fd, buf, bufsize, offset) ,bufsize
#define __NR32ATRF3_pread64                 "%" PRIu64
#define __NR32ATRA3_pread64(fd, buf, bufsize, offset) ,offset
#define __NR32ATRF0_pwrite64                "%d"
#define __NR32ATRA0_pwrite64(fd, buf, bufsize, offset) ,(int)(fd)
#define __NR32ATRF1_pwrite64                "%p"
#define __NR32ATRA1_pwrite64(fd, buf, bufsize, offset) ,buf
#define __NR32ATRF2_pwrite64                "%" PRIuSIZ
#define __NR32ATRA2_pwrite64(fd, buf, bufsize, offset) ,bufsize
#define __NR32ATRF3_pwrite64                "%" PRIu64
#define __NR32ATRA3_pwrite64(fd, buf, bufsize, offset) ,offset
#define __NR32ATRF0_chown                   "%q"
#define __NR32ATRA0_chown(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_chown                   "%" PRIu16
#define __NR32ATRA1_chown(filename, owner, group) ,owner
#define __NR32ATRF2_chown                   "%" PRIu16
#define __NR32ATRA2_chown(filename, owner, group) ,group
#define __NR32ATRF0_getcwd                  "%p"
#define __NR32ATRA0_getcwd(buf, size)       ,buf
#define __NR32ATRF1_getcwd                  "%" PRIuSIZ
#define __NR32ATRA1_getcwd(buf, size)       ,size
#define __NR32ATRF0_capget                  "%d"
#define __NR32ATRA0_capget(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR32ATRF0_capset                  "%d"
#define __NR32ATRA0_capset(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR32ATRF0_sigaltstack             "%p"
#define __NR32ATRA0_sigaltstack(ss, oss)    ,ss
#define __NR32ATRF1_sigaltstack             "%p"
#define __NR32ATRA1_sigaltstack(ss, oss)    ,oss
#define __NR32ATRF0_sendfile                "%d"
#define __NR32ATRA0_sendfile(out_fd, in_fd, offset, count) ,(int)(out_fd)
#define __NR32ATRF1_sendfile                "%d"
#define __NR32ATRA1_sendfile(out_fd, in_fd, offset, count) ,(int)(in_fd)
#define __NR32ATRF2_sendfile                "%p"
#define __NR32ATRA2_sendfile(out_fd, in_fd, offset, count) ,offset
#define __NR32ATRF3_sendfile                "%" PRIuSIZ
#define __NR32ATRA3_sendfile(out_fd, in_fd, offset, count) ,count
#define __NR32ATRF0_getpmsg                 "%d"
#define __NR32ATRA0_getpmsg(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_putpmsg                 "%d"
#define __NR32ATRA0_putpmsg(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_ugetrlimit              "%d"
#define __NR32ATRA0_ugetrlimit(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mmap2                   "%p"
#define __NR32ATRA0_mmap2(addr, len, prot, flags, fd, pgoffset) ,addr
#define __NR32ATRF1_mmap2                   "%" PRIuSIZ
#define __NR32ATRA1_mmap2(addr, len, prot, flags, fd, pgoffset) ,len
#define __NR32ATRF2_mmap2                   "%#" PRIxSIZ
#define __NR32ATRA2_mmap2(addr, len, prot, flags, fd, pgoffset) ,(uintptr_t)(prot)
#define __NR32ATRF3_mmap2                   "%#" PRIxSIZ
#define __NR32ATRA3_mmap2(addr, len, prot, flags, fd, pgoffset) ,(uintptr_t)(flags)
#define __NR32ATRF4_mmap2                   "%d"
#define __NR32ATRA4_mmap2(addr, len, prot, flags, fd, pgoffset) ,(int)(fd)
#define __NR32ATRF5_mmap2                   "%#" PRIxSIZ
#define __NR32ATRA5_mmap2(addr, len, prot, flags, fd, pgoffset) ,(uintptr_t)(pgoffset)
#define __NR32ATRF0_truncate64              "%q"
#define __NR32ATRA0_truncate64(filename, length) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_truncate64              "%" PRIu64
#define __NR32ATRA1_truncate64(filename, length) ,length
#define __NR32ATRF0_ftruncate64             "%d"
#define __NR32ATRA0_ftruncate64(fd, length) ,(int)(fd)
#define __NR32ATRF1_ftruncate64             "%" PRIu64
#define __NR32ATRA1_ftruncate64(fd, length) ,length
#define __NR32ATRF0_linux_stat64            "%q"
#define __NR32ATRA0_linux_stat64(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_stat64            "%p"
#define __NR32ATRA1_linux_stat64(filename, statbuf) ,statbuf
#define __NR32ATRF0_linux_lstat64           "%q"
#define __NR32ATRA0_linux_lstat64(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_linux_lstat64           "%p"
#define __NR32ATRA1_linux_lstat64(filename, statbuf) ,statbuf
#define __NR32ATRF0_linux_fstat64           "%d"
#define __NR32ATRA0_linux_fstat64(fd, statbuf) ,(int)(fd)
#define __NR32ATRF1_linux_fstat64           "%p"
#define __NR32ATRA1_linux_fstat64(fd, statbuf) ,statbuf
#define __NR32ATRF0_lchown32                "%q"
#define __NR32ATRA0_lchown32(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_lchown32                "%" PRIu32
#define __NR32ATRA1_lchown32(filename, owner, group) ,owner
#define __NR32ATRF2_lchown32                "%" PRIu32
#define __NR32ATRA2_lchown32(filename, owner, group) ,group
#define __NR32ATRF0_setreuid32              "%" PRIu32
#define __NR32ATRA0_setreuid32(ruid, euid)  ,ruid
#define __NR32ATRF1_setreuid32              "%" PRIu32
#define __NR32ATRA1_setreuid32(ruid, euid)  ,euid
#define __NR32ATRF0_setregid32              "%" PRIu32
#define __NR32ATRA0_setregid32(rgid, egid)  ,rgid
#define __NR32ATRF1_setregid32              "%" PRIu32
#define __NR32ATRA1_setregid32(rgid, egid)  ,egid
#define __NR32ATRF0_getgroups32             "%" PRIuSIZ
#define __NR32ATRA0_getgroups32(size, list) ,size
#define __NR32ATRF1_getgroups32             "%p"
#define __NR32ATRA1_getgroups32(size, list) ,list
#define __NR32ATRF0_setgroups32             "%" PRIuSIZ
#define __NR32ATRA0_setgroups32(count, groups) ,count
#define __NR32ATRF1_setgroups32             "%p"
#define __NR32ATRA1_setgroups32(count, groups) ,groups
#define __NR32ATRF0_fchown32                "%d"
#define __NR32ATRA0_fchown32(fd, owner, group) ,(int)(fd)
#define __NR32ATRF1_fchown32                "%" PRIu32
#define __NR32ATRA1_fchown32(fd, owner, group) ,owner
#define __NR32ATRF2_fchown32                "%" PRIu32
#define __NR32ATRA2_fchown32(fd, owner, group) ,group
#define __NR32ATRF0_setresuid32             "%" PRIu32
#define __NR32ATRA0_setresuid32(ruid, euid, suid) ,ruid
#define __NR32ATRF1_setresuid32             "%" PRIu32
#define __NR32ATRA1_setresuid32(ruid, euid, suid) ,euid
#define __NR32ATRF2_setresuid32             "%" PRIu32
#define __NR32ATRA2_setresuid32(ruid, euid, suid) ,suid
#define __NR32ATRF0_getresuid32             "%p"
#define __NR32ATRA0_getresuid32(ruid, euid, suid) ,ruid
#define __NR32ATRF1_getresuid32             "%p"
#define __NR32ATRA1_getresuid32(ruid, euid, suid) ,euid
#define __NR32ATRF2_getresuid32             "%p"
#define __NR32ATRA2_getresuid32(ruid, euid, suid) ,suid
#define __NR32ATRF0_setresgid32             "%" PRIu32
#define __NR32ATRA0_setresgid32(rgid, egid, sgid) ,rgid
#define __NR32ATRF1_setresgid32             "%" PRIu32
#define __NR32ATRA1_setresgid32(rgid, egid, sgid) ,egid
#define __NR32ATRF2_setresgid32             "%" PRIu32
#define __NR32ATRA2_setresgid32(rgid, egid, sgid) ,sgid
#define __NR32ATRF0_getresgid32             "%p"
#define __NR32ATRA0_getresgid32(rgid, egid, sgid) ,rgid
#define __NR32ATRF1_getresgid32             "%p"
#define __NR32ATRA1_getresgid32(rgid, egid, sgid) ,egid
#define __NR32ATRF2_getresgid32             "%p"
#define __NR32ATRA2_getresgid32(rgid, egid, sgid) ,sgid
#define __NR32ATRF0_chown32                 "%q"
#define __NR32ATRA0_chown32(filename, owner, group) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_chown32                 "%" PRIu32
#define __NR32ATRA1_chown32(filename, owner, group) ,owner
#define __NR32ATRF2_chown32                 "%" PRIu32
#define __NR32ATRA2_chown32(filename, owner, group) ,group
#define __NR32ATRF0_setuid32                "%" PRIu32
#define __NR32ATRA0_setuid32(uid)           ,uid
#define __NR32ATRF0_setgid32                "%" PRIu32
#define __NR32ATRA0_setgid32(gid)           ,gid
#define __NR32ATRF0_setfsuid32              "%" PRIu32
#define __NR32ATRA0_setfsuid32(uid)         ,uid
#define __NR32ATRF0_setfsgid32              "%" PRIu32
#define __NR32ATRA0_setfsgid32(gid)         ,gid
#define __NR32ATRF0_pivot_root              "%d"
#define __NR32ATRA0_pivot_root(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mincore                 "%p"
#define __NR32ATRA0_mincore(start, len, vec) ,start
#define __NR32ATRF1_mincore                 "%" PRIuSIZ
#define __NR32ATRA1_mincore(start, len, vec) ,len
#define __NR32ATRF2_mincore                 "%p"
#define __NR32ATRA2_mincore(start, len, vec) ,vec
#define __NR32ATRF0_madvise                 "%p"
#define __NR32ATRA0_madvise(addr, len, advice) ,addr
#define __NR32ATRF1_madvise                 "%" PRIuSIZ
#define __NR32ATRA1_madvise(addr, len, advice) ,len
#define __NR32ATRF2_madvise                 "%#" PRIxSIZ
#define __NR32ATRA2_madvise(addr, len, advice) ,(uintptr_t)(advice)
#define __NR32ATRF0_getdents64              "%d"
#define __NR32ATRA0_getdents64(fd, dirp, count) ,(int)(fd)
#define __NR32ATRF1_getdents64              "%p"
#define __NR32ATRA1_getdents64(fd, dirp, count) ,dirp
#define __NR32ATRF2_getdents64              "%" PRIuSIZ
#define __NR32ATRA2_getdents64(fd, dirp, count) ,count
#define __NR32ATRF0_fcntl64                 "%d"
#define __NR32ATRA0_fcntl64(fd, command, arg) ,(int)(fd)
#define __NR32ATRF1_fcntl64                 "%#" PRIxSIZ
#define __NR32ATRA1_fcntl64(fd, command, arg) ,(uintptr_t)(command)
#define __NR32ATRF2_fcntl64                 "%p"
#define __NR32ATRA2_fcntl64(fd, command, arg) ,arg
#define __NR32ATRF0_readahead               "%d"
#define __NR32ATRA0_readahead(fd, offset, count) ,(int)(fd)
#define __NR32ATRF1_readahead               "%" PRIu64
#define __NR32ATRA1_readahead(fd, offset, count) ,offset
#define __NR32ATRF2_readahead               "%" PRIuSIZ
#define __NR32ATRA2_readahead(fd, offset, count) ,count
#define __NR32ATRF0_setxattr                "%q"
#define __NR32ATRA0_setxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_setxattr                "%q"
#define __NR32ATRA1_setxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_setxattr                "%p"
#define __NR32ATRA2_setxattr(path, name, buf, bufsize, flags) ,buf
#define __NR32ATRF3_setxattr                "%" PRIuSIZ
#define __NR32ATRA3_setxattr(path, name, buf, bufsize, flags) ,bufsize
#define __NR32ATRF4_setxattr                "%#" PRIxSIZ
#define __NR32ATRA4_setxattr(path, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_lsetxattr               "%q"
#define __NR32ATRA0_lsetxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_lsetxattr               "%q"
#define __NR32ATRA1_lsetxattr(path, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_lsetxattr               "%p"
#define __NR32ATRA2_lsetxattr(path, name, buf, bufsize, flags) ,buf
#define __NR32ATRF3_lsetxattr               "%" PRIuSIZ
#define __NR32ATRA3_lsetxattr(path, name, buf, bufsize, flags) ,bufsize
#define __NR32ATRF4_lsetxattr               "%#" PRIxSIZ
#define __NR32ATRA4_lsetxattr(path, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_fsetxattr               "%d"
#define __NR32ATRA0_fsetxattr(fd, name, buf, bufsize, flags) ,(int)(fd)
#define __NR32ATRF1_fsetxattr               "%q"
#define __NR32ATRA1_fsetxattr(fd, name, buf, bufsize, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_fsetxattr               "%p"
#define __NR32ATRA2_fsetxattr(fd, name, buf, bufsize, flags) ,buf
#define __NR32ATRF3_fsetxattr               "%" PRIuSIZ
#define __NR32ATRA3_fsetxattr(fd, name, buf, bufsize, flags) ,bufsize
#define __NR32ATRF4_fsetxattr               "%#" PRIxSIZ
#define __NR32ATRA4_fsetxattr(fd, name, buf, bufsize, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_getxattr                "%q"
#define __NR32ATRA0_getxattr(path, name, buf, bufsize) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_getxattr                "%q"
#define __NR32ATRA1_getxattr(path, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_getxattr                "%p"
#define __NR32ATRA2_getxattr(path, name, buf, bufsize) ,buf
#define __NR32ATRF3_getxattr                "%" PRIuSIZ
#define __NR32ATRA3_getxattr(path, name, buf, bufsize) ,bufsize
#define __NR32ATRF0_lgetxattr               "%q"
#define __NR32ATRA0_lgetxattr(path, name, buf, bufsize) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_lgetxattr               "%q"
#define __NR32ATRA1_lgetxattr(path, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_lgetxattr               "%p"
#define __NR32ATRA2_lgetxattr(path, name, buf, bufsize) ,buf
#define __NR32ATRF3_lgetxattr               "%" PRIuSIZ
#define __NR32ATRA3_lgetxattr(path, name, buf, bufsize) ,bufsize
#define __NR32ATRF0_fgetxattr               "%d"
#define __NR32ATRA0_fgetxattr(fd, name, buf, bufsize) ,(int)(fd)
#define __NR32ATRF1_fgetxattr               "%q"
#define __NR32ATRA1_fgetxattr(fd, name, buf, bufsize) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_fgetxattr               "%p"
#define __NR32ATRA2_fgetxattr(fd, name, buf, bufsize) ,buf
#define __NR32ATRF3_fgetxattr               "%" PRIuSIZ
#define __NR32ATRA3_fgetxattr(fd, name, buf, bufsize) ,bufsize
#define __NR32ATRF0_listxattr               "%q"
#define __NR32ATRA0_listxattr(path, listbuf, listbufsize) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_listxattr               "%p"
#define __NR32ATRA1_listxattr(path, listbuf, listbufsize) ,listbuf
#define __NR32ATRF2_listxattr               "%" PRIuSIZ
#define __NR32ATRA2_listxattr(path, listbuf, listbufsize) ,listbufsize
#define __NR32ATRF0_llistxattr              "%q"
#define __NR32ATRA0_llistxattr(path, listbuf, listbufsize) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_llistxattr              "%p"
#define __NR32ATRA1_llistxattr(path, listbuf, listbufsize) ,listbuf
#define __NR32ATRF2_llistxattr              "%" PRIuSIZ
#define __NR32ATRA2_llistxattr(path, listbuf, listbufsize) ,listbufsize
#define __NR32ATRF0_flistxattr              "%d"
#define __NR32ATRA0_flistxattr(fd, listbuf, listbufsize) ,(int)(fd)
#define __NR32ATRF1_flistxattr              "%p"
#define __NR32ATRA1_flistxattr(fd, listbuf, listbufsize) ,listbuf
#define __NR32ATRF2_flistxattr              "%" PRIuSIZ
#define __NR32ATRA2_flistxattr(fd, listbuf, listbufsize) ,listbufsize
#define __NR32ATRF0_removexattr             "%q"
#define __NR32ATRA0_removexattr(path, name) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_removexattr             "%q"
#define __NR32ATRA1_removexattr(path, name) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF0_lremovexattr            "%q"
#define __NR32ATRA0_lremovexattr(path, name) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF1_lremovexattr            "%q"
#define __NR32ATRA1_lremovexattr(path, name) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF0_fremovexattr            "%d"
#define __NR32ATRA0_fremovexattr(fd, name)  ,fd
#define __NR32ATRF1_fremovexattr            "%q"
#define __NR32ATRA1_fremovexattr(fd, name)  ,(validate_readable_opt(name,1),name)
#define __NR32ATRF0_tkill                   "%" PRIdSIZ
#define __NR32ATRA0_tkill(tid, signo)       ,(intptr_t)(tid)
#define __NR32ATRF1_tkill                   "%#" PRIxSIZ
#define __NR32ATRA1_tkill(tid, signo)       ,(uintptr_t)(signo)
#define __NR32ATRF0_sendfile64              "%d"
#define __NR32ATRA0_sendfile64(out_fd, in_fd, offset, count) ,(int)(out_fd)
#define __NR32ATRF1_sendfile64              "%d"
#define __NR32ATRA1_sendfile64(out_fd, in_fd, offset, count) ,(int)(in_fd)
#define __NR32ATRF2_sendfile64              "%p"
#define __NR32ATRA2_sendfile64(out_fd, in_fd, offset, count) ,offset
#define __NR32ATRF3_sendfile64              "%" PRIuSIZ
#define __NR32ATRA3_sendfile64(out_fd, in_fd, offset, count) ,count
#define __NR32ATRF0_futex                   "%p"
#define __NR32ATRA0_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,uaddr
#define __NR32ATRF1_futex                   "%#" PRIxSIZ
#define __NR32ATRA1_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,(uintptr_t)(futex_op)
#define __NR32ATRF2_futex                   "%" PRIu32
#define __NR32ATRA2_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,val
#define __NR32ATRF3_futex                   "%p"
#define __NR32ATRA3_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,timeout_or_val2
#define __NR32ATRF4_futex                   "%p"
#define __NR32ATRA4_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,uaddr2
#define __NR32ATRF5_futex                   "%" PRIu32
#define __NR32ATRA5_futex(uaddr, futex_op, val, timeout_or_val2, uaddr2, val3) ,val3
#define __NR32ATRF0_sched_setaffinity       "%" PRIdSIZ
#define __NR32ATRA0_sched_setaffinity(pid, cpusetsize, cpuset) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_setaffinity       "%" PRIuSIZ
#define __NR32ATRA1_sched_setaffinity(pid, cpusetsize, cpuset) ,cpusetsize
#define __NR32ATRF2_sched_setaffinity       "%p"
#define __NR32ATRA2_sched_setaffinity(pid, cpusetsize, cpuset) ,cpuset
#define __NR32ATRF0_sched_getaffinity       "%" PRIdSIZ
#define __NR32ATRA0_sched_getaffinity(pid, cpusetsize, cpuset) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_getaffinity       "%" PRIuSIZ
#define __NR32ATRA1_sched_getaffinity(pid, cpusetsize, cpuset) ,cpusetsize
#define __NR32ATRF2_sched_getaffinity       "%p"
#define __NR32ATRA2_sched_getaffinity(pid, cpusetsize, cpuset) ,cpuset
#define __NR32ATRF0_set_thread_area         "%d"
#define __NR32ATRA0_set_thread_area(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_get_thread_area         "%d"
#define __NR32ATRA0_get_thread_area(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_io_setup                "%d"
#define __NR32ATRA0_io_setup(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_io_destroy              "%d"
#define __NR32ATRA0_io_destroy(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_io_getevents            "%d"
#define __NR32ATRA0_io_getevents(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_io_submit               "%d"
#define __NR32ATRA0_io_submit(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_io_cancel               "%d"
#define __NR32ATRA0_io_cancel(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_fadvise64               "%d"
#define __NR32ATRA0_fadvise64(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_exit_group              "%" PRIuSIZ
#define __NR32ATRA0_exit_group(exit_code)   ,(uintptr_t)(exit_code)
#define __NR32ATRF0_lookup_dcookie          "%d"
#define __NR32ATRA0_lookup_dcookie(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_epoll_create            "%#" PRIxSIZ
#define __NR32ATRA0_epoll_create(size)      ,(uintptr_t)(size)
#define __NR32ATRF0_epoll_ctl               "%d"
#define __NR32ATRA0_epoll_ctl(epfd, op, fd, event) ,(int)(epfd)
#define __NR32ATRF1_epoll_ctl               "%#Ix=%s"
#define __NR32ATRA1_epoll_ctl(epfd, op, fd, event) ,(op),(op) == EPOLL_CTL_ADD ? "EPOLL_CTL_ADD" : (op) == EPOLL_CTL_DEL ? "EPOLL_CTL_DEL" : (op) == EPOLL_CTL_MOD ? "EPOLL_CTL_MOD" : "?"
#define __NR32ATRF2_epoll_ctl               "%d"
#define __NR32ATRA2_epoll_ctl(epfd, op, fd, event) ,(int)(fd)
#define __NR32ATRF3_epoll_ctl               "%p"
#define __NR32ATRA3_epoll_ctl(epfd, op, fd, event) ,event
#define __NR32ATRF0_epoll_wait              "%d"
#define __NR32ATRA0_epoll_wait(epfd, events, maxevents, timeout) ,(int)(epfd)
#define __NR32ATRF1_epoll_wait              "%p"
#define __NR32ATRA1_epoll_wait(epfd, events, maxevents, timeout) ,events
#define __NR32ATRF2_epoll_wait              "%#" PRIxSIZ
#define __NR32ATRA2_epoll_wait(epfd, events, maxevents, timeout) ,(uintptr_t)(maxevents)
#define __NR32ATRF3_epoll_wait              "%" PRIdSIZ
#define __NR32ATRA3_epoll_wait(epfd, events, maxevents, timeout) ,(intptr_t)(timeout)
#define __NR32ATRF0_remap_file_pages        "%p"
#define __NR32ATRA0_remap_file_pages(start, size, prot, pgoff, flags) ,start
#define __NR32ATRF1_remap_file_pages        "%" PRIuSIZ
#define __NR32ATRA1_remap_file_pages(start, size, prot, pgoff, flags) ,size
#define __NR32ATRF2_remap_file_pages        "%#" PRIxSIZ
#define __NR32ATRA2_remap_file_pages(start, size, prot, pgoff, flags) ,(uintptr_t)(prot)
#define __NR32ATRF3_remap_file_pages        "%" PRIuSIZ
#define __NR32ATRA3_remap_file_pages(start, size, prot, pgoff, flags) ,pgoff
#define __NR32ATRF4_remap_file_pages        "%#" PRIxSIZ
#define __NR32ATRA4_remap_file_pages(start, size, prot, pgoff, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_set_tid_address         "%p"
#define __NR32ATRA0_set_tid_address(tidptr) ,tidptr
#define __NR32ATRF0_timer_create            "%#" PRIxSIZ
#define __NR32ATRA0_timer_create(clock_id, evp, timerid) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_timer_create            "%p"
#define __NR32ATRA1_timer_create(clock_id, evp, timerid) ,evp
#define __NR32ATRF2_timer_create            "%p"
#define __NR32ATRA2_timer_create(clock_id, evp, timerid) ,timerid
#define __NR32ATRF0_timer_settime           "%p"
#define __NR32ATRA0_timer_settime(timerid, flags, value, ovalue) ,timerid
#define __NR32ATRF1_timer_settime           "%#" PRIxSIZ
#define __NR32ATRA1_timer_settime(timerid, flags, value, ovalue) ,(uintptr_t)(flags)
#define __NR32ATRF2_timer_settime           "%p"
#define __NR32ATRA2_timer_settime(timerid, flags, value, ovalue) ,value
#define __NR32ATRF3_timer_settime           "%p"
#define __NR32ATRA3_timer_settime(timerid, flags, value, ovalue) ,ovalue
#define __NR32ATRF0_timer_gettime           "%p"
#define __NR32ATRA0_timer_gettime(timerid, value) ,timerid
#define __NR32ATRF1_timer_gettime           "%p"
#define __NR32ATRA1_timer_gettime(timerid, value) ,value
#define __NR32ATRF0_timer_getoverrun        "%p"
#define __NR32ATRA0_timer_getoverrun(timerid) ,timerid
#define __NR32ATRF0_timer_delete            "%p"
#define __NR32ATRA0_timer_delete(timerid)   ,timerid
#define __NR32ATRF0_clock_settime           "%#" PRIxSIZ
#define __NR32ATRA0_clock_settime(clock_id, tp) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_clock_settime           "%p"
#define __NR32ATRA1_clock_settime(clock_id, tp) ,tp
#define __NR32ATRF0_clock_gettime           "%#" PRIxSIZ
#define __NR32ATRA0_clock_gettime(clock_id, tp) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_clock_gettime           "%p"
#define __NR32ATRA1_clock_gettime(clock_id, tp) ,tp
#define __NR32ATRF0_clock_getres            "%#" PRIxSIZ
#define __NR32ATRA0_clock_getres(clock_id, res) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_clock_getres            "%p"
#define __NR32ATRA1_clock_getres(clock_id, res) ,res
#define __NR32ATRF0_clock_nanosleep         "%#" PRIxSIZ
#define __NR32ATRA0_clock_nanosleep(clock_id, flags, requested_time, remaining) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_clock_nanosleep         "%#" PRIxSIZ
#define __NR32ATRA1_clock_nanosleep(clock_id, flags, requested_time, remaining) ,(uintptr_t)(flags)
#define __NR32ATRF2_clock_nanosleep         "%p"
#define __NR32ATRA2_clock_nanosleep(clock_id, flags, requested_time, remaining) ,requested_time
#define __NR32ATRF3_clock_nanosleep         "%p"
#define __NR32ATRA3_clock_nanosleep(clock_id, flags, requested_time, remaining) ,remaining
#define __NR32ATRF0_statfs64                "%q"
#define __NR32ATRA0_statfs64(file, buf)     ,(validate_readable_opt(file,1),file)
#define __NR32ATRF1_statfs64                "%p"
#define __NR32ATRA1_statfs64(file, buf)     ,buf
#define __NR32ATRF0_fstatfs64               "%d"
#define __NR32ATRA0_fstatfs64(file, buf)    ,(int)(file)
#define __NR32ATRF1_fstatfs64               "%p"
#define __NR32ATRA1_fstatfs64(file, buf)    ,buf
#define __NR32ATRF0_tgkill                  "%" PRIdSIZ
#define __NR32ATRA0_tgkill(tgid, tid, signo) ,(intptr_t)(tgid)
#define __NR32ATRF1_tgkill                  "%" PRIdSIZ
#define __NR32ATRA1_tgkill(tgid, tid, signo) ,(intptr_t)(tid)
#define __NR32ATRF2_tgkill                  "%#" PRIxSIZ
#define __NR32ATRA2_tgkill(tgid, tid, signo) ,(uintptr_t)(signo)
#define __NR32ATRF0_utimes                  "%q"
#define __NR32ATRA0_utimes(filename, times) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_utimes                  "%p"
#define __NR32ATRA1_utimes(filename, times) ,times
#define __NR32ATRF0_fadvise64_64            "%d"
#define __NR32ATRA0_fadvise64_64(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_vserver                 "%d"
#define __NR32ATRA0_vserver(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mbind                   "%d"
#define __NR32ATRA0_mbind(TODO_PROTOTYPE)   ,TODO_PROTOTYPE
#define __NR32ATRF0_get_mempolicy           "%d"
#define __NR32ATRA0_get_mempolicy(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_set_mempolicy           "%d"
#define __NR32ATRA0_set_mempolicy(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mq_open                 "%d"
#define __NR32ATRA0_mq_open(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mq_unlink               "%d"
#define __NR32ATRA0_mq_unlink(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mq_timedsend            "%d"
#define __NR32ATRA0_mq_timedsend(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mq_timedreceive         "%d"
#define __NR32ATRA0_mq_timedreceive(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mq_notify               "%d"
#define __NR32ATRA0_mq_notify(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mq_getsetattr           "%d"
#define __NR32ATRA0_mq_getsetattr(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_kexec_load              "%d"
#define __NR32ATRA0_kexec_load(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_waitid                  "%#Ix=%s"
#define __NR32ATRA0_waitid(idtype, id, infop, options, ru) ,(idtype),(idtype) == P_ALL ? "P_ALL" : (idtype) == P_PID ? "P_PID" : (idtype) == P_PGID ? "P_PGID" : "?"
#define __NR32ATRF1_waitid                  "%" PRIuSIZ
#define __NR32ATRA1_waitid(idtype, id, infop, options, ru) ,(uintptr_t)(id)
#define __NR32ATRF2_waitid                  "%p"
#define __NR32ATRA2_waitid(idtype, id, infop, options, ru) ,infop
#define __NR32ATRF3_waitid                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_waitid(idtype, id, infop, options, ru) ,(uintptr_t)(options),(options) & WEXITED ? "WEXITED" : "" \
                                                           ,((options) & WSTOPPED) && ((options) & (WEXITED)) ? "|" : "",(options) & WSTOPPED ? "WSTOPPED" : "" \
                                                           ,((options) & WCONTINUED) && ((options) & (WEXITED|WSTOPPED)) ? "|" : "",(options) & WCONTINUED ? "WCONTINUED" : "" \
                                                           ,((options) & WNOHANG) && ((options) & (WEXITED|WSTOPPED|WCONTINUED)) ? "|" : "",(options) & WNOHANG ? "WNOHANG" : "" \
                                                           ,((options) & WNOWAIT) && ((options) & (WEXITED|WSTOPPED|WCONTINUED|WNOHANG)) ? "|" : "",(options) & WNOWAIT ? "WNOWAIT" : ""
#define __NR32ATRF4_waitid                  "%p"
#define __NR32ATRA4_waitid(idtype, id, infop, options, ru) ,ru
#define __NR32ATRF0_add_key                 "%d"
#define __NR32ATRA0_add_key(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_request_key             "%d"
#define __NR32ATRA0_request_key(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_keyctl                  "%d"
#define __NR32ATRA0_keyctl(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR32ATRF0_ioprio_set              "%#" PRIxSIZ
#define __NR32ATRA0_ioprio_set(which, who, ioprio) ,(uintptr_t)(which)
#define __NR32ATRF1_ioprio_set              "%#" PRIxSIZ
#define __NR32ATRA1_ioprio_set(which, who, ioprio) ,(uintptr_t)(who)
#define __NR32ATRF2_ioprio_set              "%#" PRIxSIZ
#define __NR32ATRA2_ioprio_set(which, who, ioprio) ,(uintptr_t)(ioprio)
#define __NR32ATRF0_ioprio_get              "%#" PRIxSIZ
#define __NR32ATRA0_ioprio_get(which, who)  ,(uintptr_t)(which)
#define __NR32ATRF1_ioprio_get              "%#" PRIxSIZ
#define __NR32ATRA1_ioprio_get(which, who)  ,(uintptr_t)(who)
#define __NR32ATRF0_inotify_init            "%d"
#define __NR32ATRA0_inotify_init(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_inotify_add_watch       "%d"
#define __NR32ATRA0_inotify_add_watch(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_inotify_rm_watch        "%d"
#define __NR32ATRA0_inotify_rm_watch(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_migrate_pages           "%d"
#define __NR32ATRA0_migrate_pages(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_openat                  "%d"
#define __NR32ATRA0_openat(dirfd, filename, oflags, mode) ,(int)(dirfd)
#define __NR32ATRF1_openat                  "%q"
#define __NR32ATRA1_openat(dirfd, filename, oflags, mode) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_openat                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_openat(dirfd, filename, oflags, mode) ,(uintptr_t)(oflags),(oflags) & O_WRONLY ? "O_WRONLY" : (oflags) ? "" : "O_RDONLY" \
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
#define __NR32ATRF3_openat                  "%#" PRIoSIZ
#define __NR32ATRA3_openat(dirfd, filename, oflags, mode) ,(uintptr_t)(mode)
#define __NR32ATRF0_mkdirat                 "%d"
#define __NR32ATRA0_mkdirat(dirfd, pathname, mode) ,(int)(dirfd)
#define __NR32ATRF1_mkdirat                 "%q"
#define __NR32ATRA1_mkdirat(dirfd, pathname, mode) ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF2_mkdirat                 "%#" PRIoSIZ
#define __NR32ATRA2_mkdirat(dirfd, pathname, mode) ,(uintptr_t)(mode)
#define __NR32ATRF0_mknodat                 "%d"
#define __NR32ATRA0_mknodat(dirfd, nodename, mode, dev) ,(int)(dirfd)
#define __NR32ATRF1_mknodat                 "%q"
#define __NR32ATRA1_mknodat(dirfd, nodename, mode, dev) ,(validate_readable_opt(nodename,1),nodename)
#define __NR32ATRF2_mknodat                 "%#" PRIoSIZ
#define __NR32ATRA2_mknodat(dirfd, nodename, mode, dev) ,(uintptr_t)(mode)
#define __NR32ATRF3_mknodat                 "%.2x:%.2x"
#define __NR32ATRA3_mknodat(dirfd, nodename, mode, dev) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR32ATRF0_fchownat                "%d"
#define __NR32ATRA0_fchownat(dirfd, filename, owner, group, flags) ,(int)(dirfd)
#define __NR32ATRF1_fchownat                "%q"
#define __NR32ATRA1_fchownat(dirfd, filename, owner, group, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_fchownat                "%" PRIu32
#define __NR32ATRA2_fchownat(dirfd, filename, owner, group, flags) ,(uint32_t)(owner)
#define __NR32ATRF3_fchownat                "%" PRIu32
#define __NR32ATRA3_fchownat(dirfd, filename, owner, group, flags) ,(uint32_t)(group)
#define __NR32ATRF4_fchownat                "%#" PRIxSIZ "=%s%s%s"
#define __NR32ATRA4_fchownat(dirfd, filename, owner, group, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                   ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_futimesat               "%d"
#define __NR32ATRA0_futimesat(dirfd, filename, times) ,(int)(dirfd)
#define __NR32ATRF1_futimesat               "%p"
#define __NR32ATRA1_futimesat(dirfd, filename, times) ,filename
#define __NR32ATRF2_futimesat               "%p"
#define __NR32ATRA2_futimesat(dirfd, filename, times) ,times
#define __NR32ATRF0_linux_fstatat64         "%d"
#define __NR32ATRA0_linux_fstatat64(dirfd, filename, statbuf, flags) ,(int)(dirfd)
#define __NR32ATRF1_linux_fstatat64         "%q"
#define __NR32ATRA1_linux_fstatat64(dirfd, filename, statbuf, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_linux_fstatat64         "%p"
#define __NR32ATRA2_linux_fstatat64(dirfd, filename, statbuf, flags) ,statbuf
#define __NR32ATRF3_linux_fstatat64         "%#" PRIxSIZ "=%s%s%s"
#define __NR32ATRA3_linux_fstatat64(dirfd, filename, statbuf, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                     ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_unlinkat                "%d"
#define __NR32ATRA0_unlinkat(dirfd, name, flags) ,(int)(dirfd)
#define __NR32ATRF1_unlinkat                "%q"
#define __NR32ATRA1_unlinkat(dirfd, name, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_unlinkat                "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA2_unlinkat(dirfd, name, flags) ,(uintptr_t)(flags),(flags) & AT_REMOVEDIR ? "AT_REMOVEDIR" : "" \
                                                 ,((flags) & AT_REMOVEREG) && ((flags) & (AT_REMOVEDIR)) ? "|" : "",(flags) & AT_REMOVEREG ? "AT_REMOVEREG" : "" \
                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_REMOVEDIR|AT_REMOVEREG)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_renameat                "%d"
#define __NR32ATRA0_renameat(oldfd, oldname, newfd, newname_or_path) ,(int)(oldfd)
#define __NR32ATRF1_renameat                "%q"
#define __NR32ATRA1_renameat(oldfd, oldname, newfd, newname_or_path) ,(validate_readable_opt(oldname,1),oldname)
#define __NR32ATRF2_renameat                "%d"
#define __NR32ATRA2_renameat(oldfd, oldname, newfd, newname_or_path) ,(int)(newfd)
#define __NR32ATRF3_renameat                "%q"
#define __NR32ATRA3_renameat(oldfd, oldname, newfd, newname_or_path) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NR32ATRF0_linkat                  "%d"
#define __NR32ATRA0_linkat(fromfd, existing_file, tofd, target_path, flags) ,(int)(fromfd)
#define __NR32ATRF1_linkat                  "%q"
#define __NR32ATRA1_linkat(fromfd, existing_file, tofd, target_path, flags) ,(validate_readable_opt(existing_file,1),existing_file)
#define __NR32ATRF2_linkat                  "%d"
#define __NR32ATRA2_linkat(fromfd, existing_file, tofd, target_path, flags) ,(int)(tofd)
#define __NR32ATRF3_linkat                  "%q"
#define __NR32ATRA3_linkat(fromfd, existing_file, tofd, target_path, flags) ,(validate_readable_opt(target_path,1),target_path)
#define __NR32ATRF4_linkat                  "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA4_linkat(fromfd, existing_file, tofd, target_path, flags) ,(uintptr_t)(flags),(flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                                            ,((flags) & AT_SYMLINK_FOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "",(flags) & AT_SYMLINK_FOLLOW ? "AT_SYMLINK_FOLLOW" : "" \
                                                                            ,((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH|AT_SYMLINK_FOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_symlinkat               "%q"
#define __NR32ATRA0_symlinkat(link_text, tofd, target_path) ,(validate_readable_opt(link_text,1),link_text)
#define __NR32ATRF1_symlinkat               "%d"
#define __NR32ATRA1_symlinkat(link_text, tofd, target_path) ,(int)(tofd)
#define __NR32ATRF2_symlinkat               "%q"
#define __NR32ATRA2_symlinkat(link_text, tofd, target_path) ,(validate_readable_opt(target_path,1),target_path)
#define __NR32ATRF0_readlinkat              "%d"
#define __NR32ATRA0_readlinkat(dirfd, path, buf, buflen) ,(int)(dirfd)
#define __NR32ATRF1_readlinkat              "%q"
#define __NR32ATRA1_readlinkat(dirfd, path, buf, buflen) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF2_readlinkat              "%p"
#define __NR32ATRA2_readlinkat(dirfd, path, buf, buflen) ,buf
#define __NR32ATRF3_readlinkat              "%" PRIuSIZ
#define __NR32ATRA3_readlinkat(dirfd, path, buf, buflen) ,buflen
#define __NR32ATRF0_fchmodat                "%d"
#define __NR32ATRA0_fchmodat(dirfd, filename, mode, flags) ,(int)(dirfd)
#define __NR32ATRF1_fchmodat                "%q"
#define __NR32ATRA1_fchmodat(dirfd, filename, mode, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_fchmodat                "%#" PRIoSIZ
#define __NR32ATRA2_fchmodat(dirfd, filename, mode, flags) ,(uintptr_t)(mode)
#define __NR32ATRF3_fchmodat                "%#" PRIxSIZ "=%s%s%s"
#define __NR32ATRA3_fchmodat(dirfd, filename, mode, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                           ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_faccessat               "%d"
#define __NR32ATRA0_faccessat(dirfd, filename, type, flags) ,(int)(dirfd)
#define __NR32ATRF1_faccessat               "%q"
#define __NR32ATRA1_faccessat(dirfd, filename, type, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_faccessat               "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA2_faccessat(dirfd, filename, type, flags) ,(uintptr_t)(type),(type) & R_OK ? "R_OK" : (type) ? "" : "F_OK" \
                                                            ,((type) & W_OK) && ((type) & (R_OK)) ? "|" : "",(type) & W_OK ? "W_OK" : "" \
                                                            ,((type) & X_OK) && ((type) & (R_OK|W_OK)) ? "|" : "",(type) & X_OK ? "X_OK" : ""
#define __NR32ATRF3_faccessat               "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA3_faccessat(dirfd, filename, type, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                            ,((flags) & AT_EACCESS) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_EACCESS ? "AT_EACCESS" : "" \
                                                            ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_EACCESS)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_pselect6                "%" PRIuSIZ
#define __NR32ATRA0_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,nfds
#define __NR32ATRF1_pselect6                "%p"
#define __NR32ATRA1_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,readfds
#define __NR32ATRF2_pselect6                "%p"
#define __NR32ATRA2_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,writefds
#define __NR32ATRF3_pselect6                "%p"
#define __NR32ATRA3_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,exceptfds
#define __NR32ATRF4_pselect6                "%p"
#define __NR32ATRA4_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,timeout
#define __NR32ATRF5_pselect6                "%p"
#define __NR32ATRA5_pselect6(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,sigmask_sigset_and_len
#define __NR32ATRF0_ppoll                   "%p"
#define __NR32ATRA0_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,fds
#define __NR32ATRF1_ppoll                   "%" PRIuSIZ
#define __NR32ATRA1_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,nfds
#define __NR32ATRF2_ppoll                   "%p"
#define __NR32ATRA2_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,timeout_ts
#define __NR32ATRF3_ppoll                   "%p"
#define __NR32ATRA3_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigmask
#define __NR32ATRF4_ppoll                   "%" PRIuSIZ
#define __NR32ATRA4_ppoll(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigsetsize
#define __NR32ATRF0_unshare                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA0_unshare(flags)          ,(uintptr_t)(flags),(flags) & CLONE_VM ? "CLONE_VM" : "" \
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
#define __NR32ATRF0_set_robust_list         "%d"
#define __NR32ATRA0_set_robust_list(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_get_robust_list         "%d"
#define __NR32ATRA0_get_robust_list(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_splice                  "%d"
#define __NR32ATRA0_splice(fdin, offin, fdout, offout, length, flags) ,(int)(fdin)
#define __NR32ATRF1_splice                  "%p"
#define __NR32ATRA1_splice(fdin, offin, fdout, offout, length, flags) ,offin
#define __NR32ATRF2_splice                  "%d"
#define __NR32ATRA2_splice(fdin, offin, fdout, offout, length, flags) ,(int)(fdout)
#define __NR32ATRF3_splice                  "%p"
#define __NR32ATRA3_splice(fdin, offin, fdout, offout, length, flags) ,offout
#define __NR32ATRF4_splice                  "%" PRIuSIZ
#define __NR32ATRA4_splice(fdin, offin, fdout, offout, length, flags) ,length
#define __NR32ATRF5_splice                  "%#" PRIxSIZ
#define __NR32ATRA5_splice(fdin, offin, fdout, offout, length, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_sync_file_range         "%d"
#define __NR32ATRA0_sync_file_range(fd, offset, count, flags) ,(int)(fd)
#define __NR32ATRF1_sync_file_range         "%" PRIu64
#define __NR32ATRA1_sync_file_range(fd, offset, count, flags) ,offset
#define __NR32ATRF2_sync_file_range         "%" PRIu64
#define __NR32ATRA2_sync_file_range(fd, offset, count, flags) ,count
#define __NR32ATRF3_sync_file_range         "%#" PRIxSIZ
#define __NR32ATRA3_sync_file_range(fd, offset, count, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_tee                     "%d"
#define __NR32ATRA0_tee(fdin, fdout, length, flags) ,(int)(fdin)
#define __NR32ATRF1_tee                     "%d"
#define __NR32ATRA1_tee(fdin, fdout, length, flags) ,(int)(fdout)
#define __NR32ATRF2_tee                     "%" PRIuSIZ
#define __NR32ATRA2_tee(fdin, fdout, length, flags) ,length
#define __NR32ATRF3_tee                     "%#" PRIxSIZ
#define __NR32ATRA3_tee(fdin, fdout, length, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_vmsplice                "%d"
#define __NR32ATRA0_vmsplice(fdout, iov, count, flags) ,(int)(fdout)
#define __NR32ATRF1_vmsplice                "%p"
#define __NR32ATRA1_vmsplice(fdout, iov, count, flags) ,iov
#define __NR32ATRF2_vmsplice                "%" PRIuSIZ
#define __NR32ATRA2_vmsplice(fdout, iov, count, flags) ,count
#define __NR32ATRF3_vmsplice                "%#" PRIxSIZ
#define __NR32ATRA3_vmsplice(fdout, iov, count, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_move_pages              "%d"
#define __NR32ATRA0_move_pages(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_getcpu                  "%p"
#define __NR32ATRA0_getcpu(cpu, node, tcache) ,cpu
#define __NR32ATRF1_getcpu                  "%p"
#define __NR32ATRA1_getcpu(cpu, node, tcache) ,node
#define __NR32ATRF2_getcpu                  "%p"
#define __NR32ATRA2_getcpu(cpu, node, tcache) ,tcache
#define __NR32ATRF0_epoll_pwait             "%d"
#define __NR32ATRA0_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(int)(epfd)
#define __NR32ATRF1_epoll_pwait             "%p"
#define __NR32ATRA1_epoll_pwait(epfd, events, maxevents, timeout, ss) ,events
#define __NR32ATRF2_epoll_pwait             "%#" PRIxSIZ
#define __NR32ATRA2_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(uintptr_t)(maxevents)
#define __NR32ATRF3_epoll_pwait             "%" PRIdSIZ
#define __NR32ATRA3_epoll_pwait(epfd, events, maxevents, timeout, ss) ,(intptr_t)(timeout)
#define __NR32ATRF4_epoll_pwait             "%p"
#define __NR32ATRA4_epoll_pwait(epfd, events, maxevents, timeout, ss) ,ss
#define __NR32ATRF0_utimensat               "%d"
#define __NR32ATRA0_utimensat(dirfd, filename, times, flags) ,(int)(dirfd)
#define __NR32ATRF1_utimensat               "%q"
#define __NR32ATRA1_utimensat(dirfd, filename, times, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_utimensat               "%p"
#define __NR32ATRA2_utimensat(dirfd, filename, times, flags) ,times
#define __NR32ATRF3_utimensat               "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA3_utimensat(dirfd, filename, times, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                             ,((flags) & AT_CHANGE_CTIME) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_CHANGE_CTIME ? "AT_CHANGE_CTIME" : "" \
                                                             ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_signalfd                "%d"
#define __NR32ATRA0_signalfd(fd, sigmask, sigsetsize) ,(int)(fd)
#define __NR32ATRF1_signalfd                "%p"
#define __NR32ATRA1_signalfd(fd, sigmask, sigsetsize) ,sigmask
#define __NR32ATRF2_signalfd                "%" PRIuSIZ
#define __NR32ATRA2_signalfd(fd, sigmask, sigsetsize) ,sigsetsize
#define __NR32ATRF0_timerfd_create          "%#" PRIxSIZ
#define __NR32ATRA0_timerfd_create(clock_id, flags) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_timerfd_create          "%#" PRIxSIZ
#define __NR32ATRA1_timerfd_create(clock_id, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_eventfd                 "%#" PRIxSIZ
#define __NR32ATRA0_eventfd(initval)        ,(uintptr_t)(initval)
#define __NR32ATRF0_fallocate               "%d"
#define __NR32ATRA0_fallocate(fd, mode, offset, length) ,(int)(fd)
#define __NR32ATRF1_fallocate               "%#" PRIxSIZ
#define __NR32ATRA1_fallocate(fd, mode, offset, length) ,(uintptr_t)(mode)
#define __NR32ATRF2_fallocate               "%#" PRIxSIZ
#define __NR32ATRA2_fallocate(fd, mode, offset, length) ,(uintptr_t)(offset)
#define __NR32ATRF3_fallocate               "%#" PRIxSIZ
#define __NR32ATRA3_fallocate(fd, mode, offset, length) ,(uintptr_t)(length)
#define __NR32ATRF0_timerfd_settime         "%d"
#define __NR32ATRA0_timerfd_settime(ufd, flags, utmr, otmr) ,(int)(ufd)
#define __NR32ATRF1_timerfd_settime         "%#" PRIxSIZ
#define __NR32ATRA1_timerfd_settime(ufd, flags, utmr, otmr) ,(uintptr_t)(flags)
#define __NR32ATRF2_timerfd_settime         "%p"
#define __NR32ATRA2_timerfd_settime(ufd, flags, utmr, otmr) ,utmr
#define __NR32ATRF3_timerfd_settime         "%p"
#define __NR32ATRA3_timerfd_settime(ufd, flags, utmr, otmr) ,otmr
#define __NR32ATRF0_timerfd_gettime         "%d"
#define __NR32ATRA0_timerfd_gettime(ufd, otmr) ,(int)(ufd)
#define __NR32ATRF1_timerfd_gettime         "%p"
#define __NR32ATRA1_timerfd_gettime(ufd, otmr) ,otmr
#define __NR32ATRF0_signalfd4               "%d"
#define __NR32ATRA0_signalfd4(fd, sigmask, sigsetsize, flags) ,(int)(fd)
#define __NR32ATRF1_signalfd4               "%p"
#define __NR32ATRA1_signalfd4(fd, sigmask, sigsetsize, flags) ,sigmask
#define __NR32ATRF2_signalfd4               "%" PRIuSIZ
#define __NR32ATRA2_signalfd4(fd, sigmask, sigsetsize, flags) ,sigsetsize
#define __NR32ATRF3_signalfd4               "%#" PRIxSIZ "=%s%s%s"
#define __NR32ATRA3_signalfd4(fd, sigmask, sigsetsize, flags) ,(uintptr_t)(flags),(flags) & SFD_NONBLOCK ? "SFD_NONBLOCK" : "" \
                                                              ,((flags) & SFD_CLOEXEC) && ((flags) & (SFD_NONBLOCK)) ? "|" : "",(flags) & SFD_CLOEXEC ? "SFD_CLOEXEC" : ""
#define __NR32ATRF0_eventfd2                "%#" PRIxSIZ
#define __NR32ATRA0_eventfd2(initval, flags) ,(uintptr_t)(initval)
#define __NR32ATRF1_eventfd2                "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA1_eventfd2(initval, flags) ,(uintptr_t)(flags),(flags) & EFD_SEMAPHORE ? "EFD_SEMAPHORE" : "" \
                                             ,((flags) & EFD_NONBLOCK) && ((flags) & (EFD_SEMAPHORE)) ? "|" : "",(flags) & EFD_NONBLOCK ? "EFD_NONBLOCK" : "" \
                                             ,((flags) & EFD_CLOEXEC) && ((flags) & (EFD_SEMAPHORE|EFD_NONBLOCK)) ? "|" : "",(flags) & EFD_CLOEXEC ? "EFD_CLOEXEC" : ""
#define __NR32ATRF0_epoll_create1           "%#" PRIxSIZ
#define __NR32ATRA0_epoll_create1(flags)    ,(uintptr_t)(flags)
#define __NR32ATRF0_dup3                    "%d"
#define __NR32ATRA0_dup3(oldfd, newfd, flags) ,(int)(oldfd)
#define __NR32ATRF1_dup3                    "%d"
#define __NR32ATRA1_dup3(oldfd, newfd, flags) ,(int)(newfd)
#define __NR32ATRF2_dup3                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_dup3(oldfd, newfd, flags) ,(uintptr_t)(flags),(flags) & O_WRONLY ? "O_WRONLY" : (flags) ? "" : "O_RDONLY" \
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
#define __NR32ATRF0_pipe2                   "%p"
#define __NR32ATRA0_pipe2(pipedes, flags)   ,pipedes
#define __NR32ATRF1_pipe2                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR32ATRA1_pipe2(pipedes, flags)   ,(uintptr_t)(flags),(flags) & O_CLOEXEC ? "O_CLOEXEC" : "" \
                                            ,((flags) & O_CLOFORK) && ((flags) & (O_CLOEXEC)) ? "|" : "",(flags) & O_CLOFORK ? "O_CLOFORK" : "" \
                                            ,((flags) & O_NONBLOCK) && ((flags) & (O_CLOEXEC|O_CLOFORK)) ? "|" : "",(flags) & O_NONBLOCK ? "O_NONBLOCK" : "" \
                                            ,((flags) & O_DIRECT) && ((flags) & (O_CLOEXEC|O_CLOFORK|O_NONBLOCK)) ? "|" : "",(flags) & O_DIRECT ? "O_DIRECT" : ""
#define __NR32ATRF0_inotify_init1           "%d"
#define __NR32ATRA0_inotify_init1(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_preadv                  "%d"
#define __NR32ATRA0_preadv(fd, iovec, count, offset) ,(int)(fd)
#define __NR32ATRF1_preadv                  "%p"
#define __NR32ATRA1_preadv(fd, iovec, count, offset) ,iovec
#define __NR32ATRF2_preadv                  "%" PRIuSIZ
#define __NR32ATRA2_preadv(fd, iovec, count, offset) ,count
#define __NR32ATRF3_preadv                  "%" PRIu64
#define __NR32ATRA3_preadv(fd, iovec, count, offset) ,offset
#define __NR32ATRF0_pwritev                 "%d"
#define __NR32ATRA0_pwritev(fd, iovec, count, offset) ,(int)(fd)
#define __NR32ATRF1_pwritev                 "%p"
#define __NR32ATRA1_pwritev(fd, iovec, count, offset) ,iovec
#define __NR32ATRF2_pwritev                 "%" PRIuSIZ
#define __NR32ATRA2_pwritev(fd, iovec, count, offset) ,count
#define __NR32ATRF3_pwritev                 "%" PRIu64
#define __NR32ATRA3_pwritev(fd, iovec, count, offset) ,offset
#define __NR32ATRF0_rt_tgsigqueueinfo       "%" PRIdSIZ
#define __NR32ATRA0_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(intptr_t)(tgid)
#define __NR32ATRF1_rt_tgsigqueueinfo       "%" PRIdSIZ
#define __NR32ATRA1_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(intptr_t)(tid)
#define __NR32ATRF2_rt_tgsigqueueinfo       "%#" PRIxSIZ
#define __NR32ATRA2_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,(uintptr_t)(signo)
#define __NR32ATRF3_rt_tgsigqueueinfo       "%p"
#define __NR32ATRA3_rt_tgsigqueueinfo(tgid, tid, signo, uinfo) ,uinfo
#define __NR32ATRF0_perf_event_open         "%d"
#define __NR32ATRA0_perf_event_open(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_recvmmsg                "%d"
#define __NR32ATRA0_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,(int)(sockfd)
#define __NR32ATRF1_recvmmsg                "%p"
#define __NR32ATRA1_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,vmessages
#define __NR32ATRF2_recvmmsg                "%" PRIuSIZ
#define __NR32ATRA2_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,vlen
#define __NR32ATRF3_recvmmsg                "%#" PRIxSIZ
#define __NR32ATRA3_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,(uintptr_t)(flags)
#define __NR32ATRF4_recvmmsg                "%p"
#define __NR32ATRA4_recvmmsg(sockfd, vmessages, vlen, flags, tmo) ,tmo
#define __NR32ATRF0_fanotify_init           "%d"
#define __NR32ATRA0_fanotify_init(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_fanotify_mark           "%d"
#define __NR32ATRA0_fanotify_mark(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_prlimit64               "%" PRIdSIZ
#define __NR32ATRA0_prlimit64(pid, resource, new_limit, old_limit) ,(intptr_t)(pid)
#define __NR32ATRF1_prlimit64               "%#" PRIxSIZ
#define __NR32ATRA1_prlimit64(pid, resource, new_limit, old_limit) ,(uintptr_t)(resource)
#define __NR32ATRF2_prlimit64               "%p"
#define __NR32ATRA2_prlimit64(pid, resource, new_limit, old_limit) ,new_limit
#define __NR32ATRF3_prlimit64               "%p"
#define __NR32ATRA3_prlimit64(pid, resource, new_limit, old_limit) ,old_limit
#define __NR32ATRF0_name_to_handle_at       "%d"
#define __NR32ATRA0_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(int)(dirfd)
#define __NR32ATRF1_name_to_handle_at       "%q"
#define __NR32ATRA1_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF2_name_to_handle_at       "%p"
#define __NR32ATRA2_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,handle
#define __NR32ATRF3_name_to_handle_at       "%p"
#define __NR32ATRA3_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,mnt_id
#define __NR32ATRF4_name_to_handle_at       "%#" PRIxSIZ
#define __NR32ATRA4_name_to_handle_at(dirfd, name, handle, mnt_id, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_open_by_handle_at       "%d"
#define __NR32ATRA0_open_by_handle_at(mountdirfd, handle, flags) ,(int)(mountdirfd)
#define __NR32ATRF1_open_by_handle_at       "%p"
#define __NR32ATRA1_open_by_handle_at(mountdirfd, handle, flags) ,handle
#define __NR32ATRF2_open_by_handle_at       "%#" PRIxSIZ
#define __NR32ATRA2_open_by_handle_at(mountdirfd, handle, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_clock_adjtime           "%d"
#define __NR32ATRA0_clock_adjtime(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_syncfs                  "%d"
#define __NR32ATRA0_syncfs(fd)              ,(int)(fd)
#define __NR32ATRF0_sendmmsg                "%d"
#define __NR32ATRA0_sendmmsg(sockfd, vmessages, vlen, flags) ,(int)(sockfd)
#define __NR32ATRF1_sendmmsg                "%p"
#define __NR32ATRA1_sendmmsg(sockfd, vmessages, vlen, flags) ,vmessages
#define __NR32ATRF2_sendmmsg                "%" PRIuSIZ
#define __NR32ATRA2_sendmmsg(sockfd, vmessages, vlen, flags) ,vlen
#define __NR32ATRF3_sendmmsg                "%#" PRIxSIZ
#define __NR32ATRA3_sendmmsg(sockfd, vmessages, vlen, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_setns                   "%d"
#define __NR32ATRA0_setns(fd, nstype)       ,(int)(fd)
#define __NR32ATRF1_setns                   "%#" PRIxSIZ
#define __NR32ATRA1_setns(fd, nstype)       ,(uintptr_t)(nstype)
#define __NR32ATRF0_process_vm_readv        "%" PRIdSIZ
#define __NR32ATRA0_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(intptr_t)(pid)
#define __NR32ATRF1_process_vm_readv        "%p"
#define __NR32ATRA1_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,lvec
#define __NR32ATRF2_process_vm_readv        "%" PRIuSIZ
#define __NR32ATRA2_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,liovcnt
#define __NR32ATRF3_process_vm_readv        "%p"
#define __NR32ATRA3_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,rvec
#define __NR32ATRF4_process_vm_readv        "%" PRIuSIZ
#define __NR32ATRA4_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,riovcnt
#define __NR32ATRF5_process_vm_readv        "%#" PRIxSIZ
#define __NR32ATRA5_process_vm_readv(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_process_vm_writev       "%" PRIdSIZ
#define __NR32ATRA0_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(intptr_t)(pid)
#define __NR32ATRF1_process_vm_writev       "%p"
#define __NR32ATRA1_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,lvec
#define __NR32ATRF2_process_vm_writev       "%" PRIuSIZ
#define __NR32ATRA2_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,liovcnt
#define __NR32ATRF3_process_vm_writev       "%p"
#define __NR32ATRA3_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,rvec
#define __NR32ATRF4_process_vm_writev       "%" PRIuSIZ
#define __NR32ATRA4_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,riovcnt
#define __NR32ATRF5_process_vm_writev       "%#" PRIxSIZ
#define __NR32ATRA5_process_vm_writev(pid, lvec, liovcnt, rvec, riovcnt, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_kcmp                    "%" PRIdSIZ
#define __NR32ATRA0_kcmp(pid1, pid2, type, idx1, idx2) ,(intptr_t)(pid1)
#define __NR32ATRF1_kcmp                    "%" PRIdSIZ
#define __NR32ATRA1_kcmp(pid1, pid2, type, idx1, idx2) ,(intptr_t)(pid2)
#define __NR32ATRF2_kcmp                    "%#" PRIxSIZ
#define __NR32ATRA2_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(type)
#define __NR32ATRF3_kcmp                    "%#" PRIxSIZ
#define __NR32ATRA3_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(idx1)
#define __NR32ATRF4_kcmp                    "%#" PRIxSIZ
#define __NR32ATRA4_kcmp(pid1, pid2, type, idx1, idx2) ,(uintptr_t)(idx2)
#define __NR32ATRF0_finit_module            "%d"
#define __NR32ATRA0_finit_module(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_sched_setattr           "%d"
#define __NR32ATRA0_sched_setattr(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_sched_getattr           "%d"
#define __NR32ATRA0_sched_getattr(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_renameat2               "%d"
#define __NR32ATRA0_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(int)(olddirfd)
#define __NR32ATRF1_renameat2               "%q"
#define __NR32ATRA1_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(validate_readable_opt(oldpath,1),oldpath)
#define __NR32ATRF2_renameat2               "%d"
#define __NR32ATRA2_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(int)(newdirfd)
#define __NR32ATRF3_renameat2               "%q"
#define __NR32ATRA3_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(validate_readable_opt(newpath,1),newpath)
#define __NR32ATRF4_renameat2               "%#" PRIxSIZ
#define __NR32ATRA4_renameat2(olddirfd, oldpath, newdirfd, newpath, flags) ,(uintptr_t)(flags)
#define __NR32ATRF0_seccomp                 "%d"
#define __NR32ATRA0_seccomp(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_getrandom               "%d"
#define __NR32ATRA0_getrandom(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_memfd_create            "%d"
#define __NR32ATRA0_memfd_create(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_bpf                     "%d"
#define __NR32ATRA0_bpf(TODO_PROTOTYPE)     ,TODO_PROTOTYPE
#define __NR32ATRF0_execveat                "%d"
#define __NR32ATRA0_execveat(dirfd, pathname, argv, envp, flags) ,(int)(dirfd)
#define __NR32ATRF1_execveat                "%q"
#define __NR32ATRA1_execveat(dirfd, pathname, argv, envp, flags) ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF2_execveat                "%p"
#define __NR32ATRA2_execveat(dirfd, pathname, argv, envp, flags) ,argv
#define __NR32ATRF3_execveat                "%p"
#define __NR32ATRA3_execveat(dirfd, pathname, argv, envp, flags) ,envp
#define __NR32ATRF4_execveat                "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA4_execveat(dirfd, pathname, argv, envp, flags) ,(uintptr_t)(flags),(flags) & AT_EMPTY_PATH ? "AT_EMPTY_PATH" : "" \
                                                                 ,((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_EMPTY_PATH)) ? "|" : "",(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_socket                  "%#" PRIxSIZ
#define __NR32ATRA0_socket(domain, type, protocol) ,(uintptr_t)(domain)
#define __NR32ATRF1_socket                  "%#" PRIxSIZ
#define __NR32ATRA1_socket(domain, type, protocol) ,(uintptr_t)(type)
#define __NR32ATRF2_socket                  "%#" PRIxSIZ
#define __NR32ATRA2_socket(domain, type, protocol) ,(uintptr_t)(protocol)
#define __NR32ATRF0_socketpair              "%#" PRIxSIZ
#define __NR32ATRA0_socketpair(domain, type, protocol, fds) ,(uintptr_t)(domain)
#define __NR32ATRF1_socketpair              "%#" PRIxSIZ
#define __NR32ATRA1_socketpair(domain, type, protocol, fds) ,(uintptr_t)(type)
#define __NR32ATRF2_socketpair              "%#" PRIxSIZ
#define __NR32ATRA2_socketpair(domain, type, protocol, fds) ,(uintptr_t)(protocol)
#define __NR32ATRF3_socketpair              "%p"
#define __NR32ATRA3_socketpair(domain, type, protocol, fds) ,fds
#define __NR32ATRF0_bind                    "%d"
#define __NR32ATRA0_bind(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_bind                    "%p"
#define __NR32ATRA1_bind(sockfd, addr, addr_len) ,addr
#define __NR32ATRF2_bind                    "%" PRIuSIZ
#define __NR32ATRA2_bind(sockfd, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NR32ATRF0_connect                 "%d"
#define __NR32ATRA0_connect(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_connect                 "%p"
#define __NR32ATRA1_connect(sockfd, addr, addr_len) ,addr
#define __NR32ATRF2_connect                 "%" PRIuSIZ
#define __NR32ATRA2_connect(sockfd, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NR32ATRF0_listen                  "%d"
#define __NR32ATRA0_listen(sockfd, max_backlog) ,(int)(sockfd)
#define __NR32ATRF1_listen                  "%#" PRIxSIZ
#define __NR32ATRA1_listen(sockfd, max_backlog) ,(uintptr_t)(max_backlog)
#define __NR32ATRF0_accept4                 "%d"
#define __NR32ATRA0_accept4(sockfd, addr, addr_len, flags) ,(int)(sockfd)
#define __NR32ATRF1_accept4                 "%p"
#define __NR32ATRA1_accept4(sockfd, addr, addr_len, flags) ,addr
#define __NR32ATRF2_accept4                 "%p"
#define __NR32ATRA2_accept4(sockfd, addr, addr_len, flags) ,addr_len
#define __NR32ATRF3_accept4                 "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA3_accept4(sockfd, addr, addr_len, flags) ,(uintptr_t)(flags),(flags) & SOCK_NONBLOCK ? "SOCK_NONBLOCK" : "" \
                                                           ,((flags) & SOCK_CLOEXEC) && ((flags) & (SOCK_NONBLOCK)) ? "|" : "",(flags) & SOCK_CLOEXEC ? "SOCK_CLOEXEC" : "" \
                                                           ,((flags) & SOCK_CLOFORK) && ((flags) & (SOCK_NONBLOCK|SOCK_CLOEXEC)) ? "|" : "",(flags) & SOCK_CLOFORK ? "SOCK_CLOFORK" : ""
#define __NR32ATRF0_getsockopt              "%d"
#define __NR32ATRA0_getsockopt(sockfd, level, optname, optval, optlen) ,(int)(sockfd)
#define __NR32ATRF1_getsockopt              "%#Ix=%s"
#define __NR32ATRA1_getsockopt(sockfd, level, optname, optval, optlen) ,(level),(level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NR32ATRF2_getsockopt              "%#" PRIxSIZ
#define __NR32ATRA2_getsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optname)
#define __NR32ATRF3_getsockopt              "%p"
#define __NR32ATRA3_getsockopt(sockfd, level, optname, optval, optlen) ,optval
#define __NR32ATRF4_getsockopt              "%p"
#define __NR32ATRA4_getsockopt(sockfd, level, optname, optval, optlen) ,optlen
#define __NR32ATRF0_setsockopt              "%d"
#define __NR32ATRA0_setsockopt(sockfd, level, optname, optval, optlen) ,(int)(sockfd)
#define __NR32ATRF1_setsockopt              "%#Ix=%s"
#define __NR32ATRA1_setsockopt(sockfd, level, optname, optval, optlen) ,(level),(level) == SOL_SOCKET ? "SOL_SOCKET" : "?"
#define __NR32ATRF2_setsockopt              "%#" PRIxSIZ
#define __NR32ATRA2_setsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optname)
#define __NR32ATRF3_setsockopt              "%p"
#define __NR32ATRA3_setsockopt(sockfd, level, optname, optval, optlen) ,optval
#define __NR32ATRF4_setsockopt              "%" PRIuSIZ
#define __NR32ATRA4_setsockopt(sockfd, level, optname, optval, optlen) ,(uintptr_t)(optlen)
#define __NR32ATRF0_getsockname             "%d"
#define __NR32ATRA0_getsockname(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_getsockname             "%p"
#define __NR32ATRA1_getsockname(sockfd, addr, addr_len) ,addr
#define __NR32ATRF2_getsockname             "%p"
#define __NR32ATRA2_getsockname(sockfd, addr, addr_len) ,addr_len
#define __NR32ATRF0_getpeername             "%d"
#define __NR32ATRA0_getpeername(sockfd, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_getpeername             "%p"
#define __NR32ATRA1_getpeername(sockfd, addr, addr_len) ,addr
#define __NR32ATRF2_getpeername             "%p"
#define __NR32ATRA2_getpeername(sockfd, addr, addr_len) ,addr_len
#define __NR32ATRF0_sendto                  "%d"
#define __NR32ATRA0_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_sendto                  "%p"
#define __NR32ATRA1_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,buf
#define __NR32ATRF2_sendto                  "%" PRIuSIZ
#define __NR32ATRA2_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,bufsize
#define __NR32ATRF3_sendto                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(flags),(flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                                        ,((flags) & MSG_DONTROUTE) && ((flags) & (MSG_CONFIRM)) ? "|" : "",(flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                                        ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                        ,((flags) & MSG_EOR) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                                        ,((flags) & MSG_MORE) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR)) ? "|" : "",(flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                                        ,((flags) & MSG_NOSIGNAL) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE)) ? "|" : "",(flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                                        ,((flags) & MSG_OOB) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NR32ATRF4_sendto                  "%p"
#define __NR32ATRA4_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,addr
#define __NR32ATRF5_sendto                  "%" PRIuSIZ
#define __NR32ATRA5_sendto(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(addr_len)
#define __NR32ATRF0_sendmsg                 "%d"
#define __NR32ATRA0_sendmsg(sockfd, message, flags) ,(int)(sockfd)
#define __NR32ATRF1_sendmsg                 "%p"
#define __NR32ATRA1_sendmsg(sockfd, message, flags) ,message
#define __NR32ATRF2_sendmsg                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_sendmsg(sockfd, message, flags) ,(uintptr_t)(flags),(flags) & MSG_CONFIRM ? "MSG_CONFIRM" : "" \
                                                    ,((flags) & MSG_DONTROUTE) && ((flags) & (MSG_CONFIRM)) ? "|" : "",(flags) & MSG_DONTROUTE ? "MSG_DONTROUTE" : "" \
                                                    ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                    ,((flags) & MSG_EOR) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_EOR ? "MSG_EOR" : "" \
                                                    ,((flags) & MSG_MORE) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR)) ? "|" : "",(flags) & MSG_MORE ? "MSG_MORE" : "" \
                                                    ,((flags) & MSG_NOSIGNAL) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE)) ? "|" : "",(flags) & MSG_NOSIGNAL ? "MSG_NOSIGNAL" : "" \
                                                    ,((flags) & MSG_OOB) && ((flags) & (MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : ""
#define __NR32ATRF0_recvfrom                "%d"
#define __NR32ATRA0_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,(int)(sockfd)
#define __NR32ATRF1_recvfrom                "%p"
#define __NR32ATRA1_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,buf
#define __NR32ATRF2_recvfrom                "%" PRIuSIZ
#define __NR32ATRA2_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,bufsize
#define __NR32ATRF3_recvfrom                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,(uintptr_t)(flags),(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                                          ,((flags) & MSG_ERRQUEUE) && ((flags) & (MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                                          ,((flags) & MSG_OOB) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                                          ,((flags) & MSG_PEEK) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB)) ? "|" : "",(flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                                          ,((flags) & MSG_TRUNC) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK)) ? "|" : "",(flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                                          ,((flags) & MSG_WAITALL) && ((flags) & (MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK|MSG_TRUNC)) ? "|" : "",(flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NR32ATRF4_recvfrom                "%p"
#define __NR32ATRA4_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,addr
#define __NR32ATRF5_recvfrom                "%p"
#define __NR32ATRA5_recvfrom(sockfd, buf, bufsize, flags, addr, addr_len) ,addr_len
#define __NR32ATRF0_recvmsg                 "%d"
#define __NR32ATRA0_recvmsg(sockfd, message, flags) ,(int)(sockfd)
#define __NR32ATRF1_recvmsg                 "%p"
#define __NR32ATRA1_recvmsg(sockfd, message, flags) ,message
#define __NR32ATRF2_recvmsg                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_recvmsg(sockfd, message, flags) ,(uintptr_t)(flags),(flags) & MSG_CMSG_CLOEXEC ? "MSG_CMSG_CLOEXEC" : "" \
                                                    ,((flags) & MSG_CMSG_CLOFORK) && ((flags) & (MSG_CMSG_CLOEXEC)) ? "|" : "",(flags) & MSG_CMSG_CLOFORK ? "MSG_CMSG_CLOFORK" : "" \
                                                    ,((flags) & MSG_DONTWAIT) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK)) ? "|" : "",(flags) & MSG_DONTWAIT ? "MSG_DONTWAIT" : "" \
                                                    ,((flags) & MSG_ERRQUEUE) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT)) ? "|" : "",(flags) & MSG_ERRQUEUE ? "MSG_ERRQUEUE" : "" \
                                                    ,((flags) & MSG_OOB) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE)) ? "|" : "",(flags) & MSG_OOB ? "MSG_OOB" : "" \
                                                    ,((flags) & MSG_PEEK) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB)) ? "|" : "",(flags) & MSG_PEEK ? "MSG_PEEK" : "" \
                                                    ,((flags) & MSG_TRUNC) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK)) ? "|" : "",(flags) & MSG_TRUNC ? "MSG_TRUNC" : "" \
                                                    ,((flags) & MSG_WAITALL) && ((flags) & (MSG_CMSG_CLOEXEC|MSG_CMSG_CLOFORK|MSG_DONTWAIT|MSG_ERRQUEUE|MSG_OOB|MSG_PEEK|MSG_TRUNC)) ? "|" : "",(flags) & MSG_WAITALL ? "MSG_WAITALL" : ""
#define __NR32ATRF0_shutdown                "%d"
#define __NR32ATRA0_shutdown(sockfd, how)   ,(int)(sockfd)
#define __NR32ATRF1_shutdown                "%#Ix=%s"
#define __NR32ATRA1_shutdown(sockfd, how)   ,(how),(how) == SHUT_RD ? "SHUT_RD" : (how) == SHUT_WR ? "SHUT_WR" : (how) == SHUT_RDWR ? "SHUT_RDWR" : "?"
#define __NR32ATRF0_userfaultfd             "%d"
#define __NR32ATRA0_userfaultfd(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_membarrier              "%d"
#define __NR32ATRA0_membarrier(TODO_PROTOTYPE) ,TODO_PROTOTYPE
#define __NR32ATRF0_mlock2                  "%d"
#define __NR32ATRA0_mlock2(TODO_PROTOTYPE)  ,TODO_PROTOTYPE
#define __NR32ATRF0_hop                     "%d"
#define __NR32ATRA0_hop(fd, command, arg)   ,(int)(fd)
#define __NR32ATRF1_hop                     "%#" PRIxSIZ
#define __NR32ATRA1_hop(fd, command, arg)   ,(uintptr_t)(command)
#define __NR32ATRF2_hop                     "%p"
#define __NR32ATRA2_hop(fd, command, arg)   ,arg
#define __NR32ATRF0_hopf                    "%d"
#define __NR32ATRA0_hopf(fd, command, mode, arg) ,(int)(fd)
#define __NR32ATRF1_hopf                    "%#" PRIxSIZ
#define __NR32ATRA1_hopf(fd, command, mode, arg) ,(uintptr_t)(command)
#define __NR32ATRF2_hopf                    "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_hopf(fd, command, mode, arg) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                 ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                 ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                 ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                 ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                 ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                 ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                 ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                 ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF3_hopf                    "%p"
#define __NR32ATRA3_hopf(fd, command, mode, arg) ,arg
#define __NR32ATRF0_readf                   "%d"
#define __NR32ATRA0_readf(fd, buf, bufsize, mode) ,(int)(fd)
#define __NR32ATRF1_readf                   "%p"
#define __NR32ATRA1_readf(fd, buf, bufsize, mode) ,buf
#define __NR32ATRF2_readf                   "%" PRIuSIZ
#define __NR32ATRA2_readf(fd, buf, bufsize, mode) ,bufsize
#define __NR32ATRF3_readf                   "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_readf(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                  ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                  ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                  ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                  ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                  ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                  ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                  ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                  ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_writef                  "%d"
#define __NR32ATRA0_writef(fd, buf, bufsize, mode) ,(int)(fd)
#define __NR32ATRF1_writef                  "%p"
#define __NR32ATRA1_writef(fd, buf, bufsize, mode) ,buf
#define __NR32ATRF2_writef                  "%" PRIuSIZ
#define __NR32ATRA2_writef(fd, buf, bufsize, mode) ,bufsize
#define __NR32ATRF3_writef                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_writef(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                   ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                   ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                   ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                   ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                   ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                   ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                   ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                   ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_detach                  "%" PRIdSIZ
#define __NR32ATRA0_detach(pid)             ,(intptr_t)(pid)
#define __NR32ATRF0_frealpath4              "%d"
#define __NR32ATRA0_frealpath4(fd, buf, buflen, flags) ,(int)(fd)
#define __NR32ATRF1_frealpath4              "%p"
#define __NR32ATRA1_frealpath4(fd, buf, buflen, flags) ,buf
#define __NR32ATRF2_frealpath4              "%" PRIuSIZ
#define __NR32ATRA2_frealpath4(fd, buf, buflen, flags) ,buflen
#define __NR32ATRF3_frealpath4              "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA3_frealpath4(fd, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                       ,((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH)) ? "|" : "",(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                       ,((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH|AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_frealpathat             "%d"
#define __NR32ATRA0_frealpathat(dirfd, filename, buf, buflen, flags) ,(int)(dirfd)
#define __NR32ATRF1_frealpathat             "%q"
#define __NR32ATRA1_frealpathat(dirfd, filename, buf, buflen, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_frealpathat             "%p"
#define __NR32ATRA2_frealpathat(dirfd, filename, buf, buflen, flags) ,buf
#define __NR32ATRF3_frealpathat             "%" PRIuSIZ
#define __NR32ATRA3_frealpathat(dirfd, filename, buf, buflen, flags) ,buflen
#define __NR32ATRF4_frealpathat             "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR32ATRA4_frealpathat(dirfd, filename, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_ALTPATH ? "AT_ALTPATH" : "" \
                                                                     ,((flags) & AT_SYMLINK_NOFOLLOW) && ((flags) & (AT_ALTPATH)) ? "|" : "",(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                                     ,((flags) & AT_READLINK_REQSIZE) && ((flags) & (AT_ALTPATH|AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                                     ,((flags) & AT_DOSPATH) && ((flags) & (AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_rpc_schedule            "%" PRIdSIZ
#define __NR32ATRA0_rpc_schedule(target, flags, program, arguments) ,(intptr_t)(target)
#define __NR32ATRF1_rpc_schedule            "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA1_rpc_schedule(target, flags, program, arguments) ,(uintptr_t)(flags),(flags) & RPC_SCHEDULE_ASYNC ? "RPC_SCHEDULE_ASYNC" : (flags) ? "" : "RPC_SCHEDULE_SYNC" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_NONSYSCALL) && ((flags) & (RPC_SCHEDULE_ASYNC)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_NONSYSCALL ? "RPC_SCHEDULE_FLAG_NONSYSCALL" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_WAITFORSTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_WAITFORSTART ? "RPC_SCHEDULE_FLAG_WAITFORSTART" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_STATUSFUTEX ? "RPC_SCHEDULE_FLAG_STATUSFUTEX" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_SYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_SYSRESTART ? "RPC_SCHEDULE_FLAG_SYSRESTART" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_NOSYSRESTART ? "RPC_SCHEDULE_FLAG_NOSYSRESTART" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_WAITSMPACK) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_WAITSMPACK ? "RPC_SCHEDULE_FLAG_WAITSMPACK" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_DONTWAKE) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_DONTWAKE ? "RPC_SCHEDULE_FLAG_DONTWAKE" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_HIGHPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK|RPC_SCHEDULE_FLAG_DONTWAKE)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_HIGHPRIO ? "RPC_SCHEDULE_FLAG_HIGHPRIO" : "" \
                                                                    ,((flags) & RPC_SCHEDULE_FLAG_LOWPRIO) && ((flags) & (RPC_SCHEDULE_ASYNC|RPC_SCHEDULE_FLAG_NONSYSCALL|RPC_SCHEDULE_FLAG_WAITFORSTART|RPC_SCHEDULE_FLAG_STATUSFUTEX|RPC_SCHEDULE_FLAG_SYSRESTART|RPC_SCHEDULE_FLAG_NOSYSRESTART|RPC_SCHEDULE_FLAG_WAITSMPACK|RPC_SCHEDULE_FLAG_DONTWAKE|RPC_SCHEDULE_FLAG_HIGHPRIO)) ? "|" : "",(flags) & RPC_SCHEDULE_FLAG_LOWPRIO ? "RPC_SCHEDULE_FLAG_LOWPRIO" : ""
#define __NR32ATRF2_rpc_schedule            "%p"
#define __NR32ATRA2_rpc_schedule(target, flags, program, arguments) ,program
#define __NR32ATRF3_rpc_schedule            "%p"
#define __NR32ATRA3_rpc_schedule(target, flags, program, arguments) ,arguments
#define __NR32ATRF0_sysctl                  "%#" PRIxSIZ
#define __NR32ATRA0_sysctl(command, arg)    ,(uintptr_t)(command)
#define __NR32ATRF1_sysctl                  "%p"
#define __NR32ATRA1_sysctl(command, arg)    ,arg
#define __NR32ATRF0_openpty                 "%p"
#define __NR32ATRA0_openpty(amaster, aslave, name, termp, winp) ,amaster
#define __NR32ATRF1_openpty                 "%p"
#define __NR32ATRA1_openpty(amaster, aslave, name, termp, winp) ,aslave
#define __NR32ATRF2_openpty                 "%p"
#define __NR32ATRA2_openpty(amaster, aslave, name, termp, winp) ,name
#define __NR32ATRF3_openpty                 "%p"
#define __NR32ATRA3_openpty(amaster, aslave, name, termp, winp) ,termp
#define __NR32ATRF4_openpty                 "%p"
#define __NR32ATRA4_openpty(amaster, aslave, name, termp, winp) ,winp
#define __NR32ATRF0_fchdirat                "%d"
#define __NR32ATRA0_fchdirat(dirfd, path, flags) ,(int)(dirfd)
#define __NR32ATRF1_fchdirat                "%q"
#define __NR32ATRA1_fchdirat(dirfd, path, flags) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF2_fchdirat                "%#" PRIxSIZ "=%s"
#define __NR32ATRA2_fchdirat(dirfd, path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_time64                  "%p"
#define __NR32ATRA0_time64(timer)           ,timer
#define __NR32ATRF0_set_exception_handler   "%#" PRIxSIZ
#define __NR32ATRA0_set_exception_handler(mode, handler, handler_sp) ,(uintptr_t)(mode)
#define __NR32ATRF1_set_exception_handler   "%p"
#define __NR32ATRA1_set_exception_handler(mode, handler, handler_sp) ,handler
#define __NR32ATRF2_set_exception_handler   "%p"
#define __NR32ATRA2_set_exception_handler(mode, handler, handler_sp) ,handler_sp
#define __NR32ATRF0_get_exception_handler   "%p"
#define __NR32ATRA0_get_exception_handler(pmode, phandler, phandler_sp) ,pmode
#define __NR32ATRF1_get_exception_handler   "%p"
#define __NR32ATRA1_get_exception_handler(pmode, phandler, phandler_sp) ,phandler
#define __NR32ATRF2_get_exception_handler   "%p"
#define __NR32ATRA2_get_exception_handler(pmode, phandler, phandler_sp) ,phandler_sp
#define __NR32ATRF0_set_library_listdef     "%p"
#define __NR32ATRA0_set_library_listdef(listdef) ,listdef
#define __NR32ATRF0_debugtrap               "%p"
#define __NR32ATRA0_debugtrap(state, reason) ,state
#define __NR32ATRF1_debugtrap               "%p"
#define __NR32ATRA1_debugtrap(state, reason) ,reason
#define __NR32ATRF0_lfutex                  "%p"
#define __NR32ATRA0_lfutex(uaddr, futex_op, val, timeout, val2) ,uaddr
#define __NR32ATRF1_lfutex                  "%#" PRIxSIZ
#define __NR32ATRA1_lfutex(uaddr, futex_op, val, timeout, val2) ,(uintptr_t)(futex_op)
#define __NR32ATRF2_lfutex                  "%" PRIu32
#define __NR32ATRA2_lfutex(uaddr, futex_op, val, timeout, val2) ,val
#define __NR32ATRF3_lfutex                  "%p"
#define __NR32ATRA3_lfutex(uaddr, futex_op, val, timeout, val2) ,timeout
#define __NR32ATRF4_lfutex                  "%" PRIu32
#define __NR32ATRA4_lfutex(uaddr, futex_op, val, timeout, val2) ,val2
#define __NR32ATRF0_lseek64                 "%d"
#define __NR32ATRA0_lseek64(fd, offset, whence) ,(int)(fd)
#define __NR32ATRF1_lseek64                 "%" PRId64
#define __NR32ATRA1_lseek64(fd, offset, whence) ,offset
#define __NR32ATRF2_lseek64                 "%#Ix=%s"
#define __NR32ATRA2_lseek64(fd, offset, whence) ,(whence),(whence) == SEEK_SET ? "SEEK_SET" : (whence) == SEEK_CUR ? "SEEK_CUR" : (whence) == SEEK_END ? "SEEK_END" : (whence) == SEEK_DATA ? "SEEK_DATA" : (whence) == SEEK_HOLE ? "SEEK_HOLE" : "?"
#define __NR32ATRF0_lfutexexpr              "%p"
#define __NR32ATRA0_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,base
#define __NR32ATRF1_lfutexexpr              "%" PRIuSIZ
#define __NR32ATRA1_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,exprc
#define __NR32ATRF2_lfutexexpr              "%p"
#define __NR32ATRA2_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,exprv
#define __NR32ATRF3_lfutexexpr              "%p"
#define __NR32ATRA3_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,timeout
#define __NR32ATRF4_lfutexexpr              "%#" PRIxSIZ
#define __NR32ATRA4_lfutexexpr(base, exprc, exprv, timeout, timeout_flags) ,(uintptr_t)(timeout_flags)
#define __NR32ATRF0_lfutexlockexpr          "%p"
#define __NR32ATRA0_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,ulockaddr
#define __NR32ATRF1_lfutexlockexpr          "%p"
#define __NR32ATRA1_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,base
#define __NR32ATRF2_lfutexlockexpr          "%" PRIuSIZ
#define __NR32ATRA2_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,exprc
#define __NR32ATRF3_lfutexlockexpr          "%p"
#define __NR32ATRA3_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,exprv
#define __NR32ATRF4_lfutexlockexpr          "%p"
#define __NR32ATRA4_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,timeout
#define __NR32ATRF5_lfutexlockexpr          "%#" PRIxSIZ
#define __NR32ATRA5_lfutexlockexpr(ulockaddr, base, exprc, exprv, timeout, timeout_flags) ,(uintptr_t)(timeout_flags)
#define __NR32ATRF0_mktty                   "%d"
#define __NR32ATRA0_mktty(keyboard, display, name, rsvd) ,(int)(keyboard)
#define __NR32ATRF1_mktty                   "%d"
#define __NR32ATRA1_mktty(keyboard, display, name, rsvd) ,(int)(display)
#define __NR32ATRF2_mktty                   "%q"
#define __NR32ATRA2_mktty(keyboard, display, name, rsvd) ,(validate_readable_opt(name,1),name)
#define __NR32ATRF3_mktty                   "%#" PRIxSIZ
#define __NR32ATRA3_mktty(keyboard, display, name, rsvd) ,(uintptr_t)(rsvd)
#define __NR32ATRF0_raiseat                 "%p"
#define __NR32ATRA0_raiseat(state, si)      ,state
#define __NR32ATRF1_raiseat                 "%p"
#define __NR32ATRA1_raiseat(state, si)      ,si
#define __NR32ATRF0_coredump                "%p"
#define __NR32ATRA0_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,curr_state
#define __NR32ATRF1_coredump                "%p"
#define __NR32ATRA1_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,orig_state
#define __NR32ATRF2_coredump                "%p"
#define __NR32ATRA2_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,traceback_vector
#define __NR32ATRF3_coredump                "%" PRIuSIZ
#define __NR32ATRA3_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,traceback_length
#define __NR32ATRF4_coredump                "%p"
#define __NR32ATRA4_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,exception
#define __NR32ATRF5_coredump                "%#" PRIxSIZ
#define __NR32ATRA5_coredump(curr_state, orig_state, traceback_vector, traceback_length, exception, unwind_error) ,(uintptr_t)(unwind_error)
#define __NR32ATRF0_stime64                 "%p"
#define __NR32ATRA0_stime64(t)              ,t
#define __NR32ATRF0_utime64                 "%q"
#define __NR32ATRA0_utime64(filename, times) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_utime64                 "%p"
#define __NR32ATRA1_utime64(filename, times) ,times
#define __NR32ATRF0_ioctlf                  "%d"
#define __NR32ATRA0_ioctlf(fd, command, mode, arg) ,(int)(fd)
#define __NR32ATRF1_ioctlf                  "%#" PRIxSIZ
#define __NR32ATRA1_ioctlf(fd, command, mode, arg) ,(uintptr_t)(command)
#define __NR32ATRF2_ioctlf                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA2_ioctlf(fd, command, mode, arg) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                   ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                   ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                   ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                   ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                   ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                   ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                   ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                   ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF3_ioctlf                  "%p"
#define __NR32ATRA3_ioctlf(fd, command, mode, arg) ,arg
#define __NR32ATRF0_fsmode                  "%" PRIu64
#define __NR32ATRA0_fsmode(mode)            ,mode
#define __NR32ATRF0_gettimeofday64          "%p"
#define __NR32ATRA0_gettimeofday64(tv, tz)  ,tv
#define __NR32ATRF1_gettimeofday64          "%p"
#define __NR32ATRA1_gettimeofday64(tv, tz)  ,tz
#define __NR32ATRF0_settimeofday64          "%p"
#define __NR32ATRA0_settimeofday64(tv, tz)  ,tv
#define __NR32ATRF1_settimeofday64          "%p"
#define __NR32ATRA1_settimeofday64(tv, tz)  ,tz
#define __NR32ATRF0_select64                "%" PRIuSIZ
#define __NR32ATRA0_select64(nfds, readfds, writefds, exceptfds, timeout) ,nfds
#define __NR32ATRF1_select64                "%p"
#define __NR32ATRA1_select64(nfds, readfds, writefds, exceptfds, timeout) ,readfds
#define __NR32ATRF2_select64                "%p"
#define __NR32ATRA2_select64(nfds, readfds, writefds, exceptfds, timeout) ,writefds
#define __NR32ATRF3_select64                "%p"
#define __NR32ATRA3_select64(nfds, readfds, writefds, exceptfds, timeout) ,exceptfds
#define __NR32ATRF4_select64                "%p"
#define __NR32ATRA4_select64(nfds, readfds, writefds, exceptfds, timeout) ,timeout
#define __NR32ATRF0_maplibrary              "%p"
#define __NR32ATRA0_maplibrary(addr, flags, fd, hdrv, hdrc) ,addr
#define __NR32ATRF1_maplibrary              "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA1_maplibrary(addr, flags, fd, hdrv, hdrc) ,(uintptr_t)(flags),(flags) & MAP_FIXED ? "MAP_FIXED" : "" \
                                                            ,((flags) & MAP_LOCKED) && ((flags) & (MAP_FIXED)) ? "|" : "",(flags) & MAP_LOCKED ? "MAP_LOCKED" : "" \
                                                            ,((flags) & MAP_NONBLOCK) && ((flags) & (MAP_FIXED|MAP_LOCKED)) ? "|" : "",(flags) & MAP_NONBLOCK ? "MAP_NONBLOCK" : "" \
                                                            ,((flags) & MAP_NORESERVE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK)) ? "|" : "",(flags) & MAP_NORESERVE ? "MAP_NORESERVE" : "" \
                                                            ,((flags) & MAP_POPULATE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE)) ? "|" : "",(flags) & MAP_POPULATE ? "MAP_POPULATE" : "" \
                                                            ,((flags) & MAP_SYNC) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE)) ? "|" : "",(flags) & MAP_SYNC ? "MAP_SYNC" : "" \
                                                            ,((flags) & MAP_DONT_MAP) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_SYNC)) ? "|" : "",(flags) & MAP_DONT_MAP ? "MAP_DONT_MAP" : "" \
                                                            ,((flags) & MAP_DONT_OVERRIDE) && ((flags) & (MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP)) ? "|" : "",(flags) & MAP_DONT_OVERRIDE ? "MAP_DONT_OVERRIDE" : ""
#define __NR32ATRF2_maplibrary              "%d"
#define __NR32ATRA2_maplibrary(addr, flags, fd, hdrv, hdrc) ,(int)(fd)
#define __NR32ATRF3_maplibrary              "%p"
#define __NR32ATRA3_maplibrary(addr, flags, fd, hdrv, hdrc) ,hdrv
#define __NR32ATRF4_maplibrary              "%" PRIuSIZ
#define __NR32ATRA4_maplibrary(addr, flags, fd, hdrv, hdrc) ,hdrc
#define __NR32ATRF0_setitimer64             "%#" PRIxSIZ
#define __NR32ATRA0_setitimer64(which, newval, oldval) ,(uintptr_t)(which)
#define __NR32ATRF1_setitimer64             "%p"
#define __NR32ATRA1_setitimer64(which, newval, oldval) ,newval
#define __NR32ATRF2_setitimer64             "%p"
#define __NR32ATRA2_setitimer64(which, newval, oldval) ,oldval
#define __NR32ATRF0_getitimer64             "%#" PRIxSIZ
#define __NR32ATRA0_getitimer64(which, curr_value) ,(uintptr_t)(which)
#define __NR32ATRF1_getitimer64             "%p"
#define __NR32ATRA1_getitimer64(which, curr_value) ,curr_value
#define __NR32ATRF0_kreaddir                "%d"
#define __NR32ATRA0_kreaddir(fd, buf, bufsize, mode) ,(int)(fd)
#define __NR32ATRF1_kreaddir                "%p"
#define __NR32ATRA1_kreaddir(fd, buf, bufsize, mode) ,buf
#define __NR32ATRF2_kreaddir                "%" PRIuSIZ
#define __NR32ATRA2_kreaddir(fd, buf, bufsize, mode) ,bufsize
#define __NR32ATRF3_kreaddir                "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR32ATRA3_kreaddir(fd, buf, bufsize, mode) ,(uintptr_t)(mode),(mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                     ,((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "",(mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                     ,((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK)) ? "|" : "",(mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                     ,((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK|READDIR_SKIPREL)) ? "|" : "",(mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NR32ATRF0_readvf                  "%d"
#define __NR32ATRA0_readvf(fd, iovec, count, mode) ,(int)(fd)
#define __NR32ATRF1_readvf                  "%p"
#define __NR32ATRA1_readvf(fd, iovec, count, mode) ,iovec
#define __NR32ATRF2_readvf                  "%" PRIuSIZ
#define __NR32ATRA2_readvf(fd, iovec, count, mode) ,count
#define __NR32ATRF3_readvf                  "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_readvf(fd, iovec, count, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                   ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                   ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                   ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                   ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                   ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                   ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                   ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                   ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_writevf                 "%d"
#define __NR32ATRA0_writevf(fd, iovec, count, mode) ,(int)(fd)
#define __NR32ATRF1_writevf                 "%p"
#define __NR32ATRA1_writevf(fd, iovec, count, mode) ,iovec
#define __NR32ATRF2_writevf                 "%" PRIuSIZ
#define __NR32ATRA2_writevf(fd, iovec, count, mode) ,count
#define __NR32ATRF3_writevf                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA3_writevf(fd, iovec, count, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                    ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                    ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                    ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                    ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                    ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                    ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                    ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                    ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_sched_rr_get_interval64 "%" PRIdSIZ
#define __NR32ATRA0_sched_rr_get_interval64(pid, tms) ,(intptr_t)(pid)
#define __NR32ATRF1_sched_rr_get_interval64 "%p"
#define __NR32ATRA1_sched_rr_get_interval64(pid, tms) ,tms
#define __NR32ATRF0_nanosleep64             "%p"
#define __NR32ATRA0_nanosleep64(req, rem)   ,req
#define __NR32ATRF1_nanosleep64             "%p"
#define __NR32ATRA1_nanosleep64(req, rem)   ,rem
#define __NR32ATRF0_rt_sigtimedwait64       "%p"
#define __NR32ATRA0_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,set
#define __NR32ATRF1_rt_sigtimedwait64       "%p"
#define __NR32ATRA1_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,info
#define __NR32ATRF2_rt_sigtimedwait64       "%p"
#define __NR32ATRA2_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,timeout
#define __NR32ATRF3_rt_sigtimedwait64       "%" PRIuSIZ
#define __NR32ATRA3_rt_sigtimedwait64(set, info, timeout, sigsetsize) ,sigsetsize
#define __NR32ATRF0_pread64f                "%d"
#define __NR32ATRA0_pread64f(fd, buf, bufsize, offset, mode) ,(int)(fd)
#define __NR32ATRF1_pread64f                "%p"
#define __NR32ATRA1_pread64f(fd, buf, bufsize, offset, mode) ,buf
#define __NR32ATRF2_pread64f                "%" PRIuSIZ
#define __NR32ATRA2_pread64f(fd, buf, bufsize, offset, mode) ,bufsize
#define __NR32ATRF3_pread64f                "%" PRIu64
#define __NR32ATRA3_pread64f(fd, buf, bufsize, offset, mode) ,offset
#define __NR32ATRF4_pread64f                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_pread64f(fd, buf, bufsize, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                             ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                             ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                             ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                             ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                             ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                             ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                             ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                             ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_pwrite64f               "%d"
#define __NR32ATRA0_pwrite64f(fd, buf, bufsize, offset, mode) ,(int)(fd)
#define __NR32ATRF1_pwrite64f               "%p"
#define __NR32ATRA1_pwrite64f(fd, buf, bufsize, offset, mode) ,buf
#define __NR32ATRF2_pwrite64f               "%" PRIuSIZ
#define __NR32ATRA2_pwrite64f(fd, buf, bufsize, offset, mode) ,bufsize
#define __NR32ATRF3_pwrite64f               "%" PRIu64
#define __NR32ATRA3_pwrite64f(fd, buf, bufsize, offset, mode) ,offset
#define __NR32ATRF4_pwrite64f               "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_pwrite64f(fd, buf, bufsize, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                              ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                              ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                              ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                              ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                              ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                              ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                              ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                              ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_kstat                   "%q"
#define __NR32ATRA0_kstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_kstat                   "%p"
#define __NR32ATRA1_kstat(filename, statbuf) ,statbuf
#define __NR32ATRF0_klstat                  "%q"
#define __NR32ATRA0_klstat(filename, statbuf) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_klstat                  "%p"
#define __NR32ATRA1_klstat(filename, statbuf) ,statbuf
#define __NR32ATRF0_kfstat                  "%d"
#define __NR32ATRA0_kfstat(fd, statbuf)     ,(int)(fd)
#define __NR32ATRF1_kfstat                  "%p"
#define __NR32ATRA1_kfstat(fd, statbuf)     ,statbuf
#define __NR32ATRF0_kreaddirf               "%d"
#define __NR32ATRA0_kreaddirf(fd, buf, bufsize, mode, iomode) ,(int)(fd)
#define __NR32ATRF1_kreaddirf               "%p"
#define __NR32ATRA1_kreaddirf(fd, buf, bufsize, mode, iomode) ,buf
#define __NR32ATRF2_kreaddirf               "%" PRIuSIZ
#define __NR32ATRA2_kreaddirf(fd, buf, bufsize, mode, iomode) ,bufsize
#define __NR32ATRF3_kreaddirf               "%#" PRIxSIZ "=%s%s%s%s%s%s%s"
#define __NR32ATRA3_kreaddirf(fd, buf, bufsize, mode, iomode) ,(uintptr_t)(mode),(mode) & READDIR_CONTINUE ? "READDIR_CONTINUE" : (mode) ? "" : "READDIR_DEFAULT" \
                                                              ,((mode) & READDIR_PEEK) && ((mode) & (READDIR_CONTINUE)) ? "|" : "",(mode) & READDIR_PEEK ? "READDIR_PEEK" : "" \
                                                              ,((mode) & READDIR_SKIPREL) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK)) ? "|" : "",(mode) & READDIR_SKIPREL ? "READDIR_SKIPREL" : "" \
                                                              ,((mode) & READDIR_WANTEOF) && ((mode) & (READDIR_CONTINUE|READDIR_PEEK|READDIR_SKIPREL)) ? "|" : "",(mode) & READDIR_WANTEOF ? "READDIR_WANTEOF" : ""
#define __NR32ATRF4_kreaddirf               "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_kreaddirf(fd, buf, bufsize, mode, iomode) ,(uintptr_t)(iomode),(iomode) & IO_WRONLY ? "IO_WRONLY" : (iomode) ? "" : "IO_RDONLY" \
                                                              ,((iomode) & IO_RDWR) && ((iomode) & (IO_WRONLY)) ? "|" : "",(iomode) & IO_RDWR ? "IO_RDWR" : "" \
                                                              ,((iomode) & IO_CLOEXEC) && ((iomode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(iomode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                              ,((iomode) & IO_CLOFORK) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(iomode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                              ,((iomode) & IO_APPEND) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(iomode) & IO_APPEND ? "IO_APPEND" : "" \
                                                              ,((iomode) & IO_NONBLOCK) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(iomode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                              ,((iomode) & IO_SYNC) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(iomode) & IO_SYNC ? "IO_SYNC" : "" \
                                                              ,((iomode) & IO_ASYNC) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(iomode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                              ,((iomode) & IO_DIRECT) && ((iomode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(iomode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_timer_settime64         "%p"
#define __NR32ATRA0_timer_settime64(timerid, flags, value, ovalue) ,timerid
#define __NR32ATRF1_timer_settime64         "%#" PRIxSIZ
#define __NR32ATRA1_timer_settime64(timerid, flags, value, ovalue) ,(uintptr_t)(flags)
#define __NR32ATRF2_timer_settime64         "%p"
#define __NR32ATRA2_timer_settime64(timerid, flags, value, ovalue) ,value
#define __NR32ATRF3_timer_settime64         "%p"
#define __NR32ATRA3_timer_settime64(timerid, flags, value, ovalue) ,ovalue
#define __NR32ATRF0_timer_gettime64         "%p"
#define __NR32ATRA0_timer_gettime64(timerid, value) ,timerid
#define __NR32ATRF1_timer_gettime64         "%p"
#define __NR32ATRA1_timer_gettime64(timerid, value) ,value
#define __NR32ATRF0_clock_settime64         "%#" PRIxSIZ
#define __NR32ATRA0_clock_settime64(clock_id, tp) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_clock_settime64         "%p"
#define __NR32ATRA1_clock_settime64(clock_id, tp) ,tp
#define __NR32ATRF0_clock_gettime64         "%#" PRIxSIZ
#define __NR32ATRA0_clock_gettime64(clock_id, tp) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_clock_gettime64         "%p"
#define __NR32ATRA1_clock_gettime64(clock_id, tp) ,tp
#define __NR32ATRF0_clock_getres64          "%#" PRIxSIZ
#define __NR32ATRA0_clock_getres64(clock_id, res) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_clock_getres64          "%p"
#define __NR32ATRA1_clock_getres64(clock_id, res) ,res
#define __NR32ATRF0_clock_nanosleep64       "%#" PRIxSIZ
#define __NR32ATRA0_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,(uintptr_t)(clock_id)
#define __NR32ATRF1_clock_nanosleep64       "%#" PRIxSIZ
#define __NR32ATRA1_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,(uintptr_t)(flags)
#define __NR32ATRF2_clock_nanosleep64       "%p"
#define __NR32ATRA2_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,requested_time
#define __NR32ATRF3_clock_nanosleep64       "%p"
#define __NR32ATRA3_clock_nanosleep64(clock_id, flags, requested_time, remaining) ,remaining
#define __NR32ATRF0_utimes64                "%q"
#define __NR32ATRA0_utimes64(filename, times) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF1_utimes64                "%p"
#define __NR32ATRA1_utimes64(filename, times) ,times
#define __NR32ATRF0_fmkdirat                "%d"
#define __NR32ATRA0_fmkdirat(dirfd, pathname, mode, flags) ,(int)(dirfd)
#define __NR32ATRF1_fmkdirat                "%q"
#define __NR32ATRA1_fmkdirat(dirfd, pathname, mode, flags) ,(validate_readable_opt(pathname,1),pathname)
#define __NR32ATRF2_fmkdirat                "%#" PRIoSIZ
#define __NR32ATRA2_fmkdirat(dirfd, pathname, mode, flags) ,(uintptr_t)(mode)
#define __NR32ATRF3_fmkdirat                "%#" PRIxSIZ "=%s"
#define __NR32ATRA3_fmkdirat(dirfd, pathname, mode, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_fmknodat                "%d"
#define __NR32ATRA0_fmknodat(dirfd, nodename, mode, dev, flags) ,(int)(dirfd)
#define __NR32ATRF1_fmknodat                "%q"
#define __NR32ATRA1_fmknodat(dirfd, nodename, mode, dev, flags) ,(validate_readable_opt(nodename,1),nodename)
#define __NR32ATRF2_fmknodat                "%#" PRIoSIZ
#define __NR32ATRA2_fmknodat(dirfd, nodename, mode, dev, flags) ,(uintptr_t)(mode)
#define __NR32ATRF3_fmknodat                "%.2x:%.2x"
#define __NR32ATRA3_fmknodat(dirfd, nodename, mode, dev, flags) ,(unsigned int)MAJOR(dev),(unsigned int)MINOR(dev)
#define __NR32ATRF4_fmknodat                "%#" PRIxSIZ "=%s"
#define __NR32ATRA4_fmknodat(dirfd, nodename, mode, dev, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_futimesat64             "%d"
#define __NR32ATRA0_futimesat64(dirfd, filename, times) ,(int)(dirfd)
#define __NR32ATRF1_futimesat64             "%p"
#define __NR32ATRA1_futimesat64(dirfd, filename, times) ,filename
#define __NR32ATRF2_futimesat64             "%p"
#define __NR32ATRA2_futimesat64(dirfd, filename, times) ,times
#define __NR32ATRF0_kfstatat                "%d"
#define __NR32ATRA0_kfstatat(dirfd, filename, statbuf, flags) ,(int)(dirfd)
#define __NR32ATRF1_kfstatat                "%q"
#define __NR32ATRA1_kfstatat(dirfd, filename, statbuf, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_kfstatat                "%p"
#define __NR32ATRA2_kfstatat(dirfd, filename, statbuf, flags) ,statbuf
#define __NR32ATRF3_kfstatat                "%#" PRIxSIZ "=%s%s%s"
#define __NR32ATRA3_kfstatat(dirfd, filename, statbuf, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                              ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_frenameat               "%d"
#define __NR32ATRA0_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(int)(oldfd)
#define __NR32ATRF1_frenameat               "%q"
#define __NR32ATRA1_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(validate_readable_opt(oldname,1),oldname)
#define __NR32ATRF2_frenameat               "%d"
#define __NR32ATRA2_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(int)(newfd)
#define __NR32ATRF3_frenameat               "%q"
#define __NR32ATRA3_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(validate_readable_opt(newname_or_path,1),newname_or_path)
#define __NR32ATRF4_frenameat               "%#" PRIxSIZ "=%s"
#define __NR32ATRA4_frenameat(oldfd, oldname, newfd, newname_or_path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_fsymlinkat              "%q"
#define __NR32ATRA0_fsymlinkat(link_text, tofd, target_path, flags) ,(validate_readable_opt(link_text,1),link_text)
#define __NR32ATRF1_fsymlinkat              "%d"
#define __NR32ATRA1_fsymlinkat(link_text, tofd, target_path, flags) ,(int)(tofd)
#define __NR32ATRF2_fsymlinkat              "%q"
#define __NR32ATRA2_fsymlinkat(link_text, tofd, target_path, flags) ,(validate_readable_opt(target_path,1),target_path)
#define __NR32ATRF3_fsymlinkat              "%#" PRIxSIZ "=%s"
#define __NR32ATRA3_fsymlinkat(link_text, tofd, target_path, flags) ,(uintptr_t)(flags),(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_freadlinkat             "%d"
#define __NR32ATRA0_freadlinkat(dirfd, path, buf, buflen, flags) ,(int)(dirfd)
#define __NR32ATRF1_freadlinkat             "%q"
#define __NR32ATRA1_freadlinkat(dirfd, path, buf, buflen, flags) ,(validate_readable_opt(path,1),path)
#define __NR32ATRF2_freadlinkat             "%p"
#define __NR32ATRA2_freadlinkat(dirfd, path, buf, buflen, flags) ,buf
#define __NR32ATRF3_freadlinkat             "%" PRIuSIZ
#define __NR32ATRA3_freadlinkat(dirfd, path, buf, buflen, flags) ,buflen
#define __NR32ATRF4_freadlinkat             "%#" PRIxSIZ "=%s%s%s"
#define __NR32ATRA4_freadlinkat(dirfd, path, buf, buflen, flags) ,(uintptr_t)(flags),(flags) & AT_READLINK_REQSIZE ? "AT_READLINK_REQSIZE" : "" \
                                                                 ,((flags) & AT_DOSPATH) && ((flags) & (AT_READLINK_REQSIZE)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_pselect6_64             "%" PRIuSIZ
#define __NR32ATRA0_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,nfds
#define __NR32ATRF1_pselect6_64             "%p"
#define __NR32ATRA1_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,readfds
#define __NR32ATRF2_pselect6_64             "%p"
#define __NR32ATRA2_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,writefds
#define __NR32ATRF3_pselect6_64             "%p"
#define __NR32ATRA3_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,exceptfds
#define __NR32ATRF4_pselect6_64             "%p"
#define __NR32ATRA4_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,timeout
#define __NR32ATRF5_pselect6_64             "%p"
#define __NR32ATRA5_pselect6_64(nfds, readfds, writefds, exceptfds, timeout, sigmask_sigset_and_len) ,sigmask_sigset_and_len
#define __NR32ATRF0_ppoll64                 "%p"
#define __NR32ATRA0_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,fds
#define __NR32ATRF1_ppoll64                 "%" PRIuSIZ
#define __NR32ATRA1_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,nfds
#define __NR32ATRF2_ppoll64                 "%p"
#define __NR32ATRA2_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,timeout_ts
#define __NR32ATRF3_ppoll64                 "%p"
#define __NR32ATRA3_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigmask
#define __NR32ATRF4_ppoll64                 "%" PRIuSIZ
#define __NR32ATRA4_ppoll64(fds, nfds, timeout_ts, sigmask, sigsetsize) ,sigsetsize
#define __NR32ATRF0_utimensat64             "%d"
#define __NR32ATRA0_utimensat64(dirfd, filename, times, flags) ,(int)(dirfd)
#define __NR32ATRF1_utimensat64             "%q"
#define __NR32ATRA1_utimensat64(dirfd, filename, times, flags) ,(validate_readable_opt(filename,1),filename)
#define __NR32ATRF2_utimensat64             "%p"
#define __NR32ATRA2_utimensat64(dirfd, filename, times, flags) ,times
#define __NR32ATRF3_utimensat64             "%#" PRIxSIZ "=%s%s%s%s%s"
#define __NR32ATRA3_utimensat64(dirfd, filename, times, flags) ,(uintptr_t)(flags),(flags) & AT_SYMLINK_NOFOLLOW ? "AT_SYMLINK_NOFOLLOW" : "" \
                                                               ,((flags) & AT_CHANGE_CTIME) && ((flags) & (AT_SYMLINK_NOFOLLOW)) ? "|" : "",(flags) & AT_CHANGE_CTIME ? "AT_CHANGE_CTIME" : "" \
                                                               ,((flags) & AT_DOSPATH) && ((flags) & (AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME)) ? "|" : "",(flags) & AT_DOSPATH ? "AT_DOSPATH" : ""
#define __NR32ATRF0_fallocate64             "%d"
#define __NR32ATRA0_fallocate64(fd, mode, offset, length) ,(int)(fd)
#define __NR32ATRF1_fallocate64             "%#" PRIxSIZ
#define __NR32ATRA1_fallocate64(fd, mode, offset, length) ,(uintptr_t)(mode)
#define __NR32ATRF2_fallocate64             "%" PRIu64
#define __NR32ATRA2_fallocate64(fd, mode, offset, length) ,offset
#define __NR32ATRF3_fallocate64             "%" PRIu64
#define __NR32ATRA3_fallocate64(fd, mode, offset, length) ,length
#define __NR32ATRF0_timerfd_settime64       "%d"
#define __NR32ATRA0_timerfd_settime64(ufd, flags, utmr, otmr) ,(int)(ufd)
#define __NR32ATRF1_timerfd_settime64       "%#" PRIxSIZ
#define __NR32ATRA1_timerfd_settime64(ufd, flags, utmr, otmr) ,(uintptr_t)(flags)
#define __NR32ATRF2_timerfd_settime64       "%p"
#define __NR32ATRA2_timerfd_settime64(ufd, flags, utmr, otmr) ,utmr
#define __NR32ATRF3_timerfd_settime64       "%p"
#define __NR32ATRA3_timerfd_settime64(ufd, flags, utmr, otmr) ,otmr
#define __NR32ATRF0_timerfd_gettime64       "%d"
#define __NR32ATRA0_timerfd_gettime64(ufd, otmr) ,(int)(ufd)
#define __NR32ATRF1_timerfd_gettime64       "%p"
#define __NR32ATRA1_timerfd_gettime64(ufd, otmr) ,otmr
#define __NR32ATRF0_preadvf                 "%d"
#define __NR32ATRA0_preadvf(fd, iovec, count, offset, mode) ,(int)(fd)
#define __NR32ATRF1_preadvf                 "%p"
#define __NR32ATRA1_preadvf(fd, iovec, count, offset, mode) ,iovec
#define __NR32ATRF2_preadvf                 "%" PRIuSIZ
#define __NR32ATRA2_preadvf(fd, iovec, count, offset, mode) ,count
#define __NR32ATRF3_preadvf                 "%" PRIu64
#define __NR32ATRA3_preadvf(fd, iovec, count, offset, mode) ,offset
#define __NR32ATRF4_preadvf                 "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_preadvf(fd, iovec, count, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                            ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                            ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                            ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                            ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                            ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                            ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                            ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                            ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_pwritevf                "%d"
#define __NR32ATRA0_pwritevf(fd, iovec, count, offset, mode) ,(int)(fd)
#define __NR32ATRF1_pwritevf                "%p"
#define __NR32ATRA1_pwritevf(fd, iovec, count, offset, mode) ,iovec
#define __NR32ATRF2_pwritevf                "%" PRIuSIZ
#define __NR32ATRA2_pwritevf(fd, iovec, count, offset, mode) ,count
#define __NR32ATRF3_pwritevf                "%" PRIu64
#define __NR32ATRA3_pwritevf(fd, iovec, count, offset, mode) ,offset
#define __NR32ATRF4_pwritevf                "%#" PRIxSIZ "=%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
#define __NR32ATRA4_pwritevf(fd, iovec, count, offset, mode) ,(uintptr_t)(mode),(mode) & IO_WRONLY ? "IO_WRONLY" : (mode) ? "" : "IO_RDONLY" \
                                                             ,((mode) & IO_RDWR) && ((mode) & (IO_WRONLY)) ? "|" : "",(mode) & IO_RDWR ? "IO_RDWR" : "" \
                                                             ,((mode) & IO_CLOEXEC) && ((mode) & (IO_WRONLY|IO_RDWR)) ? "|" : "",(mode) & IO_CLOEXEC ? "IO_CLOEXEC" : "" \
                                                             ,((mode) & IO_CLOFORK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC)) ? "|" : "",(mode) & IO_CLOFORK ? "IO_CLOFORK" : "" \
                                                             ,((mode) & IO_APPEND) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK)) ? "|" : "",(mode) & IO_APPEND ? "IO_APPEND" : "" \
                                                             ,((mode) & IO_NONBLOCK) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND)) ? "|" : "",(mode) & IO_NONBLOCK ? "IO_NONBLOCK" : "" \
                                                             ,((mode) & IO_SYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK)) ? "|" : "",(mode) & IO_SYNC ? "IO_SYNC" : "" \
                                                             ,((mode) & IO_ASYNC) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC)) ? "|" : "",(mode) & IO_ASYNC ? "IO_ASYNC" : "" \
                                                             ,((mode) & IO_DIRECT) && ((mode) & (IO_WRONLY|IO_RDWR|IO_CLOEXEC|IO_CLOFORK|IO_APPEND|IO_NONBLOCK|IO_SYNC|IO_ASYNC)) ? "|" : "",(mode) & IO_DIRECT ? "IO_DIRECT" : ""
#define __NR32ATRF0_recvmmsg64              "%d"
#define __NR32ATRA0_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,(int)(sockfd)
#define __NR32ATRF1_recvmmsg64              "%p"
#define __NR32ATRA1_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,vmessages
#define __NR32ATRF2_recvmmsg64              "%" PRIuSIZ
#define __NR32ATRA2_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,vlen
#define __NR32ATRF3_recvmmsg64              "%#" PRIxSIZ
#define __NR32ATRA3_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,(uintptr_t)(flags)
#define __NR32ATRF4_recvmmsg64              "%p"
#define __NR32ATRA4_recvmmsg64(sockfd, vmessages, vlen, flags, tmo) ,tmo
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT */
#endif /* __WANT_SYSCALL_ARGUMENT_FORMAT */

