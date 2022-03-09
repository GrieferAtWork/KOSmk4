/* HASH CRC-32:0xf3fbd1f7 */
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
/* SYSCALL ARGUMENT NAMES                                               */
/*  - __NR32AN<argI>_<name> : ArgumentName                              */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_NAMES
#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#define __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES
#define __NR32AN0_exit                         exit_code
#define __NR32AN0_read                         fd
#define __NR32AN1_read                         buf
#define __NR32AN2_read                         bufsize
#define __NR32AN0_write                        fd
#define __NR32AN1_write                        buf
#define __NR32AN2_write                        bufsize
#define __NR32AN0_open                         filename
#define __NR32AN1_open                         oflags
#define __NR32AN2_open                         mode
#define __NR32AN0_close                        fd
#define __NR32AN0_waitpid                      pid
#define __NR32AN1_waitpid                      stat_loc
#define __NR32AN2_waitpid                      options
#define __NR32AN0_creat                        filename
#define __NR32AN1_creat                        mode
#define __NR32AN0_link                         existing_file
#define __NR32AN1_link                         link_file
#define __NR32AN0_unlink                       filename
#define __NR32AN0_execve                       path
#define __NR32AN1_execve                       argv
#define __NR32AN2_execve                       envp
#define __NR32AN0_chdir                        path
#define __NR32AN0_time                         timer
#define __NR32AN0_mknod                        nodename
#define __NR32AN1_mknod                        mode
#define __NR32AN2_mknod                        dev
#define __NR32AN0_chmod                        filename
#define __NR32AN1_chmod                        mode
#define __NR32AN0_lchown                       filename
#define __NR32AN1_lchown                       owner
#define __NR32AN2_lchown                       group
#define __NR32AN0_oldstat                      filename
#define __NR32AN1_oldstat                      statbuf
#define __NR32AN0_lseek                        fd
#define __NR32AN1_lseek                        offset
#define __NR32AN2_lseek                        whence
#define __NR32AN0_mount                        special_file
#define __NR32AN1_mount                        dir
#define __NR32AN2_mount                        fstype
#define __NR32AN3_mount                        mountflags
#define __NR32AN4_mount                        data
#define __NR32AN0_umount                       special_file
#define __NR32AN0_setuid                       uid
#define __NR32AN0_stime                        t
#define __NR32AN0_ptrace                       request
#define __NR32AN1_ptrace                       pid
#define __NR32AN2_ptrace                       addr
#define __NR32AN3_ptrace                       data
#define __NR32AN0_alarm                        seconds
#define __NR32AN0_oldfstat                     fd
#define __NR32AN1_oldfstat                     statbuf
#define __NR32AN0_utime                        filename
#define __NR32AN1_utime                        times
#define __NR32AN0_access                       filename
#define __NR32AN1_access                       type
#define __NR32AN0_nice                         inc
#define __NR32AN0_ftime                        tp
#define __NR32AN0_kill                         pid
#define __NR32AN1_kill                         signo
#define __NR32AN0_rename                       oldname
#define __NR32AN1_rename                       newname_or_path
#define __NR32AN0_mkdir                        pathname
#define __NR32AN1_mkdir                        mode
#define __NR32AN0_rmdir                        path
#define __NR32AN0_dup                          fd
#define __NR32AN0_pipe                         pipedes
#define __NR32AN0_times                        buf
#define __NR32AN0_brk                          addr
#define __NR32AN0_setgid                       gid
#define __NR32AN0_signal                       signo
#define __NR32AN1_signal                       handler
#define __NR32AN0_acct                         filename
#define __NR32AN0_umount2                      special_file
#define __NR32AN1_umount2                      flags
#define __NR32AN0_ioctl                        fd
#define __NR32AN1_ioctl                        command
#define __NR32AN2_ioctl                        arg
#define __NR32AN0_fcntl                        fd
#define __NR32AN1_fcntl                        command
#define __NR32AN2_fcntl                        arg
#define __NR32AN0_setpgid                      pid
#define __NR32AN1_setpgid                      pgid
#define __NR32AN0_oldolduname                  name
#define __NR32AN0_umask                        mode
#define __NR32AN0_chroot                       path
#define __NR32AN0_ustat                        dev
#define __NR32AN1_ustat                        ubuf
#define __NR32AN0_dup2                         oldfd
#define __NR32AN1_dup2                         newfd
#define __NR32AN0_sigaction                    signo
#define __NR32AN1_sigaction                    act
#define __NR32AN2_sigaction                    oact
#define __NR32AN0_ssetmask                     sigmask
#define __NR32AN0_setreuid                     ruid
#define __NR32AN1_setreuid                     euid
#define __NR32AN0_setregid                     rgid
#define __NR32AN1_setregid                     egid
#define __NR32AN0_sigsuspend                   set
#define __NR32AN0_sigpending                   set
#define __NR32AN0_sethostname                  name
#define __NR32AN1_sethostname                  len
#define __NR32AN0_setrlimit                    resource
#define __NR32AN1_setrlimit                    rlimits
#define __NR32AN0_getrlimit                    resource
#define __NR32AN1_getrlimit                    rlimits
#define __NR32AN0_getrusage                    who
#define __NR32AN1_getrusage                    tv
#define __NR32AN0_gettimeofday                 tv
#define __NR32AN1_gettimeofday                 tz
#define __NR32AN0_settimeofday                 tv
#define __NR32AN1_settimeofday                 tz
#define __NR32AN0_getgroups                    count
#define __NR32AN1_getgroups                    list
#define __NR32AN0_setgroups                    count
#define __NR32AN1_setgroups                    groups
#define __NR32AN0_select                       arg
#define __NR32AN0_symlink                      link_text
#define __NR32AN1_symlink                      target_path
#define __NR32AN0_oldlstat                     filename
#define __NR32AN1_oldlstat                     statbuf
#define __NR32AN0_readlink                     path
#define __NR32AN1_readlink                     buf
#define __NR32AN2_readlink                     buflen
#define __NR32AN0_uselib                       library
#define __NR32AN0_swapon                       pathname
#define __NR32AN1_swapon                       swapflags
#define __NR32AN0_reboot                       how
#define __NR32AN0_readdir                      fd
#define __NR32AN1_readdir                      buf
#define __NR32AN0_mmap                         addr
#define __NR32AN1_mmap                         len
#define __NR32AN2_mmap                         prot
#define __NR32AN3_mmap                         flags
#define __NR32AN4_mmap                         fd
#define __NR32AN5_mmap                         offset
#define __NR32AN0_munmap                       addr
#define __NR32AN1_munmap                       len
#define __NR32AN0_truncate                     filename
#define __NR32AN1_truncate                     length
#define __NR32AN0_ftruncate                    fd
#define __NR32AN1_ftruncate                    length
#define __NR32AN0_fchmod                       fd
#define __NR32AN1_fchmod                       mode
#define __NR32AN0_fchown                       fd
#define __NR32AN1_fchown                       owner
#define __NR32AN2_fchown                       group
#define __NR32AN0_getpriority                  which
#define __NR32AN1_getpriority                  who
#define __NR32AN0_setpriority                  which
#define __NR32AN1_setpriority                  who
#define __NR32AN2_setpriority                  value
#define __NR32AN0_statfs                       file
#define __NR32AN1_statfs                       buf
#define __NR32AN0_fstatfs                      file
#define __NR32AN1_fstatfs                      buf
#define __NR32AN0_ioperm                       from
#define __NR32AN1_ioperm                       num
#define __NR32AN2_ioperm                       turn_on
#define __NR32AN0_socketcall                   call
#define __NR32AN1_socketcall                   args
#define __NR32AN0_syslog                       level
#define __NR32AN1_syslog                       str
#define __NR32AN2_syslog                       len
#define __NR32AN0_setitimer                    which
#define __NR32AN1_setitimer                    newval
#define __NR32AN2_setitimer                    oldval
#define __NR32AN0_getitimer                    which
#define __NR32AN1_getitimer                    curr_value
#define __NR32AN0_stat                         filename
#define __NR32AN1_stat                         statbuf
#define __NR32AN0_lstat                        filename
#define __NR32AN1_lstat                        statbuf
#define __NR32AN0_fstat                        fd
#define __NR32AN1_fstat                        statbuf
#define __NR32AN0_olduname                     name
#define __NR32AN0_iopl                         level
#define __NR32AN0_vm86old                      TODO_PROTOTYPE
#define __NR32AN0_wait4                        pid
#define __NR32AN1_wait4                        stat_loc
#define __NR32AN2_wait4                        options
#define __NR32AN3_wait4                        usage
#define __NR32AN0_swapoff                      pathname
#define __NR32AN0_sysinfo                      info
#define __NR32AN0_ipc                          TODO_PROTOTYPE
#define __NR32AN0_fsync                        fd
#define __NR32AN0_clone                        flags
#define __NR32AN1_clone                        child_stack
#define __NR32AN2_clone                        ptid
#define __NR32AN3_clone                        newtls
#define __NR32AN4_clone                        ctid
#define __NR32AN0_setdomainname                name
#define __NR32AN1_setdomainname                len
#define __NR32AN0_uname                        name
#define __NR32AN0_modify_ldt                   func
#define __NR32AN1_modify_ldt                   ptr
#define __NR32AN2_modify_ldt                   bytecount
#define __NR32AN0_adjtimex                     ntx
#define __NR32AN0_mprotect                     addr
#define __NR32AN1_mprotect                     len
#define __NR32AN2_mprotect                     prot
#define __NR32AN0_sigprocmask                  how
#define __NR32AN1_sigprocmask                  set
#define __NR32AN2_sigprocmask                  oset
#define __NR32AN0_init_module                  module_image
#define __NR32AN1_init_module                  len
#define __NR32AN2_init_module                  uargs
#define __NR32AN0_delete_module                name
#define __NR32AN1_delete_module                flags
#define __NR32AN0_quotactl                     TODO_PROTOTYPE
#define __NR32AN0_getpgid                      pid
#define __NR32AN0_fchdir                       fd
#define __NR32AN0_bdflush                      TODO_PROTOTYPE
#define __NR32AN0_sysfs                        TODO_PROTOTYPE
#define __NR32AN0_personality                  TODO_PROTOTYPE
#define __NR32AN0_setfsuid                     uid
#define __NR32AN0_setfsgid                     gid
#define __NR32AN0__llseek                      fd
#define __NR32AN1__llseek                      offset
#define __NR32AN2__llseek                      result
#define __NR32AN3__llseek                      whence
#define __NR32AN0_getdents                     fd
#define __NR32AN1_getdents                     buf
#define __NR32AN2_getdents                     buflen
#define __NR32AN0__newselect                   nfds
#define __NR32AN1__newselect                   readfds
#define __NR32AN2__newselect                   writefds
#define __NR32AN3__newselect                   exceptfds
#define __NR32AN4__newselect                   timeout
#define __NR32AN0_flock                        fd
#define __NR32AN1_flock                        operation
#define __NR32AN0_msync                        addr
#define __NR32AN1_msync                        len
#define __NR32AN2_msync                        flags
#define __NR32AN0_readv                        fd
#define __NR32AN1_readv                        iovec
#define __NR32AN2_readv                        count
#define __NR32AN0_writev                       fd
#define __NR32AN1_writev                       iovec
#define __NR32AN2_writev                       count
#define __NR32AN0_getsid                       pid
#define __NR32AN0_fdatasync                    fd
#define __NR32AN0__sysctl                      TODO_PROTOTYPE
#define __NR32AN0_mlock                        addr
#define __NR32AN1_mlock                        len
#define __NR32AN0_munlock                      addr
#define __NR32AN1_munlock                      len
#define __NR32AN0_mlockall                     flags
#define __NR32AN0_sched_setparam               pid
#define __NR32AN1_sched_setparam               param
#define __NR32AN0_sched_getparam               pid
#define __NR32AN1_sched_getparam               param
#define __NR32AN0_sched_setscheduler           pid
#define __NR32AN1_sched_setscheduler           policy
#define __NR32AN2_sched_setscheduler           param
#define __NR32AN0_sched_getscheduler           pid
#define __NR32AN0_sched_get_priority_max       algorithm
#define __NR32AN0_sched_get_priority_min       algorithm
#define __NR32AN0_sched_rr_get_interval        pid
#define __NR32AN1_sched_rr_get_interval        ts
#define __NR32AN0_nanosleep                    req
#define __NR32AN1_nanosleep                    rem
#define __NR32AN0_mremap                       addr
#define __NR32AN1_mremap                       old_len
#define __NR32AN2_mremap                       new_len
#define __NR32AN3_mremap                       flags
#define __NR32AN4_mremap                       new_address
#define __NR32AN0_setresuid                    ruid
#define __NR32AN1_setresuid                    euid
#define __NR32AN2_setresuid                    suid
#define __NR32AN0_getresuid                    ruid
#define __NR32AN1_getresuid                    euid
#define __NR32AN2_getresuid                    suid
#define __NR32AN0_vm86                         TODO_PROTOTYPE
#define __NR32AN0_poll                         fds
#define __NR32AN1_poll                         nfds
#define __NR32AN2_poll                         timeout
#define __NR32AN0_nfsservctl                   TODO_PROTOTYPE
#define __NR32AN0_setresgid                    rgid
#define __NR32AN1_setresgid                    egid
#define __NR32AN2_setresgid                    sgid
#define __NR32AN0_getresgid                    rgid
#define __NR32AN1_getresgid                    egid
#define __NR32AN2_getresgid                    sgid
#define __NR32AN0_prctl                        command
#define __NR32AN1_prctl                        arg2
#define __NR32AN2_prctl                        arg3
#define __NR32AN3_prctl                        arg4
#define __NR32AN4_prctl                        arg5
#define __NR32AN0_rt_sigaction                 signo
#define __NR32AN1_rt_sigaction                 act
#define __NR32AN2_rt_sigaction                 oact
#define __NR32AN3_rt_sigaction                 sigsetsize
#define __NR32AN0_rt_sigprocmask               how
#define __NR32AN1_rt_sigprocmask               set
#define __NR32AN2_rt_sigprocmask               oset
#define __NR32AN3_rt_sigprocmask               sigsetsize
#define __NR32AN0_rt_sigpending                set
#define __NR32AN1_rt_sigpending                sigsetsize
#define __NR32AN0_rt_sigtimedwait              set
#define __NR32AN1_rt_sigtimedwait              info
#define __NR32AN2_rt_sigtimedwait              timeout
#define __NR32AN3_rt_sigtimedwait              sigsetsize
#define __NR32AN0_rt_sigqueueinfo              pid
#define __NR32AN1_rt_sigqueueinfo              usigno
#define __NR32AN2_rt_sigqueueinfo              uinfo
#define __NR32AN0_rt_sigsuspend                set
#define __NR32AN1_rt_sigsuspend                sigsetsize
#define __NR32AN0_pread64                      fd
#define __NR32AN1_pread64                      buf
#define __NR32AN2_pread64                      bufsize
#define __NR32AN3_pread64                      offset
#define __NR32AN0_pwrite64                     fd
#define __NR32AN1_pwrite64                     buf
#define __NR32AN2_pwrite64                     bufsize
#define __NR32AN3_pwrite64                     offset
#define __NR32AN0_chown                        filename
#define __NR32AN1_chown                        owner
#define __NR32AN2_chown                        group
#define __NR32AN0_getcwd                       buf
#define __NR32AN1_getcwd                       size
#define __NR32AN0_capget                       TODO_PROTOTYPE
#define __NR32AN0_capset                       TODO_PROTOTYPE
#define __NR32AN0_sigaltstack                  ss
#define __NR32AN1_sigaltstack                  oss
#define __NR32AN0_sendfile                     outfd
#define __NR32AN1_sendfile                     infd
#define __NR32AN2_sendfile                     pin_offset
#define __NR32AN3_sendfile                     num_bytes
#define __NR32AN0_ugetrlimit                   TODO_PROTOTYPE
#define __NR32AN0_mmap2                        addr
#define __NR32AN1_mmap2                        len
#define __NR32AN2_mmap2                        prot
#define __NR32AN3_mmap2                        flags
#define __NR32AN4_mmap2                        fd
#define __NR32AN5_mmap2                        pgoffset
#define __NR32AN0_truncate64                   filename
#define __NR32AN1_truncate64                   length
#define __NR32AN0_ftruncate64                  fd
#define __NR32AN1_ftruncate64                  length
#define __NR32AN0_stat64                       filename
#define __NR32AN1_stat64                       statbuf
#define __NR32AN0_lstat64                      filename
#define __NR32AN1_lstat64                      statbuf
#define __NR32AN0_fstat64                      fd
#define __NR32AN1_fstat64                      statbuf
#define __NR32AN0_lchown32                     filename
#define __NR32AN1_lchown32                     owner
#define __NR32AN2_lchown32                     group
#define __NR32AN0_setreuid32                   ruid
#define __NR32AN1_setreuid32                   euid
#define __NR32AN0_setregid32                   rgid
#define __NR32AN1_setregid32                   egid
#define __NR32AN0_getgroups32                  count
#define __NR32AN1_getgroups32                  list
#define __NR32AN0_setgroups32                  count
#define __NR32AN1_setgroups32                  groups
#define __NR32AN0_fchown32                     fd
#define __NR32AN1_fchown32                     owner
#define __NR32AN2_fchown32                     group
#define __NR32AN0_setresuid32                  ruid
#define __NR32AN1_setresuid32                  euid
#define __NR32AN2_setresuid32                  suid
#define __NR32AN0_getresuid32                  ruid
#define __NR32AN1_getresuid32                  euid
#define __NR32AN2_getresuid32                  suid
#define __NR32AN0_setresgid32                  rgid
#define __NR32AN1_setresgid32                  egid
#define __NR32AN2_setresgid32                  sgid
#define __NR32AN0_getresgid32                  rgid
#define __NR32AN1_getresgid32                  egid
#define __NR32AN2_getresgid32                  sgid
#define __NR32AN0_chown32                      filename
#define __NR32AN1_chown32                      owner
#define __NR32AN2_chown32                      group
#define __NR32AN0_setuid32                     uid
#define __NR32AN0_setgid32                     gid
#define __NR32AN0_setfsuid32                   uid
#define __NR32AN0_setfsgid32                   gid
#define __NR32AN0_pivot_root                   TODO_PROTOTYPE
#define __NR32AN0_mincore                      start
#define __NR32AN1_mincore                      len
#define __NR32AN2_mincore                      vec
#define __NR32AN0_madvise                      addr
#define __NR32AN1_madvise                      len
#define __NR32AN2_madvise                      advice
#define __NR32AN0_getdents64                   fd
#define __NR32AN1_getdents64                   buf
#define __NR32AN2_getdents64                   buflen
#define __NR32AN0_fcntl64                      fd
#define __NR32AN1_fcntl64                      command
#define __NR32AN2_fcntl64                      arg
#define __NR32AN0_readahead                    fd
#define __NR32AN1_readahead                    offset
#define __NR32AN2_readahead                    count
#define __NR32AN0_setxattr                     path
#define __NR32AN1_setxattr                     name
#define __NR32AN2_setxattr                     buf
#define __NR32AN3_setxattr                     bufsize
#define __NR32AN4_setxattr                     flags
#define __NR32AN0_lsetxattr                    path
#define __NR32AN1_lsetxattr                    name
#define __NR32AN2_lsetxattr                    buf
#define __NR32AN3_lsetxattr                    bufsize
#define __NR32AN4_lsetxattr                    flags
#define __NR32AN0_fsetxattr                    fd
#define __NR32AN1_fsetxattr                    name
#define __NR32AN2_fsetxattr                    buf
#define __NR32AN3_fsetxattr                    bufsize
#define __NR32AN4_fsetxattr                    flags
#define __NR32AN0_getxattr                     path
#define __NR32AN1_getxattr                     name
#define __NR32AN2_getxattr                     buf
#define __NR32AN3_getxattr                     bufsize
#define __NR32AN0_lgetxattr                    path
#define __NR32AN1_lgetxattr                    name
#define __NR32AN2_lgetxattr                    buf
#define __NR32AN3_lgetxattr                    bufsize
#define __NR32AN0_fgetxattr                    fd
#define __NR32AN1_fgetxattr                    name
#define __NR32AN2_fgetxattr                    buf
#define __NR32AN3_fgetxattr                    bufsize
#define __NR32AN0_listxattr                    path
#define __NR32AN1_listxattr                    listbuf
#define __NR32AN2_listxattr                    listbufsize
#define __NR32AN0_llistxattr                   path
#define __NR32AN1_llistxattr                   listbuf
#define __NR32AN2_llistxattr                   listbufsize
#define __NR32AN0_flistxattr                   fd
#define __NR32AN1_flistxattr                   listbuf
#define __NR32AN2_flistxattr                   listbufsize
#define __NR32AN0_removexattr                  path
#define __NR32AN1_removexattr                  name
#define __NR32AN0_lremovexattr                 path
#define __NR32AN1_lremovexattr                 name
#define __NR32AN0_fremovexattr                 fd
#define __NR32AN1_fremovexattr                 name
#define __NR32AN0_tkill                        tid
#define __NR32AN1_tkill                        signo
#define __NR32AN0_sendfile64                   outfd
#define __NR32AN1_sendfile64                   infd
#define __NR32AN2_sendfile64                   pin_offset
#define __NR32AN3_sendfile64                   num_bytes
#define __NR32AN0_futex                        uaddr
#define __NR32AN1_futex                        futex_op
#define __NR32AN2_futex                        val
#define __NR32AN3_futex                        timeout_or_val2
#define __NR32AN4_futex                        uaddr2
#define __NR32AN5_futex                        val3
#define __NR32AN0_sched_setaffinity            pid
#define __NR32AN1_sched_setaffinity            cpusetsize
#define __NR32AN2_sched_setaffinity            cpuset
#define __NR32AN0_sched_getaffinity            pid
#define __NR32AN1_sched_getaffinity            cpusetsize
#define __NR32AN2_sched_getaffinity            cpuset
#define __NR32AN0_set_thread_area              TODO_PROTOTYPE
#define __NR32AN0_get_thread_area              TODO_PROTOTYPE
#define __NR32AN0_io_setup                     TODO_PROTOTYPE
#define __NR32AN0_io_destroy                   TODO_PROTOTYPE
#define __NR32AN0_io_getevents                 TODO_PROTOTYPE
#define __NR32AN0_io_submit                    TODO_PROTOTYPE
#define __NR32AN0_io_cancel                    TODO_PROTOTYPE
#define __NR32AN0_fadvise64                    TODO_PROTOTYPE
#define __NR32AN0_exit_group                   exit_code
#define __NR32AN0_lookup_dcookie               TODO_PROTOTYPE
#define __NR32AN0_epoll_create                 size
#define __NR32AN0_epoll_ctl                    epfd
#define __NR32AN1_epoll_ctl                    op
#define __NR32AN2_epoll_ctl                    fd
#define __NR32AN3_epoll_ctl                    info
#define __NR32AN0_epoll_wait                   epfd
#define __NR32AN1_epoll_wait                   events
#define __NR32AN2_epoll_wait                   maxevents
#define __NR32AN3_epoll_wait                   timeout
#define __NR32AN0_remap_file_pages             start
#define __NR32AN1_remap_file_pages             size
#define __NR32AN2_remap_file_pages             prot
#define __NR32AN3_remap_file_pages             pgoff
#define __NR32AN4_remap_file_pages             flags
#define __NR32AN0_set_tid_address              tidptr
#define __NR32AN0_timer_create                 clock_id
#define __NR32AN1_timer_create                 evp
#define __NR32AN2_timer_create                 timerid
#define __NR32AN0_timer_settime                timerid
#define __NR32AN1_timer_settime                flags
#define __NR32AN2_timer_settime                value
#define __NR32AN3_timer_settime                ovalue
#define __NR32AN0_timer_gettime                timerid
#define __NR32AN1_timer_gettime                value
#define __NR32AN0_timer_getoverrun             timerid
#define __NR32AN0_timer_delete                 timerid
#define __NR32AN0_clock_settime                clock_id
#define __NR32AN1_clock_settime                tp
#define __NR32AN0_clock_gettime                clock_id
#define __NR32AN1_clock_gettime                tp
#define __NR32AN0_clock_getres                 clock_id
#define __NR32AN1_clock_getres                 res
#define __NR32AN0_clock_nanosleep              clock_id
#define __NR32AN1_clock_nanosleep              flags
#define __NR32AN2_clock_nanosleep              requested_time
#define __NR32AN3_clock_nanosleep              remaining
#define __NR32AN0_statfs64                     file
#define __NR32AN1_statfs64                     buf
#define __NR32AN0_fstatfs64                    file
#define __NR32AN1_fstatfs64                    buf
#define __NR32AN0_tgkill                       pid
#define __NR32AN1_tgkill                       tid
#define __NR32AN2_tgkill                       signo
#define __NR32AN0_utimes                       filename
#define __NR32AN1_utimes                       times
#define __NR32AN0_fadvise64_64                 TODO_PROTOTYPE
#define __NR32AN0_mbind                        TODO_PROTOTYPE
#define __NR32AN0_get_mempolicy                TODO_PROTOTYPE
#define __NR32AN0_set_mempolicy                TODO_PROTOTYPE
#define __NR32AN0_mq_open                      name
#define __NR32AN1_mq_open                      oflags
#define __NR32AN2_mq_open                      mode
#define __NR32AN0_mq_unlink                    name
#define __NR32AN0_mq_timedsend                 mqdes
#define __NR32AN1_mq_timedsend                 msg_ptr
#define __NR32AN2_mq_timedsend                 msg_len
#define __NR32AN3_mq_timedsend                 msg_prio
#define __NR32AN4_mq_timedsend                 abs_timeout
#define __NR32AN0_mq_timedreceive              mqdes
#define __NR32AN1_mq_timedreceive              msg_ptr
#define __NR32AN2_mq_timedreceive              msg_len
#define __NR32AN3_mq_timedreceive              pmsg_prio
#define __NR32AN4_mq_timedreceive              abs_timeout
#define __NR32AN0_mq_notify                    mqdes
#define __NR32AN1_mq_notify                    notification
#define __NR32AN0_mq_getsetattr                mqdes
#define __NR32AN1_mq_getsetattr                newattr
#define __NR32AN2_mq_getsetattr                oldattr
#define __NR32AN0_kexec_load                   TODO_PROTOTYPE
#define __NR32AN0_waitid                       idtype
#define __NR32AN1_waitid                       id
#define __NR32AN2_waitid                       infop
#define __NR32AN3_waitid                       options
#define __NR32AN4_waitid                       ru
#define __NR32AN0_add_key                      TODO_PROTOTYPE
#define __NR32AN0_request_key                  TODO_PROTOTYPE
#define __NR32AN0_keyctl                       TODO_PROTOTYPE
#define __NR32AN0_ioprio_set                   who
#define __NR32AN1_ioprio_set                   id
#define __NR32AN2_ioprio_set                   ioprio
#define __NR32AN0_ioprio_get                   who
#define __NR32AN1_ioprio_get                   id
#define __NR32AN0_inotify_init                 TODO_PROTOTYPE
#define __NR32AN0_inotify_add_watch            TODO_PROTOTYPE
#define __NR32AN0_inotify_rm_watch             TODO_PROTOTYPE
#define __NR32AN0_migrate_pages                TODO_PROTOTYPE
#define __NR32AN0_openat                       dirfd
#define __NR32AN1_openat                       filename
#define __NR32AN2_openat                       oflags
#define __NR32AN3_openat                       mode
#define __NR32AN0_mkdirat                      dirfd
#define __NR32AN1_mkdirat                      pathname
#define __NR32AN2_mkdirat                      mode
#define __NR32AN0_mknodat                      dirfd
#define __NR32AN1_mknodat                      nodename
#define __NR32AN2_mknodat                      mode
#define __NR32AN3_mknodat                      dev
#define __NR32AN0_fchownat                     dirfd
#define __NR32AN1_fchownat                     filename
#define __NR32AN2_fchownat                     owner
#define __NR32AN3_fchownat                     group
#define __NR32AN4_fchownat                     flags
#define __NR32AN0_futimesat                    dirfd
#define __NR32AN1_futimesat                    filename
#define __NR32AN2_futimesat                    times
#define __NR32AN0_fstatat64                    dirfd
#define __NR32AN1_fstatat64                    filename
#define __NR32AN2_fstatat64                    statbuf
#define __NR32AN3_fstatat64                    flags
#define __NR32AN0_unlinkat                     dirfd
#define __NR32AN1_unlinkat                     name
#define __NR32AN2_unlinkat                     flags
#define __NR32AN0_renameat                     oldfd
#define __NR32AN1_renameat                     oldname
#define __NR32AN2_renameat                     newfd
#define __NR32AN3_renameat                     newname_or_path
#define __NR32AN0_linkat                       fromfd
#define __NR32AN1_linkat                       existing_file
#define __NR32AN2_linkat                       tofd
#define __NR32AN3_linkat                       target_path
#define __NR32AN4_linkat                       flags
#define __NR32AN0_symlinkat                    link_text
#define __NR32AN1_symlinkat                    tofd
#define __NR32AN2_symlinkat                    target_path
#define __NR32AN0_readlinkat                   dirfd
#define __NR32AN1_readlinkat                   path
#define __NR32AN2_readlinkat                   buf
#define __NR32AN3_readlinkat                   buflen
#define __NR32AN0_fchmodat                     dirfd
#define __NR32AN1_fchmodat                     filename
#define __NR32AN2_fchmodat                     mode
#define __NR32AN3_fchmodat                     flags
#define __NR32AN0_faccessat                    dirfd
#define __NR32AN1_faccessat                    filename
#define __NR32AN2_faccessat                    type
#define __NR32AN0_pselect6                     nfds
#define __NR32AN1_pselect6                     readfds
#define __NR32AN2_pselect6                     writefds
#define __NR32AN3_pselect6                     exceptfds
#define __NR32AN4_pselect6                     timeout
#define __NR32AN5_pselect6                     sigmask_sigset_with_size
#define __NR32AN0_ppoll                        fds
#define __NR32AN1_ppoll                        nfds
#define __NR32AN2_ppoll                        timeout_ts
#define __NR32AN3_ppoll                        sigmask
#define __NR32AN4_ppoll                        sigsetsize
#define __NR32AN0_unshare                      what
#define __NR32AN0_set_robust_list              TODO_PROTOTYPE
#define __NR32AN0_get_robust_list              TODO_PROTOTYPE
#define __NR32AN0_splice                       fdin
#define __NR32AN1_splice                       offin
#define __NR32AN2_splice                       fdout
#define __NR32AN3_splice                       offout
#define __NR32AN4_splice                       length
#define __NR32AN5_splice                       flags
#define __NR32AN0_sync_file_range              fd
#define __NR32AN1_sync_file_range              offset
#define __NR32AN2_sync_file_range              count
#define __NR32AN3_sync_file_range              flags
#define __NR32AN0_tee                          fdin
#define __NR32AN1_tee                          fdout
#define __NR32AN2_tee                          length
#define __NR32AN3_tee                          flags
#define __NR32AN0_vmsplice                     fdout
#define __NR32AN1_vmsplice                     iov
#define __NR32AN2_vmsplice                     count
#define __NR32AN3_vmsplice                     flags
#define __NR32AN0_move_pages                   TODO_PROTOTYPE
#define __NR32AN0_getcpu                       cpu
#define __NR32AN1_getcpu                       node
#define __NR32AN2_getcpu                       tcache
#define __NR32AN0_epoll_pwait                  epfd
#define __NR32AN1_epoll_pwait                  events
#define __NR32AN2_epoll_pwait                  maxevents
#define __NR32AN3_epoll_pwait                  timeout
#define __NR32AN4_epoll_pwait                  ss
#define __NR32AN5_epoll_pwait                  sigsetsize
#define __NR32AN0_utimensat                    dirfd
#define __NR32AN1_utimensat                    filename
#define __NR32AN2_utimensat                    times
#define __NR32AN3_utimensat                    flags
#define __NR32AN0_signalfd                     fd
#define __NR32AN1_signalfd                     sigmask
#define __NR32AN2_signalfd                     sigmasksize
#define __NR32AN0_timerfd_create               clock_id
#define __NR32AN1_timerfd_create               flags
#define __NR32AN0_eventfd                      initval
#define __NR32AN0_fallocate                    fd
#define __NR32AN1_fallocate                    mode
#define __NR32AN2_fallocate                    offset
#define __NR32AN3_fallocate                    length
#define __NR32AN0_timerfd_settime              timerfd
#define __NR32AN1_timerfd_settime              flags
#define __NR32AN2_timerfd_settime              utmr
#define __NR32AN3_timerfd_settime              otmr
#define __NR32AN0_timerfd_gettime              timerfd
#define __NR32AN1_timerfd_gettime              otmr
#define __NR32AN0_signalfd4                    fd
#define __NR32AN1_signalfd4                    sigmask
#define __NR32AN2_signalfd4                    sigmasksize
#define __NR32AN3_signalfd4                    flags
#define __NR32AN0_eventfd2                     initval
#define __NR32AN1_eventfd2                     flags
#define __NR32AN0_epoll_create1                flags
#define __NR32AN0_dup3                         oldfd
#define __NR32AN1_dup3                         newfd
#define __NR32AN2_dup3                         flags
#define __NR32AN0_pipe2                        pipedes
#define __NR32AN1_pipe2                        flags
#define __NR32AN0_inotify_init1                TODO_PROTOTYPE
#define __NR32AN0_preadv                       fd
#define __NR32AN1_preadv                       iovec
#define __NR32AN2_preadv                       count
#define __NR32AN3_preadv                       offset
#define __NR32AN0_pwritev                      fd
#define __NR32AN1_pwritev                      iovec
#define __NR32AN2_pwritev                      count
#define __NR32AN3_pwritev                      offset
#define __NR32AN0_rt_tgsigqueueinfo            pid
#define __NR32AN1_rt_tgsigqueueinfo            tid
#define __NR32AN2_rt_tgsigqueueinfo            usigno
#define __NR32AN3_rt_tgsigqueueinfo            uinfo
#define __NR32AN0_perf_event_open              TODO_PROTOTYPE
#define __NR32AN0_recvmmsg                     sockfd
#define __NR32AN1_recvmmsg                     vmessages
#define __NR32AN2_recvmmsg                     vlen
#define __NR32AN3_recvmmsg                     msg_flags
#define __NR32AN4_recvmmsg                     tmo
#define __NR32AN0_fanotify_init                TODO_PROTOTYPE
#define __NR32AN0_fanotify_mark                TODO_PROTOTYPE
#define __NR32AN0_prlimit64                    pid
#define __NR32AN1_prlimit64                    resource
#define __NR32AN2_prlimit64                    new_limit
#define __NR32AN3_prlimit64                    old_limit
#define __NR32AN0_name_to_handle_at            dirfd
#define __NR32AN1_name_to_handle_at            filename
#define __NR32AN2_name_to_handle_at            handle
#define __NR32AN3_name_to_handle_at            mnt_id
#define __NR32AN4_name_to_handle_at            flags
#define __NR32AN0_open_by_handle_at            mountdirfd
#define __NR32AN1_open_by_handle_at            handle
#define __NR32AN2_open_by_handle_at            flags
#define __NR32AN0_clock_adjtime                TODO_PROTOTYPE
#define __NR32AN0_syncfs                       fd
#define __NR32AN0_sendmmsg                     sockfd
#define __NR32AN1_sendmmsg                     vmessages
#define __NR32AN2_sendmmsg                     vlen
#define __NR32AN3_sendmmsg                     msg_flags
#define __NR32AN0_setns                        fd
#define __NR32AN1_setns                        nstype
#define __NR32AN0_process_vm_readv             pid
#define __NR32AN1_process_vm_readv             local_iov
#define __NR32AN2_process_vm_readv             liovcnt
#define __NR32AN3_process_vm_readv             remote_iov
#define __NR32AN4_process_vm_readv             riovcnt
#define __NR32AN5_process_vm_readv             flags
#define __NR32AN0_process_vm_writev            pid
#define __NR32AN1_process_vm_writev            local_iov
#define __NR32AN2_process_vm_writev            liovcnt
#define __NR32AN3_process_vm_writev            remote_iov
#define __NR32AN4_process_vm_writev            riovcnt
#define __NR32AN5_process_vm_writev            flags
#define __NR32AN0_kcmp                         pid1
#define __NR32AN1_kcmp                         pid2
#define __NR32AN2_kcmp                         type
#define __NR32AN3_kcmp                         idx1
#define __NR32AN4_kcmp                         idx2
#define __NR32AN0_finit_module                 fd
#define __NR32AN1_finit_module                 uargs
#define __NR32AN2_finit_module                 flags
#define __NR32AN0_sched_setattr                TODO_PROTOTYPE
#define __NR32AN0_sched_getattr                TODO_PROTOTYPE
#define __NR32AN0_renameat2                    olddirfd
#define __NR32AN1_renameat2                    oldpath
#define __NR32AN2_renameat2                    newdirfd
#define __NR32AN3_renameat2                    newpath
#define __NR32AN4_renameat2                    flags
#define __NR32AN0_seccomp                      TODO_PROTOTYPE
#define __NR32AN0_getrandom                    buf
#define __NR32AN1_getrandom                    num_bytes
#define __NR32AN2_getrandom                    flags
#define __NR32AN0_memfd_create                 name
#define __NR32AN1_memfd_create                 flags
#define __NR32AN0_bpf                          TODO_PROTOTYPE
#define __NR32AN0_execveat                     dirfd
#define __NR32AN1_execveat                     pathname
#define __NR32AN2_execveat                     argv
#define __NR32AN3_execveat                     envp
#define __NR32AN4_execveat                     flags
#define __NR32AN0_socket                       domain
#define __NR32AN1_socket                       type
#define __NR32AN2_socket                       protocol
#define __NR32AN0_socketpair                   domain
#define __NR32AN1_socketpair                   type
#define __NR32AN2_socketpair                   protocol
#define __NR32AN3_socketpair                   fds
#define __NR32AN0_bind                         sockfd
#define __NR32AN1_bind                         addr
#define __NR32AN2_bind                         addr_len
#define __NR32AN0_connect                      sockfd
#define __NR32AN1_connect                      addr
#define __NR32AN2_connect                      addr_len
#define __NR32AN0_listen                       sockfd
#define __NR32AN1_listen                       max_backlog
#define __NR32AN0_accept4                      sockfd
#define __NR32AN1_accept4                      addr
#define __NR32AN2_accept4                      addr_len
#define __NR32AN3_accept4                      sock_flags
#define __NR32AN0_getsockopt                   sockfd
#define __NR32AN1_getsockopt                   level
#define __NR32AN2_getsockopt                   optname
#define __NR32AN3_getsockopt                   optval
#define __NR32AN4_getsockopt                   optlen
#define __NR32AN0_setsockopt                   sockfd
#define __NR32AN1_setsockopt                   level
#define __NR32AN2_setsockopt                   optname
#define __NR32AN3_setsockopt                   optval
#define __NR32AN4_setsockopt                   optlen
#define __NR32AN0_getsockname                  sockfd
#define __NR32AN1_getsockname                  addr
#define __NR32AN2_getsockname                  addr_len
#define __NR32AN0_getpeername                  sockfd
#define __NR32AN1_getpeername                  addr
#define __NR32AN2_getpeername                  addr_len
#define __NR32AN0_sendto                       sockfd
#define __NR32AN1_sendto                       buf
#define __NR32AN2_sendto                       bufsize
#define __NR32AN3_sendto                       msg_flags
#define __NR32AN4_sendto                       addr
#define __NR32AN5_sendto                       addr_len
#define __NR32AN0_sendmsg                      sockfd
#define __NR32AN1_sendmsg                      message
#define __NR32AN2_sendmsg                      msg_flags
#define __NR32AN0_recvfrom                     sockfd
#define __NR32AN1_recvfrom                     buf
#define __NR32AN2_recvfrom                     bufsize
#define __NR32AN3_recvfrom                     msg_flags
#define __NR32AN4_recvfrom                     addr
#define __NR32AN5_recvfrom                     addr_len
#define __NR32AN0_recvmsg                      sockfd
#define __NR32AN1_recvmsg                      message
#define __NR32AN2_recvmsg                      msg_flags
#define __NR32AN0_shutdown                     sockfd
#define __NR32AN1_shutdown                     how
#define __NR32AN0_userfaultfd                  flags
#define __NR32AN0_membarrier                   TODO_PROTOTYPE
#define __NR32AN0_mlock2                       addr
#define __NR32AN1_mlock2                       length
#define __NR32AN2_mlock2                       flags
#define __NR32AN0_copy_file_range              TODO_PROTOTYPE
#define __NR32AN0_preadv2                      TODO_PROTOTYPE
#define __NR32AN0_pwritev2                     TODO_PROTOTYPE
#define __NR32AN0_pkey_mprotect                addr
#define __NR32AN1_pkey_mprotect                len
#define __NR32AN2_pkey_mprotect                prot
#define __NR32AN3_pkey_mprotect                pkey
#define __NR32AN0_pkey_alloc                   flags
#define __NR32AN1_pkey_alloc                   access_rights
#define __NR32AN0_pkey_free                    key
#define __NR32AN0_statx                        TODO_PROTOTYPE
#define __NR32AN0_arch_prctl                   command
#define __NR32AN1_arch_prctl                   addr
#define __NR32AN0_io_pgetevents                TODO_PROTOTYPE
#define __NR32AN0_rseq                         TODO_PROTOTYPE
#define __NR32AN0_semget                       TODO_PROTOTYPE
#define __NR32AN0_semctl                       TODO_PROTOTYPE
#define __NR32AN0_shmget                       key
#define __NR32AN1_shmget                       size
#define __NR32AN2_shmget                       shmflg
#define __NR32AN0_shmctl                       shmid
#define __NR32AN1_shmctl                       cmd
#define __NR32AN2_shmctl                       buf
#define __NR32AN0_shmat                        shmid
#define __NR32AN1_shmat                        shmaddr
#define __NR32AN2_shmat                        shmflg
#define __NR32AN0_shmdt                        shmaddr
#define __NR32AN0_msgget                       TODO_PROTOTYPE
#define __NR32AN0_msgsnd                       TODO_PROTOTYPE
#define __NR32AN0_msgrcv                       TODO_PROTOTYPE
#define __NR32AN0_msgctl                       TODO_PROTOTYPE
#define __NR32AN0_clock_gettime64              clock_id
#define __NR32AN1_clock_gettime64              tp
#define __NR32AN0_clock_settime64              clock_id
#define __NR32AN1_clock_settime64              tp
#define __NR32AN0_clock_adjtime64              TODO_PROTOTYPE
#define __NR32AN0_clock_getres_time64          clock_id
#define __NR32AN1_clock_getres_time64          res
#define __NR32AN0_clock_nanosleep_time64       clock_id
#define __NR32AN1_clock_nanosleep_time64       flags
#define __NR32AN2_clock_nanosleep_time64       requested_time
#define __NR32AN3_clock_nanosleep_time64       remaining
#define __NR32AN0_timer_gettime64              timerid
#define __NR32AN1_timer_gettime64              value
#define __NR32AN0_timer_settime64              timerid
#define __NR32AN1_timer_settime64              flags
#define __NR32AN2_timer_settime64              value
#define __NR32AN3_timer_settime64              ovalue
#define __NR32AN0_timerfd_gettime64            timerfd
#define __NR32AN1_timerfd_gettime64            otmr
#define __NR32AN0_timerfd_settime64            timerfd
#define __NR32AN1_timerfd_settime64            flags
#define __NR32AN2_timerfd_settime64            utmr
#define __NR32AN3_timerfd_settime64            otmr
#define __NR32AN0_utimensat_time64             dirfd
#define __NR32AN1_utimensat_time64             filename
#define __NR32AN2_utimensat_time64             times
#define __NR32AN3_utimensat_time64             flags
#define __NR32AN0_pselect6_time64              nfds
#define __NR32AN1_pselect6_time64              readfds
#define __NR32AN2_pselect6_time64              writefds
#define __NR32AN3_pselect6_time64              exceptfds
#define __NR32AN4_pselect6_time64              timeout
#define __NR32AN5_pselect6_time64              sigmask_sigset_with_size
#define __NR32AN0_ppoll_time64                 fds
#define __NR32AN1_ppoll_time64                 nfds
#define __NR32AN2_ppoll_time64                 timeout_ts
#define __NR32AN3_ppoll_time64                 sigmask
#define __NR32AN4_ppoll_time64                 sigsetsize
#define __NR32AN0_io_pgetevents_time64         TODO_PROTOTYPE
#define __NR32AN0_recvmmsg_time64              sockfd
#define __NR32AN1_recvmmsg_time64              vmessages
#define __NR32AN2_recvmmsg_time64              vlen
#define __NR32AN3_recvmmsg_time64              msg_flags
#define __NR32AN4_recvmmsg_time64              tmo
#define __NR32AN0_mq_timedsend_time64          mqdes
#define __NR32AN1_mq_timedsend_time64          msg_ptr
#define __NR32AN2_mq_timedsend_time64          msg_len
#define __NR32AN3_mq_timedsend_time64          msg_prio
#define __NR32AN4_mq_timedsend_time64          abs_timeout
#define __NR32AN0_mq_timedreceive_time64       mqdes
#define __NR32AN1_mq_timedreceive_time64       msg_ptr
#define __NR32AN2_mq_timedreceive_time64       msg_len
#define __NR32AN3_mq_timedreceive_time64       pmsg_prio
#define __NR32AN4_mq_timedreceive_time64       abs_timeout
#define __NR32AN0_semtimedop_time64            TODO_PROTOTYPE
#define __NR32AN0_rt_sigtimedwait_time64       set
#define __NR32AN1_rt_sigtimedwait_time64       info
#define __NR32AN2_rt_sigtimedwait_time64       timeout
#define __NR32AN3_rt_sigtimedwait_time64       sigsetsize
#define __NR32AN0_futex_time64                 uaddr
#define __NR32AN1_futex_time64                 futex_op
#define __NR32AN2_futex_time64                 val
#define __NR32AN3_futex_time64                 timeout_or_val2
#define __NR32AN4_futex_time64                 uaddr2
#define __NR32AN5_futex_time64                 val3
#define __NR32AN0_sched_rr_get_interval_time64 pid
#define __NR32AN1_sched_rr_get_interval_time64 ts
#define __NR32AN0_pidfd_send_signal            pidfd
#define __NR32AN1_pidfd_send_signal            usigno
#define __NR32AN2_pidfd_send_signal            uinfo
#define __NR32AN3_pidfd_send_signal            flags
#define __NR32AN0_io_uring_setup               TODO_PROTOTYPE
#define __NR32AN0_io_uring_enter               TODO_PROTOTYPE
#define __NR32AN0_io_uring_register            TODO_PROTOTYPE
#define __NR32AN0_open_tree                    TODO_PROTOTYPE
#define __NR32AN0_move_mount                   TODO_PROTOTYPE
#define __NR32AN0_fsopen                       TODO_PROTOTYPE
#define __NR32AN0_fsconfig                     TODO_PROTOTYPE
#define __NR32AN0_fsmount                      TODO_PROTOTYPE
#define __NR32AN0_fspick                       TODO_PROTOTYPE
#define __NR32AN0_pidfd_open                   pid
#define __NR32AN1_pidfd_open                   flags
#define __NR32AN0_clone3                       cl_args
#define __NR32AN1_clone3                       size
#define __NR32AN0_close_range                  minfd
#define __NR32AN1_close_range                  maxfd
#define __NR32AN2_close_range                  flags
#define __NR32AN0_openat2                      TODO_PROTOTYPE
#define __NR32AN0_pidfd_getfd                  pidfd
#define __NR32AN1_pidfd_getfd                  foreign_fd
#define __NR32AN2_pidfd_getfd                  flags
#define __NR32AN0_faccessat2                   dirfd
#define __NR32AN1_faccessat2                   filename
#define __NR32AN2_faccessat2                   type
#define __NR32AN3_faccessat2                   flags
#define __NR32AN0_pwritevf                     fd
#define __NR32AN1_pwritevf                     iovec
#define __NR32AN2_pwritevf                     count
#define __NR32AN3_pwritevf                     offset
#define __NR32AN4_pwritevf                     mode
#define __NR32AN0_preadvf                      fd
#define __NR32AN1_preadvf                      iovec
#define __NR32AN2_preadvf                      count
#define __NR32AN3_preadvf                      offset
#define __NR32AN4_preadvf                      mode
#define __NR32AN0_fallocate64                  fd
#define __NR32AN1_fallocate64                  mode
#define __NR32AN2_fallocate64                  offset
#define __NR32AN3_fallocate64                  length
#define __NR32AN0_freadlinkat                  dirfd
#define __NR32AN1_freadlinkat                  path
#define __NR32AN2_freadlinkat                  buf
#define __NR32AN3_freadlinkat                  buflen
#define __NR32AN4_freadlinkat                  flags
#define __NR32AN0_fsymlinkat                   link_text
#define __NR32AN1_fsymlinkat                   tofd
#define __NR32AN2_fsymlinkat                   target_path
#define __NR32AN3_fsymlinkat                   flags
#define __NR32AN0_kfstatat                     dirfd
#define __NR32AN1_kfstatat                     filename
#define __NR32AN2_kfstatat                     statbuf
#define __NR32AN3_kfstatat                     flags
#define __NR32AN0_futimesat64                  dirfd
#define __NR32AN1_futimesat64                  filename
#define __NR32AN2_futimesat64                  times
#define __NR32AN0_fmknodat                     dirfd
#define __NR32AN1_fmknodat                     nodename
#define __NR32AN2_fmknodat                     mode
#define __NR32AN3_fmknodat                     dev
#define __NR32AN4_fmknodat                     flags
#define __NR32AN0_fmkdirat                     dirfd
#define __NR32AN1_fmkdirat                     pathname
#define __NR32AN2_fmkdirat                     mode
#define __NR32AN3_fmkdirat                     flags
#define __NR32AN0_waitid64                     idtype
#define __NR32AN1_waitid64                     id
#define __NR32AN2_waitid64                     infop
#define __NR32AN3_waitid64                     options
#define __NR32AN4_waitid64                     ru
#define __NR32AN0_utimes64                     filename
#define __NR32AN1_utimes64                     times
#define __NR32AN0_kreaddirf                    fd
#define __NR32AN1_kreaddirf                    buf
#define __NR32AN2_kreaddirf                    bufsize
#define __NR32AN3_kreaddirf                    mode
#define __NR32AN4_kreaddirf                    iomode
#define __NR32AN0_kfstat                       fd
#define __NR32AN1_kfstat                       statbuf
#define __NR32AN0_klstat                       filename
#define __NR32AN1_klstat                       statbuf
#define __NR32AN0_kstat                        filename
#define __NR32AN1_kstat                        statbuf
#define __NR32AN0_pwrite64f                    fd
#define __NR32AN1_pwrite64f                    buf
#define __NR32AN2_pwrite64f                    bufsize
#define __NR32AN3_pwrite64f                    offset
#define __NR32AN4_pwrite64f                    mode
#define __NR32AN0_pread64f                     fd
#define __NR32AN1_pread64f                     buf
#define __NR32AN2_pread64f                     bufsize
#define __NR32AN3_pread64f                     offset
#define __NR32AN4_pread64f                     mode
#define __NR32AN0_ksigreturn                   restore_fpu
#define __NR32AN1_ksigreturn                   unused1
#define __NR32AN2_ksigreturn                   unused2
#define __NR32AN3_ksigreturn                   restore_sigmask
#define __NR32AN4_ksigreturn                   sc_info
#define __NR32AN5_ksigreturn                   restore_cpu
#define __NR32AN0_nanosleep64                  req
#define __NR32AN1_nanosleep64                  rem
#define __NR32AN0_ksysctl                      command
#define __NR32AN1_ksysctl                      arg
#define __NR32AN0_writevf                      fd
#define __NR32AN1_writevf                      iovec
#define __NR32AN2_writevf                      count
#define __NR32AN3_writevf                      mode
#define __NR32AN0_readvf                       fd
#define __NR32AN1_readvf                       iovec
#define __NR32AN2_readvf                       count
#define __NR32AN3_readvf                       mode
#define __NR32AN0_kreaddir                     fd
#define __NR32AN1_kreaddir                     buf
#define __NR32AN2_kreaddir                     bufsize
#define __NR32AN3_kreaddir                     mode
#define __NR32AN0_wait4_64                     pid
#define __NR32AN1_wait4_64                     stat_loc
#define __NR32AN2_wait4_64                     options
#define __NR32AN3_wait4_64                     usage
#define __NR32AN0_getitimer64                  which
#define __NR32AN1_getitimer64                  curr_value
#define __NR32AN0_setitimer64                  which
#define __NR32AN1_setitimer64                  newval
#define __NR32AN2_setitimer64                  oldval
#define __NR32AN0_maplibrary                   addr
#define __NR32AN1_maplibrary                   flags
#define __NR32AN2_maplibrary                   fd
#define __NR32AN3_maplibrary                   hdrv
#define __NR32AN4_maplibrary                   hdrc
#define __NR32AN0_select64                     nfds
#define __NR32AN1_select64                     readfds
#define __NR32AN2_select64                     writefds
#define __NR32AN3_select64                     exceptfds
#define __NR32AN4_select64                     timeout
#define __NR32AN0_settimeofday64               tv
#define __NR32AN1_settimeofday64               tz
#define __NR32AN0_gettimeofday64               tv
#define __NR32AN1_gettimeofday64               tz
#define __NR32AN0_getrusage64                  who
#define __NR32AN1_getrusage64                  tv
#define __NR32AN0_fsmode                       mode
#define __NR32AN0_ioctlf                       fd
#define __NR32AN1_ioctlf                       command
#define __NR32AN2_ioctlf                       mode
#define __NR32AN3_ioctlf                       arg
#define __NR32AN0_rtm_abort                    code
#define __NR32AN0_ftime64                      tp
#define __NR32AN0_set_userprocmask_address     ctl
#define __NR32AN0_utime64                      filename
#define __NR32AN1_utime64                      times
#define __NR32AN0_userviofd                    initial_size
#define __NR32AN1_userviofd                    flags
#define __NR32AN0_stime64                      t
#define __NR32AN0_coredump                     curr_state
#define __NR32AN1_coredump                     orig_state
#define __NR32AN2_coredump                     traceback_vector
#define __NR32AN3_coredump                     traceback_length
#define __NR32AN4_coredump                     reason
#define __NR32AN5_coredump                     unwind_error
#define __NR32AN0_mktty                        name
#define __NR32AN1_mktty                        keyboard
#define __NR32AN2_mktty                        display
#define __NR32AN3_mktty                        rsvd
#define __NR32AN0_lfutexexpr                   futexaddr
#define __NR32AN1_lfutexexpr                   base
#define __NR32AN2_lfutexexpr                   expr
#define __NR32AN3_lfutexexpr                   timeout
#define __NR32AN4_lfutexexpr                   flags
#define __NR32AN0_lseek64                      fd
#define __NR32AN1_lseek64                      offset
#define __NR32AN2_lseek64                      whence
#define __NR32AN0_lfutex                       uaddr
#define __NR32AN1_lfutex                       futex_op
#define __NR32AN2_lfutex                       val
#define __NR32AN3_lfutex                       timeout
#define __NR32AN4_lfutex                       val2
#define __NR32AN0_debugtrap                    state
#define __NR32AN1_debugtrap                    reason
#define __NR32AN0_get_exception_handler        pmode
#define __NR32AN1_get_exception_handler        phandler
#define __NR32AN2_get_exception_handler        phandler_sp
#define __NR32AN0_set_exception_handler        mode
#define __NR32AN1_set_exception_handler        handler
#define __NR32AN2_set_exception_handler        handler_sp
#define __NR32AN0_time64                       timer
#define __NR32AN0_fchdirat                     dirfd
#define __NR32AN1_fchdirat                     path
#define __NR32AN2_fchdirat                     flags
#define __NR32AN0_openpty                      amaster
#define __NR32AN1_openpty                      aslave
#define __NR32AN2_openpty                      name
#define __NR32AN3_openpty                      termp
#define __NR32AN4_openpty                      winp
#define __NR32AN0_rpc_schedule                 target_tid
#define __NR32AN1_rpc_schedule                 mode
#define __NR32AN2_rpc_schedule                 program
#define __NR32AN3_rpc_schedule                 params
#define __NR32AN4_rpc_schedule                 max_param_count
#define __NR32AN0_frealpathat                  dirfd
#define __NR32AN1_frealpathat                  filename
#define __NR32AN2_frealpathat                  buf
#define __NR32AN3_frealpathat                  buflen
#define __NR32AN4_frealpathat                  flags
#define __NR32AN0_frealpath4                   fd
#define __NR32AN1_frealpath4                   resolved
#define __NR32AN2_frealpath4                   buflen
#define __NR32AN3_frealpath4                   flags
#define __NR32AN0_detach                       pid
#define __NR32AN0_writef                       fd
#define __NR32AN1_writef                       buf
#define __NR32AN2_writef                       bufsize
#define __NR32AN3_writef                       mode
#define __NR32AN0_readf                        fd
#define __NR32AN1_readf                        buf
#define __NR32AN2_readf                        bufsize
#define __NR32AN3_readf                        mode
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_NAMES */
#endif /* __WANT_SYSCALL_ARGUMENT_NAMES */


/************************************************************************/
/* SYSCALL ARGUMENT FORMAT                                              */
/*  - __NR32RTR_<name>       : ReturnTypeRepresentation                 */
/*  - __NR32ATR<argI>_<name> : ArgumentTypeRepresentation               */
/*  - __NR32ATL<argI>_<name> : ArgumentTypeLink                         */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_FORMAT
#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#define __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT
#define __NR32RTR_restart_syscall               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_exit                         SC_REPR_EXIT_STATUS                                                  /* exit_code */ 
#define __NR32RTR_exit                          SC_REPR_SIGNO_T                                                      /* return */
#define __NR32RTR_fork                          SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_read                         SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_read                         SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_read                         SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32RTR_read                          SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_write                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_write                        SC_REPR_BUFFER                                                       /* buf */ 
#define __NR32ATL1_write                        2                                                                    /* buf -> bufsize */ 
#define __NR32ATR2_write                        SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32RTR_write                         SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_open                         SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_open                         SC_REPR_OFLAG_T                                                      /* oflags */ 
#define __NR32ATR2_open                         SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32ATL2_open                         1                                                                    /* mode -> oflags */ 
#define __NR32RTR_open                          SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_close                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32RTR_close                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_waitpid                      SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_waitpid                      SC_REPR_POINTER                                                      /* stat_loc */ 
#define __NR32ATR2_waitpid                      SC_REPR_WAITFLAGS                                                    /* options */ 
#define __NR32RTR_waitpid                       SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_creat                        SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_creat                        SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32RTR_creat                         SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_link                         SC_REPR_FILENAME                                                     /* existing_file */ 
#define __NR32ATR1_link                         SC_REPR_FILENAME                                                     /* link_file */ 
#define __NR32RTR_link                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_unlink                       SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32RTR_unlink                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_execve                       SC_REPR_STRING                                                       /* path */ 
#define __NR32ATR1_execve                       SC_REPR_STRING_VECTOR32                                              /* argv */ 
#define __NR32ATR2_execve                       SC_REPR_STRING_VECTOR32                                              /* envp */ 
#define __NR32RTR_execve                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_chdir                        SC_REPR_FILENAME                                                     /* path */ 
#define __NR32RTR_chdir                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_time                         SC_REPR_POINTER                                                      /* timer */ 
#define __NR32RTR_time                          SC_REPR_TIME_T                                                       /* return */
#define __NR32ATR0_mknod                        SC_REPR_FILENAME                                                     /* nodename */ 
#define __NR32ATR1_mknod                        SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32ATR2_mknod                        SC_REPR_DEV_T                                                        /* dev */ 
#define __NR32ATL2_mknod                        1                                                                    /* dev -> mode */ 
#define __NR32RTR_mknod                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_chmod                        SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_chmod                        SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32RTR_chmod                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_lchown                       SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_lchown                       SC_REPR_UID_T                                                        /* owner */ 
#define __NR32ATR2_lchown                       SC_REPR_GID_T                                                        /* group */ 
#define __NR32RTR_lchown                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_break                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_oldstat                      SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_oldstat                      SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_oldstat                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_lseek                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_lseek                        SC_REPR_SYSCALL_SLONG_T                                              /* offset */ 
#define __NR32ATR2_lseek                        SC_REPR_SEEK_WHENCE                                                  /* whence */ 
#define __NR32RTR_lseek                         SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32RTR_getpid                        SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_mount                        SC_REPR_FILENAME                                                     /* special_file */ 
#define __NR32ATR1_mount                        SC_REPR_FILENAME                                                     /* dir */ 
#define __NR32ATR2_mount                        SC_REPR_STRING                                                       /* fstype */ 
#define __NR32ATR3_mount                        SC_REPR_MOUNT_FLAGS                                                  /* mountflags */ 
#define __NR32ATR4_mount                        SC_REPR_STRING                                                       /* data */ 
#define __NR32RTR_mount                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_umount                       SC_REPR_FILENAME                                                     /* special_file */ 
#define __NR32RTR_umount                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setuid                       SC_REPR_UID_T                                                        /* uid */ 
#define __NR32RTR_setuid                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_getuid                        SC_REPR_UID_T                                                        /* return */
#define __NR32ATR0_stime                        SC_REPR_TIME32_T_PTR                                                 /* t */ 
#define __NR32RTR_stime                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ptrace                       SC_REPR_SYSCALL_ULONG_T                                              /* request */ 
#define __NR32ATR1_ptrace                       SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR2_ptrace                       SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR3_ptrace                       SC_REPR_POINTER                                                      /* data */ 
#define __NR32RTR_ptrace                        SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_alarm                        SC_REPR_SYSCALL_ULONG_T                                              /* seconds */ 
#define __NR32RTR_alarm                         SC_REPR_SYSCALL_ULONG_T                                              /* return */
#define __NR32ATR0_oldfstat                     SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_oldfstat                     SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_oldfstat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_pause                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_utime                        SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_utime                        SC_REPR_STRUCT_UTIMBUFX32                                            /* times */ 
#define __NR32RTR_utime                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_stty                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_gtty                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_access                       SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_access                       SC_REPR_ACCESS_TYPE                                                  /* type */ 
#define __NR32RTR_access                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_nice                         SC_REPR_SYSCALL_SLONG_T                                              /* inc */ 
#define __NR32RTR_nice                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ftime                        SC_REPR_POINTER                                                      /* tp */ 
#define __NR32RTR_ftime                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_sync                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_kill                         SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_kill                         SC_REPR_SIGNO_T                                                      /* signo */ 
#define __NR32RTR_kill                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_rename                       SC_REPR_FILENAME                                                     /* oldname */ 
#define __NR32ATR1_rename                       SC_REPR_FILENAME                                                     /* newname_or_path */ 
#define __NR32RTR_rename                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mkdir                        SC_REPR_FILENAME                                                     /* pathname */ 
#define __NR32ATR1_mkdir                        SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32RTR_mkdir                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_rmdir                        SC_REPR_STRING                                                       /* path */ 
#define __NR32RTR_rmdir                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_dup                          SC_REPR_FD_T                                                         /* fd */ 
#define __NR32RTR_dup                           SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_pipe                         SC_REPR_POINTER                                                      /* pipedes */ 
#define __NR32RTR_pipe                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_times                        SC_REPR_POINTER                                                      /* buf */ 
#define __NR32RTR_times                         SC_REPR_SIGNO_T                                                      /* return */
#define __NR32RTR_prof                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_brk                          SC_REPR_POINTER                                                      /* addr */ 
#define __NR32RTR_brk                           SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setgid                       SC_REPR_GID_T                                                        /* gid */ 
#define __NR32RTR_setgid                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_getgid                        SC_REPR_GID_T                                                        /* return */
#define __NR32ATR0_signal                       SC_REPR_SIGNO_T                                                      /* signo */ 
#define __NR32ATR1_signal                       SC_REPR_SIGHANDLER_T                                                 /* handler */ 
#define __NR32RTR_signal                        SC_REPR_SIGHANDLER_T                                                 /* return */
#define __NR32RTR_geteuid                       SC_REPR_UID_T                                                        /* return */
#define __NR32RTR_getegid                       SC_REPR_GID_T                                                        /* return */
#define __NR32ATR0_acct                         SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32RTR_acct                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_umount2                      SC_REPR_STRING                                                       /* special_file */ 
#define __NR32ATR1_umount2                      SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_umount2                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_lock                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ioctl                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_ioctl                        SC_REPR_IOCTL_COMMAND                                                /* command */ 
#define __NR32ATR2_ioctl                        SC_REPR_IOCTL_ARG                                                    /* arg */ 
#define __NR32ATL2_ioctl                        1                                                                    /* arg -> command */ 
#define __NR32RTR_ioctl                         SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_fcntl                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fcntl                        SC_REPR_FCNTL_COMMAND                                                /* command */ 
#define __NR32ATR2_fcntl                        SC_REPR_FCNTL_ARG                                                    /* arg */ 
#define __NR32ATL2_fcntl                        1                                                                    /* arg -> command */ 
#define __NR32RTR_fcntl                         SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32RTR_mpx                           SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setpgid                      SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_setpgid                      SC_REPR_PID_T                                                        /* pgid */ 
#define __NR32RTR_setpgid                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_ulimit                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_oldolduname                  SC_REPR_POINTER                                                      /* name */ 
#define __NR32RTR_oldolduname                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_umask                        SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32RTR_umask                         SC_REPR_MODE_T                                                       /* return */
#define __NR32ATR0_chroot                       SC_REPR_FILENAME                                                     /* path */ 
#define __NR32RTR_chroot                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ustat                        SC_REPR_DEV_BLK                                                      /* dev */ 
#define __NR32ATR1_ustat                        SC_REPR_POINTER                                                      /* ubuf */ 
#define __NR32RTR_ustat                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_dup2                         SC_REPR_FD_T                                                         /* oldfd */ 
#define __NR32ATR1_dup2                         SC_REPR_FD_T                                                         /* newfd */ 
#define __NR32RTR_dup2                          SC_REPR_FD_T                                                         /* return */
#define __NR32RTR_getppid                       SC_REPR_PID_T                                                        /* return */
#define __NR32RTR_getpgrp                       SC_REPR_PID_T                                                        /* return */
#define __NR32RTR_setsid                        SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_sigaction                    SC_REPR_SIGNO_T                                                      /* signo */ 
#define __NR32ATR1_sigaction                    SC_REPR_STRUCT_SIGACTIONX32                                          /* act */ 
#define __NR32ATR2_sigaction                    SC_REPR_POINTER                                                      /* oact */ 
#define __NR32RTR_sigaction                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_sgetmask                      SC_REPR_SIGMASK                                                      /* return */
#define __NR32ATR0_ssetmask                     SC_REPR_SIGMASK                                                      /* sigmask */ 
#define __NR32RTR_ssetmask                      SC_REPR_SIGMASK                                                      /* return */
#define __NR32ATR0_setreuid                     SC_REPR_UID_T                                                        /* ruid */ 
#define __NR32ATR1_setreuid                     SC_REPR_UID_T                                                        /* euid */ 
#define __NR32RTR_setreuid                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setregid                     SC_REPR_GID_T                                                        /* rgid */ 
#define __NR32ATR1_setregid                     SC_REPR_GID_T                                                        /* egid */ 
#define __NR32RTR_setregid                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sigsuspend                   SC_REPR_STRUCT_SIGSET                                                /* set */ 
#define __NR32RTR_sigsuspend                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sigpending                   SC_REPR_POINTER                                                      /* set */ 
#define __NR32RTR_sigpending                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sethostname                  SC_REPR_STRING                                                       /* name */ 
#define __NR32ATL0_sethostname                  1                                                                    /* name -> len */ 
#define __NR32ATR1_sethostname                  SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32RTR_sethostname                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setrlimit                    SC_REPR_RLIMIT_RESOURCE                                              /* resource */ 
#define __NR32ATR1_setrlimit                    SC_REPR_STRUCT_RLIMITX32                                             /* rlimits */ 
#define __NR32RTR_setrlimit                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getrlimit                    SC_REPR_RLIMIT_RESOURCE                                              /* resource */ 
#define __NR32ATR1_getrlimit                    SC_REPR_POINTER                                                      /* rlimits */ 
#define __NR32RTR_getrlimit                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getrusage                    SC_REPR_GETRUSAGE_WHO                                                /* who */ 
#define __NR32ATR1_getrusage                    SC_REPR_POINTER                                                      /* tv */ 
#define __NR32RTR_getrusage                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_gettimeofday                 SC_REPR_POINTER                                                      /* tv */ 
#define __NR32ATR1_gettimeofday                 SC_REPR_POINTER                                                      /* tz */ 
#define __NR32RTR_gettimeofday                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_settimeofday                 SC_REPR_STRUCT_TIMEVALX32                                            /* tv */ 
#define __NR32ATR1_settimeofday                 SC_REPR_STRUCT_TIMEZONE                                              /* tz */ 
#define __NR32RTR_settimeofday                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getgroups                    SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR1_getgroups                    SC_REPR_POINTER                                                      /* list */ 
#define __NR32RTR_getgroups                     SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_setgroups                    SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR1_setgroups                    SC_REPR_GID_VECTOR16                                                 /* groups */ 
#define __NR32ATL1_setgroups                    0                                                                    /* groups -> count */ 
#define __NR32RTR_setgroups                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_select                       SC_REPR_STRUCT_SEL_ARGX32                                            /* arg */ 
#define __NR32RTR_select                        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_symlink                      SC_REPR_STRING                                                       /* link_text */ 
#define __NR32ATR1_symlink                      SC_REPR_FILENAME                                                     /* target_path */ 
#define __NR32RTR_symlink                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_oldlstat                     SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_oldlstat                     SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_oldlstat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_readlink                     SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATR1_readlink                     SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_readlink                     SC_REPR_SIZE_T                                                       /* buflen */ 
#define __NR32RTR_readlink                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_uselib                       SC_REPR_FILENAME                                                     /* library */ 
#define __NR32RTR_uselib                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_swapon                       SC_REPR_FILENAME                                                     /* pathname */ 
#define __NR32ATR1_swapon                       SC_REPR_SWAPFLAGS                                                    /* swapflags */ 
#define __NR32RTR_swapon                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_reboot                       SC_REPR_REBOOT_HOW                                                   /* how */ 
#define __NR32RTR_reboot                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_readdir                      SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_readdir                      SC_REPR_POINTER                                                      /* buf */ 
#define __NR32RTR_readdir                       SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_mmap                         SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_mmap                         SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32ATR2_mmap                         SC_REPR_MMAP_PROT                                                    /* prot */ 
#define __NR32ATR3_mmap                         SC_REPR_MMAP_FLAGS                                                   /* flags */ 
#define __NR32ATR4_mmap                         SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR5_mmap                         SC_REPR_SYSCALL_ULONG_T                                              /* offset */ 
#define __NR32RTR_mmap                          SC_REPR_POINTER                                                      /* return */
#define __NR32ATR0_munmap                       SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_munmap                       SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32RTR_munmap                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_truncate                     SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_truncate                     SC_REPR_SYSCALL_ULONG_T                                              /* length */ 
#define __NR32RTR_truncate                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ftruncate                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_ftruncate                    SC_REPR_SYSCALL_ULONG_T                                              /* length */ 
#define __NR32RTR_ftruncate                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fchmod                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fchmod                       SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32RTR_fchmod                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fchown                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fchown                       SC_REPR_UID_T                                                        /* owner */ 
#define __NR32ATR2_fchown                       SC_REPR_GID_T                                                        /* group */ 
#define __NR32RTR_fchown                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getpriority                  SC_REPR_SCHED_PRIORITY_WHICH                                         /* which */ 
#define __NR32ATR1_getpriority                  SC_REPR_ID_T                                                         /* who */ 
#define __NR32RTR_getpriority                   SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_setpriority                  SC_REPR_SCHED_PRIORITY_WHICH                                         /* which */ 
#define __NR32ATR1_setpriority                  SC_REPR_ID_T                                                         /* who */ 
#define __NR32ATR2_setpriority                  SC_REPR_SYSCALL_ULONG_T                                              /* value */ 
#define __NR32RTR_setpriority                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_profil                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_statfs                       SC_REPR_FILENAME                                                     /* file */ 
#define __NR32ATR1_statfs                       SC_REPR_POINTER                                                      /* buf */ 
#define __NR32RTR_statfs                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fstatfs                      SC_REPR_FD_T                                                         /* file */ 
#define __NR32ATR1_fstatfs                      SC_REPR_POINTER                                                      /* buf */ 
#define __NR32RTR_fstatfs                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ioperm                       SC_REPR_SYSCALL_ULONG_T                                              /* from */ 
#define __NR32ATR1_ioperm                       SC_REPR_SYSCALL_ULONG_T                                              /* num */ 
#define __NR32ATR2_ioperm                       SC_REPR_SYSCALL_ULONG_T                                              /* turn_on */ 
#define __NR32RTR_ioperm                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_socketcall                   SC_REPR_SOCKETCALL_CALL                                              /* call */ 
#define __NR32ATR1_socketcall                   SC_REPR_SOCKETCALL_ARGS                                              /* args */ 
#define __NR32ATL1_socketcall                   0                                                                    /* args -> call */ 
#define __NR32RTR_socketcall                    SC_REPR_SIGNO_T                                                      /* return */
#define __NR32ATR0_syslog                       SC_REPR_SYSLOG_LEVEL                                                 /* level */ 
#define __NR32ATR1_syslog                       SC_REPR_STRING                                                       /* str */ 
#define __NR32ATL1_syslog                       2                                                                    /* str -> len */ 
#define __NR32ATR2_syslog                       SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32RTR_syslog                        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_setitimer                    SC_REPR_ITIMER_WHICH                                                 /* which */ 
#define __NR32ATR1_setitimer                    SC_REPR_STRUCT_ITIMERVALX32                                          /* newval */ 
#define __NR32ATR2_setitimer                    SC_REPR_POINTER                                                      /* oldval */ 
#define __NR32RTR_setitimer                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getitimer                    SC_REPR_ITIMER_WHICH                                                 /* which */ 
#define __NR32ATR1_getitimer                    SC_REPR_POINTER                                                      /* curr_value */ 
#define __NR32RTR_getitimer                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_stat                         SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_stat                         SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_stat                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_lstat                        SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_lstat                        SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_lstat                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fstat                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fstat                        SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_fstat                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_olduname                     SC_REPR_POINTER                                                      /* name */ 
#define __NR32RTR_olduname                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_iopl                         SC_REPR_SYSCALL_ULONG_T                                              /* level */ 
#define __NR32RTR_iopl                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_vhangup                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_idle                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_vm86old                      SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_vm86old                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_wait4                        SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_wait4                        SC_REPR_POINTER                                                      /* stat_loc */ 
#define __NR32ATR2_wait4                        SC_REPR_WAITFLAGS                                                    /* options */ 
#define __NR32ATR3_wait4                        SC_REPR_POINTER                                                      /* usage */ 
#define __NR32RTR_wait4                         SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_swapoff                      SC_REPR_FILENAME                                                     /* pathname */ 
#define __NR32RTR_swapoff                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sysinfo                      SC_REPR_POINTER                                                      /* info */ 
#define __NR32RTR_sysinfo                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ipc                          SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_ipc                           SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fsync                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32RTR_fsync                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_sigreturn                     SC_REPR_SIGNO_T                                                      /* return */
#define __NR32ATR0_clone                        SC_REPR_CLONE_FLAGS                                                  /* flags */ 
#define __NR32ATR1_clone                        SC_REPR_POINTER                                                      /* child_stack */ 
#define __NR32ATR2_clone                        SC_REPR_POINTER                                                      /* ptid */ 
#define __NR32ATR3_clone                        SC_REPR_POINTER                                                      /* newtls */ 
#define __NR32ATR4_clone                        SC_REPR_POINTER                                                      /* ctid */ 
#define __NR32RTR_clone                         SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_setdomainname                SC_REPR_STRING                                                       /* name */ 
#define __NR32ATL0_setdomainname                1                                                                    /* name -> len */ 
#define __NR32ATR1_setdomainname                SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32RTR_setdomainname                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_uname                        SC_REPR_POINTER                                                      /* name */ 
#define __NR32RTR_uname                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_modify_ldt                   SC_REPR_SYSCALL_ULONG_T                                              /* func */ 
#define __NR32ATR1_modify_ldt                   SC_REPR_POINTER                                                      /* ptr */ 
#define __NR32ATR2_modify_ldt                   SC_REPR_SYSCALL_ULONG_T                                              /* bytecount */ 
#define __NR32RTR_modify_ldt                    SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_adjtimex                     SC_REPR_POINTER                                                      /* ntx */ 
#define __NR32RTR_adjtimex                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mprotect                     SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_mprotect                     SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32ATR2_mprotect                     SC_REPR_MMAP_PROT                                                    /* prot */ 
#define __NR32RTR_mprotect                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sigprocmask                  SC_REPR_SIGPROCMASK_HOW                                              /* how */ 
#define __NR32ATR1_sigprocmask                  SC_REPR_STRUCT_SIGSET                                                /* set */ 
#define __NR32ATR2_sigprocmask                  SC_REPR_POINTER                                                      /* oset */ 
#define __NR32RTR_sigprocmask                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_create_module                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_init_module                  SC_REPR_POINTER                                                      /* module_image */ 
#define __NR32ATR1_init_module                  SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32ATR2_init_module                  SC_REPR_STRING                                                       /* uargs */ 
#define __NR32RTR_init_module                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_delete_module                SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR1_delete_module                SC_REPR_OFLAG_T                                                      /* flags */ 
#define __NR32RTR_delete_module                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_get_kernel_syms               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_quotactl                     SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_quotactl                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getpgid                      SC_REPR_PID_T                                                        /* pid */ 
#define __NR32RTR_getpgid                       SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_fchdir                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32RTR_fchdir                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_bdflush                      SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_bdflush                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sysfs                        SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_sysfs                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_personality                  SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_personality                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_afs_syscall                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setfsuid                     SC_REPR_UID_T                                                        /* uid */ 
#define __NR32RTR_setfsuid                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setfsgid                     SC_REPR_GID_T                                                        /* gid */ 
#define __NR32RTR_setfsgid                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0__llseek                      SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1__llseek                      SC_REPR_INT64_T                                                      /* offset */ 
#define __NR32ATR2__llseek                      SC_REPR_POINTER                                                      /* result */ 
#define __NR32ATR3__llseek                      SC_REPR_SEEK_WHENCE                                                  /* whence */ 
#define __NR32RTR__llseek                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getdents                     SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_getdents                     SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_getdents                     SC_REPR_SIZE_T                                                       /* buflen */ 
#define __NR32RTR_getdents                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0__newselect                   SC_REPR_SIZE_T                                                       /* nfds */ 
#define __NR32ATR1__newselect                   SC_REPR_STRUCT_FDSET                                                 /* readfds */ 
#define __NR32ATL1__newselect                   0                                                                    /* readfds -> nfds */ 
#define __NR32ATR2__newselect                   SC_REPR_STRUCT_FDSET                                                 /* writefds */ 
#define __NR32ATL2__newselect                   0                                                                    /* writefds -> nfds */ 
#define __NR32ATR3__newselect                   SC_REPR_STRUCT_FDSET                                                 /* exceptfds */ 
#define __NR32ATL3__newselect                   0                                                                    /* exceptfds -> nfds */ 
#define __NR32ATR4__newselect                   SC_REPR_STRUCT_TIMEVALX32                                            /* timeout */ 
#define __NR32RTR__newselect                    SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_flock                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_flock                        SC_REPR_SYSCALL_ULONG_T                                              /* operation */ 
#define __NR32RTR_flock                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_msync                        SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_msync                        SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32ATR2_msync                        SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_msync                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_readv                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_readv                        SC_REPR_STRUCT_IOVECX32                                              /* iovec */ 
#define __NR32ATL1_readv                        2                                                                    /* iovec -> count */ 
#define __NR32ATR2_readv                        SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32RTR_readv                         SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_writev                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_writev                       SC_REPR_STRUCT_IOVECX32_C                                            /* iovec */ 
#define __NR32ATL1_writev                       2                                                                    /* iovec -> count */ 
#define __NR32ATR2_writev                       SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32RTR_writev                        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_getsid                       SC_REPR_PID_T                                                        /* pid */ 
#define __NR32RTR_getsid                        SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_fdatasync                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32RTR_fdatasync                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0__sysctl                      SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR__sysctl                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mlock                        SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_mlock                        SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32RTR_mlock                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_munlock                      SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_munlock                      SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32RTR_munlock                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mlockall                     SC_REPR_MLOCKALL_FLAGS                                               /* flags */ 
#define __NR32RTR_mlockall                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_munlockall                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sched_setparam               SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_sched_setparam               SC_REPR_STRUCT_SCHED_PARAM                                           /* param */ 
#define __NR32RTR_sched_setparam                SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sched_getparam               SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_sched_getparam               SC_REPR_POINTER                                                      /* param */ 
#define __NR32RTR_sched_getparam                SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sched_setscheduler           SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_sched_setscheduler           SC_REPR_SCHED_POLICY                                                 /* policy */ 
#define __NR32ATR2_sched_setscheduler           SC_REPR_STRUCT_SCHED_PARAM                                           /* param */ 
#define __NR32RTR_sched_setscheduler            SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sched_getscheduler           SC_REPR_PID_T                                                        /* pid */ 
#define __NR32RTR_sched_getscheduler            SC_REPR_SCHED_POLICY                                                 /* return */
#define __NR32RTR_sched_yield                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sched_get_priority_max       SC_REPR_SCHED_POLICY                                                 /* algorithm */ 
#define __NR32RTR_sched_get_priority_max        SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_sched_get_priority_min       SC_REPR_SCHED_POLICY                                                 /* algorithm */ 
#define __NR32RTR_sched_get_priority_min        SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_sched_rr_get_interval        SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_sched_rr_get_interval        SC_REPR_POINTER                                                      /* ts */ 
#define __NR32RTR_sched_rr_get_interval         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_nanosleep                    SC_REPR_STRUCT_TIMESPECX32                                           /* req */ 
#define __NR32ATR1_nanosleep                    SC_REPR_POINTER                                                      /* rem */ 
#define __NR32RTR_nanosleep                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mremap                       SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_mremap                       SC_REPR_SIZE_T                                                       /* old_len */ 
#define __NR32ATR2_mremap                       SC_REPR_SIZE_T                                                       /* new_len */ 
#define __NR32ATR3_mremap                       SC_REPR_MREMAP_FLAGS                                                 /* flags */ 
#define __NR32ATR4_mremap                       SC_REPR_POINTER                                                      /* new_address */ 
#define __NR32RTR_mremap                        SC_REPR_POINTER                                                      /* return */
#define __NR32ATR0_setresuid                    SC_REPR_UID_T                                                        /* ruid */ 
#define __NR32ATR1_setresuid                    SC_REPR_UID_T                                                        /* euid */ 
#define __NR32ATR2_setresuid                    SC_REPR_UID_T                                                        /* suid */ 
#define __NR32RTR_setresuid                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getresuid                    SC_REPR_POINTER                                                      /* ruid */ 
#define __NR32ATR1_getresuid                    SC_REPR_POINTER                                                      /* euid */ 
#define __NR32ATR2_getresuid                    SC_REPR_POINTER                                                      /* suid */ 
#define __NR32RTR_getresuid                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_vm86                         SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_vm86                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_query_module                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_poll                         SC_REPR_STRUCT_POLLFD                                                /* fds */ 
#define __NR32ATL0_poll                         1                                                                    /* fds -> nfds */ 
#define __NR32ATR1_poll                         SC_REPR_SIZE_T                                                       /* nfds */ 
#define __NR32ATR2_poll                         SC_REPR_SYSCALL_SLONG_T                                              /* timeout */ 
#define __NR32RTR_poll                          SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_nfsservctl                   SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_nfsservctl                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setresgid                    SC_REPR_GID_T                                                        /* rgid */ 
#define __NR32ATR1_setresgid                    SC_REPR_GID_T                                                        /* egid */ 
#define __NR32ATR2_setresgid                    SC_REPR_GID_T                                                        /* sgid */ 
#define __NR32RTR_setresgid                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getresgid                    SC_REPR_POINTER                                                      /* rgid */ 
#define __NR32ATR1_getresgid                    SC_REPR_POINTER                                                      /* egid */ 
#define __NR32ATR2_getresgid                    SC_REPR_POINTER                                                      /* sgid */ 
#define __NR32RTR_getresgid                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_prctl                        SC_REPR_PRCTL_COMMAND                                                /* command */ 
#define __NR32ATR1_prctl                        SC_REPR_SYSCALL_ULONG_T                                              /* arg2 */ 
#define __NR32ATR2_prctl                        SC_REPR_SYSCALL_ULONG_T                                              /* arg3 */ 
#define __NR32ATR3_prctl                        SC_REPR_SYSCALL_ULONG_T                                              /* arg4 */ 
#define __NR32ATR4_prctl                        SC_REPR_SYSCALL_ULONG_T                                              /* arg5 */ 
#define __NR32RTR_prctl                         SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32RTR_rt_sigreturn                  SC_REPR_SIGNO_T                                                      /* return */
#define __NR32ATR0_rt_sigaction                 SC_REPR_SIGNO_T                                                      /* signo */ 
#define __NR32ATR1_rt_sigaction                 SC_REPR_STRUCT_SIGACTIONX32                                          /* act */ 
#define __NR32ATL1_rt_sigaction                 3                                                                    /* act -> sigsetsize */ 
#define __NR32ATR2_rt_sigaction                 SC_REPR_POINTER                                                      /* oact */ 
#define __NR32ATR3_rt_sigaction                 SC_REPR_SIZE_T                                                       /* sigsetsize */ 
#define __NR32RTR_rt_sigaction                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_rt_sigprocmask               SC_REPR_SIGPROCMASK_HOW                                              /* how */ 
#define __NR32ATR1_rt_sigprocmask               SC_REPR_STRUCT_SIGSET                                                /* set */ 
#define __NR32ATL1_rt_sigprocmask               3                                                                    /* set -> sigsetsize */ 
#define __NR32ATR2_rt_sigprocmask               SC_REPR_POINTER                                                      /* oset */ 
#define __NR32ATR3_rt_sigprocmask               SC_REPR_SIZE_T                                                       /* sigsetsize */ 
#define __NR32RTR_rt_sigprocmask                SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_rt_sigpending                SC_REPR_POINTER                                                      /* set */ 
#define __NR32ATR1_rt_sigpending                SC_REPR_SIZE_T                                                       /* sigsetsize */ 
#define __NR32RTR_rt_sigpending                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_rt_sigtimedwait              SC_REPR_STRUCT_SIGSET                                                /* set */ 
#define __NR32ATL0_rt_sigtimedwait              3                                                                    /* set -> sigsetsize */ 
#define __NR32ATR1_rt_sigtimedwait              SC_REPR_POINTER                                                      /* info */ 
#define __NR32ATR2_rt_sigtimedwait              SC_REPR_STRUCT_TIMESPECX32                                           /* timeout */ 
#define __NR32ATR3_rt_sigtimedwait              SC_REPR_SIZE_T                                                       /* sigsetsize */ 
#define __NR32RTR_rt_sigtimedwait               SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_rt_sigqueueinfo              SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_rt_sigqueueinfo              SC_REPR_SIGNO_T                                                      /* usigno */ 
#define __NR32ATR2_rt_sigqueueinfo              SC_REPR_STRUCT_SIGINFOX32                                            /* uinfo */ 
#define __NR32RTR_rt_sigqueueinfo               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_rt_sigsuspend                SC_REPR_STRUCT_SIGSET                                                /* set */ 
#define __NR32ATL0_rt_sigsuspend                1                                                                    /* set -> sigsetsize */ 
#define __NR32ATR1_rt_sigsuspend                SC_REPR_SIZE_T                                                       /* sigsetsize */ 
#define __NR32RTR_rt_sigsuspend                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pread64                      SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_pread64                      SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_pread64                      SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_pread64                      SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32RTR_pread64                       SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_pwrite64                     SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_pwrite64                     SC_REPR_BUFFER                                                       /* buf */ 
#define __NR32ATL1_pwrite64                     2                                                                    /* buf -> bufsize */ 
#define __NR32ATR2_pwrite64                     SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_pwrite64                     SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32RTR_pwrite64                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_chown                        SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_chown                        SC_REPR_UID_T                                                        /* owner */ 
#define __NR32ATR2_chown                        SC_REPR_GID_T                                                        /* group */ 
#define __NR32RTR_chown                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getcwd                       SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR1_getcwd                       SC_REPR_SIZE_T                                                       /* size */ 
#define __NR32RTR_getcwd                        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_capget                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_capget                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_capset                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_capset                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sigaltstack                  SC_REPR_STRUCT_SIGALTSTACKX32                                        /* ss */ 
#define __NR32ATR1_sigaltstack                  SC_REPR_POINTER                                                      /* oss */ 
#define __NR32RTR_sigaltstack                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sendfile                     SC_REPR_FD_T                                                         /* outfd */ 
#define __NR32ATR1_sendfile                     SC_REPR_FD_T                                                         /* infd */ 
#define __NR32ATR2_sendfile                     SC_REPR_POINTER                                                      /* pin_offset */ 
#define __NR32ATR3_sendfile                     SC_REPR_SIZE_T                                                       /* num_bytes */ 
#define __NR32RTR_sendfile                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32RTR_getpmsg                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_putpmsg                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_vfork                         SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_ugetrlimit                   SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_ugetrlimit                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mmap2                        SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_mmap2                        SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32ATR2_mmap2                        SC_REPR_MMAP_PROT                                                    /* prot */ 
#define __NR32ATR3_mmap2                        SC_REPR_MMAP_FLAGS                                                   /* flags */ 
#define __NR32ATR4_mmap2                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR5_mmap2                        SC_REPR_SYSCALL_ULONG_T                                              /* pgoffset */ 
#define __NR32RTR_mmap2                         SC_REPR_POINTER                                                      /* return */
#define __NR32ATR0_truncate64                   SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_truncate64                   SC_REPR_UINT64_T                                                     /* length */ 
#define __NR32RTR_truncate64                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ftruncate64                  SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_ftruncate64                  SC_REPR_UINT64_T                                                     /* length */ 
#define __NR32RTR_ftruncate64                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_stat64                       SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_stat64                       SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_stat64                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_lstat64                      SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_lstat64                      SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_lstat64                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fstat64                      SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fstat64                      SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_fstat64                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_lchown32                     SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_lchown32                     SC_REPR_UID_T                                                        /* owner */ 
#define __NR32ATR2_lchown32                     SC_REPR_GID_T                                                        /* group */ 
#define __NR32RTR_lchown32                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_getuid32                      SC_REPR_UID_T                                                        /* return */
#define __NR32RTR_getgid32                      SC_REPR_GID_T                                                        /* return */
#define __NR32RTR_geteuid32                     SC_REPR_UID_T                                                        /* return */
#define __NR32RTR_getegid32                     SC_REPR_GID_T                                                        /* return */
#define __NR32ATR0_setreuid32                   SC_REPR_UID_T                                                        /* ruid */ 
#define __NR32ATR1_setreuid32                   SC_REPR_UID_T                                                        /* euid */ 
#define __NR32RTR_setreuid32                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setregid32                   SC_REPR_GID_T                                                        /* rgid */ 
#define __NR32ATR1_setregid32                   SC_REPR_GID_T                                                        /* egid */ 
#define __NR32RTR_setregid32                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getgroups32                  SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR1_getgroups32                  SC_REPR_POINTER                                                      /* list */ 
#define __NR32RTR_getgroups32                   SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_setgroups32                  SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR1_setgroups32                  SC_REPR_GID_VECTOR32                                                 /* groups */ 
#define __NR32ATL1_setgroups32                  0                                                                    /* groups -> count */ 
#define __NR32RTR_setgroups32                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fchown32                     SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fchown32                     SC_REPR_UID_T                                                        /* owner */ 
#define __NR32ATR2_fchown32                     SC_REPR_GID_T                                                        /* group */ 
#define __NR32RTR_fchown32                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setresuid32                  SC_REPR_UID_T                                                        /* ruid */ 
#define __NR32ATR1_setresuid32                  SC_REPR_UID_T                                                        /* euid */ 
#define __NR32ATR2_setresuid32                  SC_REPR_UID_T                                                        /* suid */ 
#define __NR32RTR_setresuid32                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getresuid32                  SC_REPR_POINTER                                                      /* ruid */ 
#define __NR32ATR1_getresuid32                  SC_REPR_POINTER                                                      /* euid */ 
#define __NR32ATR2_getresuid32                  SC_REPR_POINTER                                                      /* suid */ 
#define __NR32RTR_getresuid32                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setresgid32                  SC_REPR_GID_T                                                        /* rgid */ 
#define __NR32ATR1_setresgid32                  SC_REPR_GID_T                                                        /* egid */ 
#define __NR32ATR2_setresgid32                  SC_REPR_GID_T                                                        /* sgid */ 
#define __NR32RTR_setresgid32                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getresgid32                  SC_REPR_POINTER                                                      /* rgid */ 
#define __NR32ATR1_getresgid32                  SC_REPR_POINTER                                                      /* egid */ 
#define __NR32ATR2_getresgid32                  SC_REPR_POINTER                                                      /* sgid */ 
#define __NR32RTR_getresgid32                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_chown32                      SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_chown32                      SC_REPR_UID_T                                                        /* owner */ 
#define __NR32ATR2_chown32                      SC_REPR_GID_T                                                        /* group */ 
#define __NR32RTR_chown32                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setuid32                     SC_REPR_UID_T                                                        /* uid */ 
#define __NR32RTR_setuid32                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setgid32                     SC_REPR_GID_T                                                        /* gid */ 
#define __NR32RTR_setgid32                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setfsuid32                   SC_REPR_UID_T                                                        /* uid */ 
#define __NR32RTR_setfsuid32                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setfsgid32                   SC_REPR_GID_T                                                        /* gid */ 
#define __NR32RTR_setfsgid32                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pivot_root                   SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_pivot_root                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mincore                      SC_REPR_POINTER                                                      /* start */ 
#define __NR32ATR1_mincore                      SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32ATR2_mincore                      SC_REPR_POINTER                                                      /* vec */ 
#define __NR32RTR_mincore                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_madvise                      SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_madvise                      SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32ATR2_madvise                      SC_REPR_SYSCALL_ULONG_T                                              /* advice */ 
#define __NR32RTR_madvise                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getdents64                   SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_getdents64                   SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_getdents64                   SC_REPR_SIZE_T                                                       /* buflen */ 
#define __NR32RTR_getdents64                    SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_fcntl64                      SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fcntl64                      SC_REPR_FCNTL64_COMMAND                                              /* command */ 
#define __NR32ATR2_fcntl64                      SC_REPR_FCNTL64_ARG                                                  /* arg */ 
#define __NR32ATL2_fcntl64                      1                                                                    /* arg -> command */ 
#define __NR32RTR_fcntl64                       SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32RTR_gettid                        SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_readahead                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_readahead                    SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32ATR2_readahead                    SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32RTR_readahead                     SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_setxattr                     SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATR1_setxattr                     SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR2_setxattr                     SC_REPR_BUFFER                                                       /* buf */ 
#define __NR32ATL2_setxattr                     3                                                                    /* buf -> bufsize */ 
#define __NR32ATR3_setxattr                     SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR4_setxattr                     SC_REPR_XATTR_FLAGS                                                  /* flags */ 
#define __NR32RTR_setxattr                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_lsetxattr                    SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATR1_lsetxattr                    SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR2_lsetxattr                    SC_REPR_BUFFER                                                       /* buf */ 
#define __NR32ATL2_lsetxattr                    3                                                                    /* buf -> bufsize */ 
#define __NR32ATR3_lsetxattr                    SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR4_lsetxattr                    SC_REPR_XATTR_FLAGS                                                  /* flags */ 
#define __NR32RTR_lsetxattr                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fsetxattr                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fsetxattr                    SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR2_fsetxattr                    SC_REPR_BUFFER                                                       /* buf */ 
#define __NR32ATL2_fsetxattr                    3                                                                    /* buf -> bufsize */ 
#define __NR32ATR3_fsetxattr                    SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR4_fsetxattr                    SC_REPR_XATTR_FLAGS                                                  /* flags */ 
#define __NR32RTR_fsetxattr                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getxattr                     SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATR1_getxattr                     SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR2_getxattr                     SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR3_getxattr                     SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32RTR_getxattr                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_lgetxattr                    SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATR1_lgetxattr                    SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR2_lgetxattr                    SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR3_lgetxattr                    SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32RTR_lgetxattr                     SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_fgetxattr                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fgetxattr                    SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR2_fgetxattr                    SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR3_fgetxattr                    SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32RTR_fgetxattr                     SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_listxattr                    SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATR1_listxattr                    SC_REPR_POINTER                                                      /* listbuf */ 
#define __NR32ATR2_listxattr                    SC_REPR_SIZE_T                                                       /* listbufsize */ 
#define __NR32RTR_listxattr                     SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_llistxattr                   SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATR1_llistxattr                   SC_REPR_POINTER                                                      /* listbuf */ 
#define __NR32ATR2_llistxattr                   SC_REPR_SIZE_T                                                       /* listbufsize */ 
#define __NR32RTR_llistxattr                    SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_flistxattr                   SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_flistxattr                   SC_REPR_POINTER                                                      /* listbuf */ 
#define __NR32ATR2_flistxattr                   SC_REPR_SIZE_T                                                       /* listbufsize */ 
#define __NR32RTR_flistxattr                    SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_removexattr                  SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATR1_removexattr                  SC_REPR_STRING                                                       /* name */ 
#define __NR32RTR_removexattr                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_lremovexattr                 SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATR1_lremovexattr                 SC_REPR_STRING                                                       /* name */ 
#define __NR32RTR_lremovexattr                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fremovexattr                 SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fremovexattr                 SC_REPR_STRING                                                       /* name */ 
#define __NR32RTR_fremovexattr                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_tkill                        SC_REPR_PID_T                                                        /* tid */ 
#define __NR32ATR1_tkill                        SC_REPR_SIGNO_T                                                      /* signo */ 
#define __NR32RTR_tkill                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sendfile64                   SC_REPR_FD_T                                                         /* outfd */ 
#define __NR32ATR1_sendfile64                   SC_REPR_FD_T                                                         /* infd */ 
#define __NR32ATR2_sendfile64                   SC_REPR_POINTER                                                      /* pin_offset */ 
#define __NR32ATR3_sendfile64                   SC_REPR_SIZE_T                                                       /* num_bytes */ 
#define __NR32RTR_sendfile64                    SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_futex                        SC_REPR_POINTER                                                      /* uaddr */ 
#define __NR32ATR1_futex                        SC_REPR_FUTEX_OP                                                     /* futex_op */ 
#define __NR32ATR2_futex                        SC_REPR_UINT32_T                                                     /* val */ 
#define __NR32ATR3_futex                        SC_REPR_STRUCT_TIMESPECX32_OR_UINT32                                 /* timeout_or_val2 */ 
#define __NR32ATL3_futex                        1                                                                    /* timeout_or_val2 -> futex_op */ 
#define __NR32ATR4_futex                        SC_REPR_POINTER                                                      /* uaddr2 */ 
#define __NR32ATR5_futex                        SC_REPR_UINT32_T                                                     /* val3 */ 
#define __NR32RTR_futex                         SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_sched_setaffinity            SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_sched_setaffinity            SC_REPR_SIZE_T                                                       /* cpusetsize */ 
#define __NR32ATR2_sched_setaffinity            SC_REPR_CPUSET                                                       /* cpuset */ 
#define __NR32ATL2_sched_setaffinity            1                                                                    /* cpuset -> cpusetsize */ 
#define __NR32RTR_sched_setaffinity             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sched_getaffinity            SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_sched_getaffinity            SC_REPR_SIZE_T                                                       /* cpusetsize */ 
#define __NR32ATR2_sched_getaffinity            SC_REPR_POINTER                                                      /* cpuset */ 
#define __NR32RTR_sched_getaffinity             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_set_thread_area              SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_set_thread_area               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_get_thread_area              SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_get_thread_area               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_io_setup                     SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_setup                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_io_destroy                   SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_destroy                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_io_getevents                 SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_getevents                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_io_submit                    SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_submit                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_io_cancel                    SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_cancel                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fadvise64                    SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_fadvise64                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_exit_group                   SC_REPR_EXIT_STATUS                                                  /* exit_code */ 
#define __NR32RTR_exit_group                    SC_REPR_SIGNO_T                                                      /* return */
#define __NR32ATR0_lookup_dcookie               SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_lookup_dcookie                SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_epoll_create                 SC_REPR_SYSCALL_ULONG_T                                              /* size */ 
#define __NR32RTR_epoll_create                  SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_epoll_ctl                    SC_REPR_FD_T                                                         /* epfd */ 
#define __NR32ATR1_epoll_ctl                    SC_REPR_EPOLL_OP                                                     /* op */ 
#define __NR32ATR2_epoll_ctl                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR3_epoll_ctl                    SC_REPR_STRUCT_EPOLL_EVENT                                           /* info */ 
#define __NR32RTR_epoll_ctl                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_epoll_wait                   SC_REPR_FD_T                                                         /* epfd */ 
#define __NR32ATR1_epoll_wait                   SC_REPR_POINTER                                                      /* events */ 
#define __NR32ATR2_epoll_wait                   SC_REPR_SIZE_T                                                       /* maxevents */ 
#define __NR32ATR3_epoll_wait                   SC_REPR_SYSCALL_SLONG_T                                              /* timeout */ 
#define __NR32RTR_epoll_wait                    SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_remap_file_pages             SC_REPR_POINTER                                                      /* start */ 
#define __NR32ATR1_remap_file_pages             SC_REPR_SIZE_T                                                       /* size */ 
#define __NR32ATR2_remap_file_pages             SC_REPR_MMAP_PROT                                                    /* prot */ 
#define __NR32ATR3_remap_file_pages             SC_REPR_SIZE_T                                                       /* pgoff */ 
#define __NR32ATR4_remap_file_pages             SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_remap_file_pages              SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_set_tid_address              SC_REPR_POINTER                                                      /* tidptr */ 
#define __NR32RTR_set_tid_address               SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_timer_create                 SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_timer_create                 SC_REPR_POINTER                                                      /* evp */ 
#define __NR32ATR2_timer_create                 SC_REPR_POINTER                                                      /* timerid */ 
#define __NR32RTR_timer_create                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timer_settime                SC_REPR_TIMER_T                                                      /* timerid */ 
#define __NR32ATR1_timer_settime                SC_REPR_TIMER_FLAGS                                                  /* flags */ 
#define __NR32ATR2_timer_settime                SC_REPR_STRUCT_ITIMERSPECX32                                         /* value */ 
#define __NR32ATR3_timer_settime                SC_REPR_POINTER                                                      /* ovalue */ 
#define __NR32RTR_timer_settime                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timer_gettime                SC_REPR_TIMER_T                                                      /* timerid */ 
#define __NR32ATR1_timer_gettime                SC_REPR_POINTER                                                      /* value */ 
#define __NR32RTR_timer_gettime                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timer_getoverrun             SC_REPR_TIMER_T                                                      /* timerid */ 
#define __NR32RTR_timer_getoverrun              SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_timer_delete                 SC_REPR_TIMER_T                                                      /* timerid */ 
#define __NR32RTR_timer_delete                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_clock_settime                SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_clock_settime                SC_REPR_STRUCT_TIMESPECX32                                           /* tp */ 
#define __NR32RTR_clock_settime                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_clock_gettime                SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_clock_gettime                SC_REPR_POINTER                                                      /* tp */ 
#define __NR32RTR_clock_gettime                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_clock_getres                 SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_clock_getres                 SC_REPR_POINTER                                                      /* res */ 
#define __NR32RTR_clock_getres                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_clock_nanosleep              SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_clock_nanosleep              SC_REPR_TIMER_FLAGS                                                  /* flags */ 
#define __NR32ATR2_clock_nanosleep              SC_REPR_STRUCT_TIMESPECX32                                           /* requested_time */ 
#define __NR32ATR3_clock_nanosleep              SC_REPR_POINTER                                                      /* remaining */ 
#define __NR32RTR_clock_nanosleep               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_statfs64                     SC_REPR_FILENAME                                                     /* file */ 
#define __NR32ATR1_statfs64                     SC_REPR_POINTER                                                      /* buf */ 
#define __NR32RTR_statfs64                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fstatfs64                    SC_REPR_FD_T                                                         /* file */ 
#define __NR32ATR1_fstatfs64                    SC_REPR_POINTER                                                      /* buf */ 
#define __NR32RTR_fstatfs64                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_tgkill                       SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_tgkill                       SC_REPR_PID_T                                                        /* tid */ 
#define __NR32ATR2_tgkill                       SC_REPR_SIGNO_T                                                      /* signo */ 
#define __NR32RTR_tgkill                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_utimes                       SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_utimes                       SC_REPR_STRUCT_TIMEVALX32_VEC2                                       /* times */ 
#define __NR32RTR_utimes                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fadvise64_64                 SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_fadvise64_64                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_vserver                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mbind                        SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_mbind                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_get_mempolicy                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_get_mempolicy                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_set_mempolicy                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_set_mempolicy                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mq_open                      SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR1_mq_open                      SC_REPR_OFLAG_T                                                      /* oflags */ 
#define __NR32ATR2_mq_open                      SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32ATL2_mq_open                      1                                                                    /* mode -> oflags */ 
#define __NR32RTR_mq_open                       SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_mq_unlink                    SC_REPR_STRING                                                       /* name */ 
#define __NR32RTR_mq_unlink                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mq_timedsend                 SC_REPR_FD_T                                                         /* mqdes */ 
#define __NR32ATR1_mq_timedsend                 SC_REPR_BUFFER                                                       /* msg_ptr */ 
#define __NR32ATL1_mq_timedsend                 2                                                                    /* msg_ptr -> msg_len */ 
#define __NR32ATR2_mq_timedsend                 SC_REPR_SIZE_T                                                       /* msg_len */ 
#define __NR32ATR3_mq_timedsend                 SC_REPR_UINT32_T                                                     /* msg_prio */ 
#define __NR32ATR4_mq_timedsend                 SC_REPR_STRUCT_TIMESPECX32                                           /* abs_timeout */ 
#define __NR32RTR_mq_timedsend                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mq_timedreceive              SC_REPR_FD_T                                                         /* mqdes */ 
#define __NR32ATR1_mq_timedreceive              SC_REPR_POINTER                                                      /* msg_ptr */ 
#define __NR32ATR2_mq_timedreceive              SC_REPR_SIZE_T                                                       /* msg_len */ 
#define __NR32ATR3_mq_timedreceive              SC_REPR_POINTER                                                      /* pmsg_prio */ 
#define __NR32ATR4_mq_timedreceive              SC_REPR_STRUCT_TIMESPECX32                                           /* abs_timeout */ 
#define __NR32RTR_mq_timedreceive               SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_mq_notify                    SC_REPR_FD_T                                                         /* mqdes */ 
#define __NR32ATR1_mq_notify                    SC_REPR_STRUCT_SIGEVENT                                              /* notification */ 
#define __NR32RTR_mq_notify                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mq_getsetattr                SC_REPR_FD_T                                                         /* mqdes */ 
#define __NR32ATR1_mq_getsetattr                SC_REPR_STRUCT_MQ_ATTR                                               /* newattr */ 
#define __NR32ATR2_mq_getsetattr                SC_REPR_POINTER                                                      /* oldattr */ 
#define __NR32RTR_mq_getsetattr                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_kexec_load                   SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_kexec_load                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_waitid                       SC_REPR_IDTYPE_T                                                     /* idtype */ 
#define __NR32ATR1_waitid                       SC_REPR_ID_T                                                         /* id */ 
#define __NR32ATL1_waitid                       0                                                                    /* id -> idtype */ 
#define __NR32ATR2_waitid                       SC_REPR_POINTER                                                      /* infop */ 
#define __NR32ATR3_waitid                       SC_REPR_WAITFLAGS                                                    /* options */ 
#define __NR32ATR4_waitid                       SC_REPR_POINTER                                                      /* ru */ 
#define __NR32RTR_waitid                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_add_key                      SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_add_key                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_request_key                  SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_request_key                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_keyctl                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_keyctl                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ioprio_set                   SC_REPR_IOPRIO_WHO                                                   /* who */ 
#define __NR32ATR1_ioprio_set                   SC_REPR_IOPRIO_ID                                                    /* id */ 
#define __NR32ATL1_ioprio_set                   0                                                                    /* id -> who */ 
#define __NR32ATR2_ioprio_set                   SC_REPR_IOPRIO_VALUE                                                 /* ioprio */ 
#define __NR32RTR_ioprio_set                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ioprio_get                   SC_REPR_IOPRIO_WHO                                                   /* who */ 
#define __NR32ATR1_ioprio_get                   SC_REPR_IOPRIO_ID                                                    /* id */ 
#define __NR32ATL1_ioprio_get                   0                                                                    /* id -> who */ 
#define __NR32RTR_ioprio_get                    SC_REPR_IOPRIO_VALUE                                                 /* return */
#define __NR32ATR0_inotify_init                 SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_inotify_init                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_inotify_add_watch            SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_inotify_add_watch             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_inotify_rm_watch             SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_inotify_rm_watch              SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_migrate_pages                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_migrate_pages                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_openat                       SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_openat                       SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_openat                       0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_openat                       SC_REPR_OFLAG_T                                                      /* oflags */ 
#define __NR32ATR3_openat                       SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32ATL3_openat                       2                                                                    /* mode -> oflags */ 
#define __NR32RTR_openat                        SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_mkdirat                      SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_mkdirat                      SC_REPR_FILENAME                                                     /* pathname */ 
#define __NR32ATL1_mkdirat                      0                                                                    /* pathname -> dirfd */ 
#define __NR32ATR2_mkdirat                      SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32RTR_mkdirat                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mknodat                      SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_mknodat                      SC_REPR_FILENAME                                                     /* nodename */ 
#define __NR32ATL1_mknodat                      0                                                                    /* nodename -> dirfd */ 
#define __NR32ATR2_mknodat                      SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32ATR3_mknodat                      SC_REPR_DEV_T                                                        /* dev */ 
#define __NR32ATL3_mknodat                      2                                                                    /* dev -> mode */ 
#define __NR32RTR_mknodat                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fchownat                     SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_fchownat                     SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_fchownat                     0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_fchownat                     SC_REPR_UID_T                                                        /* owner */ 
#define __NR32ATR3_fchownat                     SC_REPR_GID_T                                                        /* group */ 
#define __NR32ATR4_fchownat                     SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH                            /* flags */ 
#define __NR32RTR_fchownat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_futimesat                    SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_futimesat                    SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_futimesat                    0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_futimesat                    SC_REPR_STRUCT_TIMEVALX32_VEC2                                       /* times */ 
#define __NR32RTR_futimesat                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fstatat64                    SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_fstatat64                    SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_fstatat64                    0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_fstatat64                    SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32ATR3_fstatat64                    SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH                            /* flags */ 
#define __NR32RTR_fstatat64                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_unlinkat                     SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_unlinkat                     SC_REPR_FILENAME                                                     /* name */ 
#define __NR32ATL1_unlinkat                     0                                                                    /* name -> dirfd */ 
#define __NR32ATR2_unlinkat                     SC_REPR_ATFLAG__REMOVEDIR__REMOVEREG__DOSPATH                        /* flags */ 
#define __NR32RTR_unlinkat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_renameat                     SC_REPR_FD_T                                                         /* oldfd */ 
#define __NR32ATR1_renameat                     SC_REPR_FILENAME                                                     /* oldname */ 
#define __NR32ATL1_renameat                     0                                                                    /* oldname -> oldfd */ 
#define __NR32ATR2_renameat                     SC_REPR_FD_T                                                         /* newfd */ 
#define __NR32ATR3_renameat                     SC_REPR_FILENAME                                                     /* newname_or_path */ 
#define __NR32ATL3_renameat                     2                                                                    /* newname_or_path -> newfd */ 
#define __NR32RTR_renameat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_linkat                       SC_REPR_FD_T                                                         /* fromfd */ 
#define __NR32ATR1_linkat                       SC_REPR_FILENAME                                                     /* existing_file */ 
#define __NR32ATL1_linkat                       0                                                                    /* existing_file -> fromfd */ 
#define __NR32ATR2_linkat                       SC_REPR_FD_T                                                         /* tofd */ 
#define __NR32ATR3_linkat                       SC_REPR_FILENAME                                                     /* target_path */ 
#define __NR32ATL3_linkat                       2                                                                    /* target_path -> tofd */ 
#define __NR32ATR4_linkat                       SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH                  /* flags */ 
#define __NR32RTR_linkat                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_symlinkat                    SC_REPR_STRING                                                       /* link_text */ 
#define __NR32ATR1_symlinkat                    SC_REPR_FD_T                                                         /* tofd */ 
#define __NR32ATR2_symlinkat                    SC_REPR_FILENAME                                                     /* target_path */ 
#define __NR32ATL2_symlinkat                    1                                                                    /* target_path -> tofd */ 
#define __NR32RTR_symlinkat                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_readlinkat                   SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_readlinkat                   SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATL1_readlinkat                   0                                                                    /* path -> dirfd */ 
#define __NR32ATR2_readlinkat                   SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR3_readlinkat                   SC_REPR_SIZE_T                                                       /* buflen */ 
#define __NR32RTR_readlinkat                    SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_fchmodat                     SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_fchmodat                     SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_fchmodat                     0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_fchmodat                     SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32ATR3_fchmodat                     SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH                            /* flags */ 
#define __NR32RTR_fchmodat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_faccessat                    SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_faccessat                    SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_faccessat                    0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_faccessat                    SC_REPR_ACCESS_TYPE                                                  /* type */ 
#define __NR32RTR_faccessat                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pselect6                     SC_REPR_SIZE_T                                                       /* nfds */ 
#define __NR32ATR1_pselect6                     SC_REPR_STRUCT_FDSET                                                 /* readfds */ 
#define __NR32ATL1_pselect6                     0                                                                    /* readfds -> nfds */ 
#define __NR32ATR2_pselect6                     SC_REPR_STRUCT_FDSET                                                 /* writefds */ 
#define __NR32ATL2_pselect6                     0                                                                    /* writefds -> nfds */ 
#define __NR32ATR3_pselect6                     SC_REPR_STRUCT_FDSET                                                 /* exceptfds */ 
#define __NR32ATL3_pselect6                     0                                                                    /* exceptfds -> nfds */ 
#define __NR32ATR4_pselect6                     SC_REPR_STRUCT_TIMESPECX32                                           /* timeout */ 
#define __NR32ATR5_pselect6                     SC_REPR_STRUCT_SIGSET_WITH_SIZE_X32                                  /* sigmask_sigset_with_size */ 
#define __NR32RTR_pselect6                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_ppoll                        SC_REPR_STRUCT_POLLFD                                                /* fds */ 
#define __NR32ATL0_ppoll                        1                                                                    /* fds -> nfds */ 
#define __NR32ATR1_ppoll                        SC_REPR_SIZE_T                                                       /* nfds */ 
#define __NR32ATR2_ppoll                        SC_REPR_STRUCT_TIMESPECX32                                           /* timeout_ts */ 
#define __NR32ATR3_ppoll                        SC_REPR_STRUCT_SIGSET                                                /* sigmask */ 
#define __NR32ATL3_ppoll                        4                                                                    /* sigmask -> sigsetsize */ 
#define __NR32ATR4_ppoll                        SC_REPR_SIZE_T                                                       /* sigsetsize */ 
#define __NR32RTR_ppoll                         SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_unshare                      SC_REPR_CLONE_FLAGS_UNSHARE                                          /* what */ 
#define __NR32RTR_unshare                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_set_robust_list              SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_set_robust_list               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_get_robust_list              SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_get_robust_list               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_splice                       SC_REPR_FD_T                                                         /* fdin */ 
#define __NR32ATR1_splice                       SC_REPR_POINTER                                                      /* offin */ 
#define __NR32ATR2_splice                       SC_REPR_FD_T                                                         /* fdout */ 
#define __NR32ATR3_splice                       SC_REPR_POINTER                                                      /* offout */ 
#define __NR32ATR4_splice                       SC_REPR_SIZE_T                                                       /* length */ 
#define __NR32ATR5_splice                       SC_REPR_SPLICE_FLAGS                                                 /* flags */ 
#define __NR32RTR_splice                        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_sync_file_range              SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_sync_file_range              SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32ATR2_sync_file_range              SC_REPR_UINT64_T                                                     /* count */ 
#define __NR32ATR3_sync_file_range              SC_REPR_SYNC_FILE_RANGE_FLAGS                                        /* flags */ 
#define __NR32RTR_sync_file_range               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_tee                          SC_REPR_FD_T                                                         /* fdin */ 
#define __NR32ATR1_tee                          SC_REPR_FD_T                                                         /* fdout */ 
#define __NR32ATR2_tee                          SC_REPR_SIZE_T                                                       /* length */ 
#define __NR32ATR3_tee                          SC_REPR_SPLICE_FLAGS                                                 /* flags */ 
#define __NR32RTR_tee                           SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_vmsplice                     SC_REPR_FD_T                                                         /* fdout */ 
#define __NR32ATR1_vmsplice                     SC_REPR_STRUCT_IOVECX32_C                                            /* iov */ 
#define __NR32ATL1_vmsplice                     2                                                                    /* iov -> count */ 
#define __NR32ATR2_vmsplice                     SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR3_vmsplice                     SC_REPR_SPLICE_FLAGS                                                 /* flags */ 
#define __NR32RTR_vmsplice                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_move_pages                   SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_move_pages                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getcpu                       SC_REPR_POINTER                                                      /* cpu */ 
#define __NR32ATR1_getcpu                       SC_REPR_POINTER                                                      /* node */ 
#define __NR32ATR2_getcpu                       SC_REPR_POINTER                                                      /* tcache */ 
#define __NR32RTR_getcpu                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_epoll_pwait                  SC_REPR_FD_T                                                         /* epfd */ 
#define __NR32ATR1_epoll_pwait                  SC_REPR_POINTER                                                      /* events */ 
#define __NR32ATR2_epoll_pwait                  SC_REPR_SIZE_T                                                       /* maxevents */ 
#define __NR32ATR3_epoll_pwait                  SC_REPR_SYSCALL_SLONG_T                                              /* timeout */ 
#define __NR32ATR4_epoll_pwait                  SC_REPR_STRUCT_SIGSET                                                /* ss */ 
#define __NR32ATL4_epoll_pwait                  5                                                                    /* ss -> sigsetsize */ 
#define __NR32ATR5_epoll_pwait                  SC_REPR_SIZE_T                                                       /* sigsetsize */ 
#define __NR32RTR_epoll_pwait                   SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_utimensat                    SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_utimensat                    SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_utimensat                    0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_utimensat                    SC_REPR_STRUCT_TIMESPECX32_VEC2_OR_3                                 /* times */ 
#define __NR32ATL2_utimensat                    3                                                                    /* times -> flags */ 
#define __NR32ATR3_utimensat                    SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_CTIME__DOSPATH              /* flags */ 
#define __NR32RTR_utimensat                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_signalfd                     SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_signalfd                     SC_REPR_STRUCT_SIGSET                                                /* sigmask */ 
#define __NR32ATL1_signalfd                     2                                                                    /* sigmask -> sigmasksize */ 
#define __NR32ATR2_signalfd                     SC_REPR_SIZE_T                                                       /* sigmasksize */ 
#define __NR32RTR_signalfd                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timerfd_create               SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_timerfd_create               SC_REPR_TIMERFD_FLAGS                                                /* flags */ 
#define __NR32RTR_timerfd_create                SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_eventfd                      SC_REPR_SYSCALL_ULONG_T                                              /* initval */ 
#define __NR32RTR_eventfd                       SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_fallocate                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fallocate                    SC_REPR_FALLOCATE_MODE                                               /* mode */ 
#define __NR32ATR2_fallocate                    SC_REPR_SYSCALL_ULONG_T                                              /* offset */ 
#define __NR32ATR3_fallocate                    SC_REPR_SYSCALL_ULONG_T                                              /* length */ 
#define __NR32RTR_fallocate                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timerfd_settime              SC_REPR_FD_T                                                         /* timerfd */ 
#define __NR32ATR1_timerfd_settime              SC_REPR_TIMERFD_TIMER_FLAGS                                          /* flags */ 
#define __NR32ATR2_timerfd_settime              SC_REPR_STRUCT_ITIMERSPECX32                                         /* utmr */ 
#define __NR32ATR3_timerfd_settime              SC_REPR_POINTER                                                      /* otmr */ 
#define __NR32RTR_timerfd_settime               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timerfd_gettime              SC_REPR_FD_T                                                         /* timerfd */ 
#define __NR32ATR1_timerfd_gettime              SC_REPR_POINTER                                                      /* otmr */ 
#define __NR32RTR_timerfd_gettime               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_signalfd4                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_signalfd4                    SC_REPR_STRUCT_SIGSET                                                /* sigmask */ 
#define __NR32ATL1_signalfd4                    2                                                                    /* sigmask -> sigmasksize */ 
#define __NR32ATR2_signalfd4                    SC_REPR_SIZE_T                                                       /* sigmasksize */ 
#define __NR32ATR3_signalfd4                    SC_REPR_SIGNALFD4_FLAGS                                              /* flags */ 
#define __NR32RTR_signalfd4                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_eventfd2                     SC_REPR_SYSCALL_ULONG_T                                              /* initval */ 
#define __NR32ATR1_eventfd2                     SC_REPR_EVENTFD2_FLAGS                                               /* flags */ 
#define __NR32RTR_eventfd2                      SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_epoll_create1                SC_REPR_EPOLL_CREATE1_FLAGS                                          /* flags */ 
#define __NR32RTR_epoll_create1                 SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_dup3                         SC_REPR_FD_T                                                         /* oldfd */ 
#define __NR32ATR1_dup3                         SC_REPR_FD_T                                                         /* newfd */ 
#define __NR32ATR2_dup3                         SC_REPR_OFLAG__CLOEXEC__CLOFORK                                      /* flags */ 
#define __NR32RTR_dup3                          SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_pipe2                        SC_REPR_POINTER                                                      /* pipedes */ 
#define __NR32ATR1_pipe2                        SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK__DIRECT                    /* flags */ 
#define __NR32RTR_pipe2                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_inotify_init1                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_inotify_init1                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_preadv                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_preadv                       SC_REPR_STRUCT_IOVECX32                                              /* iovec */ 
#define __NR32ATL1_preadv                       2                                                                    /* iovec -> count */ 
#define __NR32ATR2_preadv                       SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR3_preadv                       SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32RTR_preadv                        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_pwritev                      SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_pwritev                      SC_REPR_STRUCT_IOVECX32_C                                            /* iovec */ 
#define __NR32ATL1_pwritev                      2                                                                    /* iovec -> count */ 
#define __NR32ATR2_pwritev                      SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR3_pwritev                      SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32RTR_pwritev                       SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_rt_tgsigqueueinfo            SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_rt_tgsigqueueinfo            SC_REPR_PID_T                                                        /* tid */ 
#define __NR32ATR2_rt_tgsigqueueinfo            SC_REPR_SIGNO_T                                                      /* usigno */ 
#define __NR32ATR3_rt_tgsigqueueinfo            SC_REPR_STRUCT_SIGINFOX32                                            /* uinfo */ 
#define __NR32RTR_rt_tgsigqueueinfo             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_perf_event_open              SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_perf_event_open               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_recvmmsg                     SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_recvmmsg                     SC_REPR_POINTER                                                      /* vmessages */ 
#define __NR32ATR2_recvmmsg                     SC_REPR_SIZE_T                                                       /* vlen */ 
#define __NR32ATR3_recvmmsg                     SC_REPR_SOCKET_RECVMSG_FLAGS3                                        /* msg_flags */ 
#define __NR32ATR4_recvmmsg                     SC_REPR_STRUCT_TIMESPECX32                                           /* tmo */ 
#define __NR32RTR_recvmmsg                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_fanotify_init                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_fanotify_init                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fanotify_mark                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_fanotify_mark                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_prlimit64                    SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_prlimit64                    SC_REPR_RLIMIT_RESOURCE                                              /* resource */ 
#define __NR32ATR2_prlimit64                    SC_REPR_STRUCT_RLIMITX32_64                                          /* new_limit */ 
#define __NR32ATR3_prlimit64                    SC_REPR_POINTER                                                      /* old_limit */ 
#define __NR32RTR_prlimit64                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_name_to_handle_at            SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_name_to_handle_at            SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_name_to_handle_at            0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_name_to_handle_at            SC_REPR_POINTER                                                      /* handle */ 
#define __NR32ATR3_name_to_handle_at            SC_REPR_POINTER                                                      /* mnt_id */ 
#define __NR32ATR4_name_to_handle_at            SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_FOLLOW__DOSPATH                  /* flags */ 
#define __NR32RTR_name_to_handle_at             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_open_by_handle_at            SC_REPR_FD_T                                                         /* mountdirfd */ 
#define __NR32ATR1_open_by_handle_at            SC_REPR_STRUCT_FILE_HANDLE                                           /* handle */ 
#define __NR32ATR2_open_by_handle_at            SC_REPR_OFLAG_T                                                      /* flags */ 
#define __NR32RTR_open_by_handle_at             SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_clock_adjtime                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_clock_adjtime                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_syncfs                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32RTR_syncfs                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sendmmsg                     SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_sendmmsg                     SC_REPR_STRUCT_MMSGHDRX32                                            /* vmessages */ 
#define __NR32ATL1_sendmmsg                     2                                                                    /* vmessages -> vlen */ 
#define __NR32ATR2_sendmmsg                     SC_REPR_SIZE_T                                                       /* vlen */ 
#define __NR32ATR3_sendmmsg                     SC_REPR_SOCKET_SENDMSG_FLAGS                                         /* msg_flags */ 
#define __NR32RTR_sendmmsg                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_setns                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_setns                        SC_REPR_CLONE_FLAGS_SETNS                                            /* nstype */ 
#define __NR32RTR_setns                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_process_vm_readv             SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_process_vm_readv             SC_REPR_STRUCT_IOVECX32                                              /* local_iov */ 
#define __NR32ATL1_process_vm_readv             2                                                                    /* local_iov -> liovcnt */ 
#define __NR32ATR2_process_vm_readv             SC_REPR_SIZE_T                                                       /* liovcnt */ 
#define __NR32ATR3_process_vm_readv             SC_REPR_STRUCT_IOVECX32                                              /* remote_iov */ 
#define __NR32ATL3_process_vm_readv             4                                                                    /* remote_iov -> riovcnt */ 
#define __NR32ATR4_process_vm_readv             SC_REPR_SIZE_T                                                       /* riovcnt */ 
#define __NR32ATR5_process_vm_readv             SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_process_vm_readv              SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_process_vm_writev            SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_process_vm_writev            SC_REPR_STRUCT_IOVECX32_C                                            /* local_iov */ 
#define __NR32ATL1_process_vm_writev            2                                                                    /* local_iov -> liovcnt */ 
#define __NR32ATR2_process_vm_writev            SC_REPR_SIZE_T                                                       /* liovcnt */ 
#define __NR32ATR3_process_vm_writev            SC_REPR_STRUCT_IOVECX32                                              /* remote_iov */ 
#define __NR32ATL3_process_vm_writev            4                                                                    /* remote_iov -> riovcnt */ 
#define __NR32ATR4_process_vm_writev            SC_REPR_SIZE_T                                                       /* riovcnt */ 
#define __NR32ATR5_process_vm_writev            SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_process_vm_writev             SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_kcmp                         SC_REPR_PID_T                                                        /* pid1 */ 
#define __NR32ATR1_kcmp                         SC_REPR_PID_T                                                        /* pid2 */ 
#define __NR32ATR2_kcmp                         SC_REPR_KCMP_TYPE                                                    /* type */ 
#define __NR32ATR3_kcmp                         SC_REPR_SYSCALL_ULONG_T                                              /* idx1 */ 
#define __NR32ATR4_kcmp                         SC_REPR_SYSCALL_ULONG_T                                              /* idx2 */ 
#define __NR32RTR_kcmp                          SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_finit_module                 SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_finit_module                 SC_REPR_STRING                                                       /* uargs */ 
#define __NR32ATR2_finit_module                 SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_finit_module                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sched_setattr                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_sched_setattr                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sched_getattr                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_sched_getattr                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_renameat2                    SC_REPR_FD_T                                                         /* olddirfd */ 
#define __NR32ATR1_renameat2                    SC_REPR_FILENAME                                                     /* oldpath */ 
#define __NR32ATL1_renameat2                    0                                                                    /* oldpath -> olddirfd */ 
#define __NR32ATR2_renameat2                    SC_REPR_FD_T                                                         /* newdirfd */ 
#define __NR32ATR3_renameat2                    SC_REPR_FILENAME                                                     /* newpath */ 
#define __NR32ATL3_renameat2                    2                                                                    /* newpath -> newdirfd */ 
#define __NR32ATR4_renameat2                    SC_REPR_RENAMEAT2_FLAGS                                              /* flags */ 
#define __NR32RTR_renameat2                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_seccomp                      SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_seccomp                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getrandom                    SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR1_getrandom                    SC_REPR_SIZE_T                                                       /* num_bytes */ 
#define __NR32ATR2_getrandom                    SC_REPR_GETRANDOM_FLAGS                                              /* flags */ 
#define __NR32RTR_getrandom                     SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_memfd_create                 SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR1_memfd_create                 SC_REPR_MEMFD_CREATE_FLAGS                                           /* flags */ 
#define __NR32RTR_memfd_create                  SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_bpf                          SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_bpf                           SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_execveat                     SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_execveat                     SC_REPR_FILENAME                                                     /* pathname */ 
#define __NR32ATL1_execveat                     0                                                                    /* pathname -> dirfd */ 
#define __NR32ATR2_execveat                     SC_REPR_STRING_VECTOR32                                              /* argv */ 
#define __NR32ATR3_execveat                     SC_REPR_STRING_VECTOR32                                              /* envp */ 
#define __NR32ATR4_execveat                     SC_REPR_ATFLAG__EMPTY_PATH__SYMLINK_NOFOLLOW__DOSPATH                /* flags */ 
#define __NR32RTR_execveat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_socket                       SC_REPR_SOCKET_DOMAIN                                                /* domain */ 
#define __NR32ATR1_socket                       SC_REPR_SOCKET_TYPE                                                  /* type */ 
#define __NR32ATR2_socket                       SC_REPR_SOCKET_PROTOCOL                                              /* protocol */ 
#define __NR32ATL2_socket                       0                                                                    /* protocol -> domain */ 
#define __NR32RTR_socket                        SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_socketpair                   SC_REPR_SOCKET_DOMAIN                                                /* domain */ 
#define __NR32ATR1_socketpair                   SC_REPR_SOCKET_TYPE                                                  /* type */ 
#define __NR32ATR2_socketpair                   SC_REPR_SOCKET_PROTOCOL                                              /* protocol */ 
#define __NR32ATL2_socketpair                   0                                                                    /* protocol -> domain */ 
#define __NR32ATR3_socketpair                   SC_REPR_POINTER                                                      /* fds */ 
#define __NR32RTR_socketpair                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_bind                         SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_bind                         SC_REPR_STRUCT_SOCKADDR                                              /* addr */ 
#define __NR32ATL1_bind                         2                                                                    /* addr -> addr_len */ 
#define __NR32ATR2_bind                         SC_REPR_SOCKLEN_T                                                    /* addr_len */ 
#define __NR32RTR_bind                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_connect                      SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_connect                      SC_REPR_STRUCT_SOCKADDR                                              /* addr */ 
#define __NR32ATL1_connect                      2                                                                    /* addr -> addr_len */ 
#define __NR32ATR2_connect                      SC_REPR_SOCKLEN_T                                                    /* addr_len */ 
#define __NR32RTR_connect                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_listen                       SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_listen                       SC_REPR_SYSCALL_ULONG_T                                              /* max_backlog */ 
#define __NR32RTR_listen                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_accept4                      SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_accept4                      SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR2_accept4                      SC_REPR_POINTER                                                      /* addr_len */ 
#define __NR32ATR3_accept4                      SC_REPR_ACCEPT4_FLAGS                                                /* sock_flags */ 
#define __NR32RTR_accept4                       SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_getsockopt                   SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_getsockopt                   SC_REPR_SOCKOPT_LEVEL                                                /* level */ 
#define __NR32ATR2_getsockopt                   SC_REPR_SOCKOPT_OPTNAME                                              /* optname */ 
#define __NR32ATL2_getsockopt                   1                                                                    /* optname -> level */ 
#define __NR32ATR3_getsockopt                   SC_REPR_POINTER                                                      /* optval */ 
#define __NR32ATR4_getsockopt                   SC_REPR_POINTER                                                      /* optlen */ 
#define __NR32RTR_getsockopt                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setsockopt                   SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_setsockopt                   SC_REPR_SOCKOPT_LEVEL                                                /* level */ 
#define __NR32ATR2_setsockopt                   SC_REPR_SOCKOPT_OPTNAME                                              /* optname */ 
#define __NR32ATL2_setsockopt                   1                                                                    /* optname -> level */ 
#define __NR32ATR3_setsockopt                   SC_REPR_SOCKOPT_OPTVAL                                               /* optval */ 
#define __NR32ATL3_setsockopt                   4                                                                    /* optval -> optlen */ 
#define __NR32ATR4_setsockopt                   SC_REPR_SOCKLEN_T                                                    /* optlen */ 
#define __NR32ATL4_setsockopt                   2                                                                    /* optlen -> optname */ 
#define __NR32RTR_setsockopt                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getsockname                  SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_getsockname                  SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR2_getsockname                  SC_REPR_POINTER                                                      /* addr_len */ 
#define __NR32RTR_getsockname                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getpeername                  SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_getpeername                  SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR2_getpeername                  SC_REPR_POINTER                                                      /* addr_len */ 
#define __NR32RTR_getpeername                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_sendto                       SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_sendto                       SC_REPR_BUFFER                                                       /* buf */ 
#define __NR32ATL1_sendto                       2                                                                    /* buf -> bufsize */ 
#define __NR32ATR2_sendto                       SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_sendto                       SC_REPR_SOCKET_SENDMSG_FLAGS                                         /* msg_flags */ 
#define __NR32ATR4_sendto                       SC_REPR_STRUCT_SOCKADDR                                              /* addr */ 
#define __NR32ATL4_sendto                       5                                                                    /* addr -> addr_len */ 
#define __NR32ATR5_sendto                       SC_REPR_SOCKLEN_T                                                    /* addr_len */ 
#define __NR32RTR_sendto                        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_sendmsg                      SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_sendmsg                      SC_REPR_STRUCT_MSGHDRX32                                             /* message */ 
#define __NR32ATR2_sendmsg                      SC_REPR_SOCKET_SENDMSG_FLAGS                                         /* msg_flags */ 
#define __NR32RTR_sendmsg                       SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_recvfrom                     SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_recvfrom                     SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_recvfrom                     SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_recvfrom                     SC_REPR_SOCKET_RECVMSG_FLAGS                                         /* msg_flags */ 
#define __NR32ATR4_recvfrom                     SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR5_recvfrom                     SC_REPR_POINTER                                                      /* addr_len */ 
#define __NR32RTR_recvfrom                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_recvmsg                      SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_recvmsg                      SC_REPR_POINTER                                                      /* message */ 
#define __NR32ATR2_recvmsg                      SC_REPR_SOCKET_RECVMSG_FLAGS2                                        /* msg_flags */ 
#define __NR32RTR_recvmsg                       SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_shutdown                     SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_shutdown                     SC_REPR_SOCKET_SHUTDOWN_HOW                                          /* how */ 
#define __NR32RTR_shutdown                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_userfaultfd                  SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_userfaultfd                   SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_membarrier                   SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_membarrier                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mlock2                       SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_mlock2                       SC_REPR_SIZE_T                                                       /* length */ 
#define __NR32ATR2_mlock2                       SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_mlock2                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_copy_file_range              SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_copy_file_range               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_preadv2                      SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_preadv2                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pwritev2                     SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_pwritev2                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pkey_mprotect                SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_pkey_mprotect                SC_REPR_SIZE_T                                                       /* len */ 
#define __NR32ATR2_pkey_mprotect                SC_REPR_SYSCALL_ULONG_T                                              /* prot */ 
#define __NR32ATR3_pkey_mprotect                SC_REPR_SYSCALL_ULONG_T                                              /* pkey */ 
#define __NR32RTR_pkey_mprotect                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pkey_alloc                   SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32ATR1_pkey_alloc                   SC_REPR_SYSCALL_ULONG_T                                              /* access_rights */ 
#define __NR32RTR_pkey_alloc                    SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_pkey_free                    SC_REPR_SYSCALL_ULONG_T                                              /* key */ 
#define __NR32RTR_pkey_free                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_statx                        SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_statx                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_arch_prctl                   SC_REPR_ARCH_PRCTL_COMMAND                                           /* command */ 
#define __NR32ATR1_arch_prctl                   SC_REPR_POINTER                                                      /* addr */ 
#define __NR32RTR_arch_prctl                    SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_io_pgetevents                SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_pgetevents                 SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_rseq                         SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_rseq                          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_semget                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_semget                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_semctl                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_semctl                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_shmget                       SC_REPR_SIGNO_T                                                      /* key */ 
#define __NR32ATR1_shmget                       SC_REPR_SIZE_T                                                       /* size */ 
#define __NR32ATR2_shmget                       SC_REPR_SYSCALL_ULONG_T                                              /* shmflg */ 
#define __NR32RTR_shmget                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_shmctl                       SC_REPR_SYSCALL_ULONG_T                                              /* shmid */ 
#define __NR32ATR1_shmctl                       SC_REPR_SYSCALL_ULONG_T                                              /* cmd */ 
#define __NR32ATR2_shmctl                       SC_REPR_POINTER                                                      /* buf */ 
#define __NR32RTR_shmctl                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_shmat                        SC_REPR_SYSCALL_ULONG_T                                              /* shmid */ 
#define __NR32ATR1_shmat                        SC_REPR_POINTER                                                      /* shmaddr */ 
#define __NR32ATR2_shmat                        SC_REPR_SYSCALL_ULONG_T                                              /* shmflg */ 
#define __NR32RTR_shmat                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_shmdt                        SC_REPR_POINTER                                                      /* shmaddr */ 
#define __NR32RTR_shmdt                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_msgget                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_msgget                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_msgsnd                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_msgsnd                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_msgrcv                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_msgrcv                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_msgctl                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_msgctl                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_clock_gettime64              SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_clock_gettime64              SC_REPR_POINTER                                                      /* tp */ 
#define __NR32RTR_clock_gettime64               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_clock_settime64              SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_clock_settime64              SC_REPR_STRUCT_TIMESPECX32_64                                        /* tp */ 
#define __NR32RTR_clock_settime64               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_clock_adjtime64              SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_clock_adjtime64               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_clock_getres_time64          SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_clock_getres_time64          SC_REPR_POINTER                                                      /* res */ 
#define __NR32RTR_clock_getres_time64           SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_clock_nanosleep_time64       SC_REPR_CLOCKID_T                                                    /* clock_id */ 
#define __NR32ATR1_clock_nanosleep_time64       SC_REPR_TIMER_FLAGS                                                  /* flags */ 
#define __NR32ATR2_clock_nanosleep_time64       SC_REPR_STRUCT_TIMESPECX32_64                                        /* requested_time */ 
#define __NR32ATR3_clock_nanosleep_time64       SC_REPR_POINTER                                                      /* remaining */ 
#define __NR32RTR_clock_nanosleep_time64        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timer_gettime64              SC_REPR_TIMER_T                                                      /* timerid */ 
#define __NR32ATR1_timer_gettime64              SC_REPR_POINTER                                                      /* value */ 
#define __NR32RTR_timer_gettime64               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timer_settime64              SC_REPR_TIMER_T                                                      /* timerid */ 
#define __NR32ATR1_timer_settime64              SC_REPR_TIMER_FLAGS                                                  /* flags */ 
#define __NR32ATR2_timer_settime64              SC_REPR_STRUCT_ITIMERSPECX32_64                                      /* value */ 
#define __NR32ATR3_timer_settime64              SC_REPR_POINTER                                                      /* ovalue */ 
#define __NR32RTR_timer_settime64               SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timerfd_gettime64            SC_REPR_FD_T                                                         /* timerfd */ 
#define __NR32ATR1_timerfd_gettime64            SC_REPR_POINTER                                                      /* otmr */ 
#define __NR32RTR_timerfd_gettime64             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_timerfd_settime64            SC_REPR_FD_T                                                         /* timerfd */ 
#define __NR32ATR1_timerfd_settime64            SC_REPR_TIMERFD_TIMER_FLAGS                                          /* flags */ 
#define __NR32ATR2_timerfd_settime64            SC_REPR_STRUCT_ITIMERSPECX32_64                                      /* utmr */ 
#define __NR32ATR3_timerfd_settime64            SC_REPR_POINTER                                                      /* otmr */ 
#define __NR32RTR_timerfd_settime64             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_utimensat_time64             SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_utimensat_time64             SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_utimensat_time64             0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_utimensat_time64             SC_REPR_STRUCT_TIMESPECX32_64_VEC2_OR_3                              /* times */ 
#define __NR32ATL2_utimensat_time64             3                                                                    /* times -> flags */ 
#define __NR32ATR3_utimensat_time64             SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__CHANGE_CTIME__DOSPATH              /* flags */ 
#define __NR32RTR_utimensat_time64              SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pselect6_time64              SC_REPR_SIZE_T                                                       /* nfds */ 
#define __NR32ATR1_pselect6_time64              SC_REPR_STRUCT_FDSET                                                 /* readfds */ 
#define __NR32ATL1_pselect6_time64              0                                                                    /* readfds -> nfds */ 
#define __NR32ATR2_pselect6_time64              SC_REPR_STRUCT_FDSET                                                 /* writefds */ 
#define __NR32ATL2_pselect6_time64              0                                                                    /* writefds -> nfds */ 
#define __NR32ATR3_pselect6_time64              SC_REPR_STRUCT_FDSET                                                 /* exceptfds */ 
#define __NR32ATL3_pselect6_time64              0                                                                    /* exceptfds -> nfds */ 
#define __NR32ATR4_pselect6_time64              SC_REPR_STRUCT_TIMESPECX32_64                                        /* timeout */ 
#define __NR32ATR5_pselect6_time64              SC_REPR_STRUCT_SIGSET_WITH_SIZE_X32                                  /* sigmask_sigset_with_size */ 
#define __NR32RTR_pselect6_time64               SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_ppoll_time64                 SC_REPR_STRUCT_POLLFD                                                /* fds */ 
#define __NR32ATL0_ppoll_time64                 1                                                                    /* fds -> nfds */ 
#define __NR32ATR1_ppoll_time64                 SC_REPR_SIZE_T                                                       /* nfds */ 
#define __NR32ATR2_ppoll_time64                 SC_REPR_STRUCT_TIMESPECX32_64                                        /* timeout_ts */ 
#define __NR32ATR3_ppoll_time64                 SC_REPR_STRUCT_SIGSET                                                /* sigmask */ 
#define __NR32ATL3_ppoll_time64                 4                                                                    /* sigmask -> sigsetsize */ 
#define __NR32ATR4_ppoll_time64                 SC_REPR_SIZE_T                                                       /* sigsetsize */ 
#define __NR32RTR_ppoll_time64                  SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_io_pgetevents_time64         SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_pgetevents_time64          SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_recvmmsg_time64              SC_REPR_FD_T                                                         /* sockfd */ 
#define __NR32ATR1_recvmmsg_time64              SC_REPR_POINTER                                                      /* vmessages */ 
#define __NR32ATR2_recvmmsg_time64              SC_REPR_SIZE_T                                                       /* vlen */ 
#define __NR32ATR3_recvmmsg_time64              SC_REPR_SOCKET_RECVMSG_FLAGS3                                        /* msg_flags */ 
#define __NR32ATR4_recvmmsg_time64              SC_REPR_STRUCT_TIMESPECX32_64                                        /* tmo */ 
#define __NR32RTR_recvmmsg_time64               SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_mq_timedsend_time64          SC_REPR_FD_T                                                         /* mqdes */ 
#define __NR32ATR1_mq_timedsend_time64          SC_REPR_BUFFER                                                       /* msg_ptr */ 
#define __NR32ATL1_mq_timedsend_time64          2                                                                    /* msg_ptr -> msg_len */ 
#define __NR32ATR2_mq_timedsend_time64          SC_REPR_SIZE_T                                                       /* msg_len */ 
#define __NR32ATR3_mq_timedsend_time64          SC_REPR_UINT32_T                                                     /* msg_prio */ 
#define __NR32ATR4_mq_timedsend_time64          SC_REPR_STRUCT_TIMESPECX32_64                                        /* abs_timeout */ 
#define __NR32RTR_mq_timedsend_time64           SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mq_timedreceive_time64       SC_REPR_FD_T                                                         /* mqdes */ 
#define __NR32ATR1_mq_timedreceive_time64       SC_REPR_POINTER                                                      /* msg_ptr */ 
#define __NR32ATR2_mq_timedreceive_time64       SC_REPR_SIZE_T                                                       /* msg_len */ 
#define __NR32ATR3_mq_timedreceive_time64       SC_REPR_POINTER                                                      /* pmsg_prio */ 
#define __NR32ATR4_mq_timedreceive_time64       SC_REPR_STRUCT_TIMESPECX32_64                                        /* abs_timeout */ 
#define __NR32RTR_mq_timedreceive_time64        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_semtimedop_time64            SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_semtimedop_time64             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_rt_sigtimedwait_time64       SC_REPR_STRUCT_SIGSET                                                /* set */ 
#define __NR32ATL0_rt_sigtimedwait_time64       3                                                                    /* set -> sigsetsize */ 
#define __NR32ATR1_rt_sigtimedwait_time64       SC_REPR_POINTER                                                      /* info */ 
#define __NR32ATR2_rt_sigtimedwait_time64       SC_REPR_STRUCT_TIMESPECX32_64                                        /* timeout */ 
#define __NR32ATR3_rt_sigtimedwait_time64       SC_REPR_SIZE_T                                                       /* sigsetsize */ 
#define __NR32RTR_rt_sigtimedwait_time64        SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_futex_time64                 SC_REPR_POINTER                                                      /* uaddr */ 
#define __NR32ATR1_futex_time64                 SC_REPR_FUTEX_OP                                                     /* futex_op */ 
#define __NR32ATR2_futex_time64                 SC_REPR_UINT32_T                                                     /* val */ 
#define __NR32ATR3_futex_time64                 SC_REPR_STRUCT_TIMESPECX32_64_OR_UINT32                              /* timeout_or_val2 */ 
#define __NR32ATL3_futex_time64                 1                                                                    /* timeout_or_val2 -> futex_op */ 
#define __NR32ATR4_futex_time64                 SC_REPR_POINTER                                                      /* uaddr2 */ 
#define __NR32ATR5_futex_time64                 SC_REPR_UINT32_T                                                     /* val3 */ 
#define __NR32RTR_futex_time64                  SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_sched_rr_get_interval_time64 SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_sched_rr_get_interval_time64 SC_REPR_POINTER                                                      /* ts */ 
#define __NR32RTR_sched_rr_get_interval_time64  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pidfd_send_signal            SC_REPR_FD_T                                                         /* pidfd */ 
#define __NR32ATR1_pidfd_send_signal            SC_REPR_SIGNO_T                                                      /* usigno */ 
#define __NR32ATR2_pidfd_send_signal            SC_REPR_POINTER                                                      /* uinfo */ 
#define __NR32ATR3_pidfd_send_signal            SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_pidfd_send_signal             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_io_uring_setup               SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_uring_setup                SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_io_uring_enter               SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_uring_enter                SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_io_uring_register            SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_io_uring_register             SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_open_tree                    SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_open_tree                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_move_mount                   SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_move_mount                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fsopen                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_fsopen                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fsconfig                     SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_fsconfig                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fsmount                      SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_fsmount                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fspick                       SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_fspick                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pidfd_open                   SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_pidfd_open                   SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_pidfd_open                    SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_clone3                       SC_REPR_STRUCT_CLONE_ARGS                                            /* cl_args */ 
#define __NR32ATL0_clone3                       1                                                                    /* cl_args -> size */ 
#define __NR32ATR1_clone3                       SC_REPR_SIZE_T                                                       /* size */ 
#define __NR32RTR_clone3                        SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_close_range                  SC_REPR_UNSIGNED_INT                                                 /* minfd */ 
#define __NR32ATR1_close_range                  SC_REPR_UNSIGNED_INT                                                 /* maxfd */ 
#define __NR32ATR2_close_range                  SC_REPR_CLOSE_RANGE_FLAGS                                            /* flags */ 
#define __NR32RTR_close_range                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_openat2                      SC_REPR_INT                                                          /* TODO_PROTOTYPE */ 
#define __NR32RTR_openat2                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pidfd_getfd                  SC_REPR_FD_T                                                         /* pidfd */ 
#define __NR32ATR1_pidfd_getfd                  SC_REPR_FD_T                                                         /* foreign_fd */ 
#define __NR32ATR2_pidfd_getfd                  SC_REPR_SYSCALL_ULONG_T                                              /* flags */ 
#define __NR32RTR_pidfd_getfd                   SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_faccessat2                   SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_faccessat2                   SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_faccessat2                   0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_faccessat2                   SC_REPR_ACCESS_TYPE                                                  /* type */ 
#define __NR32ATR3_faccessat2                   SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__EACCESS__DOSPATH                   /* flags */ 
#define __NR32RTR_faccessat2                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pwritevf                     SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_pwritevf                     SC_REPR_STRUCT_IOVECX32_C                                            /* iovec */ 
#define __NR32ATL1_pwritevf                     2                                                                    /* iovec -> count */ 
#define __NR32ATR2_pwritevf                     SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR3_pwritevf                     SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32ATR4_pwritevf                     SC_REPR_IOMODE_T                                                     /* mode */ 
#define __NR32RTR_pwritevf                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_preadvf                      SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_preadvf                      SC_REPR_STRUCT_IOVECX32                                              /* iovec */ 
#define __NR32ATL1_preadvf                      2                                                                    /* iovec -> count */ 
#define __NR32ATR2_preadvf                      SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR3_preadvf                      SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32ATR4_preadvf                      SC_REPR_IOMODE_T                                                     /* mode */ 
#define __NR32RTR_preadvf                       SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_fallocate64                  SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_fallocate64                  SC_REPR_FALLOCATE_MODE                                               /* mode */ 
#define __NR32ATR2_fallocate64                  SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32ATR3_fallocate64                  SC_REPR_UINT64_T                                                     /* length */ 
#define __NR32RTR_fallocate64                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_freadlinkat                  SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_freadlinkat                  SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATL1_freadlinkat                  0                                                                    /* path -> dirfd */ 
#define __NR32ATR2_freadlinkat                  SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR3_freadlinkat                  SC_REPR_SIZE_T                                                       /* buflen */ 
#define __NR32ATR4_freadlinkat                  SC_REPR_ATFLAG__READLINK_REQSIZE__DOSPATH                            /* flags */ 
#define __NR32RTR_freadlinkat                   SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_fsymlinkat                   SC_REPR_STRING                                                       /* link_text */ 
#define __NR32ATR1_fsymlinkat                   SC_REPR_FD_T                                                         /* tofd */ 
#define __NR32ATR2_fsymlinkat                   SC_REPR_FILENAME                                                     /* target_path */ 
#define __NR32ATL2_fsymlinkat                   1                                                                    /* target_path -> tofd */ 
#define __NR32ATR3_fsymlinkat                   SC_REPR_ATFLAG__DOSPATH                                              /* flags */ 
#define __NR32RTR_fsymlinkat                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_kfstatat                     SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_kfstatat                     SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_kfstatat                     0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_kfstatat                     SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32ATR3_kfstatat                     SC_REPR_ATFLAG__SYMLINK_NOFOLLOW__DOSPATH                            /* flags */ 
#define __NR32RTR_kfstatat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_futimesat64                  SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_futimesat64                  SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_futimesat64                  0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_futimesat64                  SC_REPR_STRUCT_TIMEVALX32_64_VEC2                                    /* times */ 
#define __NR32RTR_futimesat64                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fmknodat                     SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_fmknodat                     SC_REPR_FILENAME                                                     /* nodename */ 
#define __NR32ATL1_fmknodat                     0                                                                    /* nodename -> dirfd */ 
#define __NR32ATR2_fmknodat                     SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32ATR3_fmknodat                     SC_REPR_DEV_T                                                        /* dev */ 
#define __NR32ATL3_fmknodat                     2                                                                    /* dev -> mode */ 
#define __NR32ATR4_fmknodat                     SC_REPR_ATFLAG__DOSPATH                                              /* flags */ 
#define __NR32RTR_fmknodat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fmkdirat                     SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_fmkdirat                     SC_REPR_FILENAME                                                     /* pathname */ 
#define __NR32ATL1_fmkdirat                     0                                                                    /* pathname -> dirfd */ 
#define __NR32ATR2_fmkdirat                     SC_REPR_MODE_T                                                       /* mode */ 
#define __NR32ATR3_fmkdirat                     SC_REPR_ATFLAG__DOSPATH                                              /* flags */ 
#define __NR32RTR_fmkdirat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_waitid64                     SC_REPR_IDTYPE_T                                                     /* idtype */ 
#define __NR32ATR1_waitid64                     SC_REPR_ID_T                                                         /* id */ 
#define __NR32ATL1_waitid64                     0                                                                    /* id -> idtype */ 
#define __NR32ATR2_waitid64                     SC_REPR_POINTER                                                      /* infop */ 
#define __NR32ATR3_waitid64                     SC_REPR_WAITFLAGS                                                    /* options */ 
#define __NR32ATR4_waitid64                     SC_REPR_POINTER                                                      /* ru */ 
#define __NR32RTR_waitid64                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_utimes64                     SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_utimes64                     SC_REPR_STRUCT_TIMEVALX32_64_VEC2                                    /* times */ 
#define __NR32RTR_utimes64                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_kreaddirf                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_kreaddirf                    SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_kreaddirf                    SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_kreaddirf                    SC_REPR_KREADDIR_MODE                                                /* mode */ 
#define __NR32ATR4_kreaddirf                    SC_REPR_IOMODE_T                                                     /* iomode */ 
#define __NR32RTR_kreaddirf                     SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_kfstat                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_kfstat                       SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_kfstat                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_klstat                       SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_klstat                       SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_klstat                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_kstat                        SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_kstat                        SC_REPR_POINTER                                                      /* statbuf */ 
#define __NR32RTR_kstat                         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_pwrite64f                    SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_pwrite64f                    SC_REPR_BUFFER                                                       /* buf */ 
#define __NR32ATL1_pwrite64f                    2                                                                    /* buf -> bufsize */ 
#define __NR32ATR2_pwrite64f                    SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_pwrite64f                    SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32ATR4_pwrite64f                    SC_REPR_IOMODE_T                                                     /* mode */ 
#define __NR32RTR_pwrite64f                     SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_pread64f                     SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_pread64f                     SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_pread64f                     SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_pread64f                     SC_REPR_UINT64_T                                                     /* offset */ 
#define __NR32ATR4_pread64f                     SC_REPR_IOMODE_T                                                     /* mode */ 
#define __NR32RTR_pread64f                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_ksigreturn                   SC_REPR_STRUCT_FPUSTATE32                                            /* restore_fpu */ 
#define __NR32ATR1_ksigreturn                   SC_REPR_SYSCALL_ULONG_T                                              /* unused1 */ 
#define __NR32ATR2_ksigreturn                   SC_REPR_SYSCALL_ULONG_T                                              /* unused2 */ 
#define __NR32ATR3_ksigreturn                   SC_REPR_STRUCT_SIGSET_WITH_SIZE_X32                                  /* restore_sigmask */ 
#define __NR32ATR4_ksigreturn                   SC_REPR_STRUCT_RPC_SYSCALL_INFO32                                    /* sc_info */ 
#define __NR32ATR5_ksigreturn                   SC_REPR_STRUCT_UCPUSTATE32                                           /* restore_cpu */ 
#define __NR32RTR_ksigreturn                    SC_REPR_SIGNO_T                                                      /* return */
#define __NR32ATR0_nanosleep64                  SC_REPR_STRUCT_TIMESPECX32_64                                        /* req */ 
#define __NR32ATR1_nanosleep64                  SC_REPR_POINTER                                                      /* rem */ 
#define __NR32RTR_nanosleep64                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_rpc_serve                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_ksysctl                      SC_REPR_KSYSCTL_COMMAND                                              /* command */ 
#define __NR32ATR1_ksysctl                      SC_REPR_KSYSCTL_ARG                                                  /* arg */ 
#define __NR32ATL1_ksysctl                      0                                                                    /* arg -> command */ 
#define __NR32RTR_ksysctl                       SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_writevf                      SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_writevf                      SC_REPR_STRUCT_IOVECX32_C                                            /* iovec */ 
#define __NR32ATL1_writevf                      2                                                                    /* iovec -> count */ 
#define __NR32ATR2_writevf                      SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR3_writevf                      SC_REPR_IOMODE_T                                                     /* mode */ 
#define __NR32RTR_writevf                       SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_readvf                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_readvf                       SC_REPR_STRUCT_IOVECX32                                              /* iovec */ 
#define __NR32ATL1_readvf                       2                                                                    /* iovec -> count */ 
#define __NR32ATR2_readvf                       SC_REPR_SIZE_T                                                       /* count */ 
#define __NR32ATR3_readvf                       SC_REPR_IOMODE_T                                                     /* mode */ 
#define __NR32RTR_readvf                        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_kreaddir                     SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_kreaddir                     SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_kreaddir                     SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_kreaddir                     SC_REPR_KREADDIR_MODE                                                /* mode */ 
#define __NR32RTR_kreaddir                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_wait4_64                     SC_REPR_PID_T                                                        /* pid */ 
#define __NR32ATR1_wait4_64                     SC_REPR_POINTER                                                      /* stat_loc */ 
#define __NR32ATR2_wait4_64                     SC_REPR_WAITFLAGS                                                    /* options */ 
#define __NR32ATR3_wait4_64                     SC_REPR_POINTER                                                      /* usage */ 
#define __NR32RTR_wait4_64                      SC_REPR_PID_T                                                        /* return */
#define __NR32ATR0_getitimer64                  SC_REPR_ITIMER_WHICH                                                 /* which */ 
#define __NR32ATR1_getitimer64                  SC_REPR_POINTER                                                      /* curr_value */ 
#define __NR32RTR_getitimer64                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_setitimer64                  SC_REPR_ITIMER_WHICH                                                 /* which */ 
#define __NR32ATR1_setitimer64                  SC_REPR_STRUCT_ITIMERVALX64                                          /* newval */ 
#define __NR32ATR2_setitimer64                  SC_REPR_POINTER                                                      /* oldval */ 
#define __NR32RTR_setitimer64                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_maplibrary                   SC_REPR_POINTER                                                      /* addr */ 
#define __NR32ATR1_maplibrary                   SC_REPR_MMAP_FLAGS                                                   /* flags */ 
#define __NR32ATR2_maplibrary                   SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR3_maplibrary                   SC_REPR_STRUCT_ELF_PHDR32_VECTOR                                     /* hdrv */ 
#define __NR32ATL3_maplibrary                   4                                                                    /* hdrv -> hdrc */ 
#define __NR32ATR4_maplibrary                   SC_REPR_SIZE_T                                                       /* hdrc */ 
#define __NR32RTR_maplibrary                    SC_REPR_POINTER                                                      /* return */
#define __NR32ATR0_select64                     SC_REPR_SIZE_T                                                       /* nfds */ 
#define __NR32ATR1_select64                     SC_REPR_STRUCT_FDSET                                                 /* readfds */ 
#define __NR32ATL1_select64                     0                                                                    /* readfds -> nfds */ 
#define __NR32ATR2_select64                     SC_REPR_STRUCT_FDSET                                                 /* writefds */ 
#define __NR32ATL2_select64                     0                                                                    /* writefds -> nfds */ 
#define __NR32ATR3_select64                     SC_REPR_STRUCT_FDSET                                                 /* exceptfds */ 
#define __NR32ATL3_select64                     0                                                                    /* exceptfds -> nfds */ 
#define __NR32ATR4_select64                     SC_REPR_STRUCT_TIMEVALX32_64                                         /* timeout */ 
#define __NR32RTR_select64                      SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_settimeofday64               SC_REPR_STRUCT_TIMEVALX32_64                                         /* tv */ 
#define __NR32ATR1_settimeofday64               SC_REPR_STRUCT_TIMEZONE                                              /* tz */ 
#define __NR32RTR_settimeofday64                SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_gettimeofday64               SC_REPR_POINTER                                                      /* tv */ 
#define __NR32ATR1_gettimeofday64               SC_REPR_POINTER                                                      /* tz */ 
#define __NR32RTR_gettimeofday64                SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_getrusage64                  SC_REPR_GETRUSAGE_WHO                                                /* who */ 
#define __NR32ATR1_getrusage64                  SC_REPR_POINTER                                                      /* tv */ 
#define __NR32RTR_getrusage64                   SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_fsmode                       SC_REPR_FSMODE                                                       /* mode */ 
#define __NR32RTR_fsmode                        SC_REPR_FSMODE                                                       /* return */
#define __NR32ATR0_ioctlf                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_ioctlf                       SC_REPR_IOCTL_COMMAND                                                /* command */ 
#define __NR32ATR2_ioctlf                       SC_REPR_IOMODE_T                                                     /* mode */ 
#define __NR32ATR3_ioctlf                       SC_REPR_IOCTL_ARG                                                    /* arg */ 
#define __NR32ATL3_ioctlf                       1                                                                    /* arg -> command */ 
#define __NR32RTR_ioctlf                        SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32RTR_rtm_test                      SC_REPR_SYSCALL_ULONG_T                                              /* return */
#define __NR32ATR0_rtm_abort                    SC_REPR_SYSCALL_ULONG_T                                              /* code */ 
#define __NR32RTR_rtm_abort                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_rtm_end                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_rtm_begin                     SC_REPR_SIGNO_T                                                      /* return */
#define __NR32ATR0_ftime64                      SC_REPR_POINTER                                                      /* tp */ 
#define __NR32RTR_ftime64                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32RTR_rpc_serve_sysret              SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_set_userprocmask_address     SC_REPR_POINTER                                                      /* ctl */ 
#define __NR32RTR_set_userprocmask_address      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_utime64                      SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATR1_utime64                      SC_REPR_STRUCT_UTIMBUFX32_64                                         /* times */ 
#define __NR32RTR_utime64                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_userviofd                    SC_REPR_SIZE_T                                                       /* initial_size */ 
#define __NR32ATR1_userviofd                    SC_REPR_OFLAG__CLOEXEC__CLOFORK__NONBLOCK                            /* flags */ 
#define __NR32RTR_userviofd                     SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_stime64                      SC_REPR_TIME64_T_PTR                                                 /* t */ 
#define __NR32RTR_stime64                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_coredump                     SC_REPR_STRUCT_UCPUSTATE32                                           /* curr_state */ 
#define __NR32ATR1_coredump                     SC_REPR_STRUCT_UCPUSTATE32                                           /* orig_state */ 
#define __NR32ATR2_coredump                     SC_REPR_VOID_VECTOR32                                                /* traceback_vector */ 
#define __NR32ATL2_coredump                     3                                                                    /* traceback_vector -> traceback_length */ 
#define __NR32ATR3_coredump                     SC_REPR_SIZE_T                                                       /* traceback_length */ 
#define __NR32ATR4_coredump                     SC_REPR_STRUCT_EXCEPTION_DATA32                                      /* reason */ 
#define __NR32ATR5_coredump                     SC_REPR_UNWIND_ERROR                                                 /* unwind_error */ 
#define __NR32RTR_coredump                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_mktty                        SC_REPR_STRING                                                       /* name */ 
#define __NR32ATR1_mktty                        SC_REPR_FD_T                                                         /* keyboard */ 
#define __NR32ATR2_mktty                        SC_REPR_FD_T                                                         /* display */ 
#define __NR32ATR3_mktty                        SC_REPR_SYSCALL_ULONG_T                                              /* rsvd */ 
#define __NR32RTR_mktty                         SC_REPR_FD_T                                                         /* return */
#define __NR32ATR0_lfutexexpr                   SC_REPR_POINTER                                                      /* futexaddr */ 
#define __NR32ATR1_lfutexexpr                   SC_REPR_POINTER                                                      /* base */ 
#define __NR32ATR2_lfutexexpr                   SC_REPR_STRUCT_LFUTEXEXPRX32_VECTOR                                  /* expr */ 
#define __NR32ATR3_lfutexexpr                   SC_REPR_STRUCT_TIMESPECX32_64                                        /* timeout */ 
#define __NR32ATR4_lfutexexpr                   SC_REPR_LFUTEX_TIMEOUT_FLAGS                                         /* flags */ 
#define __NR32RTR_lfutexexpr                    SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_lseek64                      SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_lseek64                      SC_REPR_INT64_T                                                      /* offset */ 
#define __NR32ATR2_lseek64                      SC_REPR_SEEK_WHENCE                                                  /* whence */ 
#define __NR32RTR_lseek64                       SC_REPR_INT64_T                                                      /* return */
#define __NR32ATR0_lfutex                       SC_REPR_POINTER                                                      /* uaddr */ 
#define __NR32ATR1_lfutex                       SC_REPR_LFUTEX_OP                                                    /* futex_op */ 
#define __NR32ATR2_lfutex                       SC_REPR_UINT32_T                                                     /* val */ 
#define __NR32ATR3_lfutex                       SC_REPR_STRUCT_TIMESPECX32_64                                        /* timeout */ 
#define __NR32ATR4_lfutex                       SC_REPR_UINT32_T                                                     /* val2 */ 
#define __NR32RTR_lfutex                        SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_debugtrap                    SC_REPR_STRUCT_UCPUSTATE32                                           /* state */ 
#define __NR32ATR1_debugtrap                    SC_REPR_STRUCT_DEBUGTRAP_REASON32                                    /* reason */ 
#define __NR32RTR_debugtrap                     SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_get_exception_handler        SC_REPR_POINTER                                                      /* pmode */ 
#define __NR32ATR1_get_exception_handler        SC_REPR_POINTER                                                      /* phandler */ 
#define __NR32ATR2_get_exception_handler        SC_REPR_POINTER                                                      /* phandler_sp */ 
#define __NR32RTR_get_exception_handler         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_set_exception_handler        SC_REPR_EXCEPTION_HANDLER_MODE                                       /* mode */ 
#define __NR32ATR1_set_exception_handler        SC_REPR_EXCEPT_HANDLER_T                                             /* handler */ 
#define __NR32ATR2_set_exception_handler        SC_REPR_EXCEPTION_HANDLER_SP                                         /* handler_sp */ 
#define __NR32ATL2_set_exception_handler        0                                                                    /* handler_sp -> mode */ 
#define __NR32RTR_set_exception_handler         SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_time64                       SC_REPR_POINTER                                                      /* timer */ 
#define __NR32RTR_time64                        SC_REPR_TIME_T                                                       /* return */
#define __NR32ATR0_fchdirat                     SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_fchdirat                     SC_REPR_FILENAME                                                     /* path */ 
#define __NR32ATL1_fchdirat                     0                                                                    /* path -> dirfd */ 
#define __NR32ATR2_fchdirat                     SC_REPR_ATFLAG__DOSPATH                                              /* flags */ 
#define __NR32RTR_fchdirat                      SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_openpty                      SC_REPR_POINTER                                                      /* amaster */ 
#define __NR32ATR1_openpty                      SC_REPR_POINTER                                                      /* aslave */ 
#define __NR32ATR2_openpty                      SC_REPR_POINTER                                                      /* name */ 
#define __NR32ATR3_openpty                      SC_REPR_STRUCT_TERMIOS                                               /* termp */ 
#define __NR32ATR4_openpty                      SC_REPR_STRUCT_WINSIZE                                               /* winp */ 
#define __NR32RTR_openpty                       SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_rpc_schedule                 SC_REPR_PID_T                                                        /* target_tid */ 
#define __NR32ATR1_rpc_schedule                 SC_REPR_RPC_SCHEDULE_MODE                                            /* mode */ 
#define __NR32ATR2_rpc_schedule                 SC_REPR_POINTER                                                      /* program */ 
#define __NR32ATR3_rpc_schedule                 SC_REPR_VOID_VECTOR32                                                /* params */ 
#define __NR32ATL3_rpc_schedule                 4                                                                    /* params -> max_param_count */ 
#define __NR32ATR4_rpc_schedule                 SC_REPR_SIZE_T                                                       /* max_param_count */ 
#define __NR32RTR_rpc_schedule                  SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_frealpathat                  SC_REPR_FD_T                                                         /* dirfd */ 
#define __NR32ATR1_frealpathat                  SC_REPR_FILENAME                                                     /* filename */ 
#define __NR32ATL1_frealpathat                  0                                                                    /* filename -> dirfd */ 
#define __NR32ATR2_frealpathat                  SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR3_frealpathat                  SC_REPR_SIZE_T                                                       /* buflen */ 
#define __NR32ATR4_frealpathat                  SC_REPR_ATFLAG__ALTPATH__SYMLINK_NOFOLLOW__READLINK_REQSIZE__DOSPATH /* flags */ 
#define __NR32RTR_frealpathat                   SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_frealpath4                   SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_frealpath4                   SC_REPR_POINTER                                                      /* resolved */ 
#define __NR32ATR2_frealpath4                   SC_REPR_SIZE_T                                                       /* buflen */ 
#define __NR32ATR3_frealpath4                   SC_REPR_ATFLAG__ALTPATH__READLINK_REQSIZE__DOSPATH                   /* flags */ 
#define __NR32RTR_frealpath4                    SC_REPR_SSIZE_T                                                      /* return */
#define __NR32RTR_getdrives                     SC_REPR_SYSCALL_SLONG_T                                              /* return */
#define __NR32ATR0_detach                       SC_REPR_PID_T                                                        /* pid */ 
#define __NR32RTR_detach                        SC_REPR_ERRNO_T                                                      /* return */
#define __NR32ATR0_writef                       SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_writef                       SC_REPR_BUFFER                                                       /* buf */ 
#define __NR32ATL1_writef                       2                                                                    /* buf -> bufsize */ 
#define __NR32ATR2_writef                       SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_writef                       SC_REPR_IOMODE_T                                                     /* mode */ 
#define __NR32RTR_writef                        SC_REPR_SSIZE_T                                                      /* return */
#define __NR32ATR0_readf                        SC_REPR_FD_T                                                         /* fd */ 
#define __NR32ATR1_readf                        SC_REPR_POINTER                                                      /* buf */ 
#define __NR32ATR2_readf                        SC_REPR_SIZE_T                                                       /* bufsize */ 
#define __NR32ATR3_readf                        SC_REPR_IOMODE_T                                                     /* mode */ 
#define __NR32RTR_readf                         SC_REPR_SSIZE_T                                                      /* return */
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_FORMAT */
#endif /* __WANT_SYSCALL_ARGUMENT_FORMAT */


/************************************************************************/
/* SYSCALL ARGUMENT DOUBLE WIDE                                         */
/************************************************************************/
#ifdef __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE
#ifndef __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE
#define __NR32FEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE
#define __NR32DW1__llseek
#define __NR32DW3_pread64
#define __NR32DW3_pwrite64
#define __NR32DW1_truncate64
#define __NR32DW1_ftruncate64
#define __NR32DW1_readahead
#define __NR32DW1_sync_file_range
#define __NR32DW2_sync_file_range
#define __NR32DW3_preadv
#define __NR32DW3_pwritev
#define __NR32DW3_pwritevf
#define __NR32DW3_preadvf
#define __NR32DW2_fallocate64
#define __NR32DW3_fallocate64
#define __NR32DW3_pwrite64f
#define __NR32DW3_pread64f
#define __NR32DW0_fsmode
#define __NR32DW1_lseek64
#endif /* !__NR32FEAT_DEFINED_SYSCALL_ARGUMENT_DOUBLE_WIDE */
#endif /* __WANT_SYSCALL_ARGUMENT_DOUBLE_WIDE */

