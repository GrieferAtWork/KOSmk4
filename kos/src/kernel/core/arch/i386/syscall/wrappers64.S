/* HASH CRC-32:0x47c3c63a */
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

#include <hybrid/compiler.h>
#include <kernel/paging.h>
#include <kernel/syscall.h>
#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/interrupt.h>
#include <sys/syscall.h>
#include <kos/kernel/cpu-state.h>


EXTERN(sys_read)
EXTERN(sys_write)
EXTERN(sys_open)
EXTERN(sys_close)
EXTERN(sys_linux_stat64)
EXTERN(sys_linux_fstat64)
EXTERN(sys_linux_lstat64)
EXTERN(sys_poll)
EXTERN(sys_lseek64)
EXTERN(sys_mmap)
EXTERN(sys_mprotect)
EXTERN(sys_munmap)
EXTERN(sys_brk)
EXTERN(sys_rt_sigaction)
EXTERN(sys_rt_sigprocmask)
EXTERN(sys_rt_sigreturn)
EXTERN(sys_ioctl)
EXTERN(sys_pread64)
EXTERN(sys_pwrite64)
EXTERN(sys_readv)
EXTERN(sys_writev)
EXTERN(sys_access)
EXTERN(sys_pipe)
EXTERN(sys_select)
EXTERN(sys_sched_yield)
EXTERN(sys_mremap)
EXTERN(sys_msync)
EXTERN(sys_mincore)
EXTERN(sys_madvise)
EXTERN(sys_dup)
EXTERN(sys_dup2)
EXTERN(sys_pause)
EXTERN(sys_nanosleep)
EXTERN(sys_getitimer)
EXTERN(sys_alarm)
EXTERN(sys_setitimer)
EXTERN(sys_getpid)
EXTERN(sys_sendfile)
EXTERN(sys_socket)
EXTERN(sys_connect)
EXTERN(sys_sendto)
EXTERN(sys_recvfrom)
EXTERN(sys_sendmsg)
EXTERN(sys_recvmsg)
EXTERN(sys_shutdown)
EXTERN(sys_bind)
EXTERN(sys_listen)
EXTERN(sys_getsockname)
EXTERN(sys_getpeername)
EXTERN(sys_socketpair)
EXTERN(sys_setsockopt)
EXTERN(sys_getsockopt)
EXTERN(sys_clone)
EXTERN(sys_fork)
EXTERN(sys_vfork)
EXTERN(sys_execve)
EXTERN(sys_exit)
EXTERN(sys_wait4)
EXTERN(sys_kill)
EXTERN(sys_uname)
EXTERN(sys_fcntl)
EXTERN(sys_flock)
EXTERN(sys_fsync)
EXTERN(sys_fdatasync)
EXTERN(sys_truncate)
EXTERN(sys_ftruncate)
EXTERN(sys_getdents)
EXTERN(sys_getcwd)
EXTERN(sys_chdir)
EXTERN(sys_fchdir)
EXTERN(sys_rename)
EXTERN(sys_mkdir)
EXTERN(sys_rmdir)
EXTERN(sys_creat)
EXTERN(sys_link)
EXTERN(sys_unlink)
EXTERN(sys_symlink)
EXTERN(sys_readlink)
EXTERN(sys_chmod)
EXTERN(sys_fchmod)
EXTERN(sys_chown)
EXTERN(sys_fchown)
EXTERN(sys_lchown)
EXTERN(sys_umask)
EXTERN(sys_gettimeofday)
EXTERN(sys_getrlimit)
EXTERN(sys_getrusage)
EXTERN(sys_sysinfo)
EXTERN(sys_times)
EXTERN(sys_ptrace)
EXTERN(sys_getuid32)
EXTERN(sys_syslog)
EXTERN(sys_getgid32)
EXTERN(sys_setuid32)
EXTERN(sys_setgid32)
EXTERN(sys_geteuid32)
EXTERN(sys_getegid32)
EXTERN(sys_setpgid)
EXTERN(sys_getppid)
EXTERN(sys_getpgrp)
EXTERN(sys_setsid)
EXTERN(sys_setreuid32)
EXTERN(sys_setregid32)
EXTERN(sys_getgroups32)
EXTERN(sys_setgroups32)
EXTERN(sys_setresuid32)
EXTERN(sys_getresuid32)
EXTERN(sys_setresgid32)
EXTERN(sys_getresgid32)
EXTERN(sys_getpgid)
EXTERN(sys_setfsuid32)
EXTERN(sys_setfsgid32)
EXTERN(sys_getsid)
EXTERN(sys_rt_sigpending)
EXTERN(sys_rt_sigtimedwait)
EXTERN(sys_rt_sigqueueinfo)
EXTERN(sys_rt_sigsuspend)
EXTERN(sys_sigaltstack)
EXTERN(sys_utime)
EXTERN(sys_mknod)
EXTERN(sys_ustat)
EXTERN(sys_statfs)
EXTERN(sys_fstatfs)
EXTERN(sys_getpriority)
EXTERN(sys_setpriority)
EXTERN(sys_sched_setparam)
EXTERN(sys_sched_getparam)
EXTERN(sys_sched_setscheduler)
EXTERN(sys_sched_getscheduler)
EXTERN(sys_sched_get_priority_max)
EXTERN(sys_sched_get_priority_min)
EXTERN(sys_sched_rr_get_interval)
EXTERN(sys_mlock)
EXTERN(sys_munlock)
EXTERN(sys_mlockall)
EXTERN(sys_munlockall)
EXTERN(sys_vhangup)
EXTERN(sys_modify_ldt)
EXTERN(sys_setrlimit)
EXTERN(sys_chroot)
EXTERN(sys_sync)
EXTERN(sys_acct)
EXTERN(sys_settimeofday)
EXTERN(sys_mount)
EXTERN(sys_umount2)
EXTERN(sys_swapon)
EXTERN(sys_swapoff)
EXTERN(sys_reboot)
EXTERN(sys_sethostname)
EXTERN(sys_setdomainname)
EXTERN(sys_iopl)
EXTERN(sys_ioperm)
EXTERN(sys_gettid)
EXTERN(sys_readahead)
EXTERN(sys_setxattr)
EXTERN(sys_lsetxattr)
EXTERN(sys_fsetxattr)
EXTERN(sys_getxattr)
EXTERN(sys_lgetxattr)
EXTERN(sys_fgetxattr)
EXTERN(sys_listxattr)
EXTERN(sys_llistxattr)
EXTERN(sys_flistxattr)
EXTERN(sys_removexattr)
EXTERN(sys_lremovexattr)
EXTERN(sys_fremovexattr)
EXTERN(sys_tkill)
EXTERN(sys_time)
EXTERN(sys_futex)
EXTERN(sys_sched_setaffinity)
EXTERN(sys_sched_getaffinity)
EXTERN(sys_epoll_create)
EXTERN(sys_epoll_ctl_old)
EXTERN(sys_epoll_wait_old)
EXTERN(sys_remap_file_pages)
EXTERN(sys_getdents64)
EXTERN(sys_set_tid_address)
EXTERN(sys_timer_create)
EXTERN(sys_timer_settime)
EXTERN(sys_timer_gettime)
EXTERN(sys_timer_getoverrun)
EXTERN(sys_timer_delete)
EXTERN(sys_clock_settime)
EXTERN(sys_clock_gettime)
EXTERN(sys_clock_getres)
EXTERN(sys_clock_nanosleep)
EXTERN(sys_exit_group)
EXTERN(sys_epoll_wait)
EXTERN(sys_epoll_ctl)
EXTERN(sys_tgkill)
EXTERN(sys_utimes)
EXTERN(sys_waitid)
EXTERN(sys_ioprio_set)
EXTERN(sys_ioprio_get)
EXTERN(sys_openat)
EXTERN(sys_mkdirat)
EXTERN(sys_mknodat)
EXTERN(sys_fchownat)
EXTERN(sys_futimesat)
EXTERN(sys_fstatat)
EXTERN(sys_unlinkat)
EXTERN(sys_renameat)
EXTERN(sys_linkat)
EXTERN(sys_symlinkat)
EXTERN(sys_readlinkat)
EXTERN(sys_fchmodat)
EXTERN(sys_faccessat)
EXTERN(sys_pselect6)
EXTERN(sys_ppoll)
EXTERN(sys_unshare)
EXTERN(sys_splice)
EXTERN(sys_tee)
EXTERN(sys_sync_file_range)
EXTERN(sys_vmsplice)
EXTERN(sys_utimensat)
EXTERN(sys_epoll_pwait)
EXTERN(sys_signalfd)
EXTERN(sys_timerfd_create)
EXTERN(sys_eventfd)
EXTERN(sys_fallocate)
EXTERN(sys_timerfd_settime)
EXTERN(sys_timerfd_gettime)
EXTERN(sys_accept4)
EXTERN(sys_signalfd4)
EXTERN(sys_eventfd2)
EXTERN(sys_epoll_create1)
EXTERN(sys_dup3)
EXTERN(sys_pipe2)
EXTERN(sys_preadv)
EXTERN(sys_pwritev)
EXTERN(sys_rt_tgsigqueueinfo)
EXTERN(sys_recvmmsg)
EXTERN(sys_prlimit64)
EXTERN(sys_name_to_handle_at)
EXTERN(sys_open_by_handle_at)
EXTERN(sys_syncfs)
EXTERN(sys_sendmmsg)
EXTERN(sys_setns)
EXTERN(sys_getcpu)
EXTERN(sys_process_vm_readv)
EXTERN(sys_process_vm_writev)
EXTERN(sys_kcmp)
EXTERN(sys_renameat2)
EXTERN(sys_execveat)
EXTERN(sys_readf)
EXTERN(sys_writef)
EXTERN(sys_hop)
EXTERN(sys_hopf)
EXTERN(sys_kstat)
EXTERN(sys_kfstat)
EXTERN(sys_klstat)
EXTERN(sys_detach)
EXTERN(sys_getdrives)
EXTERN(sys_frealpath4)
EXTERN(sys_frealpathat)
EXTERN(sys_rpc_schedule)
EXTERN(sys_sysctl)
EXTERN(sys_openpty)
EXTERN(sys_set_exception_handler)
EXTERN(sys_get_exception_handler)
EXTERN(sys_ioctlf)
EXTERN(sys_pread64f)
EXTERN(sys_pwrite64f)
EXTERN(sys_readvf)
EXTERN(sys_writevf)
EXTERN(sys_set_library_listdef)
EXTERN(sys_debugtrap)
EXTERN(sys_select64)
EXTERN(sys_rpc_service)
EXTERN(sys_lfutex)
EXTERN(sys_lfutexexpr)
EXTERN(sys_lfutexlockexpr)
EXTERN(sys_mktty)
EXTERN(sys_raiseat)
EXTERN(sys_coredump)
EXTERN(sys_getitimer64)
EXTERN(sys_setitimer64)
EXTERN(sys_kreaddir)
EXTERN(sys_fchdirat)
EXTERN(sys_fsmode)
EXTERN(sys_gettimeofday64)
EXTERN(sys_utime64)
EXTERN(sys_maplibrary)
EXTERN(sys_settimeofday64)
EXTERN(sys_time64)
EXTERN(sys_kreaddirf)
EXTERN(sys_utimes64)
EXTERN(sys_fmkdirat)
EXTERN(sys_fmknodat)
EXTERN(sys_futimesat64)
EXTERN(sys_kfstatat)
EXTERN(sys_frenameat)
EXTERN(sys_fsymlinkat)
EXTERN(sys_freadlinkat)
EXTERN(sys_fallocate64)
EXTERN(sys_preadvf)
EXTERN(sys_pwritevf)



EXTERN(sys32_exit)
EXTERN(sys32_fork)
EXTERN(sys32_read)
EXTERN(sys32_write)
EXTERN(sys32_open)
EXTERN(sys32_close)
EXTERN(sys32_waitpid)
EXTERN(sys32_creat)
EXTERN(sys32_link)
EXTERN(sys32_unlink)
EXTERN(sys32_execve)
EXTERN(sys32_chdir)
EXTERN(sys32_time)
EXTERN(sys32_mknod)
EXTERN(sys32_chmod)
EXTERN(sys32_lchown)
EXTERN(sys32_linux_oldstat)
EXTERN(sys32_lseek)
EXTERN(sys32_getpid)
EXTERN(sys32_mount)
EXTERN(sys32_umount)
EXTERN(sys32_setuid)
EXTERN(sys32_getuid)
EXTERN(sys32_stime)
EXTERN(sys32_ptrace)
EXTERN(sys32_alarm)
EXTERN(sys32_linux_oldfstat)
EXTERN(sys32_pause)
EXTERN(sys32_utime)
EXTERN(sys32_access)
EXTERN(sys32_nice)
EXTERN(sys32_ftime)
EXTERN(sys32_sync)
EXTERN(sys32_kill)
EXTERN(sys32_rename)
EXTERN(sys32_mkdir)
EXTERN(sys32_rmdir)
EXTERN(sys32_dup)
EXTERN(sys32_pipe)
EXTERN(sys32_times)
EXTERN(sys32_brk)
EXTERN(sys32_setgid)
EXTERN(sys32_getgid)
EXTERN(sys32_signal)
EXTERN(sys32_geteuid)
EXTERN(sys32_getegid)
EXTERN(sys32_acct)
EXTERN(sys32_umount2)
EXTERN(sys32_ioctl)
EXTERN(sys32_fcntl)
EXTERN(sys32_setpgid)
EXTERN(sys32_oldolduname)
EXTERN(sys32_umask)
EXTERN(sys32_chroot)
EXTERN(sys32_ustat)
EXTERN(sys32_dup2)
EXTERN(sys32_getppid)
EXTERN(sys32_getpgrp)
EXTERN(sys32_setsid)
EXTERN(sys32_sigaction)
EXTERN(sys32_sgetmask)
EXTERN(sys32_ssetmask)
EXTERN(sys32_setreuid)
EXTERN(sys32_setregid)
EXTERN(sys32_sigsuspend)
EXTERN(sys32_sigpending)
EXTERN(sys32_sethostname)
EXTERN(sys32_setrlimit)
EXTERN(sys32_getrlimit)
EXTERN(sys32_getrusage)
EXTERN(sys32_gettimeofday)
EXTERN(sys32_settimeofday)
EXTERN(sys32_getgroups)
EXTERN(sys32_setgroups)
EXTERN(sys32_select)
EXTERN(sys32_symlink)
EXTERN(sys32_linux_oldlstat)
EXTERN(sys32_readlink)
EXTERN(sys32_swapon)
EXTERN(sys32_reboot)
EXTERN(sys32_readdir)
EXTERN(sys32_mmap)
EXTERN(sys32_munmap)
EXTERN(sys32_truncate)
EXTERN(sys32_ftruncate)
EXTERN(sys32_fchmod)
EXTERN(sys32_fchown)
EXTERN(sys32_getpriority)
EXTERN(sys32_setpriority)
EXTERN(sys32_profil)
EXTERN(sys32_statfs)
EXTERN(sys32_fstatfs)
EXTERN(sys32_ioperm)
EXTERN(sys32_socketcall)
EXTERN(sys32_syslog)
EXTERN(sys32_setitimer)
EXTERN(sys32_getitimer)
EXTERN(sys32_linux_stat32)
EXTERN(sys32_linux_lstat32)
EXTERN(sys32_linux_fstat32)
EXTERN(sys32_olduname)
EXTERN(sys32_iopl)
EXTERN(sys32_vhangup)
EXTERN(sys32_wait4)
EXTERN(sys32_swapoff)
EXTERN(sys32_sysinfo)
EXTERN(sys32_fsync)
EXTERN(sys32_sigreturn)
EXTERN(sys32_clone)
EXTERN(sys32_setdomainname)
EXTERN(sys32_uname)
EXTERN(sys32_modify_ldt)
EXTERN(sys32_mprotect)
EXTERN(sys32_sigprocmask)
EXTERN(sys32_getpgid)
EXTERN(sys32_fchdir)
EXTERN(sys32_setfsuid)
EXTERN(sys32_setfsgid)
EXTERN(sys32__llseek)
EXTERN(sys32_getdents)
EXTERN(sys32_flock)
EXTERN(sys32_msync)
EXTERN(sys32_readv)
EXTERN(sys32_writev)
EXTERN(sys32_getsid)
EXTERN(sys32_fdatasync)
EXTERN(sys32_mlock)
EXTERN(sys32_munlock)
EXTERN(sys32_mlockall)
EXTERN(sys32_munlockall)
EXTERN(sys32_sched_setparam)
EXTERN(sys32_sched_getparam)
EXTERN(sys32_sched_setscheduler)
EXTERN(sys32_sched_getscheduler)
EXTERN(sys32_sched_yield)
EXTERN(sys32_sched_get_priority_max)
EXTERN(sys32_sched_get_priority_min)
EXTERN(sys32_sched_rr_get_interval)
EXTERN(sys32_nanosleep)
EXTERN(sys32_mremap)
EXTERN(sys32_setresuid)
EXTERN(sys32_getresuid)
EXTERN(sys32_poll)
EXTERN(sys32_setresgid)
EXTERN(sys32_getresgid)
EXTERN(sys32_rt_sigaction)
EXTERN(sys32_rt_sigprocmask)
EXTERN(sys32_rt_sigpending)
EXTERN(sys32_rt_sigtimedwait)
EXTERN(sys32_rt_sigqueueinfo)
EXTERN(sys32_rt_sigsuspend)
EXTERN(sys32_pread64)
EXTERN(sys32_pwrite64)
EXTERN(sys32_chown)
EXTERN(sys32_getcwd)
EXTERN(sys32_sigaltstack)
EXTERN(sys32_sendfile)
EXTERN(sys32_vfork)
EXTERN(sys32_mmap2)
EXTERN(sys32_truncate64)
EXTERN(sys32_ftruncate64)
EXTERN(sys32_linux_stat64)
EXTERN(sys32_linux_lstat64)
EXTERN(sys32_linux_fstat64)
EXTERN(sys32_lchown32)
EXTERN(sys32_getuid32)
EXTERN(sys32_getgid32)
EXTERN(sys32_geteuid32)
EXTERN(sys32_getegid32)
EXTERN(sys32_setreuid32)
EXTERN(sys32_setregid32)
EXTERN(sys32_getgroups32)
EXTERN(sys32_setgroups32)
EXTERN(sys32_fchown32)
EXTERN(sys32_setresuid32)
EXTERN(sys32_getresuid32)
EXTERN(sys32_setresgid32)
EXTERN(sys32_getresgid32)
EXTERN(sys32_chown32)
EXTERN(sys32_setuid32)
EXTERN(sys32_setgid32)
EXTERN(sys32_setfsuid32)
EXTERN(sys32_setfsgid32)
EXTERN(sys32_mincore)
EXTERN(sys32_madvise)
EXTERN(sys32_getdents64)
EXTERN(sys32_fcntl64)
EXTERN(sys32_gettid)
EXTERN(sys32_readahead)
EXTERN(sys32_setxattr)
EXTERN(sys32_lsetxattr)
EXTERN(sys32_fsetxattr)
EXTERN(sys32_getxattr)
EXTERN(sys32_lgetxattr)
EXTERN(sys32_fgetxattr)
EXTERN(sys32_listxattr)
EXTERN(sys32_llistxattr)
EXTERN(sys32_flistxattr)
EXTERN(sys32_removexattr)
EXTERN(sys32_lremovexattr)
EXTERN(sys32_fremovexattr)
EXTERN(sys32_tkill)
EXTERN(sys32_sendfile64)
EXTERN(sys32_futex)
EXTERN(sys32_sched_setaffinity)
EXTERN(sys32_sched_getaffinity)
EXTERN(sys32_exit_group)
EXTERN(sys32_epoll_create)
EXTERN(sys32_epoll_ctl)
EXTERN(sys32_epoll_wait)
EXTERN(sys32_remap_file_pages)
EXTERN(sys32_set_tid_address)
EXTERN(sys32_timer_create)
EXTERN(sys32_timer_settime)
EXTERN(sys32_timer_gettime)
EXTERN(sys32_timer_getoverrun)
EXTERN(sys32_timer_delete)
EXTERN(sys32_clock_settime)
EXTERN(sys32_clock_gettime)
EXTERN(sys32_clock_getres)
EXTERN(sys32_clock_nanosleep)
EXTERN(sys32_statfs64)
EXTERN(sys32_fstatfs64)
EXTERN(sys32_tgkill)
EXTERN(sys32_utimes)
EXTERN(sys32_waitid)
EXTERN(sys32_ioprio_set)
EXTERN(sys32_ioprio_get)
EXTERN(sys32_openat)
EXTERN(sys32_mkdirat)
EXTERN(sys32_mknodat)
EXTERN(sys32_fchownat)
EXTERN(sys32_futimesat)
EXTERN(sys32_linux_fstatat64)
EXTERN(sys32_unlinkat)
EXTERN(sys32_renameat)
EXTERN(sys32_linkat)
EXTERN(sys32_symlinkat)
EXTERN(sys32_readlinkat)
EXTERN(sys32_fchmodat)
EXTERN(sys32_faccessat)
EXTERN(sys32_pselect6)
EXTERN(sys32_ppoll)
EXTERN(sys32_unshare)
EXTERN(sys32_splice)
EXTERN(sys32_sync_file_range)
EXTERN(sys32_tee)
EXTERN(sys32_vmsplice)
EXTERN(sys32_getcpu)
EXTERN(sys32_epoll_pwait)
EXTERN(sys32_utimensat)
EXTERN(sys32_signalfd)
EXTERN(sys32_timerfd_create)
EXTERN(sys32_eventfd)
EXTERN(sys32_fallocate)
EXTERN(sys32_timerfd_settime)
EXTERN(sys32_timerfd_gettime)
EXTERN(sys32_signalfd4)
EXTERN(sys32_eventfd2)
EXTERN(sys32_epoll_create1)
EXTERN(sys32_dup3)
EXTERN(sys32_pipe2)
EXTERN(sys32_preadv)
EXTERN(sys32_pwritev)
EXTERN(sys32_rt_tgsigqueueinfo)
EXTERN(sys32_recvmmsg)
EXTERN(sys32_prlimit64)
EXTERN(sys32_name_to_handle_at)
EXTERN(sys32_open_by_handle_at)
EXTERN(sys32_syncfs)
EXTERN(sys32_sendmmsg)
EXTERN(sys32_setns)
EXTERN(sys32_process_vm_readv)
EXTERN(sys32_process_vm_writev)
EXTERN(sys32_kcmp)
EXTERN(sys32_renameat2)
EXTERN(sys32_execveat)
EXTERN(sys32_socket)
EXTERN(sys32_socketpair)
EXTERN(sys32_bind)
EXTERN(sys32_connect)
EXTERN(sys32_listen)
EXTERN(sys32_accept4)
EXTERN(sys32_getsockopt)
EXTERN(sys32_setsockopt)
EXTERN(sys32_getsockname)
EXTERN(sys32_getpeername)
EXTERN(sys32_sendto)
EXTERN(sys32_sendmsg)
EXTERN(sys32_recvfrom)
EXTERN(sys32_recvmsg)
EXTERN(sys32_shutdown)
EXTERN(sys32_hop)
EXTERN(sys32_hopf)
EXTERN(sys32_readf)
EXTERN(sys32_writef)
EXTERN(sys32_detach)
EXTERN(sys32_getdrives)
EXTERN(sys32_frealpath4)
EXTERN(sys32_frealpathat)
EXTERN(sys32_rpc_schedule)
EXTERN(sys32_sysctl)
EXTERN(sys32_openpty)
EXTERN(sys32_fchdirat)
EXTERN(sys32_time64)
EXTERN(sys32_set_exception_handler)
EXTERN(sys32_get_exception_handler)
EXTERN(sys32_set_library_listdef)
EXTERN(sys32_debugtrap)
EXTERN(sys32_lfutex)
EXTERN(sys32_lseek64)
EXTERN(sys32_lfutexexpr)
EXTERN(sys32_lfutexlockexpr)
EXTERN(sys32_mktty)
EXTERN(sys32_raiseat)
EXTERN(sys32_coredump)
EXTERN(sys32_stime64)
EXTERN(sys32_utime64)
EXTERN(sys32_ioctlf)
EXTERN(sys32_fsmode)
EXTERN(sys32_gettimeofday64)
EXTERN(sys32_settimeofday64)
EXTERN(sys32_select64)
EXTERN(sys32_maplibrary)
EXTERN(sys32_setitimer64)
EXTERN(sys32_getitimer64)
EXTERN(sys32_kreaddir)
EXTERN(sys32_readvf)
EXTERN(sys32_writevf)
EXTERN(sys32_rpc_service)
EXTERN(sys32_sched_rr_get_interval64)
EXTERN(sys32_nanosleep64)
EXTERN(sys32_rt_sigtimedwait64)
EXTERN(sys32_pread64f)
EXTERN(sys32_pwrite64f)
EXTERN(sys32_kstat)
EXTERN(sys32_klstat)
EXTERN(sys32_kfstat)
EXTERN(sys32_kreaddirf)
EXTERN(sys32_timer_settime64)
EXTERN(sys32_timer_gettime64)
EXTERN(sys32_clock_settime64)
EXTERN(sys32_clock_gettime64)
EXTERN(sys32_clock_getres64)
EXTERN(sys32_clock_nanosleep64)
EXTERN(sys32_utimes64)
EXTERN(sys32_fmkdirat)
EXTERN(sys32_fmknodat)
EXTERN(sys32_futimesat64)
EXTERN(sys32_kfstatat)
EXTERN(sys32_frenameat)
EXTERN(sys32_fsymlinkat)
EXTERN(sys32_freadlinkat)
EXTERN(sys32_pselect6_64)
EXTERN(sys32_ppoll64)
EXTERN(sys32_utimensat64)
EXTERN(sys32_fallocate64)
EXTERN(sys32_timerfd_settime64)
EXTERN(sys32_timerfd_gettime64)
EXTERN(sys32_preadvf)
EXTERN(sys32_pwritevf)
EXTERN(sys32_recvmmsg64)



/* Weakly alias implementations of compatibility-mode system calls to their long-mode variants */
.weak sys32_exit; .set sys32_exit, sys_exit
.weak sys32_fork; .set sys32_fork, sys_fork
.weak sys32_read; .set sys32_read, sys_read
.weak sys32_write; .set sys32_write, sys_write
.weak sys32_open; .set sys32_open, sys_open
.weak sys32_close; .set sys32_close, sys_close
.weak sys32_creat; .set sys32_creat, sys_creat
.weak sys32_link; .set sys32_link, sys_link
.weak sys32_unlink; .set sys32_unlink, sys_unlink
.weak sys32_execve; .set sys32_execve, sys_execve
.weak sys32_chdir; .set sys32_chdir, sys_chdir
.weak sys32_time; .set sys32_time, sys_time
.weak sys32_mknod; .set sys32_mknod, sys_mknod
.weak sys32_chmod; .set sys32_chmod, sys_chmod
.weak sys32_lchown; .set sys32_lchown, sys_lchown
.weak sys32_getpid; .set sys32_getpid, sys_getpid
.weak sys32_mount; .set sys32_mount, sys_mount
.weak sys32_ptrace; .set sys32_ptrace, sys_ptrace
.weak sys32_alarm; .set sys32_alarm, sys_alarm
.weak sys32_pause; .set sys32_pause, sys_pause
.weak sys32_utime; .set sys32_utime, sys_utime
.weak sys32_access; .set sys32_access, sys_access
.weak sys32_sync; .set sys32_sync, sys_sync
.weak sys32_kill; .set sys32_kill, sys_kill
.weak sys32_rename; .set sys32_rename, sys_rename
.weak sys32_mkdir; .set sys32_mkdir, sys_mkdir
.weak sys32_rmdir; .set sys32_rmdir, sys_rmdir
.weak sys32_dup; .set sys32_dup, sys_dup
.weak sys32_pipe; .set sys32_pipe, sys_pipe
.weak sys32_times; .set sys32_times, sys_times
.weak sys32_brk; .set sys32_brk, sys_brk
.weak sys32_acct; .set sys32_acct, sys_acct
.weak sys32_umount2; .set sys32_umount2, sys_umount2
.weak sys32_ioctl; .set sys32_ioctl, sys_ioctl
.weak sys32_fcntl; .set sys32_fcntl, sys_fcntl
.weak sys32_setpgid; .set sys32_setpgid, sys_setpgid
.weak sys32_umask; .set sys32_umask, sys_umask
.weak sys32_chroot; .set sys32_chroot, sys_chroot
.weak sys32_ustat; .set sys32_ustat, sys_ustat
.weak sys32_dup2; .set sys32_dup2, sys_dup2
.weak sys32_getppid; .set sys32_getppid, sys_getppid
.weak sys32_getpgrp; .set sys32_getpgrp, sys_getpgrp
.weak sys32_setsid; .set sys32_setsid, sys_setsid
.weak sys32_sethostname; .set sys32_sethostname, sys_sethostname
.weak sys32_setrlimit; .set sys32_setrlimit, sys_setrlimit
.weak sys32_getrlimit; .set sys32_getrlimit, sys_getrlimit
.weak sys32_getrusage; .set sys32_getrusage, sys_getrusage
.weak sys32_gettimeofday; .set sys32_gettimeofday, sys_gettimeofday
.weak sys32_settimeofday; .set sys32_settimeofday, sys_settimeofday
.weak sys32_select; .set sys32_select, sys_select
.weak sys32_symlink; .set sys32_symlink, sys_symlink
.weak sys32_readlink; .set sys32_readlink, sys_readlink
.weak sys32_swapon; .set sys32_swapon, sys_swapon
.weak sys32_reboot; .set sys32_reboot, sys_reboot
.weak sys32_mmap; .set sys32_mmap, sys_mmap
.weak sys32_munmap; .set sys32_munmap, sys_munmap
.weak sys32_truncate; .set sys32_truncate, sys_truncate
.weak sys32_ftruncate; .set sys32_ftruncate, sys_ftruncate
.weak sys32_fchmod; .set sys32_fchmod, sys_fchmod
.weak sys32_fchown; .set sys32_fchown, sys_fchown
.weak sys32_getpriority; .set sys32_getpriority, sys_getpriority
.weak sys32_setpriority; .set sys32_setpriority, sys_setpriority
.weak sys32_statfs; .set sys32_statfs, sys_statfs
.weak sys32_fstatfs; .set sys32_fstatfs, sys_fstatfs
.weak sys32_ioperm; .set sys32_ioperm, sys_ioperm
.weak sys32_syslog; .set sys32_syslog, sys_syslog
.weak sys32_setitimer; .set sys32_setitimer, sys_setitimer
.weak sys32_getitimer; .set sys32_getitimer, sys_getitimer
.weak sys32_iopl; .set sys32_iopl, sys_iopl
.weak sys32_vhangup; .set sys32_vhangup, sys_vhangup
.weak sys32_wait4; .set sys32_wait4, sys_wait4
.weak sys32_swapoff; .set sys32_swapoff, sys_swapoff
.weak sys32_sysinfo; .set sys32_sysinfo, sys_sysinfo
.weak sys32_fsync; .set sys32_fsync, sys_fsync
.weak sys32_clone; .set sys32_clone, sys_clone
.weak sys32_setdomainname; .set sys32_setdomainname, sys_setdomainname
.weak sys32_uname; .set sys32_uname, sys_uname
.weak sys32_modify_ldt; .set sys32_modify_ldt, sys_modify_ldt
.weak sys32_mprotect; .set sys32_mprotect, sys_mprotect
.weak sys32_getpgid; .set sys32_getpgid, sys_getpgid
.weak sys32_fchdir; .set sys32_fchdir, sys_fchdir
.weak sys32_getdents; .set sys32_getdents, sys_getdents
.weak sys32_flock; .set sys32_flock, sys_flock
.weak sys32_msync; .set sys32_msync, sys_msync
.weak sys32_readv; .set sys32_readv, sys_readv
.weak sys32_writev; .set sys32_writev, sys_writev
.weak sys32_getsid; .set sys32_getsid, sys_getsid
.weak sys32_fdatasync; .set sys32_fdatasync, sys_fdatasync
.weak sys32_mlock; .set sys32_mlock, sys_mlock
.weak sys32_munlock; .set sys32_munlock, sys_munlock
.weak sys32_mlockall; .set sys32_mlockall, sys_mlockall
.weak sys32_munlockall; .set sys32_munlockall, sys_munlockall
.weak sys32_sched_setparam; .set sys32_sched_setparam, sys_sched_setparam
.weak sys32_sched_getparam; .set sys32_sched_getparam, sys_sched_getparam
.weak sys32_sched_setscheduler; .set sys32_sched_setscheduler, sys_sched_setscheduler
.weak sys32_sched_getscheduler; .set sys32_sched_getscheduler, sys_sched_getscheduler
.weak sys32_sched_yield; .set sys32_sched_yield, sys_sched_yield
.weak sys32_sched_get_priority_max; .set sys32_sched_get_priority_max, sys_sched_get_priority_max
.weak sys32_sched_get_priority_min; .set sys32_sched_get_priority_min, sys_sched_get_priority_min
.weak sys32_sched_rr_get_interval; .set sys32_sched_rr_get_interval, sys_sched_rr_get_interval
.weak sys32_nanosleep; .set sys32_nanosleep, sys_nanosleep
.weak sys32_mremap; .set sys32_mremap, sys_mremap
.weak sys32_poll; .set sys32_poll, sys_poll
.weak sys32_rt_sigaction; .set sys32_rt_sigaction, sys_rt_sigaction
.weak sys32_rt_sigprocmask; .set sys32_rt_sigprocmask, sys_rt_sigprocmask
.weak sys32_rt_sigpending; .set sys32_rt_sigpending, sys_rt_sigpending
.weak sys32_rt_sigtimedwait; .set sys32_rt_sigtimedwait, sys_rt_sigtimedwait
.weak sys32_rt_sigqueueinfo; .set sys32_rt_sigqueueinfo, sys_rt_sigqueueinfo
.weak sys32_rt_sigsuspend; .set sys32_rt_sigsuspend, sys_rt_sigsuspend
.weak sys32_pread64; .set sys32_pread64, sys_pread64
.weak sys32_pwrite64; .set sys32_pwrite64, sys_pwrite64
.weak sys32_chown; .set sys32_chown, sys_chown
.weak sys32_getcwd; .set sys32_getcwd, sys_getcwd
.weak sys32_sigaltstack; .set sys32_sigaltstack, sys_sigaltstack
.weak sys32_sendfile; .set sys32_sendfile, sys_sendfile
.weak sys32_vfork; .set sys32_vfork, sys_vfork
.weak sys32_linux_stat64; .set sys32_linux_stat64, sys_linux_stat64
.weak sys32_linux_lstat64; .set sys32_linux_lstat64, sys_linux_lstat64
.weak sys32_linux_fstat64; .set sys32_linux_fstat64, sys_linux_fstat64
.weak sys32_getuid32; .set sys32_getuid32, sys_getuid32
.weak sys32_getgid32; .set sys32_getgid32, sys_getgid32
.weak sys32_geteuid32; .set sys32_geteuid32, sys_geteuid32
.weak sys32_getegid32; .set sys32_getegid32, sys_getegid32
.weak sys32_setreuid32; .set sys32_setreuid32, sys_setreuid32
.weak sys32_setregid32; .set sys32_setregid32, sys_setregid32
.weak sys32_getgroups32; .set sys32_getgroups32, sys_getgroups32
.weak sys32_setgroups32; .set sys32_setgroups32, sys_setgroups32
.weak sys32_setresuid32; .set sys32_setresuid32, sys_setresuid32
.weak sys32_getresuid32; .set sys32_getresuid32, sys_getresuid32
.weak sys32_setresgid32; .set sys32_setresgid32, sys_setresgid32
.weak sys32_getresgid32; .set sys32_getresgid32, sys_getresgid32
.weak sys32_setuid32; .set sys32_setuid32, sys_setuid32
.weak sys32_setgid32; .set sys32_setgid32, sys_setgid32
.weak sys32_setfsuid32; .set sys32_setfsuid32, sys_setfsuid32
.weak sys32_setfsgid32; .set sys32_setfsgid32, sys_setfsgid32
.weak sys32_mincore; .set sys32_mincore, sys_mincore
.weak sys32_madvise; .set sys32_madvise, sys_madvise
.weak sys32_getdents64; .set sys32_getdents64, sys_getdents64
.weak sys32_gettid; .set sys32_gettid, sys_gettid
.weak sys32_readahead; .set sys32_readahead, sys_readahead
.weak sys32_setxattr; .set sys32_setxattr, sys_setxattr
.weak sys32_lsetxattr; .set sys32_lsetxattr, sys_lsetxattr
.weak sys32_fsetxattr; .set sys32_fsetxattr, sys_fsetxattr
.weak sys32_getxattr; .set sys32_getxattr, sys_getxattr
.weak sys32_lgetxattr; .set sys32_lgetxattr, sys_lgetxattr
.weak sys32_fgetxattr; .set sys32_fgetxattr, sys_fgetxattr
.weak sys32_listxattr; .set sys32_listxattr, sys_listxattr
.weak sys32_llistxattr; .set sys32_llistxattr, sys_llistxattr
.weak sys32_flistxattr; .set sys32_flistxattr, sys_flistxattr
.weak sys32_removexattr; .set sys32_removexattr, sys_removexattr
.weak sys32_lremovexattr; .set sys32_lremovexattr, sys_lremovexattr
.weak sys32_fremovexattr; .set sys32_fremovexattr, sys_fremovexattr
.weak sys32_tkill; .set sys32_tkill, sys_tkill
.weak sys32_futex; .set sys32_futex, sys_futex
.weak sys32_sched_setaffinity; .set sys32_sched_setaffinity, sys_sched_setaffinity
.weak sys32_sched_getaffinity; .set sys32_sched_getaffinity, sys_sched_getaffinity
.weak sys32_exit_group; .set sys32_exit_group, sys_exit_group
.weak sys32_epoll_create; .set sys32_epoll_create, sys_epoll_create
.weak sys32_epoll_ctl; .set sys32_epoll_ctl, sys_epoll_ctl
.weak sys32_epoll_wait; .set sys32_epoll_wait, sys_epoll_wait
.weak sys32_remap_file_pages; .set sys32_remap_file_pages, sys_remap_file_pages
.weak sys32_set_tid_address; .set sys32_set_tid_address, sys_set_tid_address
.weak sys32_timer_create; .set sys32_timer_create, sys_timer_create
.weak sys32_timer_settime; .set sys32_timer_settime, sys_timer_settime
.weak sys32_timer_gettime; .set sys32_timer_gettime, sys_timer_gettime
.weak sys32_timer_getoverrun; .set sys32_timer_getoverrun, sys_timer_getoverrun
.weak sys32_timer_delete; .set sys32_timer_delete, sys_timer_delete
.weak sys32_clock_settime; .set sys32_clock_settime, sys_clock_settime
.weak sys32_clock_gettime; .set sys32_clock_gettime, sys_clock_gettime
.weak sys32_clock_getres; .set sys32_clock_getres, sys_clock_getres
.weak sys32_clock_nanosleep; .set sys32_clock_nanosleep, sys_clock_nanosleep
.weak sys32_tgkill; .set sys32_tgkill, sys_tgkill
.weak sys32_utimes; .set sys32_utimes, sys_utimes
.weak sys32_waitid; .set sys32_waitid, sys_waitid
.weak sys32_ioprio_set; .set sys32_ioprio_set, sys_ioprio_set
.weak sys32_ioprio_get; .set sys32_ioprio_get, sys_ioprio_get
.weak sys32_openat; .set sys32_openat, sys_openat
.weak sys32_mkdirat; .set sys32_mkdirat, sys_mkdirat
.weak sys32_mknodat; .set sys32_mknodat, sys_mknodat
.weak sys32_fchownat; .set sys32_fchownat, sys_fchownat
.weak sys32_futimesat; .set sys32_futimesat, sys_futimesat
.weak sys32_unlinkat; .set sys32_unlinkat, sys_unlinkat
.weak sys32_renameat; .set sys32_renameat, sys_renameat
.weak sys32_linkat; .set sys32_linkat, sys_linkat
.weak sys32_symlinkat; .set sys32_symlinkat, sys_symlinkat
.weak sys32_readlinkat; .set sys32_readlinkat, sys_readlinkat
.weak sys32_fchmodat; .set sys32_fchmodat, sys_fchmodat
.weak sys32_faccessat; .set sys32_faccessat, sys_faccessat
.weak sys32_pselect6; .set sys32_pselect6, sys_pselect6
.weak sys32_ppoll; .set sys32_ppoll, sys_ppoll
.weak sys32_unshare; .set sys32_unshare, sys_unshare
.weak sys32_splice; .set sys32_splice, sys_splice
.weak sys32_sync_file_range; .set sys32_sync_file_range, sys_sync_file_range
.weak sys32_tee; .set sys32_tee, sys_tee
.weak sys32_vmsplice; .set sys32_vmsplice, sys_vmsplice
.weak sys32_getcpu; .set sys32_getcpu, sys_getcpu
.weak sys32_epoll_pwait; .set sys32_epoll_pwait, sys_epoll_pwait
.weak sys32_utimensat; .set sys32_utimensat, sys_utimensat
.weak sys32_signalfd; .set sys32_signalfd, sys_signalfd
.weak sys32_timerfd_create; .set sys32_timerfd_create, sys_timerfd_create
.weak sys32_eventfd; .set sys32_eventfd, sys_eventfd
.weak sys32_fallocate; .set sys32_fallocate, sys_fallocate
.weak sys32_timerfd_settime; .set sys32_timerfd_settime, sys_timerfd_settime
.weak sys32_timerfd_gettime; .set sys32_timerfd_gettime, sys_timerfd_gettime
.weak sys32_signalfd4; .set sys32_signalfd4, sys_signalfd4
.weak sys32_eventfd2; .set sys32_eventfd2, sys_eventfd2
.weak sys32_epoll_create1; .set sys32_epoll_create1, sys_epoll_create1
.weak sys32_dup3; .set sys32_dup3, sys_dup3
.weak sys32_pipe2; .set sys32_pipe2, sys_pipe2
.weak sys32_preadv; .set sys32_preadv, sys_preadv
.weak sys32_pwritev; .set sys32_pwritev, sys_pwritev
.weak sys32_rt_tgsigqueueinfo; .set sys32_rt_tgsigqueueinfo, sys_rt_tgsigqueueinfo
.weak sys32_recvmmsg; .set sys32_recvmmsg, sys_recvmmsg
.weak sys32_prlimit64; .set sys32_prlimit64, sys_prlimit64
.weak sys32_name_to_handle_at; .set sys32_name_to_handle_at, sys_name_to_handle_at
.weak sys32_open_by_handle_at; .set sys32_open_by_handle_at, sys_open_by_handle_at
.weak sys32_syncfs; .set sys32_syncfs, sys_syncfs
.weak sys32_sendmmsg; .set sys32_sendmmsg, sys_sendmmsg
.weak sys32_setns; .set sys32_setns, sys_setns
.weak sys32_process_vm_readv; .set sys32_process_vm_readv, sys_process_vm_readv
.weak sys32_process_vm_writev; .set sys32_process_vm_writev, sys_process_vm_writev
.weak sys32_kcmp; .set sys32_kcmp, sys_kcmp
.weak sys32_renameat2; .set sys32_renameat2, sys_renameat2
.weak sys32_execveat; .set sys32_execveat, sys_execveat
.weak sys32_socket; .set sys32_socket, sys_socket
.weak sys32_socketpair; .set sys32_socketpair, sys_socketpair
.weak sys32_bind; .set sys32_bind, sys_bind
.weak sys32_connect; .set sys32_connect, sys_connect
.weak sys32_listen; .set sys32_listen, sys_listen
.weak sys32_accept4; .set sys32_accept4, sys_accept4
.weak sys32_getsockopt; .set sys32_getsockopt, sys_getsockopt
.weak sys32_setsockopt; .set sys32_setsockopt, sys_setsockopt
.weak sys32_getsockname; .set sys32_getsockname, sys_getsockname
.weak sys32_getpeername; .set sys32_getpeername, sys_getpeername
.weak sys32_sendto; .set sys32_sendto, sys_sendto
.weak sys32_sendmsg; .set sys32_sendmsg, sys_sendmsg
.weak sys32_recvfrom; .set sys32_recvfrom, sys_recvfrom
.weak sys32_recvmsg; .set sys32_recvmsg, sys_recvmsg
.weak sys32_shutdown; .set sys32_shutdown, sys_shutdown
.weak sys32_hop; .set sys32_hop, sys_hop
.weak sys32_hopf; .set sys32_hopf, sys_hopf
.weak sys32_readf; .set sys32_readf, sys_readf
.weak sys32_writef; .set sys32_writef, sys_writef
.weak sys32_detach; .set sys32_detach, sys_detach
.weak sys32_getdrives; .set sys32_getdrives, sys_getdrives
.weak sys32_frealpath4; .set sys32_frealpath4, sys_frealpath4
.weak sys32_frealpathat; .set sys32_frealpathat, sys_frealpathat
.weak sys32_rpc_schedule; .set sys32_rpc_schedule, sys_rpc_schedule
.weak sys32_sysctl; .set sys32_sysctl, sys_sysctl
.weak sys32_openpty; .set sys32_openpty, sys_openpty
.weak sys32_fchdirat; .set sys32_fchdirat, sys_fchdirat
.weak sys32_time64; .set sys32_time64, sys_time64
.weak sys32_set_exception_handler; .set sys32_set_exception_handler, sys_set_exception_handler
.weak sys32_get_exception_handler; .set sys32_get_exception_handler, sys_get_exception_handler
.weak sys32_set_library_listdef; .set sys32_set_library_listdef, sys_set_library_listdef
.weak sys32_debugtrap; .set sys32_debugtrap, sys_debugtrap
.weak sys32_lfutex; .set sys32_lfutex, sys_lfutex
.weak sys32_lseek64; .set sys32_lseek64, sys_lseek64
.weak sys32_lfutexexpr; .set sys32_lfutexexpr, sys_lfutexexpr
.weak sys32_lfutexlockexpr; .set sys32_lfutexlockexpr, sys_lfutexlockexpr
.weak sys32_mktty; .set sys32_mktty, sys_mktty
.weak sys32_raiseat; .set sys32_raiseat, sys_raiseat
.weak sys32_coredump; .set sys32_coredump, sys_coredump
.weak sys32_utime64; .set sys32_utime64, sys_utime64
.weak sys32_ioctlf; .set sys32_ioctlf, sys_ioctlf
.weak sys32_fsmode; .set sys32_fsmode, sys_fsmode
.weak sys32_gettimeofday64; .set sys32_gettimeofday64, sys_gettimeofday64
.weak sys32_settimeofday64; .set sys32_settimeofday64, sys_settimeofday64
.weak sys32_select64; .set sys32_select64, sys_select64
.weak sys32_maplibrary; .set sys32_maplibrary, sys_maplibrary
.weak sys32_setitimer64; .set sys32_setitimer64, sys_setitimer64
.weak sys32_getitimer64; .set sys32_getitimer64, sys_getitimer64
.weak sys32_kreaddir; .set sys32_kreaddir, sys_kreaddir
.weak sys32_readvf; .set sys32_readvf, sys_readvf
.weak sys32_writevf; .set sys32_writevf, sys_writevf
.weak sys32_rpc_service; .set sys32_rpc_service, sys_rpc_service
.weak sys32_pread64f; .set sys32_pread64f, sys_pread64f
.weak sys32_pwrite64f; .set sys32_pwrite64f, sys_pwrite64f
.weak sys32_kstat; .set sys32_kstat, sys_kstat
.weak sys32_klstat; .set sys32_klstat, sys_klstat
.weak sys32_kfstat; .set sys32_kfstat, sys_kfstat
.weak sys32_kreaddirf; .set sys32_kreaddirf, sys_kreaddirf
.weak sys32_utimes64; .set sys32_utimes64, sys_utimes64
.weak sys32_fmkdirat; .set sys32_fmkdirat, sys_fmkdirat
.weak sys32_fmknodat; .set sys32_fmknodat, sys_fmknodat
.weak sys32_futimesat64; .set sys32_futimesat64, sys_futimesat64
.weak sys32_kfstatat; .set sys32_kfstatat, sys_kfstatat
.weak sys32_frenameat; .set sys32_frenameat, sys_frenameat
.weak sys32_fsymlinkat; .set sys32_fsymlinkat, sys_fsymlinkat
.weak sys32_freadlinkat; .set sys32_freadlinkat, sys_freadlinkat
.weak sys32_fallocate64; .set sys32_fallocate64, sys_fallocate64
.weak sys32_preadvf; .set sys32_preadvf, sys_preadvf
.weak sys32_pwritevf; .set sys32_pwritevf, sys_pwritevf



INTERN(__asm32_bad_sysenter_extension)
EXTERN(x86_syscall_personality)



.section .text.x86.asm64_syscall.read
	/* ssize_t read(fd_t fd,
	 *              void *buf,
	 *              size_t bufsize) */
	.weak __asm64_syscall_read
INTERN_FUNCTION(__asm64_syscall_read)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_read
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_read)

.section .text.x86.asm64_syscall.write
	/* ssize_t write(fd_t fd,
	 *               void const *buf,
	 *               size_t bufsize) */
	.weak __asm64_syscall_write
INTERN_FUNCTION(__asm64_syscall_write)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_write
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_write)

.section .text.x86.asm64_syscall.open
	/* fd_t open(char const *filename,
	 *           oflag_t oflags,
	 *           mode_t mode) */
	.weak __asm64_syscall_open
INTERN_FUNCTION(__asm64_syscall_open)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_open
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_open)

/* Close a given file descriptor/handle `FD' */
.section .text.x86.asm64_syscall.close
	/* errno_t close(fd_t fd) */
	.weak __asm64_syscall_close
INTERN_FUNCTION(__asm64_syscall_close)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_close
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_close)

.section .text.x86.asm64_syscall.linux_stat64
	/* errno_t linux_stat64(char const *filename,
	 *                      struct linux_stat64 *statbuf) */
	.weak __asm64_syscall_linux_stat64
INTERN_FUNCTION(__asm64_syscall_linux_stat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_linux_stat64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_linux_stat64)

.section .text.x86.asm64_syscall.linux_fstat64
	/* errno_t linux_fstat64(fd_t fd,
	 *                       struct linux_stat64 *statbuf) */
	.weak __asm64_syscall_linux_fstat64
INTERN_FUNCTION(__asm64_syscall_linux_fstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_linux_fstat64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_linux_fstat64)

.section .text.x86.asm64_syscall.linux_lstat64
	/* errno_t linux_lstat64(char const *filename,
	 *                       struct linux_stat64 *statbuf) */
	.weak __asm64_syscall_linux_lstat64
INTERN_FUNCTION(__asm64_syscall_linux_lstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_linux_lstat64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_linux_lstat64)

.section .text.x86.asm64_syscall.poll
	/* ssize_t poll(struct pollfd *fds,
	 *              size_t nfds,
	 *              syscall_slong_t timeout) */
	.weak __asm64_syscall_poll
INTERN_FUNCTION(__asm64_syscall_poll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_poll
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_poll)

.section .text.x86.asm64_syscall.lseek64
	/* int64_t lseek64(fd_t fd,
	 *                 int64_t offset,
	 *                 syscall_ulong_t whence) */
	.weak __asm64_syscall_lseek64
INTERN_FUNCTION(__asm64_syscall_lseek64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_lseek64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_lseek64)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
.section .text.x86.asm64_syscall.mmap
	/* void *mmap(void *addr,
	 *            size_t len,
	 *            syscall_ulong_t prot,
	 *            syscall_ulong_t flags,
	 *            fd_t fd,
	 *            syscall_ulong_t offset) */
	.weak __asm64_syscall_mmap
INTERN_FUNCTION(__asm64_syscall_mmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_mmap
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mmap)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
.section .text.x86.asm64_syscall.mprotect
	/* errno_t mprotect(void *addr,
	 *                  size_t len,
	 *                  syscall_ulong_t prot) */
	.weak __asm64_syscall_mprotect
INTERN_FUNCTION(__asm64_syscall_mprotect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_mprotect
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mprotect)

.section .text.x86.asm64_syscall.munmap
	/* errno_t munmap(void *addr,
	 *                size_t len) */
	.weak __asm64_syscall_munmap
INTERN_FUNCTION(__asm64_syscall_munmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_munmap
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_munmap)

.section .text.x86.asm64_syscall.brk
	/* errno_t brk(void *addr) */
	.weak __asm64_syscall_brk
INTERN_FUNCTION(__asm64_syscall_brk)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_brk
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_brk)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm64_syscall.rt_sigaction
	/* errno_t rt_sigaction(syscall_ulong_t signo,
	 *                      struct sigaction const *act,
	 *                      struct sigaction *oact,
	 *                      size_t sigsetsize) */
	.weak __asm64_syscall_rt_sigaction
INTERN_FUNCTION(__asm64_syscall_rt_sigaction)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_rt_sigaction
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
.section .text.x86.asm64_syscall.rt_sigprocmask
	/* errno_t rt_sigprocmask(syscall_ulong_t how,
	 *                        struct __sigset_struct const *set,
	 *                        struct __sigset_struct *oset,
	 *                        size_t sigsetsize) */
	.weak __asm64_syscall_rt_sigprocmask
INTERN_FUNCTION(__asm64_syscall_rt_sigprocmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_rt_sigprocmask
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rt_sigprocmask)

.section .text.x86.asm64_syscall.rt_sigreturn
	/* void rt_sigreturn(void); */
	.weak __asm64_syscall_rt_sigreturn
INTERN_FUNCTION(__asm64_syscall_rt_sigreturn)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xf
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_rt_sigreturn
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rt_sigreturn)

.section .text.x86.asm64_syscall.ioctl
	/* syscall_slong_t ioctl(fd_t fd,
	 *                       syscall_ulong_t request,
	 *                       void *arg) */
	.weak __asm64_syscall_ioctl
INTERN_FUNCTION(__asm64_syscall_ioctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_ioctl
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_ioctl)

.section .text.x86.asm64_syscall.pread64
	/* ssize_t pread64(fd_t fd,
	 *                 void *buf,
	 *                 size_t bufsize,
	 *                 uint64_t offset) */
	.weak __asm64_syscall_pread64
INTERN_FUNCTION(__asm64_syscall_pread64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x11
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_pread64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pread64)

.section .text.x86.asm64_syscall.pwrite64
	/* ssize_t pwrite64(fd_t fd,
	 *                  void const *buf,
	 *                  size_t bufsize,
	 *                  uint64_t offset) */
	.weak __asm64_syscall_pwrite64
INTERN_FUNCTION(__asm64_syscall_pwrite64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_pwrite64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pwrite64)

.section .text.x86.asm64_syscall.readv
	/* ssize_t readv(fd_t fd,
	 *               struct iovec const *iovec,
	 *               size_t count) */
	.weak __asm64_syscall_readv
INTERN_FUNCTION(__asm64_syscall_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x13
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_readv
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_readv)

.section .text.x86.asm64_syscall.writev
	/* ssize_t writev(fd_t fd,
	 *                struct iovec const *iovec,
	 *                size_t count) */
	.weak __asm64_syscall_writev
INTERN_FUNCTION(__asm64_syscall_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x14
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_writev
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_writev)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
.section .text.x86.asm64_syscall.access
	/* errno_t access(char const *filename,
	 *                syscall_ulong_t type) */
	.weak __asm64_syscall_access
INTERN_FUNCTION(__asm64_syscall_access)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x15
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_access
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_access)

.section .text.x86.asm64_syscall.pipe
	/* errno_t pipe([2] fd_t *pipedes) */
	.weak __asm64_syscall_pipe
INTERN_FUNCTION(__asm64_syscall_pipe)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x16
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_pipe
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pipe)

.section .text.x86.asm64_syscall.select
	/* ssize_t select(size_t nfds,
	 *                struct __fd_set_struct *readfds,
	 *                struct __fd_set_struct *writefds,
	 *                struct __fd_set_struct *exceptfds,
	 *                struct __timeval32 *timeout) */
	.weak __asm64_syscall_select
INTERN_FUNCTION(__asm64_syscall_select)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x17
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_select
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_select)

.section .text.x86.asm64_syscall.sched_yield
	/* errno_t sched_yield(void); */
	.weak __asm64_syscall_sched_yield
INTERN_FUNCTION(__asm64_syscall_sched_yield)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x18
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_yield
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_yield)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
.section .text.x86.asm64_syscall.mremap
	/* void *mremap(void *addr,
	 *              size_t old_len,
	 *              size_t new_len,
	 *              syscall_ulong_t flags,
	 *              void *new_address) */
	.weak __asm64_syscall_mremap
INTERN_FUNCTION(__asm64_syscall_mremap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x19
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_mremap
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mremap)

.section .text.x86.asm64_syscall.msync
	/* errno_t msync(void *addr,
	 *               size_t len,
	 *               syscall_ulong_t flags) */
	.weak __asm64_syscall_msync
INTERN_FUNCTION(__asm64_syscall_msync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_msync
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_msync)

.section .text.x86.asm64_syscall.mincore
	/* errno_t mincore(void *start,
	 *                 size_t len,
	 *                 uint8_t *vec) */
	.weak __asm64_syscall_mincore
INTERN_FUNCTION(__asm64_syscall_mincore)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_mincore
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mincore)

.section .text.x86.asm64_syscall.madvise
	/* errno_t madvise(void *addr,
	 *                 size_t len,
	 *                 syscall_ulong_t advice) */
	.weak __asm64_syscall_madvise
INTERN_FUNCTION(__asm64_syscall_madvise)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_madvise
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_madvise)

.section .text.x86.asm64_syscall.dup
	/* fd_t dup(fd_t fd) */
	.weak __asm64_syscall_dup
INTERN_FUNCTION(__asm64_syscall_dup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x20
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_dup
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_dup)

.section .text.x86.asm64_syscall.dup2
	/* fd_t dup2(fd_t oldfd,
	 *           fd_t newfd) */
	.weak __asm64_syscall_dup2
INTERN_FUNCTION(__asm64_syscall_dup2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x21
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_dup2
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_dup2)

.section .text.x86.asm64_syscall.pause
	/* errno_t pause(void); */
	.weak __asm64_syscall_pause
INTERN_FUNCTION(__asm64_syscall_pause)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x22
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_pause
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pause)

.section .text.x86.asm64_syscall.nanosleep
	/* errno_t nanosleep(struct __timespec32 const *req,
	 *                   struct __timespec32 *rem) */
	.weak __asm64_syscall_nanosleep
INTERN_FUNCTION(__asm64_syscall_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x23
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_nanosleep
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_nanosleep)

.section .text.x86.asm64_syscall.getitimer
	/* errno_t getitimer(syscall_ulong_t which,
	 *                   struct __itimerval32 *curr_value) */
	.weak __asm64_syscall_getitimer
INTERN_FUNCTION(__asm64_syscall_getitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x24
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getitimer
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getitimer)

.section .text.x86.asm64_syscall.alarm
	/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
	.weak __asm64_syscall_alarm
INTERN_FUNCTION(__asm64_syscall_alarm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x25
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_alarm
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_alarm)

.section .text.x86.asm64_syscall.setitimer
	/* errno_t setitimer(syscall_ulong_t which,
	 *                   struct __itimerval32 const *newval,
	 *                   struct __itimerval32 *oldval) */
	.weak __asm64_syscall_setitimer
INTERN_FUNCTION(__asm64_syscall_setitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x26
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setitimer
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setitimer)

.section .text.x86.asm64_syscall.getpid
	/* pid_t getpid(void); */
	.weak __asm64_syscall_getpid
INTERN_FUNCTION(__asm64_syscall_getpid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x27
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getpid
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getpid)

.section .text.x86.asm64_syscall.sendfile
	/* ssize_t sendfile(fd_t out_fd,
	 *                  fd_t in_fd,
	 *                  syscall_ulong_t *offset,
	 *                  size_t count) */
	.weak __asm64_syscall_sendfile
INTERN_FUNCTION(__asm64_syscall_sendfile)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x28
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_sendfile
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sendfile)

.section .text.x86.asm64_syscall.socket
	/* fd_t socket(syscall_ulong_t domain,
	 *             syscall_ulong_t type,
	 *             syscall_ulong_t protocol) */
	.weak __asm64_syscall_socket
INTERN_FUNCTION(__asm64_syscall_socket)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x29
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_socket
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_socket)

.section .text.x86.asm64_syscall.connect
	/* errno_t connect(fd_t sockfd,
	 *                 struct sockaddr const *addr,
	 *                 socklen_t addr_len) */
	.weak __asm64_syscall_connect
INTERN_FUNCTION(__asm64_syscall_connect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_connect
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_connect)

/* param flags: Set of `MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL|MSG_OOB' */
.section .text.x86.asm64_syscall.sendto
	/* ssize_t sendto(fd_t sockfd,
	 *                void const *buf,
	 *                size_t bufsize,
	 *                syscall_ulong_t flags,
	 *                struct sockaddr const *addr,
	 *                socklen_t addr_len) */
	.weak __asm64_syscall_sendto
INTERN_FUNCTION(__asm64_syscall_sendto)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_sendto
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sendto)

.section .text.x86.asm64_syscall.recvfrom
	/* ssize_t recvfrom(fd_t sockfd,
	 *                  void *buf,
	 *                  size_t bufsize,
	 *                  syscall_ulong_t flags,
	 *                  struct sockaddr *addr,
	 *                  socklen_t *addr_len) */
	.weak __asm64_syscall_recvfrom
INTERN_FUNCTION(__asm64_syscall_recvfrom)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_recvfrom
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_recvfrom)

.section .text.x86.asm64_syscall.sendmsg
	/* ssize_t sendmsg(fd_t sockfd,
	 *                 struct msghdr const *message,
	 *                 syscall_ulong_t flags) */
	.weak __asm64_syscall_sendmsg
INTERN_FUNCTION(__asm64_syscall_sendmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sendmsg
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sendmsg)

.section .text.x86.asm64_syscall.recvmsg
	/* ssize_t recvmsg(fd_t sockfd,
	 *                 struct msghdr *message,
	 *                 syscall_ulong_t flags) */
	.weak __asm64_syscall_recvmsg
INTERN_FUNCTION(__asm64_syscall_recvmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_recvmsg
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_recvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
.section .text.x86.asm64_syscall.shutdown
	/* errno_t shutdown(fd_t sockfd,
	 *                  syscall_ulong_t how) */
	.weak __asm64_syscall_shutdown
INTERN_FUNCTION(__asm64_syscall_shutdown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x30
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_shutdown
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_shutdown)

.section .text.x86.asm64_syscall.bind
	/* errno_t bind(fd_t sockfd,
	 *              struct sockaddr const *addr,
	 *              socklen_t addr_len) */
	.weak __asm64_syscall_bind
INTERN_FUNCTION(__asm64_syscall_bind)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x31
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_bind
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_bind)

.section .text.x86.asm64_syscall.listen
	/* errno_t listen(fd_t sockfd,
	 *                syscall_ulong_t max_backlog) */
	.weak __asm64_syscall_listen
INTERN_FUNCTION(__asm64_syscall_listen)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x32
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_listen
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_listen)

.section .text.x86.asm64_syscall.getsockname
	/* errno_t getsockname(fd_t sockfd,
	 *                     struct sockaddr *addr,
	 *                     socklen_t *addr_len) */
	.weak __asm64_syscall_getsockname
INTERN_FUNCTION(__asm64_syscall_getsockname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x33
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getsockname
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getsockname)

.section .text.x86.asm64_syscall.getpeername
	/* errno_t getpeername(fd_t sockfd,
	 *                     struct sockaddr *addr,
	 *                     socklen_t *addr_len) */
	.weak __asm64_syscall_getpeername
INTERN_FUNCTION(__asm64_syscall_getpeername)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x34
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getpeername
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getpeername)

.section .text.x86.asm64_syscall.socketpair
	/* errno_t socketpair(syscall_ulong_t domain,
	 *                    syscall_ulong_t type,
	 *                    syscall_ulong_t protocol,
	 *                    [2] fd_t *fds) */
	.weak __asm64_syscall_socketpair
INTERN_FUNCTION(__asm64_syscall_socketpair)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x35
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_socketpair
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_socketpair)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.x86.asm64_syscall.setsockopt
	/* errno_t setsockopt(fd_t sockfd,
	 *                    syscall_ulong_t level,
	 *                    syscall_ulong_t optname,
	 *                    void const *optval,
	 *                    socklen_t optlen) */
	.weak __asm64_syscall_setsockopt
INTERN_FUNCTION(__asm64_syscall_setsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x36
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_setsockopt
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.x86.asm64_syscall.getsockopt
	/* errno_t getsockopt(fd_t sockfd,
	 *                    syscall_ulong_t level,
	 *                    syscall_ulong_t optname,
	 *                    void *optval,
	 *                    socklen_t *optlen) */
	.weak __asm64_syscall_getsockopt
INTERN_FUNCTION(__asm64_syscall_getsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x37
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_getsockopt
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getsockopt)

.section .text.x86.asm64_syscall.clone
	/* pid_t clone(syscall_ulong_t flags,
	 *             void *child_stack,
	 *             pid_t *ptid,
	 *             pid_t *ctid,
	 *             uintptr_t newtls) */
	.weak __asm64_syscall_clone
INTERN_FUNCTION(__asm64_syscall_clone)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x38
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_clone
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_clone)

.section .text.x86.asm64_syscall.fork
	/* pid_t fork(void); */
	.weak __asm64_syscall_fork
INTERN_FUNCTION(__asm64_syscall_fork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x39
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fork
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fork)

.section .text.x86.asm64_syscall.vfork
	/* pid_t vfork(void); */
	.weak __asm64_syscall_vfork
INTERN_FUNCTION(__asm64_syscall_vfork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_vfork
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_vfork)

.section .text.x86.asm64_syscall.execve
	/* errno_t execve(char const *path,
	 *                char const *const *argv,
	 *                char const *const *envp) */
	.weak __asm64_syscall_execve
INTERN_FUNCTION(__asm64_syscall_execve)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_execve
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_execve)

.section .text.x86.asm64_syscall.exit
	/* void exit(syscall_ulong_t status) */
	.weak __asm64_syscall_exit
INTERN_FUNCTION(__asm64_syscall_exit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_exit
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_exit)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
.section .text.x86.asm64_syscall.wait4
	/* pid_t wait4(pid_t pid,
	 *             int32_t *stat_loc,
	 *             syscall_ulong_t options,
	 *             struct rusage *usage) */
	.weak __asm64_syscall_wait4
INTERN_FUNCTION(__asm64_syscall_wait4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_wait4
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_wait4)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm64_syscall.kill
	/* errno_t kill(pid_t pid,
	 *              syscall_ulong_t signo) */
	.weak __asm64_syscall_kill
INTERN_FUNCTION(__asm64_syscall_kill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_kill
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_kill)

.section .text.x86.asm64_syscall.uname
	/* errno_t uname(struct utsname *name) */
	.weak __asm64_syscall_uname
INTERN_FUNCTION(__asm64_syscall_uname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_uname
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_uname)

.section .text.x86.asm64_syscall.fcntl
	/* syscall_slong_t fcntl(fd_t fd,
	 *                       syscall_ulong_t cmd,
	 *                       void *arg) */
	.weak __asm64_syscall_fcntl
INTERN_FUNCTION(__asm64_syscall_fcntl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x48
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fcntl
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fcntl)

.section .text.x86.asm64_syscall.flock
	/* errno_t flock(fd_t fd,
	 *               syscall_ulong_t operation) */
	.weak __asm64_syscall_flock
INTERN_FUNCTION(__asm64_syscall_flock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x49
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_flock
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_flock)

.section .text.x86.asm64_syscall.fsync
	/* errno_t fsync(fd_t fd) */
	.weak __asm64_syscall_fsync
INTERN_FUNCTION(__asm64_syscall_fsync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fsync
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fsync)

.section .text.x86.asm64_syscall.fdatasync
	/* errno_t fdatasync(fd_t fd) */
	.weak __asm64_syscall_fdatasync
INTERN_FUNCTION(__asm64_syscall_fdatasync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fdatasync
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fdatasync)

.section .text.x86.asm64_syscall.truncate
	/* errno_t truncate(char const *filename,
	 *                  syscall_ulong_t length) */
	.weak __asm64_syscall_truncate
INTERN_FUNCTION(__asm64_syscall_truncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_truncate
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_truncate)

.section .text.x86.asm64_syscall.ftruncate
	/* errno_t ftruncate(fd_t fd,
	 *                   syscall_ulong_t length) */
	.weak __asm64_syscall_ftruncate
INTERN_FUNCTION(__asm64_syscall_ftruncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_ftruncate
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_ftruncate)

.section .text.x86.asm64_syscall.getdents
	/* ssize_t getdents(fd_t fd,
	 *                  struct linux_dirent *dirp,
	 *                  size_t count) */
	.weak __asm64_syscall_getdents
INTERN_FUNCTION(__asm64_syscall_getdents)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getdents
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getdents)

.section .text.x86.asm64_syscall.getcwd
	/* ssize_t getcwd(char *buf,
	 *                size_t size) */
	.weak __asm64_syscall_getcwd
INTERN_FUNCTION(__asm64_syscall_getcwd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getcwd
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getcwd)

.section .text.x86.asm64_syscall.chdir
	/* errno_t chdir(char const *path) */
	.weak __asm64_syscall_chdir
INTERN_FUNCTION(__asm64_syscall_chdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x50
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_chdir
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_chdir)

.section .text.x86.asm64_syscall.fchdir
	/* errno_t fchdir(fd_t fd) */
	.weak __asm64_syscall_fchdir
INTERN_FUNCTION(__asm64_syscall_fchdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x51
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fchdir
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fchdir)

.section .text.x86.asm64_syscall.rename
	/* errno_t rename(char const *oldname,
	 *                char const *newname_or_path) */
	.weak __asm64_syscall_rename
INTERN_FUNCTION(__asm64_syscall_rename)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x52
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_rename
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rename)

.section .text.x86.asm64_syscall.mkdir
	/* errno_t mkdir(char const *pathname,
	 *               mode_t mode) */
	.weak __asm64_syscall_mkdir
INTERN_FUNCTION(__asm64_syscall_mkdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x53
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_mkdir
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mkdir)

.section .text.x86.asm64_syscall.rmdir
	/* errno_t rmdir(char const *path) */
	.weak __asm64_syscall_rmdir
INTERN_FUNCTION(__asm64_syscall_rmdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x54
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_rmdir
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rmdir)

.section .text.x86.asm64_syscall.creat
	/* fd_t creat(char const *filename,
	 *            mode_t mode) */
	.weak __asm64_syscall_creat
INTERN_FUNCTION(__asm64_syscall_creat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x55
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_creat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_creat)

.section .text.x86.asm64_syscall.link
	/* errno_t link(char const *existing_file,
	 *              char const *link_file) */
	.weak __asm64_syscall_link
INTERN_FUNCTION(__asm64_syscall_link)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x56
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_link
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_link)

.section .text.x86.asm64_syscall.unlink
	/* errno_t unlink(char const *filename) */
	.weak __asm64_syscall_unlink
INTERN_FUNCTION(__asm64_syscall_unlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x57
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_unlink
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_unlink)

.section .text.x86.asm64_syscall.symlink
	/* errno_t symlink(char const *link_text,
	 *                 char const *target_path) */
	.weak __asm64_syscall_symlink
INTERN_FUNCTION(__asm64_syscall_symlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x58
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_symlink
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_symlink)

.section .text.x86.asm64_syscall.readlink
	/* ssize_t readlink(char const *path,
	 *                  char *buf,
	 *                  size_t buflen) */
	.weak __asm64_syscall_readlink
INTERN_FUNCTION(__asm64_syscall_readlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x59
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_readlink
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_readlink)

.section .text.x86.asm64_syscall.chmod
	/* errno_t chmod(char const *filename,
	 *               mode_t mode) */
	.weak __asm64_syscall_chmod
INTERN_FUNCTION(__asm64_syscall_chmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_chmod
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_chmod)

.section .text.x86.asm64_syscall.fchmod
	/* errno_t fchmod(fd_t fd,
	 *                mode_t mode) */
	.weak __asm64_syscall_fchmod
INTERN_FUNCTION(__asm64_syscall_fchmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fchmod
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fchmod)

.section .text.x86.asm64_syscall.chown
	/* errno_t chown(char const *filename,
	 *               uint32_t owner,
	 *               uint32_t group) */
	.weak __asm64_syscall_chown
INTERN_FUNCTION(__asm64_syscall_chown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_chown
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_chown)

.section .text.x86.asm64_syscall.fchown
	/* errno_t fchown(fd_t fd,
	 *                uint32_t owner,
	 *                uint32_t group) */
	.weak __asm64_syscall_fchown
INTERN_FUNCTION(__asm64_syscall_fchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fchown
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fchown)

.section .text.x86.asm64_syscall.lchown
	/* errno_t lchown(char const *filename,
	 *                uint32_t owner,
	 *                uint32_t group) */
	.weak __asm64_syscall_lchown
INTERN_FUNCTION(__asm64_syscall_lchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_lchown
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_lchown)

.section .text.x86.asm64_syscall.umask
	/* mode_t umask(mode_t mode) */
	.weak __asm64_syscall_umask
INTERN_FUNCTION(__asm64_syscall_umask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_umask
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_umask)

.section .text.x86.asm64_syscall.gettimeofday
	/* errno_t gettimeofday(struct __timeval32 *tv,
	 *                      struct timezone *tz) */
	.weak __asm64_syscall_gettimeofday
INTERN_FUNCTION(__asm64_syscall_gettimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x60
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_gettimeofday
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_gettimeofday)

.section .text.x86.asm64_syscall.getrlimit
	/* errno_t getrlimit(syscall_ulong_t resource,
	 *                   struct rlimit *rlimits) */
	.weak __asm64_syscall_getrlimit
INTERN_FUNCTION(__asm64_syscall_getrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x61
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getrlimit
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getrlimit)

.section .text.x86.asm64_syscall.getrusage
	/* errno_t getrusage(syscall_slong_t who,
	 *                   struct rusage *usage) */
	.weak __asm64_syscall_getrusage
INTERN_FUNCTION(__asm64_syscall_getrusage)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x62
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getrusage
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getrusage)

.section .text.x86.asm64_syscall.sysinfo
	/* errno_t sysinfo(struct sysinfo *info) */
	.weak __asm64_syscall_sysinfo
INTERN_FUNCTION(__asm64_syscall_sysinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x63
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sysinfo
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sysinfo)

.section .text.x86.asm64_syscall.times
	/* clock_t times(struct tms *buf) */
	.weak __asm64_syscall_times
INTERN_FUNCTION(__asm64_syscall_times)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x64
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_times
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_times)

.section .text.x86.asm64_syscall.ptrace
	/* syscall_slong_t ptrace(syscall_ulong_t request,
	 *                        pid_t pid,
	 *                        void *addr,
	 *                        void *data) */
	.weak __asm64_syscall_ptrace
INTERN_FUNCTION(__asm64_syscall_ptrace)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x65
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_ptrace
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_ptrace)

.section .text.x86.asm64_syscall.getuid32
	/* uint32_t getuid32(void); */
	.weak __asm64_syscall_getuid32
INTERN_FUNCTION(__asm64_syscall_getuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x66
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getuid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getuid32)

.section .text.x86.asm64_syscall.syslog
	/* ssize_t syslog(syscall_ulong_t level,
	 *                char const *str,
	 *                size_t len) */
	.weak __asm64_syscall_syslog
INTERN_FUNCTION(__asm64_syscall_syslog)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x67
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_syslog
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_syslog)

.section .text.x86.asm64_syscall.getgid32
	/* uint32_t getgid32(void); */
	.weak __asm64_syscall_getgid32
INTERN_FUNCTION(__asm64_syscall_getgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x68
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getgid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getgid32)

.section .text.x86.asm64_syscall.setuid32
	/* errno_t setuid32(uint32_t uid) */
	.weak __asm64_syscall_setuid32
INTERN_FUNCTION(__asm64_syscall_setuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x69
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setuid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setuid32)

.section .text.x86.asm64_syscall.setgid32
	/* errno_t setgid32(uint32_t gid) */
	.weak __asm64_syscall_setgid32
INTERN_FUNCTION(__asm64_syscall_setgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setgid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setgid32)

.section .text.x86.asm64_syscall.geteuid32
	/* uint32_t geteuid32(void); */
	.weak __asm64_syscall_geteuid32
INTERN_FUNCTION(__asm64_syscall_geteuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_geteuid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_geteuid32)

.section .text.x86.asm64_syscall.getegid32
	/* uint32_t getegid32(void); */
	.weak __asm64_syscall_getegid32
INTERN_FUNCTION(__asm64_syscall_getegid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getegid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getegid32)

.section .text.x86.asm64_syscall.setpgid
	/* errno_t setpgid(pid_t pid,
	 *                 pid_t pgid) */
	.weak __asm64_syscall_setpgid
INTERN_FUNCTION(__asm64_syscall_setpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setpgid
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setpgid)

.section .text.x86.asm64_syscall.getppid
	/* pid_t getppid(void); */
	.weak __asm64_syscall_getppid
INTERN_FUNCTION(__asm64_syscall_getppid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getppid
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getppid)

.section .text.x86.asm64_syscall.getpgrp
	/* pid_t getpgrp(void); */
	.weak __asm64_syscall_getpgrp
INTERN_FUNCTION(__asm64_syscall_getpgrp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getpgrp
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getpgrp)

.section .text.x86.asm64_syscall.setsid
	/* pid_t setsid(void); */
	.weak __asm64_syscall_setsid
INTERN_FUNCTION(__asm64_syscall_setsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x70
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setsid
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setsid)

.section .text.x86.asm64_syscall.setreuid32
	/* errno_t setreuid32(uint32_t ruid,
	 *                    uint32_t euid) */
	.weak __asm64_syscall_setreuid32
INTERN_FUNCTION(__asm64_syscall_setreuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x71
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setreuid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setreuid32)

.section .text.x86.asm64_syscall.setregid32
	/* errno_t setregid32(uint32_t rgid,
	 *                    uint32_t egid) */
	.weak __asm64_syscall_setregid32
INTERN_FUNCTION(__asm64_syscall_setregid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x72
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setregid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setregid32)

.section .text.x86.asm64_syscall.getgroups32
	/* errno_t getgroups32(size_t size,
	 *                     [] uint32_t *list) */
	.weak __asm64_syscall_getgroups32
INTERN_FUNCTION(__asm64_syscall_getgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x73
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getgroups32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getgroups32)

.section .text.x86.asm64_syscall.setgroups32
	/* errno_t setgroups32(size_t count,
	 *                     uint32_t const *groups) */
	.weak __asm64_syscall_setgroups32
INTERN_FUNCTION(__asm64_syscall_setgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x74
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setgroups32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setgroups32)

.section .text.x86.asm64_syscall.setresuid32
	/* errno_t setresuid32(uint32_t ruid,
	 *                     uint32_t euid,
	 *                     uint32_t suid) */
	.weak __asm64_syscall_setresuid32
INTERN_FUNCTION(__asm64_syscall_setresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x75
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setresuid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setresuid32)

.section .text.x86.asm64_syscall.getresuid32
	/* errno_t getresuid32(uint32_t *ruid,
	 *                     uint32_t *euid,
	 *                     uint32_t *suid) */
	.weak __asm64_syscall_getresuid32
INTERN_FUNCTION(__asm64_syscall_getresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x76
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getresuid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getresuid32)

.section .text.x86.asm64_syscall.setresgid32
	/* errno_t setresgid32(uint32_t rgid,
	 *                     uint32_t egid,
	 *                     uint32_t sgid) */
	.weak __asm64_syscall_setresgid32
INTERN_FUNCTION(__asm64_syscall_setresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x77
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setresgid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setresgid32)

.section .text.x86.asm64_syscall.getresgid32
	/* errno_t getresgid32(uint32_t *rgid,
	 *                     uint32_t *egid,
	 *                     uint32_t *sgid) */
	.weak __asm64_syscall_getresgid32
INTERN_FUNCTION(__asm64_syscall_getresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x78
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getresgid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getresgid32)

.section .text.x86.asm64_syscall.getpgid
	/* pid_t getpgid(pid_t pid) */
	.weak __asm64_syscall_getpgid
INTERN_FUNCTION(__asm64_syscall_getpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x79
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getpgid
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getpgid)

.section .text.x86.asm64_syscall.setfsuid32
	/* errno_t setfsuid32(uint32_t uid) */
	.weak __asm64_syscall_setfsuid32
INTERN_FUNCTION(__asm64_syscall_setfsuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setfsuid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setfsuid32)

.section .text.x86.asm64_syscall.setfsgid32
	/* errno_t setfsgid32(uint32_t gid) */
	.weak __asm64_syscall_setfsgid32
INTERN_FUNCTION(__asm64_syscall_setfsgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setfsgid32
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setfsgid32)

.section .text.x86.asm64_syscall.getsid
	/* pid_t getsid(pid_t pid) */
	.weak __asm64_syscall_getsid
INTERN_FUNCTION(__asm64_syscall_getsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getsid
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getsid)

.section .text.x86.asm64_syscall.rt_sigpending
	/* errno_t rt_sigpending(struct __sigset_struct *set,
	 *                       size_t sigsetsize) */
	.weak __asm64_syscall_rt_sigpending
INTERN_FUNCTION(__asm64_syscall_rt_sigpending)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_rt_sigpending
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rt_sigpending)

.section .text.x86.asm64_syscall.rt_sigtimedwait
	/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set,
	 *                                 struct __siginfo_struct *info,
	 *                                 struct __timespec32 const *timeout,
	 *                                 size_t sigsetsize) */
	.weak __asm64_syscall_rt_sigtimedwait
INTERN_FUNCTION(__asm64_syscall_rt_sigtimedwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_rt_sigtimedwait
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rt_sigtimedwait)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm64_syscall.rt_sigqueueinfo
	/* errno_t rt_sigqueueinfo(pid_t tgid,
	 *                         syscall_ulong_t signo,
	 *                         struct __siginfo_struct const *uinfo) */
	.weak __asm64_syscall_rt_sigqueueinfo
INTERN_FUNCTION(__asm64_syscall_rt_sigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x81
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_rt_sigqueueinfo
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rt_sigqueueinfo)

.section .text.x86.asm64_syscall.rt_sigsuspend
	/* errno_t rt_sigsuspend(struct __sigset_struct const *set,
	 *                       size_t sigsetsize) */
	.weak __asm64_syscall_rt_sigsuspend
INTERN_FUNCTION(__asm64_syscall_rt_sigsuspend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x82
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_rt_sigsuspend
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rt_sigsuspend)

.section .text.x86.asm64_syscall.sigaltstack
	/* errno_t sigaltstack(struct sigaltstack const *ss,
	 *                     struct sigaltstack *oss) */
	.weak __asm64_syscall_sigaltstack
INTERN_FUNCTION(__asm64_syscall_sigaltstack)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x83
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sigaltstack
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sigaltstack)

.section .text.x86.asm64_syscall.utime
	/* errno_t utime(char const *filename,
	 *               struct __utimbuf32 const *times) */
	.weak __asm64_syscall_utime
INTERN_FUNCTION(__asm64_syscall_utime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x84
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_utime
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_utime)

.section .text.x86.asm64_syscall.mknod
	/* errno_t mknod(char const *nodename,
	 *               mode_t mode,
	 *               dev_t dev) */
	.weak __asm64_syscall_mknod
INTERN_FUNCTION(__asm64_syscall_mknod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x85
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_mknod
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mknod)

.section .text.x86.asm64_syscall.ustat
	/* errno_t ustat(dev_t dev,
	 *               struct ustat *ubuf) */
	.weak __asm64_syscall_ustat
INTERN_FUNCTION(__asm64_syscall_ustat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x88
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_ustat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_ustat)

.section .text.x86.asm64_syscall.statfs
	/* errno_t statfs(char const *file,
	 *                struct __statfs32 *buf) */
	.weak __asm64_syscall_statfs
INTERN_FUNCTION(__asm64_syscall_statfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x89
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_statfs
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_statfs)

.section .text.x86.asm64_syscall.fstatfs
	/* errno_t fstatfs(fd_t file,
	 *                 struct __statfs32 *buf) */
	.weak __asm64_syscall_fstatfs
INTERN_FUNCTION(__asm64_syscall_fstatfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fstatfs
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fstatfs)

.section .text.x86.asm64_syscall.getpriority
	/* syscall_slong_t getpriority(syscall_ulong_t which,
	 *                             id_t who) */
	.weak __asm64_syscall_getpriority
INTERN_FUNCTION(__asm64_syscall_getpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getpriority
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getpriority)

.section .text.x86.asm64_syscall.setpriority
	/* errno_t setpriority(syscall_ulong_t which,
	 *                     id_t who,
	 *                     syscall_ulong_t value) */
	.weak __asm64_syscall_setpriority
INTERN_FUNCTION(__asm64_syscall_setpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setpriority
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setpriority)

.section .text.x86.asm64_syscall.sched_setparam
	/* errno_t sched_setparam(pid_t pid,
	 *                        struct sched_param const *param) */
	.weak __asm64_syscall_sched_setparam
INTERN_FUNCTION(__asm64_syscall_sched_setparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_setparam
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_setparam)

.section .text.x86.asm64_syscall.sched_getparam
	/* errno_t sched_getparam(pid_t pid,
	 *                        struct sched_param *param) */
	.weak __asm64_syscall_sched_getparam
INTERN_FUNCTION(__asm64_syscall_sched_getparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_getparam
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_getparam)

.section .text.x86.asm64_syscall.sched_setscheduler
	/* errno_t sched_setscheduler(pid_t pid,
	 *                            syscall_ulong_t policy,
	 *                            struct sched_param const *param) */
	.weak __asm64_syscall_sched_setscheduler
INTERN_FUNCTION(__asm64_syscall_sched_setscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x90
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_setscheduler
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_setscheduler)

.section .text.x86.asm64_syscall.sched_getscheduler
	/* syscall_slong_t sched_getscheduler(pid_t pid) */
	.weak __asm64_syscall_sched_getscheduler
INTERN_FUNCTION(__asm64_syscall_sched_getscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x91
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_getscheduler
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_getscheduler)

.section .text.x86.asm64_syscall.sched_get_priority_max
	/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
	.weak __asm64_syscall_sched_get_priority_max
INTERN_FUNCTION(__asm64_syscall_sched_get_priority_max)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x92
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_get_priority_max
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_get_priority_max)

.section .text.x86.asm64_syscall.sched_get_priority_min
	/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
	.weak __asm64_syscall_sched_get_priority_min
INTERN_FUNCTION(__asm64_syscall_sched_get_priority_min)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x93
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_get_priority_min
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_get_priority_min)

.section .text.x86.asm64_syscall.sched_rr_get_interval
	/* errno_t sched_rr_get_interval(pid_t pid,
	 *                               struct __timespec32 *tms) */
	.weak __asm64_syscall_sched_rr_get_interval
INTERN_FUNCTION(__asm64_syscall_sched_rr_get_interval)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x94
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_rr_get_interval
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_rr_get_interval)

.section .text.x86.asm64_syscall.mlock
	/* errno_t mlock(void const *addr,
	 *               size_t len) */
	.weak __asm64_syscall_mlock
INTERN_FUNCTION(__asm64_syscall_mlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x95
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_mlock
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mlock)

.section .text.x86.asm64_syscall.munlock
	/* errno_t munlock(void const *addr,
	 *                 size_t len) */
	.weak __asm64_syscall_munlock
INTERN_FUNCTION(__asm64_syscall_munlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x96
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_munlock
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_munlock)

.section .text.x86.asm64_syscall.mlockall
	/* errno_t mlockall(syscall_ulong_t flags) */
	.weak __asm64_syscall_mlockall
INTERN_FUNCTION(__asm64_syscall_mlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x97
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_mlockall
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mlockall)

.section .text.x86.asm64_syscall.munlockall
	/* errno_t munlockall(void); */
	.weak __asm64_syscall_munlockall
INTERN_FUNCTION(__asm64_syscall_munlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x98
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_munlockall
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_munlockall)

.section .text.x86.asm64_syscall.vhangup
	/* errno_t vhangup(void); */
	.weak __asm64_syscall_vhangup
INTERN_FUNCTION(__asm64_syscall_vhangup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x99
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_vhangup
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_vhangup)

.section .text.x86.asm64_syscall.modify_ldt
	/* syscall_slong_t modify_ldt(syscall_ulong_t func,
	 *                            void *ptr,
	 *                            syscall_ulong_t bytecount) */
	.weak __asm64_syscall_modify_ldt
INTERN_FUNCTION(__asm64_syscall_modify_ldt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x9a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_modify_ldt
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_modify_ldt)

.section .text.x86.asm64_syscall.setrlimit
	/* errno_t setrlimit(syscall_ulong_t resource,
	 *                   struct rlimit const *rlimits) */
	.weak __asm64_syscall_setrlimit
INTERN_FUNCTION(__asm64_syscall_setrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setrlimit
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setrlimit)

.section .text.x86.asm64_syscall.chroot
	/* errno_t chroot(char const *path) */
	.weak __asm64_syscall_chroot
INTERN_FUNCTION(__asm64_syscall_chroot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_chroot
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_chroot)

.section .text.x86.asm64_syscall.sync
	/* errno_t sync(void); */
	.weak __asm64_syscall_sync
INTERN_FUNCTION(__asm64_syscall_sync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sync
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sync)

.section .text.x86.asm64_syscall.acct
	/* errno_t acct(char const *filename) */
	.weak __asm64_syscall_acct
INTERN_FUNCTION(__asm64_syscall_acct)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_acct
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_acct)

.section .text.x86.asm64_syscall.settimeofday
	/* errno_t settimeofday(struct __timeval32 const *tv,
	 *                      struct timezone const *tz) */
	.weak __asm64_syscall_settimeofday
INTERN_FUNCTION(__asm64_syscall_settimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_settimeofday
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_settimeofday)

.section .text.x86.asm64_syscall.mount
	/* errno_t mount(char const *special_file,
	 *               char const *dir,
	 *               char const *fstype,
	 *               syscall_ulong_t rwflag,
	 *               void const *data) */
	.weak __asm64_syscall_mount
INTERN_FUNCTION(__asm64_syscall_mount)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_mount
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mount)

.section .text.x86.asm64_syscall.umount2
	/* errno_t umount2(char const *special_file,
	 *                 syscall_ulong_t flags) */
	.weak __asm64_syscall_umount2
INTERN_FUNCTION(__asm64_syscall_umount2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_umount2
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_umount2)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
.section .text.x86.asm64_syscall.swapon
	/* errno_t swapon(char const *pathname,
	 *                syscall_ulong_t swapflags) */
	.weak __asm64_syscall_swapon
INTERN_FUNCTION(__asm64_syscall_swapon)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_swapon
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_swapon)

.section .text.x86.asm64_syscall.swapoff
	/* errno_t swapoff(char const *pathname) */
	.weak __asm64_syscall_swapoff
INTERN_FUNCTION(__asm64_syscall_swapoff)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_swapoff
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_swapoff)

/* @param: howto: One of the `RB_*' constants from <sys/reboot.h> */
.section .text.x86.asm64_syscall.reboot
	/* errno_t reboot(syscall_ulong_t how) */
	.weak __asm64_syscall_reboot
INTERN_FUNCTION(__asm64_syscall_reboot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_reboot
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_reboot)

.section .text.x86.asm64_syscall.sethostname
	/* errno_t sethostname(char const *name,
	 *                     size_t len) */
	.weak __asm64_syscall_sethostname
INTERN_FUNCTION(__asm64_syscall_sethostname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xaa
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sethostname
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sethostname)

.section .text.x86.asm64_syscall.setdomainname
	/* errno_t setdomainname(char const *name,
	 *                       size_t len) */
	.weak __asm64_syscall_setdomainname
INTERN_FUNCTION(__asm64_syscall_setdomainname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xab
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setdomainname
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setdomainname)

.section .text.x86.asm64_syscall.iopl
	/* errno_t iopl(syscall_ulong_t level) */
	.weak __asm64_syscall_iopl
INTERN_FUNCTION(__asm64_syscall_iopl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xac
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_iopl
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_iopl)

.section .text.x86.asm64_syscall.ioperm
	/* errno_t ioperm(syscall_ulong_t from,
	 *                syscall_ulong_t num,
	 *                syscall_ulong_t turn_on) */
	.weak __asm64_syscall_ioperm
INTERN_FUNCTION(__asm64_syscall_ioperm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xad
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_ioperm
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_ioperm)

.section .text.x86.asm64_syscall.gettid
	/* pid_t gettid(void); */
	.weak __asm64_syscall_gettid
INTERN_FUNCTION(__asm64_syscall_gettid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xba
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_gettid
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_gettid)

.section .text.x86.asm64_syscall.readahead
	/* ssize_t readahead(fd_t fd,
	 *                   uint64_t offset,
	 *                   size_t count) */
	.weak __asm64_syscall_readahead
INTERN_FUNCTION(__asm64_syscall_readahead)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xbb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_readahead
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_readahead)

.section .text.x86.asm64_syscall.setxattr
	/* errno_t setxattr(char const *path,
	 *                  char const *name,
	 *                  void const *buf,
	 *                  size_t bufsize,
	 *                  syscall_ulong_t flags) */
	.weak __asm64_syscall_setxattr
INTERN_FUNCTION(__asm64_syscall_setxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xbc
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_setxattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setxattr)

.section .text.x86.asm64_syscall.lsetxattr
	/* errno_t lsetxattr(char const *path,
	 *                   char const *name,
	 *                   void const *buf,
	 *                   size_t bufsize,
	 *                   syscall_ulong_t flags) */
	.weak __asm64_syscall_lsetxattr
INTERN_FUNCTION(__asm64_syscall_lsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xbd
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_lsetxattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_lsetxattr)

.section .text.x86.asm64_syscall.fsetxattr
	/* errno_t fsetxattr(fd_t fd,
	 *                   char const *name,
	 *                   void const *buf,
	 *                   size_t bufsize,
	 *                   syscall_ulong_t flags) */
	.weak __asm64_syscall_fsetxattr
INTERN_FUNCTION(__asm64_syscall_fsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xbe
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fsetxattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fsetxattr)

.section .text.x86.asm64_syscall.getxattr
	/* ssize_t getxattr(char const *path,
	 *                  char const *name,
	 *                  void *buf,
	 *                  size_t bufsize) */
	.weak __asm64_syscall_getxattr
INTERN_FUNCTION(__asm64_syscall_getxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xbf
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_getxattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getxattr)

.section .text.x86.asm64_syscall.lgetxattr
	/* ssize_t lgetxattr(char const *path,
	 *                   char const *name,
	 *                   void *buf,
	 *                   size_t bufsize) */
	.weak __asm64_syscall_lgetxattr
INTERN_FUNCTION(__asm64_syscall_lgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_lgetxattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_lgetxattr)

.section .text.x86.asm64_syscall.fgetxattr
	/* ssize_t fgetxattr(fd_t fd,
	 *                   char const *name,
	 *                   void *buf,
	 *                   size_t bufsize) */
	.weak __asm64_syscall_fgetxattr
INTERN_FUNCTION(__asm64_syscall_fgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fgetxattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fgetxattr)

.section .text.x86.asm64_syscall.listxattr
	/* ssize_t listxattr(char const *path,
	 *                   char *listbuf,
	 *                   size_t listbufsize) */
	.weak __asm64_syscall_listxattr
INTERN_FUNCTION(__asm64_syscall_listxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_listxattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_listxattr)

.section .text.x86.asm64_syscall.llistxattr
	/* ssize_t llistxattr(char const *path,
	 *                    char *listbuf,
	 *                    size_t listbufsize) */
	.weak __asm64_syscall_llistxattr
INTERN_FUNCTION(__asm64_syscall_llistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_llistxattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_llistxattr)

.section .text.x86.asm64_syscall.flistxattr
	/* ssize_t flistxattr(fd_t fd,
	 *                    char *listbuf,
	 *                    size_t listbufsize) */
	.weak __asm64_syscall_flistxattr
INTERN_FUNCTION(__asm64_syscall_flistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_flistxattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_flistxattr)

.section .text.x86.asm64_syscall.removexattr
	/* errno_t removexattr(char const *path,
	 *                     char const *name) */
	.weak __asm64_syscall_removexattr
INTERN_FUNCTION(__asm64_syscall_removexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_removexattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_removexattr)

.section .text.x86.asm64_syscall.lremovexattr
	/* errno_t lremovexattr(char const *path,
	 *                      char const *name) */
	.weak __asm64_syscall_lremovexattr
INTERN_FUNCTION(__asm64_syscall_lremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_lremovexattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_lremovexattr)

.section .text.x86.asm64_syscall.fremovexattr
	/* errno_t fremovexattr(int fd,
	 *                      char const *name) */
	.weak __asm64_syscall_fremovexattr
INTERN_FUNCTION(__asm64_syscall_fremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fremovexattr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fremovexattr)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm64_syscall.tkill
	/* errno_t tkill(pid_t tid,
	 *               syscall_ulong_t signo) */
	.weak __asm64_syscall_tkill
INTERN_FUNCTION(__asm64_syscall_tkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_tkill
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_tkill)

.section .text.x86.asm64_syscall.time
	/* time32_t time(time32_t *timer) */
	.weak __asm64_syscall_time
INTERN_FUNCTION(__asm64_syscall_time)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_time
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_time)

.section .text.x86.asm64_syscall.futex
	/* syscall_slong_t futex(uint32_t *uaddr,
	 *                       syscall_ulong_t futex_op,
	 *                       uint32_t val,
	 *                       struct __timespec32 const *timeout_or_val2,
	 *                       uint32_t *uaddr2,
	 *                       uint32_t val3) */
	.weak __asm64_syscall_futex
INTERN_FUNCTION(__asm64_syscall_futex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xca
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_futex
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_futex)

.section .text.x86.asm64_syscall.sched_setaffinity
	/* errno_t sched_setaffinity(pid_t pid,
	 *                           size_t cpusetsize,
	 *                           struct __cpu_set_struct const *cpuset) */
	.weak __asm64_syscall_sched_setaffinity
INTERN_FUNCTION(__asm64_syscall_sched_setaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xcb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_setaffinity
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_setaffinity)

.section .text.x86.asm64_syscall.sched_getaffinity
	/* errno_t sched_getaffinity(pid_t pid,
	 *                           size_t cpusetsize,
	 *                           struct __cpu_set_struct *cpuset) */
	.weak __asm64_syscall_sched_getaffinity
INTERN_FUNCTION(__asm64_syscall_sched_getaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xcc
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sched_getaffinity
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sched_getaffinity)

.section .text.x86.asm64_syscall.epoll_create
	/* fd_t epoll_create(syscall_ulong_t size) */
	.weak __asm64_syscall_epoll_create
INTERN_FUNCTION(__asm64_syscall_epoll_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_epoll_create
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_epoll_create)

.section .text.x86.asm64_syscall.epoll_ctl_old
	/* errno_t epoll_ctl_old(fd_t epfd,
	 *                       syscall_ulong_t op,
	 *                       fd_t fd,
	 *                       struct epoll_event *event) */
	.weak __asm64_syscall_epoll_ctl_old
INTERN_FUNCTION(__asm64_syscall_epoll_ctl_old)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_epoll_ctl_old
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_epoll_ctl_old)

.section .text.x86.asm64_syscall.epoll_wait_old
	/* errno_t epoll_wait_old(fd_t epfd,
	 *                        struct epoll_event *events,
	 *                        syscall_ulong_t maxevents,
	 *                        syscall_slong_t timeout) */
	.weak __asm64_syscall_epoll_wait_old
INTERN_FUNCTION(__asm64_syscall_epoll_wait_old)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_epoll_wait_old
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_epoll_wait_old)

.section .text.x86.asm64_syscall.remap_file_pages
	/* errno_t remap_file_pages(void *start,
	 *                          size_t size,
	 *                          syscall_ulong_t prot,
	 *                          size_t pgoff,
	 *                          syscall_ulong_t flags) */
	.weak __asm64_syscall_remap_file_pages
INTERN_FUNCTION(__asm64_syscall_remap_file_pages)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_remap_file_pages
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_remap_file_pages)

.section .text.x86.asm64_syscall.getdents64
	/* ssize_t getdents64(fd_t fd,
	 *                    struct linux_dirent64 *dirp,
	 *                    size_t count) */
	.weak __asm64_syscall_getdents64
INTERN_FUNCTION(__asm64_syscall_getdents64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getdents64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getdents64)

.section .text.x86.asm64_syscall.set_tid_address
	/* pid_t set_tid_address(pid_t *tidptr) */
	.weak __asm64_syscall_set_tid_address
INTERN_FUNCTION(__asm64_syscall_set_tid_address)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xda
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_set_tid_address
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_set_tid_address)

.section .text.x86.asm64_syscall.timer_create
	/* errno_t timer_create(clockid_t clock_id,
	 *                      struct sigevent *evp,
	 *                      timer_t *timerid) */
	.weak __asm64_syscall_timer_create
INTERN_FUNCTION(__asm64_syscall_timer_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xde
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_timer_create
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_timer_create)

.section .text.x86.asm64_syscall.timer_settime
	/* errno_t timer_settime(timer_t timerid,
	 *                       syscall_ulong_t flags,
	 *                       struct __itimerspec32 const *value,
	 *                       struct __itimerspec32 *ovalue) */
	.weak __asm64_syscall_timer_settime
INTERN_FUNCTION(__asm64_syscall_timer_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xdf
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_timer_settime
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_timer_settime)

.section .text.x86.asm64_syscall.timer_gettime
	/* errno_t timer_gettime(timer_t timerid,
	 *                       struct __itimerspec32 *value) */
	.weak __asm64_syscall_timer_gettime
INTERN_FUNCTION(__asm64_syscall_timer_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_timer_gettime
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_timer_gettime)

.section .text.x86.asm64_syscall.timer_getoverrun
	/* syscall_slong_t timer_getoverrun(timer_t timerid) */
	.weak __asm64_syscall_timer_getoverrun
INTERN_FUNCTION(__asm64_syscall_timer_getoverrun)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_timer_getoverrun
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_timer_getoverrun)

.section .text.x86.asm64_syscall.timer_delete
	/* errno_t timer_delete(timer_t timerid) */
	.weak __asm64_syscall_timer_delete
INTERN_FUNCTION(__asm64_syscall_timer_delete)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_timer_delete
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_timer_delete)

.section .text.x86.asm64_syscall.clock_settime
	/* errno_t clock_settime(clockid_t clock_id,
	 *                       struct __timespec32 const *tp) */
	.weak __asm64_syscall_clock_settime
INTERN_FUNCTION(__asm64_syscall_clock_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_clock_settime
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_clock_settime)

.section .text.x86.asm64_syscall.clock_gettime
	/* errno_t clock_gettime(clockid_t clock_id,
	 *                       struct __timespec32 *tp) */
	.weak __asm64_syscall_clock_gettime
INTERN_FUNCTION(__asm64_syscall_clock_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_clock_gettime
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_clock_gettime)

.section .text.x86.asm64_syscall.clock_getres
	/* errno_t clock_getres(clockid_t clock_id,
	 *                      struct __timespec32 *res) */
	.weak __asm64_syscall_clock_getres
INTERN_FUNCTION(__asm64_syscall_clock_getres)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_clock_getres
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_clock_getres)

.section .text.x86.asm64_syscall.clock_nanosleep
	/* errno_t clock_nanosleep(clockid_t clock_id,
	 *                         syscall_ulong_t flags,
	 *                         struct __timespec32 const *requested_time,
	 *                         struct __timespec32 *remaining) */
	.weak __asm64_syscall_clock_nanosleep
INTERN_FUNCTION(__asm64_syscall_clock_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_clock_nanosleep
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_clock_nanosleep)

.section .text.x86.asm64_syscall.exit_group
	/* void exit_group(syscall_ulong_t exit_code) */
	.weak __asm64_syscall_exit_group
INTERN_FUNCTION(__asm64_syscall_exit_group)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_exit_group
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_exit_group)

.section .text.x86.asm64_syscall.epoll_wait
	/* errno_t epoll_wait(fd_t epfd,
	 *                    struct epoll_event *events,
	 *                    syscall_ulong_t maxevents,
	 *                    syscall_slong_t timeout) */
	.weak __asm64_syscall_epoll_wait
INTERN_FUNCTION(__asm64_syscall_epoll_wait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_epoll_wait
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_epoll_wait)

.section .text.x86.asm64_syscall.epoll_ctl
	/* errno_t epoll_ctl(fd_t epfd,
	 *                   syscall_ulong_t op,
	 *                   fd_t fd,
	 *                   struct epoll_event *event) */
	.weak __asm64_syscall_epoll_ctl
INTERN_FUNCTION(__asm64_syscall_epoll_ctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_epoll_ctl
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_epoll_ctl)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm64_syscall.tgkill
	/* errno_t tgkill(pid_t tgid,
	 *                pid_t tid,
	 *                syscall_ulong_t signo) */
	.weak __asm64_syscall_tgkill
INTERN_FUNCTION(__asm64_syscall_tgkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xea
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_tgkill
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_tgkill)

.section .text.x86.asm64_syscall.utimes
	/* errno_t utimes(char const *filename,
	 *                [2] struct __timeval32 const *times) */
	.weak __asm64_syscall_utimes
INTERN_FUNCTION(__asm64_syscall_utimes)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xeb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_utimes
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_utimes)

/* @param: options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
.section .text.x86.asm64_syscall.waitid
	/* errno_t waitid(idtype_t idtype,
	 *                id_t id,
	 *                struct __siginfo_struct *infop,
	 *                syscall_ulong_t options,
	 *                struct rusage *ru) */
	.weak __asm64_syscall_waitid
INTERN_FUNCTION(__asm64_syscall_waitid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xf7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_waitid
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_waitid)

.section .text.x86.asm64_syscall.ioprio_set
	/* errno_t ioprio_set(syscall_ulong_t which,
	 *                    syscall_ulong_t who,
	 *                    syscall_ulong_t ioprio) */
	.weak __asm64_syscall_ioprio_set
INTERN_FUNCTION(__asm64_syscall_ioprio_set)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xfb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_ioprio_set
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_ioprio_set)

.section .text.x86.asm64_syscall.ioprio_get
	/* errno_t ioprio_get(syscall_ulong_t which,
	 *                    syscall_ulong_t who) */
	.weak __asm64_syscall_ioprio_get
INTERN_FUNCTION(__asm64_syscall_ioprio_get)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xfc
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_ioprio_get
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_ioprio_get)

.section .text.x86.asm64_syscall.openat
	/* fd_t openat(fd_t dirfd,
	 *             char const *filename,
	 *             oflag_t oflags,
	 *             mode_t mode) */
	.weak __asm64_syscall_openat
INTERN_FUNCTION(__asm64_syscall_openat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x101
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_openat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_openat)

.section .text.x86.asm64_syscall.mkdirat
	/* errno_t mkdirat(fd_t dirfd,
	 *                 char const *pathname,
	 *                 mode_t mode) */
	.weak __asm64_syscall_mkdirat
INTERN_FUNCTION(__asm64_syscall_mkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x102
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_mkdirat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mkdirat)

.section .text.x86.asm64_syscall.mknodat
	/* errno_t mknodat(fd_t dirfd,
	 *                 char const *nodename,
	 *                 mode_t mode,
	 *                 dev_t dev) */
	.weak __asm64_syscall_mknodat
INTERN_FUNCTION(__asm64_syscall_mknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x103
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_mknodat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm64_syscall.fchownat
	/* errno_t fchownat(fd_t dirfd,
	 *                  char const *filename,
	 *                  uint32_t owner,
	 *                  uint32_t group,
	 *                  atflag_t flags) */
	.weak __asm64_syscall_fchownat
INTERN_FUNCTION(__asm64_syscall_fchownat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x104
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fchownat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fchownat)

.section .text.x86.asm64_syscall.futimesat
	/* errno_t futimesat(fd_t dirfd,
	 *                   const char *filename,
	 *                   [2] struct __timeval32 const *times) */
	.weak __asm64_syscall_futimesat
INTERN_FUNCTION(__asm64_syscall_futimesat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x105
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_futimesat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_futimesat)

.section .text.x86.asm64_syscall.fstatat
	/* errno_t fstatat(fd_t dirfd,
	 *                 char const *filename,
	 *                 struct linux64_stat32 *statbuf,
	 *                 atflag_t flags) */
	.weak __asm64_syscall_fstatat
INTERN_FUNCTION(__asm64_syscall_fstatat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x106
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fstatat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fstatat)

/* @param: flags: Set of `0|AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
.section .text.x86.asm64_syscall.unlinkat
	/* errno_t unlinkat(fd_t dirfd,
	 *                  char const *name,
	 *                  atflag_t flags) */
	.weak __asm64_syscall_unlinkat
INTERN_FUNCTION(__asm64_syscall_unlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x107
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_unlinkat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_unlinkat)

.section .text.x86.asm64_syscall.renameat
	/* errno_t renameat(fd_t oldfd,
	 *                  char const *oldname,
	 *                  fd_t newfd,
	 *                  char const *newname_or_path) */
	.weak __asm64_syscall_renameat
INTERN_FUNCTION(__asm64_syscall_renameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x108
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_renameat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_renameat)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
.section .text.x86.asm64_syscall.linkat
	/* errno_t linkat(fd_t fromfd,
	 *                char const *existing_file,
	 *                fd_t tofd,
	 *                char const *target_path,
	 *                atflag_t flags) */
	.weak __asm64_syscall_linkat
INTERN_FUNCTION(__asm64_syscall_linkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x109
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_linkat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_linkat)

.section .text.x86.asm64_syscall.symlinkat
	/* errno_t symlinkat(char const *link_text,
	 *                   fd_t tofd,
	 *                   char const *target_path) */
	.weak __asm64_syscall_symlinkat
INTERN_FUNCTION(__asm64_syscall_symlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_symlinkat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_symlinkat)

.section .text.x86.asm64_syscall.readlinkat
	/* ssize_t readlinkat(fd_t dirfd,
	 *                    char const *path,
	 *                    char *buf,
	 *                    size_t buflen) */
	.weak __asm64_syscall_readlinkat
INTERN_FUNCTION(__asm64_syscall_readlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_readlinkat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_readlinkat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm64_syscall.fchmodat
	/* errno_t fchmodat(fd_t dirfd,
	 *                  char const *filename,
	 *                  mode_t mode,
	 *                  atflag_t flags) */
	.weak __asm64_syscall_fchmodat
INTERN_FUNCTION(__asm64_syscall_fchmodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fchmodat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
.section .text.x86.asm64_syscall.faccessat
	/* errno_t faccessat(fd_t dirfd,
	 *                   char const *filename,
	 *                   syscall_ulong_t type,
	 *                   atflag_t flags) */
	.weak __asm64_syscall_faccessat
INTERN_FUNCTION(__asm64_syscall_faccessat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_faccessat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_faccessat)

.section .text.x86.asm64_syscall.pselect6
	/* ssize_t pselect6(size_t nfds,
	 *                  struct __fd_set_struct *readfds,
	 *                  struct __fd_set_struct *writefds,
	 *                  struct __fd_set_struct *exceptfds,
	 *                  struct __timespec32 const *timeout,
	 *                  void const *sigmask_sigset_and_len) */
	.weak __asm64_syscall_pselect6
INTERN_FUNCTION(__asm64_syscall_pselect6)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_pselect6
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pselect6)

.section .text.x86.asm64_syscall.ppoll
	/* ssize_t ppoll(struct pollfd *fds,
	 *               size_t nfds,
	 *               struct __timespec32 const *timeout_ts,
	 *               struct __sigset_struct const *sigmask,
	 *               size_t sigsetsize) */
	.weak __asm64_syscall_ppoll
INTERN_FUNCTION(__asm64_syscall_ppoll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_ppoll
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_ppoll)

/* param flags: Set of `CLONE_*' */
.section .text.x86.asm64_syscall.unshare
	/* errno_t unshare(syscall_ulong_t flags) */
	.weak __asm64_syscall_unshare
INTERN_FUNCTION(__asm64_syscall_unshare)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x110
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_unshare
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_unshare)

.section .text.x86.asm64_syscall.splice
	/* ssize_t splice(fd_t fdin,
	 *                uint64_t *offin,
	 *                fd_t fdout,
	 *                uint64_t *offout,
	 *                size_t length,
	 *                syscall_ulong_t flags) */
	.weak __asm64_syscall_splice
INTERN_FUNCTION(__asm64_syscall_splice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x113
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_splice
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_splice)

.section .text.x86.asm64_syscall.tee
	/* ssize_t tee(fd_t fdin,
	 *             fd_t fdout,
	 *             size_t length,
	 *             syscall_ulong_t flags) */
	.weak __asm64_syscall_tee
INTERN_FUNCTION(__asm64_syscall_tee)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x114
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_tee
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_tee)

.section .text.x86.asm64_syscall.sync_file_range
	/* errno_t sync_file_range(fd_t fd,
	 *                         uint64_t offset,
	 *                         uint64_t count,
	 *                         syscall_ulong_t flags) */
	.weak __asm64_syscall_sync_file_range
INTERN_FUNCTION(__asm64_syscall_sync_file_range)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x115
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_sync_file_range
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sync_file_range)

.section .text.x86.asm64_syscall.vmsplice
	/* ssize_t vmsplice(fd_t fdout,
	 *                  struct iovec const *iov,
	 *                  size_t count,
	 *                  syscall_ulong_t flags) */
	.weak __asm64_syscall_vmsplice
INTERN_FUNCTION(__asm64_syscall_vmsplice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x116
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_vmsplice
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_vmsplice)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.x86.asm64_syscall.utimensat
	/* errno_t utimensat(fd_t dirfd,
	 *                   char const *filename,
	 *                   [2-3] struct __timespec32 const *times,
	 *                   atflag_t flags) */
	.weak __asm64_syscall_utimensat
INTERN_FUNCTION(__asm64_syscall_utimensat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x118
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_utimensat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_utimensat)

.section .text.x86.asm64_syscall.epoll_pwait
	/* errno_t epoll_pwait(fd_t epfd,
	 *                     struct epoll_event *events,
	 *                     syscall_ulong_t maxevents,
	 *                     syscall_slong_t timeout,
	 *                     struct __sigset_struct const *ss) */
	.weak __asm64_syscall_epoll_pwait
INTERN_FUNCTION(__asm64_syscall_epoll_pwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x119
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_epoll_pwait
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_epoll_pwait)

.section .text.x86.asm64_syscall.signalfd
	/* errno_t signalfd(fd_t fd,
	 *                  struct __sigset_struct const *sigmask,
	 *                  size_t sigsetsize) */
	.weak __asm64_syscall_signalfd
INTERN_FUNCTION(__asm64_syscall_signalfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x11a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_signalfd
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_signalfd)

/* Return file descriptor for new interval timer source */
.section .text.x86.asm64_syscall.timerfd_create
	/* fd_t timerfd_create(clockid_t clock_id,
	 *                     syscall_ulong_t flags) */
	.weak __asm64_syscall_timerfd_create
INTERN_FUNCTION(__asm64_syscall_timerfd_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x11b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_timerfd_create
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_timerfd_create)

.section .text.x86.asm64_syscall.eventfd
	/* fd_t eventfd(syscall_ulong_t initval) */
	.weak __asm64_syscall_eventfd
INTERN_FUNCTION(__asm64_syscall_eventfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x11c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_eventfd
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_eventfd)

.section .text.x86.asm64_syscall.fallocate
	/* errno_t fallocate(fd_t fd,
	 *                   syscall_ulong_t mode,
	 *                   uint32_t offset,
	 *                   uint32_t length) */
	.weak __asm64_syscall_fallocate
INTERN_FUNCTION(__asm64_syscall_fallocate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x11d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fallocate
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
.section .text.x86.asm64_syscall.timerfd_settime
	/* errno_t timerfd_settime(fd_t ufd,
	 *                         syscall_ulong_t flags,
	 *                         struct __itimerspec32 const *utmr,
	 *                         struct __itimerspec32 *otmr) */
	.weak __asm64_syscall_timerfd_settime
INTERN_FUNCTION(__asm64_syscall_timerfd_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x11e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_timerfd_settime
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_timerfd_settime)

/* Return the next expiration time of UFD */
.section .text.x86.asm64_syscall.timerfd_gettime
	/* errno_t timerfd_gettime(fd_t ufd,
	 *                         struct __itimerspec32 *otmr) */
	.weak __asm64_syscall_timerfd_gettime
INTERN_FUNCTION(__asm64_syscall_timerfd_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x11f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_timerfd_gettime
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_timerfd_gettime)

.section .text.x86.asm64_syscall.accept4
	/* fd_t accept4(fd_t sockfd,
	 *              struct sockaddr *addr,
	 *              socklen_t *addr_len,
	 *              syscall_ulong_t flags) */
	.weak __asm64_syscall_accept4
INTERN_FUNCTION(__asm64_syscall_accept4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x120
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_accept4
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_accept4)

.section .text.x86.asm64_syscall.signalfd4
	/* errno_t signalfd4(fd_t fd,
	 *                   struct __sigset_struct const *sigmask,
	 *                   size_t sigsetsize,
	 *                   syscall_ulong_t flags) */
	.weak __asm64_syscall_signalfd4
INTERN_FUNCTION(__asm64_syscall_signalfd4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x121
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_signalfd4
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_signalfd4)

.section .text.x86.asm64_syscall.eventfd2
	/* fd_t eventfd2(syscall_ulong_t initval,
	 *               syscall_ulong_t flags) */
	.weak __asm64_syscall_eventfd2
INTERN_FUNCTION(__asm64_syscall_eventfd2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x122
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_eventfd2
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_eventfd2)

.section .text.x86.asm64_syscall.epoll_create1
	/* fd_t epoll_create1(syscall_ulong_t flags) */
	.weak __asm64_syscall_epoll_create1
INTERN_FUNCTION(__asm64_syscall_epoll_create1)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x123
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_epoll_create1
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
.section .text.x86.asm64_syscall.dup3
	/* fd_t dup3(fd_t oldfd,
	 *           fd_t newfd,
	 *           oflag_t flags) */
	.weak __asm64_syscall_dup3
INTERN_FUNCTION(__asm64_syscall_dup3)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x124
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_dup3
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_dup3)

.section .text.x86.asm64_syscall.pipe2
	/* errno_t pipe2([2] fd_t *pipedes,
	 *               oflag_t flags) */
	.weak __asm64_syscall_pipe2
INTERN_FUNCTION(__asm64_syscall_pipe2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x125
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_pipe2
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pipe2)

.section .text.x86.asm64_syscall.preadv
	/* ssize_t preadv(fd_t fd,
	 *                struct iovec const *iovec,
	 *                size_t count,
	 *                uint64_t offset) */
	.weak __asm64_syscall_preadv
INTERN_FUNCTION(__asm64_syscall_preadv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x127
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_preadv
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_preadv)

.section .text.x86.asm64_syscall.pwritev
	/* ssize_t pwritev(fd_t fd,
	 *                 struct iovec const *iovec,
	 *                 size_t count,
	 *                 uint64_t offset) */
	.weak __asm64_syscall_pwritev
INTERN_FUNCTION(__asm64_syscall_pwritev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x128
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_pwritev
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pwritev)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm64_syscall.rt_tgsigqueueinfo
	/* errno_t rt_tgsigqueueinfo(pid_t tgid,
	 *                           pid_t tid,
	 *                           syscall_ulong_t signo,
	 *                           struct __siginfo_struct const *uinfo) */
	.weak __asm64_syscall_rt_tgsigqueueinfo
INTERN_FUNCTION(__asm64_syscall_rt_tgsigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x129
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_rt_tgsigqueueinfo
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rt_tgsigqueueinfo)

.section .text.x86.asm64_syscall.recvmmsg
	/* ssize_t recvmmsg(fd_t sockfd,
	 *                  struct mmsghdr *vmessages,
	 *                  size_t vlen,
	 *                  syscall_ulong_t flags,
	 *                  struct __timespec32 *tmo) */
	.weak __asm64_syscall_recvmmsg
INTERN_FUNCTION(__asm64_syscall_recvmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_recvmmsg
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_recvmmsg)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
.section .text.x86.asm64_syscall.prlimit64
	/* errno_t prlimit64(pid_t pid,
	 *                   syscall_ulong_t resource,
	 *                   struct rlimit64 const *new_limit,
	 *                   struct rlimit64 *old_limit) */
	.weak __asm64_syscall_prlimit64
INTERN_FUNCTION(__asm64_syscall_prlimit64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_prlimit64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_prlimit64)

.section .text.x86.asm64_syscall.name_to_handle_at
	/* errno_t name_to_handle_at(fd_t dirfd,
	 *                           char const *name,
	 *                           struct file_handle *handle,
	 *                           int32_t *mnt_id,
	 *                           syscall_ulong_t flags) */
	.weak __asm64_syscall_name_to_handle_at
INTERN_FUNCTION(__asm64_syscall_name_to_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_name_to_handle_at
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_name_to_handle_at)

.section .text.x86.asm64_syscall.open_by_handle_at
	/* fd_t open_by_handle_at(fd_t mountdirfd,
	 *                        struct file_handle *handle,
	 *                        syscall_ulong_t flags) */
	.weak __asm64_syscall_open_by_handle_at
INTERN_FUNCTION(__asm64_syscall_open_by_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x130
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_open_by_handle_at
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_open_by_handle_at)

.section .text.x86.asm64_syscall.syncfs
	/* errno_t syncfs(fd_t fd) */
	.weak __asm64_syscall_syncfs
INTERN_FUNCTION(__asm64_syscall_syncfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x132
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_syncfs
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_syncfs)

.section .text.x86.asm64_syscall.sendmmsg
	/* ssize_t sendmmsg(fd_t sockfd,
	 *                  struct mmsghdr *vmessages,
	 *                  size_t vlen,
	 *                  syscall_ulong_t flags) */
	.weak __asm64_syscall_sendmmsg
INTERN_FUNCTION(__asm64_syscall_sendmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x133
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_sendmmsg
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sendmmsg)

.section .text.x86.asm64_syscall.setns
	/* errno_t setns(fd_t fd,
	 *               syscall_ulong_t nstype) */
	.weak __asm64_syscall_setns
INTERN_FUNCTION(__asm64_syscall_setns)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x134
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setns
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setns)

.section .text.x86.asm64_syscall.getcpu
	/* errno_t getcpu(uint32_t *cpu,
	 *                uint32_t *node,
	 *                struct getcpu_cache *tcache) */
	.weak __asm64_syscall_getcpu
INTERN_FUNCTION(__asm64_syscall_getcpu)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x135
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getcpu
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getcpu)

.section .text.x86.asm64_syscall.process_vm_readv
	/* ssize_t process_vm_readv(pid_t pid,
	 *                          struct iovec const *lvec,
	 *                          size_t liovcnt,
	 *                          struct iovec const *rvec,
	 *                          size_t riovcnt,
	 *                          syscall_ulong_t flags) */
	.weak __asm64_syscall_process_vm_readv
INTERN_FUNCTION(__asm64_syscall_process_vm_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x136
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_process_vm_readv
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_process_vm_readv)

.section .text.x86.asm64_syscall.process_vm_writev
	/* ssize_t process_vm_writev(pid_t pid,
	 *                           struct iovec const *lvec,
	 *                           size_t liovcnt,
	 *                           struct iovec const *rvec,
	 *                           size_t riovcnt,
	 *                           syscall_ulong_t flags) */
	.weak __asm64_syscall_process_vm_writev
INTERN_FUNCTION(__asm64_syscall_process_vm_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x137
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_process_vm_writev
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_process_vm_writev)

.section .text.x86.asm64_syscall.kcmp
	/* syscall_slong_t kcmp(pid_t pid1,
	 *                      pid_t pid2,
	 *                      syscall_ulong_t type,
	 *                      syscall_ulong_t idx1,
	 *                      syscall_ulong_t idx2) */
	.weak __asm64_syscall_kcmp
INTERN_FUNCTION(__asm64_syscall_kcmp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x138
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_kcmp
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_kcmp)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
.section .text.x86.asm64_syscall.renameat2
	/* errno_t renameat2(fd_t olddirfd,
	 *                   char const *oldpath,
	 *                   fd_t newdirfd,
	 *                   char const *newpath,
	 *                   syscall_ulong_t flags) */
	.weak __asm64_syscall_renameat2
INTERN_FUNCTION(__asm64_syscall_renameat2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x13c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_renameat2
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_renameat2)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm64_syscall.execveat
	/* errno_t execveat(fd_t dirfd,
	 *                  char const *pathname,
	 *                  char const *const *argv,
	 *                  char const *const *envp,
	 *                  atflag_t flags) */
	.weak __asm64_syscall_execveat
INTERN_FUNCTION(__asm64_syscall_execveat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x142
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_execveat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_execveat)

.section .text.x86.asm64_syscall.readf
	/* ssize_t readf(fd_t fd,
	 *               void *buf,
	 *               size_t bufsize,
	 *               iomode_t mode) */
	.weak __asm64_syscall_readf
INTERN_FUNCTION(__asm64_syscall_readf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000000
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_readf
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_readf)

.section .text.x86.asm64_syscall.writef
	/* ssize_t writef(fd_t fd,
	 *                void const *buf,
	 *                size_t bufsize,
	 *                iomode_t mode) */
	.weak __asm64_syscall_writef
INTERN_FUNCTION(__asm64_syscall_writef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000001
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_writef
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_writef)

.section .text.x86.asm64_syscall.hop
	/* syscall_slong_t hop(fd_t fd,
	 *                     syscall_ulong_t command,
	 *                     void *arg) */
	.weak __asm64_syscall_hop
INTERN_FUNCTION(__asm64_syscall_hop)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000002
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_hop
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_hop)

.section .text.x86.asm64_syscall.hopf
	/* syscall_slong_t hopf(fd_t fd,
	 *                      syscall_ulong_t command,
	 *                      iomode_t mode,
	 *                      void *arg) */
	.weak __asm64_syscall_hopf
INTERN_FUNCTION(__asm64_syscall_hopf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000003
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_hopf
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_hopf)

.section .text.x86.asm64_syscall.kstat
	/* errno_t kstat(char const *filename,
	 *               struct stat *statbuf) */
	.weak __asm64_syscall_kstat
INTERN_FUNCTION(__asm64_syscall_kstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000004
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_kstat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_kstat)

.section .text.x86.asm64_syscall.kfstat
	/* errno_t kfstat(fd_t fd,
	 *                struct stat *statbuf) */
	.weak __asm64_syscall_kfstat
INTERN_FUNCTION(__asm64_syscall_kfstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000005
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_kfstat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_kfstat)

.section .text.x86.asm64_syscall.klstat
	/* errno_t klstat(char const *filename,
	 *                struct stat *statbuf) */
	.weak __asm64_syscall_klstat
INTERN_FUNCTION(__asm64_syscall_klstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000006
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_klstat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_klstat)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
.section .text.x86.asm64_syscall.detach
	/* errno_t detach(pid_t pid) */
	.weak __asm64_syscall_detach
INTERN_FUNCTION(__asm64_syscall_detach)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000007
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_detach
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_detach)

/* Returns a bitset of all of the currently mounted dos-drives */
.section .text.x86.asm64_syscall.getdrives
	/* syscall_slong_t getdrives(void); */
	.weak __asm64_syscall_getdrives
INTERN_FUNCTION(__asm64_syscall_getdrives)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000008
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getdrives
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.x86.asm64_syscall.frealpath4
	/* ssize_t frealpath4(fd_t fd,
	 *                    char *buf,
	 *                    size_t buflen,
	 *                    atflag_t flags) */
	.weak __asm64_syscall_frealpath4
INTERN_FUNCTION(__asm64_syscall_frealpath4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000009
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_frealpath4
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_frealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.x86.asm64_syscall.frealpathat
	/* ssize_t frealpathat(fd_t dirfd,
	 *                     char const *filename,
	 *                     char *buf,
	 *                     size_t buflen,
	 *                     atflag_t flags) */
	.weak __asm64_syscall_frealpathat
INTERN_FUNCTION(__asm64_syscall_frealpathat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_frealpathat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_frealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
.section .text.x86.asm64_syscall.rpc_schedule
	/* syscall_slong_t rpc_schedule(pid_t target,
	 *                              syscall_ulong_t flags,
	 *                              uint8_t const *program,
	 *                              void **arguments) */
	.weak __asm64_syscall_rpc_schedule
INTERN_FUNCTION(__asm64_syscall_rpc_schedule)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_rpc_schedule
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rpc_schedule)

.section .text.x86.asm64_syscall.sysctl
	/* syscall_slong_t sysctl(syscall_ulong_t command,
	 *                        void *arg) */
	.weak __asm64_syscall_sysctl
INTERN_FUNCTION(__asm64_syscall_sysctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_sysctl
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_sysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
.section .text.x86.asm64_syscall.openpty
	/* errno_t openpty(fd_t *amaster,
	 *                 fd_t *aslave,
	 *                 char *name,
	 *                 struct termios const *termp,
	 *                 struct winsize const *winp) */
	.weak __asm64_syscall_openpty
INTERN_FUNCTION(__asm64_syscall_openpty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_openpty
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_openpty)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
.section .text.x86.asm64_syscall.set_exception_handler
	/* errno_t set_exception_handler(syscall_ulong_t mode,
	 *                               except_handler_t handler,
	 *                               void *handler_sp) */
	.weak __asm64_syscall_set_exception_handler
INTERN_FUNCTION(__asm64_syscall_set_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_set_exception_handler
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
.section .text.x86.asm64_syscall.get_exception_handler
	/* errno_t get_exception_handler(syscall_ulong_t *pmode,
	 *                               except_handler_t *phandler,
	 *                               void **phandler_sp) */
	.weak __asm64_syscall_get_exception_handler
INTERN_FUNCTION(__asm64_syscall_get_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_get_exception_handler
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_get_exception_handler)

.section .text.x86.asm64_syscall.ioctlf
	/* syscall_slong_t ioctlf(fd_t fd,
	 *                        syscall_ulong_t command,
	 *                        iomode_t mode,
	 *                        void *arg) */
	.weak __asm64_syscall_ioctlf
INTERN_FUNCTION(__asm64_syscall_ioctlf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000010
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_ioctlf
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_ioctlf)

.section .text.x86.asm64_syscall.pread64f
	/* ssize_t pread64f(fd_t fd,
	 *                  void *buf,
	 *                  size_t bufsize,
	 *                  uint64_t offset,
	 *                  iomode_t mode) */
	.weak __asm64_syscall_pread64f
INTERN_FUNCTION(__asm64_syscall_pread64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000011
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_pread64f
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pread64f)

.section .text.x86.asm64_syscall.pwrite64f
	/* ssize_t pwrite64f(fd_t fd,
	 *                   void const *buf,
	 *                   size_t bufsize,
	 *                   uint64_t offset,
	 *                   iomode_t mode) */
	.weak __asm64_syscall_pwrite64f
INTERN_FUNCTION(__asm64_syscall_pwrite64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000012
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_pwrite64f
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pwrite64f)

.section .text.x86.asm64_syscall.readvf
	/* ssize_t readvf(fd_t fd,
	 *                struct iovec const *iovec,
	 *                size_t count,
	 *                iomode_t mode) */
	.weak __asm64_syscall_readvf
INTERN_FUNCTION(__asm64_syscall_readvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000013
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_readvf
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_readvf)

.section .text.x86.asm64_syscall.writevf
	/* ssize_t writevf(fd_t fd,
	 *                 struct iovec const *iovec,
	 *                 size_t count,
	 *                 iomode_t mode) */
	.weak __asm64_syscall_writevf
INTERN_FUNCTION(__asm64_syscall_writevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000014
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_writevf
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_writevf)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
.section .text.x86.asm64_syscall.set_library_listdef
	/* errno_t set_library_listdef(struct library_listdef const *listdef) */
	.weak __asm64_syscall_set_library_listdef
INTERN_FUNCTION(__asm64_syscall_set_library_listdef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000015
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_set_library_listdef
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_set_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
.section .text.x86.asm64_syscall.debugtrap
	/* errno_t debugtrap(struct ucpustate const *state,
	 *                   struct debugtrap_reason const *reason) */
	.weak __asm64_syscall_debugtrap
INTERN_FUNCTION(__asm64_syscall_debugtrap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000016
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_debugtrap
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_debugtrap)

.section .text.x86.asm64_syscall.select64
	/* ssize_t select64(size_t nfds,
	 *                  struct __fd_set_struct *readfds,
	 *                  struct __fd_set_struct *writefds,
	 *                  struct __fd_set_struct *exceptfds,
	 *                  struct __timeval64 *timeout) */
	.weak __asm64_syscall_select64
INTERN_FUNCTION(__asm64_syscall_select64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000017
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_select64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_select64)

.section .text.x86.asm64_syscall.rpc_service
	/* syscall_slong_t rpc_service(void); */
	.weak __asm64_syscall_rpc_service
INTERN_FUNCTION(__asm64_syscall_rpc_service)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000018
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_rpc_service
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_rpc_service)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
.section .text.x86.asm64_syscall.lfutex
	/* syscall_slong_t lfutex(uintptr_t *uaddr,
	 *                        syscall_ulong_t futex_op,
	 *                        uintptr_t val,
	 *                        struct __timespec64 const *timeout,
	 *                        uintptr_t val2) */
	.weak __asm64_syscall_lfutex
INTERN_FUNCTION(__asm64_syscall_lfutex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000019
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_lfutex
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_lfutex)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.x86.asm64_syscall.lfutexexpr
	/* errno_t lfutexexpr(void *base,
	 *                    size_t exprc,
	 *                    struct lfutexexpr const *exprv,
	 *                    struct __timespec64 const *timeout,
	 *                    syscall_ulong_t timeout_flags) */
	.weak __asm64_syscall_lfutexexpr
INTERN_FUNCTION(__asm64_syscall_lfutexexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000001a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_lfutexexpr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_lfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.x86.asm64_syscall.lfutexlockexpr
	/* errno_t lfutexlockexpr(uintptr_t *ulockaddr,
	 *                        void *base,
	 *                        size_t exprc,
	 *                        struct lfutexexpr const *exprv,
	 *                        struct __timespec64 const *timeout,
	 *                        syscall_ulong_t timeout_flags) */
	.weak __asm64_syscall_lfutexlockexpr
INTERN_FUNCTION(__asm64_syscall_lfutexlockexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000001b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_lfutexlockexpr
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_lfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
.section .text.x86.asm64_syscall.mktty
	/* fd_t mktty(fd_t keyboard,
	 *            fd_t display,
	 *            char const *name,
	 *            syscall_ulong_t rsvd) */
	.weak __asm64_syscall_mktty
INTERN_FUNCTION(__asm64_syscall_mktty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000001c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_mktty
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_mktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
.section .text.x86.asm64_syscall.raiseat
	/* errno_t raiseat(struct ucpustate const *state,
	 *                 struct __siginfo_struct const *si) */
	.weak __asm64_syscall_raiseat
INTERN_FUNCTION(__asm64_syscall_raiseat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000001d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_raiseat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_raiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
.section .text.x86.asm64_syscall.coredump
	/* errno_t coredump(struct ucpustate const *curr_state,
	 *                  struct ucpustate const *orig_state,
	 *                  void const *const *traceback_vector,
	 *                  size_t traceback_length,
	 *                  struct exception_data const *exception,
	 *                  syscall_ulong_t unwind_error) */
	.weak __asm64_syscall_coredump
INTERN_FUNCTION(__asm64_syscall_coredump)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000001e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_coredump
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_coredump)

.section .text.x86.asm64_syscall.getitimer64
	/* errno_t getitimer64(syscall_ulong_t which,
	 *                     struct __itimerval64 *curr_value) */
	.weak __asm64_syscall_getitimer64
INTERN_FUNCTION(__asm64_syscall_getitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000024
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_getitimer64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_getitimer64)

.section .text.x86.asm64_syscall.setitimer64
	/* errno_t setitimer64(syscall_ulong_t which,
	 *                     struct __itimerval64 const *newval,
	 *                     struct __itimerval64 *oldval) */
	.weak __asm64_syscall_setitimer64
INTERN_FUNCTION(__asm64_syscall_setitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000026
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_setitimer64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_setitimer64)

.section .text.x86.asm64_syscall.kreaddir
	/* ssize_t kreaddir(fd_t fd,
	 *                  struct dirent *buf,
	 *                  size_t bufsize,
	 *                  syscall_ulong_t mode) */
	.weak __asm64_syscall_kreaddir
INTERN_FUNCTION(__asm64_syscall_kreaddir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000004e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_kreaddir
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_kreaddir)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm64_syscall.fchdirat
	/* errno_t fchdirat(fd_t dirfd,
	 *                  char const *path,
	 *                  atflag_t flags) */
	.weak __asm64_syscall_fchdirat
INTERN_FUNCTION(__asm64_syscall_fchdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000050
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fchdirat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fchdirat)

.section .text.x86.asm64_syscall.fsmode
	/* uint64_t fsmode(uint64_t mode) */
	.weak __asm64_syscall_fsmode
INTERN_FUNCTION(__asm64_syscall_fsmode)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000005f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_fsmode
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fsmode)

.section .text.x86.asm64_syscall.gettimeofday64
	/* errno_t gettimeofday64(struct __timeval64 *tv,
	 *                        struct timezone *tz) */
	.weak __asm64_syscall_gettimeofday64
INTERN_FUNCTION(__asm64_syscall_gettimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000060
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_gettimeofday64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_gettimeofday64)

.section .text.x86.asm64_syscall.utime64
	/* errno_t utime64(char const *filename,
	 *                 struct utimbuf64 const *times) */
	.weak __asm64_syscall_utime64
INTERN_FUNCTION(__asm64_syscall_utime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000084
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_utime64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_utime64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
.section .text.x86.asm64_syscall.maplibrary
	/* void *maplibrary(void *addr,
	 *                  syscall_ulong_t flags,
	 *                  fd_t fd,
	 *                  void *hdrv,
	 *                  size_t hdrc) */
	.weak __asm64_syscall_maplibrary
INTERN_FUNCTION(__asm64_syscall_maplibrary)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000086
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_maplibrary
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_maplibrary)

.section .text.x86.asm64_syscall.settimeofday64
	/* errno_t settimeofday64(struct __timeval64 const *tv,
	 *                        struct timezone const *tz) */
	.weak __asm64_syscall_settimeofday64
INTERN_FUNCTION(__asm64_syscall_settimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000a4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_settimeofday64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_settimeofday64)

.section .text.x86.asm64_syscall.time64
	/* time64_t time64(time64_t *timer) */
	.weak __asm64_syscall_time64
INTERN_FUNCTION(__asm64_syscall_time64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000c9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_time64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_time64)

.section .text.x86.asm64_syscall.kreaddirf
	/* ssize_t kreaddirf(fd_t fd,
	 *                   struct dirent *buf,
	 *                   size_t bufsize,
	 *                   syscall_ulong_t mode,
	 *                   iomode_t iomode) */
	.weak __asm64_syscall_kreaddirf
INTERN_FUNCTION(__asm64_syscall_kreaddirf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000d9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_kreaddirf
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_kreaddirf)

.section .text.x86.asm64_syscall.utimes64
	/* errno_t utimes64(char const *filename,
	 *                  [2] struct __timeval64 const *times) */
	.weak __asm64_syscall_utimes64
INTERN_FUNCTION(__asm64_syscall_utimes64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000eb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_utimes64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_utimes64)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm64_syscall.fmkdirat
	/* errno_t fmkdirat(fd_t dirfd,
	 *                  char const *pathname,
	 *                  mode_t mode,
	 *                  atflag_t flags) */
	.weak __asm64_syscall_fmkdirat
INTERN_FUNCTION(__asm64_syscall_fmkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000102
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fmkdirat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fmkdirat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm64_syscall.fmknodat
	/* errno_t fmknodat(fd_t dirfd,
	 *                  char const *nodename,
	 *                  mode_t mode,
	 *                  dev_t dev,
	 *                  atflag_t flags) */
	.weak __asm64_syscall_fmknodat
INTERN_FUNCTION(__asm64_syscall_fmknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000103
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fmknodat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fmknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.x86.asm64_syscall.futimesat64
	/* errno_t futimesat64(fd_t dirfd,
	 *                     const char *filename,
	 *                     [2-3] struct __timeval64 const *times) */
	.weak __asm64_syscall_futimesat64
INTERN_FUNCTION(__asm64_syscall_futimesat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000105
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	call   sys_futimesat64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_futimesat64)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm64_syscall.kfstatat
	/* errno_t kfstatat(fd_t dirfd,
	 *                  char const *filename,
	 *                  struct stat *statbuf,
	 *                  atflag_t flags) */
	.weak __asm64_syscall_kfstatat
INTERN_FUNCTION(__asm64_syscall_kfstatat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000106
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_kfstatat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_kfstatat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm64_syscall.frenameat
	/* errno_t frenameat(fd_t oldfd,
	 *                   char const *oldname,
	 *                   fd_t newfd,
	 *                   char const *newname_or_path,
	 *                   atflag_t flags) */
	.weak __asm64_syscall_frenameat
INTERN_FUNCTION(__asm64_syscall_frenameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000108
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_frenameat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_frenameat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm64_syscall.fsymlinkat
	/* errno_t fsymlinkat(char const *link_text,
	 *                    fd_t tofd,
	 *                    char const *target_path,
	 *                    atflag_t flags) */
	.weak __asm64_syscall_fsymlinkat
INTERN_FUNCTION(__asm64_syscall_fsymlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000010a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fsymlinkat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fsymlinkat)

/* @param: flags: Set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.x86.asm64_syscall.freadlinkat
	/* ssize_t freadlinkat(fd_t dirfd,
	 *                     char const *path,
	 *                     char *buf,
	 *                     size_t buflen,
	 *                     atflag_t flags) */
	.weak __asm64_syscall_freadlinkat
INTERN_FUNCTION(__asm64_syscall_freadlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000010b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_freadlinkat
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_freadlinkat)

.section .text.x86.asm64_syscall.fallocate64
	/* errno_t fallocate64(fd_t fd,
	 *                     syscall_ulong_t mode,
	 *                     uint64_t offset,
	 *                     uint64_t length) */
	.weak __asm64_syscall_fallocate64
INTERN_FUNCTION(__asm64_syscall_fallocate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000011d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_fallocate64
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_fallocate64)

.section .text.x86.asm64_syscall.preadvf
	/* ssize_t preadvf(fd_t fd,
	 *                 struct iovec const *iovec,
	 *                 size_t count,
	 *                 uint64_t offset,
	 *                 iomode_t mode) */
	.weak __asm64_syscall_preadvf
INTERN_FUNCTION(__asm64_syscall_preadvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000127
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_preadvf
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_preadvf)

.section .text.x86.asm64_syscall.pwritevf
	/* ssize_t pwritevf(fd_t fd,
	 *                  struct iovec const *iovec,
	 *                  size_t count,
	 *                  uint64_t offset,
	 *                  iomode_t mode) */
	.weak __asm64_syscall_pwritevf
INTERN_FUNCTION(__asm64_syscall_pwritevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000128
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	pushq_cfi_r %r8
	pushq_cfi_r %r9
	pushq_cfi_r %r10
	pushq_cfi_r %r11
	movq   %r10, %rcx
	call   sys_pwritevf
	pushq_cfi_r %r11
	pushq_cfi_r %r10
	pushq_cfi_r %r9
	pushq_cfi_r %r8
	pushq_cfi_r %rdi
	pushq_cfi_r %rsi
	pushq_cfi_r %rdx
	pushq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm64_syscall_pwritevf)




.section .text.x86.asm32_syscall_int80.exit
	/* void exit(syscall_ulong_t status) */
	.weak __asm32_int80_exit
INTERN_FUNCTION(__asm32_int80_exit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_exit
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_exit)

.section .text.x86.asm32_syscall_int80.fork
	/* pid_t fork(void); */
	.weak __asm32_int80_fork
INTERN_FUNCTION(__asm32_int80_fork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_fork
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fork)

.section .text.x86.asm32_syscall_int80.read
	/* ssize_t read(fd_t fd,
	 *              void *buf,
	 *              size_t bufsize) */
	.weak __asm32_int80_read
INTERN_FUNCTION(__asm32_int80_read)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_read
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_read)

.section .text.x86.asm32_syscall_int80.write
	/* ssize_t write(fd_t fd,
	 *               void const *buf,
	 *               size_t bufsize) */
	.weak __asm32_int80_write
INTERN_FUNCTION(__asm32_int80_write)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_write
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_write)

.section .text.x86.asm32_syscall_int80.open
	/* fd_t open(char const *filename,
	 *           oflag_t oflags,
	 *           mode_t mode) */
	.weak __asm32_int80_open
INTERN_FUNCTION(__asm32_int80_open)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_open
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_open)

/* Close a given file descriptor/handle `FD' */
.section .text.x86.asm32_syscall_int80.close
	/* errno_t close(fd_t fd) */
	.weak __asm32_int80_close
INTERN_FUNCTION(__asm32_int80_close)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_close
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_close)

/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
.section .text.x86.asm32_syscall_int80.waitpid
	/* pid_t waitpid(pid_t pid,
	 *               int32_t *stat_loc,
	 *               syscall_ulong_t options) */
	.weak __asm32_int80_waitpid
INTERN_FUNCTION(__asm32_int80_waitpid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_waitpid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_waitpid)

.section .text.x86.asm32_syscall_int80.creat
	/* fd_t creat(char const *filename,
	 *            mode_t mode) */
	.weak __asm32_int80_creat
INTERN_FUNCTION(__asm32_int80_creat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_creat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_creat)

.section .text.x86.asm32_syscall_int80.link
	/* errno_t link(char const *existing_file,
	 *              char const *link_file) */
	.weak __asm32_int80_link
INTERN_FUNCTION(__asm32_int80_link)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_link
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_link)

.section .text.x86.asm32_syscall_int80.unlink
	/* errno_t unlink(char const *filename) */
	.weak __asm32_int80_unlink
INTERN_FUNCTION(__asm32_int80_unlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_unlink
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_unlink)

.section .text.x86.asm32_syscall_int80.execve
	/* errno_t execve(char const *path,
	 *                char const *const *argv,
	 *                char const *const *envp) */
	.weak __asm32_int80_execve
INTERN_FUNCTION(__asm32_int80_execve)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_execve
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_execve)

.section .text.x86.asm32_syscall_int80.chdir
	/* errno_t chdir(char const *path) */
	.weak __asm32_int80_chdir
INTERN_FUNCTION(__asm32_int80_chdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_chdir
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_chdir)

.section .text.x86.asm32_syscall_int80.time
	/* time32_t time(time32_t *timer) */
	.weak __asm32_int80_time
INTERN_FUNCTION(__asm32_int80_time)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_time
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_time)

.section .text.x86.asm32_syscall_int80.mknod
	/* errno_t mknod(char const *nodename,
	 *               mode_t mode,
	 *               dev_t dev) */
	.weak __asm32_int80_mknod
INTERN_FUNCTION(__asm32_int80_mknod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mknod
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mknod)

.section .text.x86.asm32_syscall_int80.chmod
	/* errno_t chmod(char const *filename,
	 *               mode_t mode) */
	.weak __asm32_int80_chmod
INTERN_FUNCTION(__asm32_int80_chmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xf
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_chmod
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_chmod)

.section .text.x86.asm32_syscall_int80.lchown
	/* errno_t lchown(char const *filename,
	 *                uint16_t owner,
	 *                uint16_t group) */
	.weak __asm32_int80_lchown
INTERN_FUNCTION(__asm32_int80_lchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lchown
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lchown)

.section .text.x86.asm32_syscall_int80.linux_oldstat
	/* errno_t linux_oldstat(char const *filename,
	 *                       struct linux_oldstat *statbuf) */
	.weak __asm32_int80_linux_oldstat
INTERN_FUNCTION(__asm32_int80_linux_oldstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_oldstat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_oldstat)

.section .text.x86.asm32_syscall_int80.lseek
	/* int32_t lseek(fd_t fd,
	 *               int32_t offset,
	 *               syscall_ulong_t whence) */
	.weak __asm32_int80_lseek
INTERN_FUNCTION(__asm32_int80_lseek)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x13
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lseek
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lseek)

.section .text.x86.asm32_syscall_int80.getpid
	/* pid_t getpid(void); */
	.weak __asm32_int80_getpid
INTERN_FUNCTION(__asm32_int80_getpid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x14
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getpid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getpid)

.section .text.x86.asm32_syscall_int80.mount
	/* errno_t mount(char const *special_file,
	 *               char const *dir,
	 *               char const *fstype,
	 *               syscall_ulong_t rwflag,
	 *               void const *data) */
	.weak __asm32_int80_mount
INTERN_FUNCTION(__asm32_int80_mount)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x15
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mount
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mount)

.section .text.x86.asm32_syscall_int80.umount
	/* errno_t umount(char const *special_file) */
	.weak __asm32_int80_umount
INTERN_FUNCTION(__asm32_int80_umount)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x16
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_umount
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_umount)

.section .text.x86.asm32_syscall_int80.setuid
	/* errno_t setuid(uint16_t uid) */
	.weak __asm32_int80_setuid
INTERN_FUNCTION(__asm32_int80_setuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x17
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_setuid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setuid)

.section .text.x86.asm32_syscall_int80.getuid
	/* uint16_t getuid(void); */
	.weak __asm32_int80_getuid
INTERN_FUNCTION(__asm32_int80_getuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x18
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getuid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getuid)

.section .text.x86.asm32_syscall_int80.stime
	/* errno_t stime(time32_t const *t) */
	.weak __asm32_int80_stime
INTERN_FUNCTION(__asm32_int80_stime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x19
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_stime
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_stime)

.section .text.x86.asm32_syscall_int80.ptrace
	/* syscall_slong_t ptrace(syscall_ulong_t request,
	 *                        pid_t pid,
	 *                        void *addr,
	 *                        void *data) */
	.weak __asm32_int80_ptrace
INTERN_FUNCTION(__asm32_int80_ptrace)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ptrace
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ptrace)

.section .text.x86.asm32_syscall_int80.alarm
	/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
	.weak __asm32_int80_alarm
INTERN_FUNCTION(__asm32_int80_alarm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_alarm
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_alarm)

.section .text.x86.asm32_syscall_int80.linux_oldfstat
	/* errno_t linux_oldfstat(fd_t fd,
	 *                        struct linux_oldstat *statbuf) */
	.weak __asm32_int80_linux_oldfstat
INTERN_FUNCTION(__asm32_int80_linux_oldfstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_oldfstat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_oldfstat)

.section .text.x86.asm32_syscall_int80.pause
	/* errno_t pause(void); */
	.weak __asm32_int80_pause
INTERN_FUNCTION(__asm32_int80_pause)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_pause
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pause)

.section .text.x86.asm32_syscall_int80.utime
	/* errno_t utime(char const *filename,
	 *               struct __utimbuf32 const *times) */
	.weak __asm32_int80_utime
INTERN_FUNCTION(__asm32_int80_utime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x1e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_utime
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_utime)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
.section .text.x86.asm32_syscall_int80.access
	/* errno_t access(char const *filename,
	 *                syscall_ulong_t type) */
	.weak __asm32_int80_access
INTERN_FUNCTION(__asm32_int80_access)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x21
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_access
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_access)

.section .text.x86.asm32_syscall_int80.nice
	/* errno_t nice(syscall_slong_t inc) */
	.weak __asm32_int80_nice
INTERN_FUNCTION(__asm32_int80_nice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x22
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_nice
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_nice)

.section .text.x86.asm32_syscall_int80.ftime
	/* errno_t ftime(struct timeb *tp) */
	.weak __asm32_int80_ftime
INTERN_FUNCTION(__asm32_int80_ftime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x23
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_ftime
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ftime)

.section .text.x86.asm32_syscall_int80.sync
	/* errno_t sync(void); */
	.weak __asm32_int80_sync
INTERN_FUNCTION(__asm32_int80_sync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x24
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_sync
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sync)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_int80.kill
	/* errno_t kill(pid_t pid,
	 *              syscall_ulong_t signo) */
	.weak __asm32_int80_kill
INTERN_FUNCTION(__asm32_int80_kill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x25
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_kill
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_kill)

.section .text.x86.asm32_syscall_int80.rename
	/* errno_t rename(char const *oldname,
	 *                char const *newname_or_path) */
	.weak __asm32_int80_rename
INTERN_FUNCTION(__asm32_int80_rename)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x26
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rename
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rename)

.section .text.x86.asm32_syscall_int80.mkdir
	/* errno_t mkdir(char const *pathname,
	 *               mode_t mode) */
	.weak __asm32_int80_mkdir
INTERN_FUNCTION(__asm32_int80_mkdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x27
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mkdir
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mkdir)

.section .text.x86.asm32_syscall_int80.rmdir
	/* errno_t rmdir(char const *path) */
	.weak __asm32_int80_rmdir
INTERN_FUNCTION(__asm32_int80_rmdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x28
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_rmdir
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rmdir)

.section .text.x86.asm32_syscall_int80.dup
	/* fd_t dup(fd_t fd) */
	.weak __asm32_int80_dup
INTERN_FUNCTION(__asm32_int80_dup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x29
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_dup
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_dup)

.section .text.x86.asm32_syscall_int80.pipe
	/* errno_t pipe([2] fd_t *pipedes) */
	.weak __asm32_int80_pipe
INTERN_FUNCTION(__asm32_int80_pipe)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_pipe
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pipe)

.section .text.x86.asm32_syscall_int80.times
	/* clock_t times(struct tms *buf) */
	.weak __asm32_int80_times
INTERN_FUNCTION(__asm32_int80_times)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_times
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_times)

.section .text.x86.asm32_syscall_int80.brk
	/* errno_t brk(void *addr) */
	.weak __asm32_int80_brk
INTERN_FUNCTION(__asm32_int80_brk)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_brk
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_brk)

.section .text.x86.asm32_syscall_int80.setgid
	/* errno_t setgid(uint16_t gid) */
	.weak __asm32_int80_setgid
INTERN_FUNCTION(__asm32_int80_setgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_setgid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setgid)

.section .text.x86.asm32_syscall_int80.getgid
	/* uint16_t getgid(void); */
	.weak __asm32_int80_getgid
INTERN_FUNCTION(__asm32_int80_getgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x2f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getgid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getgid)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_int80.signal
	/* sighandler_t signal(syscall_ulong_t signo,
	 *                     sighandler_t handler) */
	.weak __asm32_int80_signal
INTERN_FUNCTION(__asm32_int80_signal)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x30
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_signal
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_signal)

.section .text.x86.asm32_syscall_int80.geteuid
	/* uint16_t geteuid(void); */
	.weak __asm32_int80_geteuid
INTERN_FUNCTION(__asm32_int80_geteuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x31
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_geteuid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_geteuid)

.section .text.x86.asm32_syscall_int80.getegid
	/* uint16_t getegid(void); */
	.weak __asm32_int80_getegid
INTERN_FUNCTION(__asm32_int80_getegid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x32
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getegid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getegid)

.section .text.x86.asm32_syscall_int80.acct
	/* errno_t acct(char const *filename) */
	.weak __asm32_int80_acct
INTERN_FUNCTION(__asm32_int80_acct)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x33
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_acct
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_acct)

.section .text.x86.asm32_syscall_int80.umount2
	/* errno_t umount2(char const *special_file,
	 *                 syscall_ulong_t flags) */
	.weak __asm32_int80_umount2
INTERN_FUNCTION(__asm32_int80_umount2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x34
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_umount2
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_umount2)

.section .text.x86.asm32_syscall_int80.ioctl
	/* syscall_slong_t ioctl(fd_t fd,
	 *                       syscall_ulong_t request,
	 *                       void *arg) */
	.weak __asm32_int80_ioctl
INTERN_FUNCTION(__asm32_int80_ioctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x36
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ioctl
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ioctl)

.section .text.x86.asm32_syscall_int80.fcntl
	/* syscall_slong_t fcntl(fd_t fd,
	 *                       syscall_ulong_t cmd,
	 *                       void *arg) */
	.weak __asm32_int80_fcntl
INTERN_FUNCTION(__asm32_int80_fcntl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x37
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fcntl
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fcntl)

.section .text.x86.asm32_syscall_int80.setpgid
	/* errno_t setpgid(pid_t pid,
	 *                 pid_t pgid) */
	.weak __asm32_int80_setpgid
INTERN_FUNCTION(__asm32_int80_setpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x39
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setpgid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setpgid)

.section .text.x86.asm32_syscall_int80.oldolduname
	/* errno_t oldolduname(struct linux_oldolduname *name) */
	.weak __asm32_int80_oldolduname
INTERN_FUNCTION(__asm32_int80_oldolduname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_oldolduname
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_oldolduname)

.section .text.x86.asm32_syscall_int80.umask
	/* mode_t umask(mode_t mode) */
	.weak __asm32_int80_umask
INTERN_FUNCTION(__asm32_int80_umask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_umask
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_umask)

.section .text.x86.asm32_syscall_int80.chroot
	/* errno_t chroot(char const *path) */
	.weak __asm32_int80_chroot
INTERN_FUNCTION(__asm32_int80_chroot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_chroot
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_chroot)

.section .text.x86.asm32_syscall_int80.ustat
	/* errno_t ustat(dev_t dev,
	 *               struct ustat *ubuf) */
	.weak __asm32_int80_ustat
INTERN_FUNCTION(__asm32_int80_ustat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ustat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ustat)

.section .text.x86.asm32_syscall_int80.dup2
	/* fd_t dup2(fd_t oldfd,
	 *           fd_t newfd) */
	.weak __asm32_int80_dup2
INTERN_FUNCTION(__asm32_int80_dup2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x3f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_dup2
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_dup2)

.section .text.x86.asm32_syscall_int80.getppid
	/* pid_t getppid(void); */
	.weak __asm32_int80_getppid
INTERN_FUNCTION(__asm32_int80_getppid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getppid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getppid)

.section .text.x86.asm32_syscall_int80.getpgrp
	/* pid_t getpgrp(void); */
	.weak __asm32_int80_getpgrp
INTERN_FUNCTION(__asm32_int80_getpgrp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x41
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getpgrp
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getpgrp)

.section .text.x86.asm32_syscall_int80.setsid
	/* pid_t setsid(void); */
	.weak __asm32_int80_setsid
INTERN_FUNCTION(__asm32_int80_setsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x42
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_setsid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setsid)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_int80.sigaction
	/* errno_t sigaction(syscall_ulong_t signo,
	 *                   struct sigaction const *act,
	 *                   struct sigaction *oact) */
	.weak __asm32_int80_sigaction
INTERN_FUNCTION(__asm32_int80_sigaction)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x43
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sigaction
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sigaction)

.section .text.x86.asm32_syscall_int80.sgetmask
	/* syscall_ulong_t sgetmask(void); */
	.weak __asm32_int80_sgetmask
INTERN_FUNCTION(__asm32_int80_sgetmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x44
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_sgetmask
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sgetmask)

.section .text.x86.asm32_syscall_int80.ssetmask
	/* syscall_ulong_t ssetmask(syscall_ulong_t sigmask) */
	.weak __asm32_int80_ssetmask
INTERN_FUNCTION(__asm32_int80_ssetmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x45
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_ssetmask
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ssetmask)

.section .text.x86.asm32_syscall_int80.setreuid
	/* errno_t setreuid(uint16_t ruid,
	 *                  uint16_t euid) */
	.weak __asm32_int80_setreuid
INTERN_FUNCTION(__asm32_int80_setreuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x46
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setreuid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setreuid)

.section .text.x86.asm32_syscall_int80.setregid
	/* errno_t setregid(uint16_t rgid,
	 *                  uint16_t egid) */
	.weak __asm32_int80_setregid
INTERN_FUNCTION(__asm32_int80_setregid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x47
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setregid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setregid)

.section .text.x86.asm32_syscall_int80.sigsuspend
	/* errno_t sigsuspend(struct __sigset_struct const *set) */
	.weak __asm32_int80_sigsuspend
INTERN_FUNCTION(__asm32_int80_sigsuspend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x48
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_sigsuspend
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sigsuspend)

.section .text.x86.asm32_syscall_int80.sigpending
	/* errno_t sigpending(struct __sigset_struct *set) */
	.weak __asm32_int80_sigpending
INTERN_FUNCTION(__asm32_int80_sigpending)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x49
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_sigpending
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sigpending)

.section .text.x86.asm32_syscall_int80.sethostname
	/* errno_t sethostname(char const *name,
	 *                     size_t len) */
	.weak __asm32_int80_sethostname
INTERN_FUNCTION(__asm32_int80_sethostname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sethostname
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sethostname)

.section .text.x86.asm32_syscall_int80.setrlimit
	/* errno_t setrlimit(syscall_ulong_t resource,
	 *                   struct rlimit const *rlimits) */
	.weak __asm32_int80_setrlimit
INTERN_FUNCTION(__asm32_int80_setrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setrlimit
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setrlimit)

.section .text.x86.asm32_syscall_int80.getrlimit
	/* errno_t getrlimit(syscall_ulong_t resource,
	 *                   struct rlimit *rlimits) */
	.weak __asm32_int80_getrlimit
INTERN_FUNCTION(__asm32_int80_getrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getrlimit
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getrlimit)

.section .text.x86.asm32_syscall_int80.getrusage
	/* errno_t getrusage(syscall_slong_t who,
	 *                   struct rusage *usage) */
	.weak __asm32_int80_getrusage
INTERN_FUNCTION(__asm32_int80_getrusage)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getrusage
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getrusage)

.section .text.x86.asm32_syscall_int80.gettimeofday
	/* errno_t gettimeofday(struct __timeval32 *tv,
	 *                      struct timezone *tz) */
	.weak __asm32_int80_gettimeofday
INTERN_FUNCTION(__asm32_int80_gettimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_gettimeofday
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_gettimeofday)

.section .text.x86.asm32_syscall_int80.settimeofday
	/* errno_t settimeofday(struct __timeval32 const *tv,
	 *                      struct timezone const *tz) */
	.weak __asm32_int80_settimeofday
INTERN_FUNCTION(__asm32_int80_settimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_settimeofday
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_settimeofday)

.section .text.x86.asm32_syscall_int80.getgroups
	/* errno_t getgroups(size_t size,
	 *                   [] uint16_t *list) */
	.weak __asm32_int80_getgroups
INTERN_FUNCTION(__asm32_int80_getgroups)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x50
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getgroups
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getgroups)

.section .text.x86.asm32_syscall_int80.setgroups
	/* errno_t setgroups(size_t count,
	 *                   uint16_t const *groups) */
	.weak __asm32_int80_setgroups
INTERN_FUNCTION(__asm32_int80_setgroups)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x51
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setgroups
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setgroups)

.section .text.x86.asm32_syscall_int80.select
	/* ssize_t select(size_t nfds,
	 *                struct __fd_set_struct *readfds,
	 *                struct __fd_set_struct *writefds,
	 *                struct __fd_set_struct *exceptfds,
	 *                struct __timeval32 *timeout) */
	.weak __asm32_int80_select
INTERN_FUNCTION(__asm32_int80_select)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x52
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_select
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_select)

.section .text.x86.asm32_syscall_int80.symlink
	/* errno_t symlink(char const *link_text,
	 *                 char const *target_path) */
	.weak __asm32_int80_symlink
INTERN_FUNCTION(__asm32_int80_symlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x53
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_symlink
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_symlink)

.section .text.x86.asm32_syscall_int80.linux_oldlstat
	/* errno_t linux_oldlstat(char const *filename,
	 *                        struct linux_oldstat *statbuf) */
	.weak __asm32_int80_linux_oldlstat
INTERN_FUNCTION(__asm32_int80_linux_oldlstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x54
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_oldlstat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_oldlstat)

.section .text.x86.asm32_syscall_int80.readlink
	/* ssize_t readlink(char const *path,
	 *                  char *buf,
	 *                  size_t buflen) */
	.weak __asm32_int80_readlink
INTERN_FUNCTION(__asm32_int80_readlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x55
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_readlink
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_readlink)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
.section .text.x86.asm32_syscall_int80.swapon
	/* errno_t swapon(char const *pathname,
	 *                syscall_ulong_t swapflags) */
	.weak __asm32_int80_swapon
INTERN_FUNCTION(__asm32_int80_swapon)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x57
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_swapon
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_swapon)

/* @param: howto: One of the `RB_*' constants from <sys/reboot.h> */
.section .text.x86.asm32_syscall_int80.reboot
	/* errno_t reboot(syscall_ulong_t how) */
	.weak __asm32_int80_reboot
INTERN_FUNCTION(__asm32_int80_reboot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x58
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_reboot
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_reboot)

/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
.section .text.x86.asm32_syscall_int80.readdir
	/* errno_t readdir(fd_t fd,
	 *                 struct old_linux_dirent *dirp,
	 *                 size_t count) */
	.weak __asm32_int80_readdir
INTERN_FUNCTION(__asm32_int80_readdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x59
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_readdir
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_readdir)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
.section .text.x86.asm32_syscall_int80.mmap
	/* void *mmap(void *addr,
	 *            size_t len,
	 *            syscall_ulong_t prot,
	 *            syscall_ulong_t flags,
	 *            fd_t fd,
	 *            syscall_ulong_t offset) */
	.weak __asm32_int80_mmap
INTERN_FUNCTION(__asm32_int80_mmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mmap
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mmap)

.section .text.x86.asm32_syscall_int80.munmap
	/* errno_t munmap(void *addr,
	 *                size_t len) */
	.weak __asm32_int80_munmap
INTERN_FUNCTION(__asm32_int80_munmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_munmap
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_munmap)

.section .text.x86.asm32_syscall_int80.truncate
	/* errno_t truncate(char const *filename,
	 *                  syscall_ulong_t length) */
	.weak __asm32_int80_truncate
INTERN_FUNCTION(__asm32_int80_truncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_truncate
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_truncate)

.section .text.x86.asm32_syscall_int80.ftruncate
	/* errno_t ftruncate(fd_t fd,
	 *                   syscall_ulong_t length) */
	.weak __asm32_int80_ftruncate
INTERN_FUNCTION(__asm32_int80_ftruncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ftruncate
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ftruncate)

.section .text.x86.asm32_syscall_int80.fchmod
	/* errno_t fchmod(fd_t fd,
	 *                mode_t mode) */
	.weak __asm32_int80_fchmod
INTERN_FUNCTION(__asm32_int80_fchmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fchmod
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fchmod)

.section .text.x86.asm32_syscall_int80.fchown
	/* errno_t fchown(fd_t fd,
	 *                uint16_t owner,
	 *                uint16_t group) */
	.weak __asm32_int80_fchown
INTERN_FUNCTION(__asm32_int80_fchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x5f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fchown
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fchown)

.section .text.x86.asm32_syscall_int80.getpriority
	/* syscall_slong_t getpriority(syscall_ulong_t which,
	 *                             id_t who) */
	.weak __asm32_int80_getpriority
INTERN_FUNCTION(__asm32_int80_getpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x60
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getpriority
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getpriority)

.section .text.x86.asm32_syscall_int80.setpriority
	/* errno_t setpriority(syscall_ulong_t which,
	 *                     id_t who,
	 *                     syscall_ulong_t value) */
	.weak __asm32_int80_setpriority
INTERN_FUNCTION(__asm32_int80_setpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x61
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setpriority
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setpriority)

.section .text.x86.asm32_syscall_int80.profil
	/* errno_t profil(uint16_t *sample_buffer,
	 *                size_t size,
	 *                size_t offset,
	 *                syscall_ulong_t scale) */
	.weak __asm32_int80_profil
INTERN_FUNCTION(__asm32_int80_profil)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x62
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_profil
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_profil)

.section .text.x86.asm32_syscall_int80.statfs
	/* errno_t statfs(char const *file,
	 *                struct __statfs32 *buf) */
	.weak __asm32_int80_statfs
INTERN_FUNCTION(__asm32_int80_statfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x63
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_statfs
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_statfs)

.section .text.x86.asm32_syscall_int80.fstatfs
	/* errno_t fstatfs(fd_t file,
	 *                 struct __statfs32 *buf) */
	.weak __asm32_int80_fstatfs
INTERN_FUNCTION(__asm32_int80_fstatfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x64
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fstatfs
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fstatfs)

.section .text.x86.asm32_syscall_int80.ioperm
	/* errno_t ioperm(syscall_ulong_t from,
	 *                syscall_ulong_t num,
	 *                syscall_ulong_t turn_on) */
	.weak __asm32_int80_ioperm
INTERN_FUNCTION(__asm32_int80_ioperm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x65
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ioperm
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ioperm)

.section .text.x86.asm32_syscall_int80.socketcall
	/* errno_t socketcall(int call,
	 *                    unsigned long *args) */
	.weak __asm32_int80_socketcall
INTERN_FUNCTION(__asm32_int80_socketcall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x66
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_socketcall
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_socketcall)

.section .text.x86.asm32_syscall_int80.syslog
	/* ssize_t syslog(syscall_ulong_t level,
	 *                char const *str,
	 *                size_t len) */
	.weak __asm32_int80_syslog
INTERN_FUNCTION(__asm32_int80_syslog)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x67
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_syslog
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_syslog)

.section .text.x86.asm32_syscall_int80.setitimer
	/* errno_t setitimer(syscall_ulong_t which,
	 *                   struct __itimerval32 const *newval,
	 *                   struct __itimerval32 *oldval) */
	.weak __asm32_int80_setitimer
INTERN_FUNCTION(__asm32_int80_setitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x68
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setitimer
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setitimer)

.section .text.x86.asm32_syscall_int80.getitimer
	/* errno_t getitimer(syscall_ulong_t which,
	 *                   struct __itimerval32 *curr_value) */
	.weak __asm32_int80_getitimer
INTERN_FUNCTION(__asm32_int80_getitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x69
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getitimer
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getitimer)

.section .text.x86.asm32_syscall_int80.linux_stat32
	/* errno_t linux_stat32(char const *filename,
	 *                      struct linux_stat32 *statbuf) */
	.weak __asm32_int80_linux_stat32
INTERN_FUNCTION(__asm32_int80_linux_stat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_stat32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_stat32)

.section .text.x86.asm32_syscall_int80.linux_lstat32
	/* errno_t linux_lstat32(char const *filename,
	 *                       struct linux_stat32 *statbuf) */
	.weak __asm32_int80_linux_lstat32
INTERN_FUNCTION(__asm32_int80_linux_lstat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_lstat32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_lstat32)

.section .text.x86.asm32_syscall_int80.linux_fstat32
	/* errno_t linux_fstat32(fd_t fd,
	 *                       struct linux_stat32 *statbuf) */
	.weak __asm32_int80_linux_fstat32
INTERN_FUNCTION(__asm32_int80_linux_fstat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_fstat32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_fstat32)

.section .text.x86.asm32_syscall_int80.olduname
	/* errno_t olduname(struct linux_olduname *name) */
	.weak __asm32_int80_olduname
INTERN_FUNCTION(__asm32_int80_olduname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_olduname
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_olduname)

.section .text.x86.asm32_syscall_int80.iopl
	/* errno_t iopl(syscall_ulong_t level) */
	.weak __asm32_int80_iopl
INTERN_FUNCTION(__asm32_int80_iopl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_iopl
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_iopl)

.section .text.x86.asm32_syscall_int80.vhangup
	/* errno_t vhangup(void); */
	.weak __asm32_int80_vhangup
INTERN_FUNCTION(__asm32_int80_vhangup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x6f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_vhangup
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_vhangup)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
.section .text.x86.asm32_syscall_int80.wait4
	/* pid_t wait4(pid_t pid,
	 *             int32_t *stat_loc,
	 *             syscall_ulong_t options,
	 *             struct rusage *usage) */
	.weak __asm32_int80_wait4
INTERN_FUNCTION(__asm32_int80_wait4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x72
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_wait4
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_wait4)

.section .text.x86.asm32_syscall_int80.swapoff
	/* errno_t swapoff(char const *pathname) */
	.weak __asm32_int80_swapoff
INTERN_FUNCTION(__asm32_int80_swapoff)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x73
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_swapoff
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_swapoff)

.section .text.x86.asm32_syscall_int80.sysinfo
	/* errno_t sysinfo(struct sysinfo *info) */
	.weak __asm32_int80_sysinfo
INTERN_FUNCTION(__asm32_int80_sysinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x74
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_sysinfo
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sysinfo)

.section .text.x86.asm32_syscall_int80.fsync
	/* errno_t fsync(fd_t fd) */
	.weak __asm32_int80_fsync
INTERN_FUNCTION(__asm32_int80_fsync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x76
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_fsync
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fsync)

/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
.section .text.x86.asm32_syscall_int80.sigreturn
	/* void sigreturn(struct fpustate const *restore_fpu,
	 *                syscall_ulong_t unused1,
	 *                syscall_ulong_t unused2,
	 *                struct __sigset_struct const *restore_sigmask,
	 *                struct rpc_syscall_info *sc_info,
	 *                struct ucpustate const *restore_cpu) */
	.weak __asm32_int80_sigreturn
INTERN_FUNCTION(__asm32_int80_sigreturn)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x77
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sigreturn
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sigreturn)

.section .text.x86.asm32_syscall_int80.clone
	/* pid_t clone(syscall_ulong_t flags,
	 *             void *child_stack,
	 *             pid_t *ptid,
	 *             uintptr_t newtls,
	 *             pid_t *ctid) */
	.weak __asm32_int80_clone
INTERN_FUNCTION(__asm32_int80_clone)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x78
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_clone
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_clone)

.section .text.x86.asm32_syscall_int80.setdomainname
	/* errno_t setdomainname(char const *name,
	 *                       size_t len) */
	.weak __asm32_int80_setdomainname
INTERN_FUNCTION(__asm32_int80_setdomainname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x79
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setdomainname
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setdomainname)

.section .text.x86.asm32_syscall_int80.uname
	/* errno_t uname(struct utsname *name) */
	.weak __asm32_int80_uname
INTERN_FUNCTION(__asm32_int80_uname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_uname
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_uname)

.section .text.x86.asm32_syscall_int80.modify_ldt
	/* syscall_slong_t modify_ldt(syscall_ulong_t func,
	 *                            void *ptr,
	 *                            syscall_ulong_t bytecount) */
	.weak __asm32_int80_modify_ldt
INTERN_FUNCTION(__asm32_int80_modify_ldt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_modify_ldt
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_modify_ldt)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
.section .text.x86.asm32_syscall_int80.mprotect
	/* errno_t mprotect(void *addr,
	 *                  size_t len,
	 *                  syscall_ulong_t prot) */
	.weak __asm32_int80_mprotect
INTERN_FUNCTION(__asm32_int80_mprotect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mprotect
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mprotect)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
.section .text.x86.asm32_syscall_int80.sigprocmask
	/* errno_t sigprocmask(syscall_ulong_t how,
	 *                     struct __sigset_struct const *set,
	 *                     struct __sigset_struct *oset) */
	.weak __asm32_int80_sigprocmask
INTERN_FUNCTION(__asm32_int80_sigprocmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x7e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sigprocmask
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sigprocmask)

.section .text.x86.asm32_syscall_int80.getpgid
	/* pid_t getpgid(pid_t pid) */
	.weak __asm32_int80_getpgid
INTERN_FUNCTION(__asm32_int80_getpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x84
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_getpgid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getpgid)

.section .text.x86.asm32_syscall_int80.fchdir
	/* errno_t fchdir(fd_t fd) */
	.weak __asm32_int80_fchdir
INTERN_FUNCTION(__asm32_int80_fchdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x85
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_fchdir
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fchdir)

.section .text.x86.asm32_syscall_int80.setfsuid
	/* errno_t setfsuid(uint16_t uid) */
	.weak __asm32_int80_setfsuid
INTERN_FUNCTION(__asm32_int80_setfsuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_setfsuid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setfsuid)

.section .text.x86.asm32_syscall_int80.setfsgid
	/* errno_t setfsgid(uint16_t gid) */
	.weak __asm32_int80_setfsgid
INTERN_FUNCTION(__asm32_int80_setfsgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_setfsgid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setfsgid)

.section .text.x86.asm32_syscall_int80._llseek
	/* errno_t _llseek(fd_t fd,
	 *                 int64_t offset,
	 *                 uint64_t *result,
	 *                 syscall_ulong_t whence) */
	.weak __asm32_int80__llseek
INTERN_FUNCTION(__asm32_int80__llseek)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32__llseek
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80__llseek)

.section .text.x86.asm32_syscall_int80.getdents
	/* ssize_t getdents(fd_t fd,
	 *                  struct linux_dirent *dirp,
	 *                  size_t count) */
	.weak __asm32_int80_getdents
INTERN_FUNCTION(__asm32_int80_getdents)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getdents
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getdents)

.section .text.x86.asm32_syscall_int80.flock
	/* errno_t flock(fd_t fd,
	 *               syscall_ulong_t operation) */
	.weak __asm32_int80_flock
INTERN_FUNCTION(__asm32_int80_flock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_flock
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_flock)

.section .text.x86.asm32_syscall_int80.msync
	/* errno_t msync(void *addr,
	 *               size_t len,
	 *               syscall_ulong_t flags) */
	.weak __asm32_int80_msync
INTERN_FUNCTION(__asm32_int80_msync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x90
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_msync
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_msync)

.section .text.x86.asm32_syscall_int80.readv
	/* ssize_t readv(fd_t fd,
	 *               struct iovec const *iovec,
	 *               size_t count) */
	.weak __asm32_int80_readv
INTERN_FUNCTION(__asm32_int80_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x91
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_readv
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_readv)

.section .text.x86.asm32_syscall_int80.writev
	/* ssize_t writev(fd_t fd,
	 *                struct iovec const *iovec,
	 *                size_t count) */
	.weak __asm32_int80_writev
INTERN_FUNCTION(__asm32_int80_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x92
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_writev
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_writev)

.section .text.x86.asm32_syscall_int80.getsid
	/* pid_t getsid(pid_t pid) */
	.weak __asm32_int80_getsid
INTERN_FUNCTION(__asm32_int80_getsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x93
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_getsid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getsid)

.section .text.x86.asm32_syscall_int80.fdatasync
	/* errno_t fdatasync(fd_t fd) */
	.weak __asm32_int80_fdatasync
INTERN_FUNCTION(__asm32_int80_fdatasync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x94
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_fdatasync
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fdatasync)

.section .text.x86.asm32_syscall_int80.mlock
	/* errno_t mlock(void const *addr,
	 *               size_t len) */
	.weak __asm32_int80_mlock
INTERN_FUNCTION(__asm32_int80_mlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x96
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mlock
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mlock)

.section .text.x86.asm32_syscall_int80.munlock
	/* errno_t munlock(void const *addr,
	 *                 size_t len) */
	.weak __asm32_int80_munlock
INTERN_FUNCTION(__asm32_int80_munlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x97
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_munlock
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_munlock)

.section .text.x86.asm32_syscall_int80.mlockall
	/* errno_t mlockall(syscall_ulong_t flags) */
	.weak __asm32_int80_mlockall
INTERN_FUNCTION(__asm32_int80_mlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x98
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_mlockall
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mlockall)

.section .text.x86.asm32_syscall_int80.munlockall
	/* errno_t munlockall(void); */
	.weak __asm32_int80_munlockall
INTERN_FUNCTION(__asm32_int80_munlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x99
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_munlockall
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_munlockall)

.section .text.x86.asm32_syscall_int80.sched_setparam
	/* errno_t sched_setparam(pid_t pid,
	 *                        struct sched_param const *param) */
	.weak __asm32_int80_sched_setparam
INTERN_FUNCTION(__asm32_int80_sched_setparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x9a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sched_setparam
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_setparam)

.section .text.x86.asm32_syscall_int80.sched_getparam
	/* errno_t sched_getparam(pid_t pid,
	 *                        struct sched_param *param) */
	.weak __asm32_int80_sched_getparam
INTERN_FUNCTION(__asm32_int80_sched_getparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x9b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sched_getparam
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_getparam)

.section .text.x86.asm32_syscall_int80.sched_setscheduler
	/* errno_t sched_setscheduler(pid_t pid,
	 *                            syscall_ulong_t policy,
	 *                            struct sched_param const *param) */
	.weak __asm32_int80_sched_setscheduler
INTERN_FUNCTION(__asm32_int80_sched_setscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x9c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sched_setscheduler
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_setscheduler)

.section .text.x86.asm32_syscall_int80.sched_getscheduler
	/* syscall_slong_t sched_getscheduler(pid_t pid) */
	.weak __asm32_int80_sched_getscheduler
INTERN_FUNCTION(__asm32_int80_sched_getscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x9d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_sched_getscheduler
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_getscheduler)

.section .text.x86.asm32_syscall_int80.sched_yield
	/* errno_t sched_yield(void); */
	.weak __asm32_int80_sched_yield
INTERN_FUNCTION(__asm32_int80_sched_yield)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x9e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_sched_yield
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_yield)

.section .text.x86.asm32_syscall_int80.sched_get_priority_max
	/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
	.weak __asm32_int80_sched_get_priority_max
INTERN_FUNCTION(__asm32_int80_sched_get_priority_max)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x9f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_sched_get_priority_max
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_get_priority_max)

.section .text.x86.asm32_syscall_int80.sched_get_priority_min
	/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
	.weak __asm32_int80_sched_get_priority_min
INTERN_FUNCTION(__asm32_int80_sched_get_priority_min)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_sched_get_priority_min
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_get_priority_min)

.section .text.x86.asm32_syscall_int80.sched_rr_get_interval
	/* errno_t sched_rr_get_interval(pid_t pid,
	 *                               struct __timespec32 *tms) */
	.weak __asm32_int80_sched_rr_get_interval
INTERN_FUNCTION(__asm32_int80_sched_rr_get_interval)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sched_rr_get_interval
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_rr_get_interval)

.section .text.x86.asm32_syscall_int80.nanosleep
	/* errno_t nanosleep(struct __timespec32 const *req,
	 *                   struct __timespec32 *rem) */
	.weak __asm32_int80_nanosleep
INTERN_FUNCTION(__asm32_int80_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_nanosleep
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_nanosleep)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
.section .text.x86.asm32_syscall_int80.mremap
	/* void *mremap(void *addr,
	 *              size_t old_len,
	 *              size_t new_len,
	 *              syscall_ulong_t flags,
	 *              void *new_address) */
	.weak __asm32_int80_mremap
INTERN_FUNCTION(__asm32_int80_mremap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mremap
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mremap)

.section .text.x86.asm32_syscall_int80.setresuid
	/* errno_t setresuid(uint16_t ruid,
	 *                   uint16_t euid,
	 *                   uint16_t suid) */
	.weak __asm32_int80_setresuid
INTERN_FUNCTION(__asm32_int80_setresuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setresuid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setresuid)

.section .text.x86.asm32_syscall_int80.getresuid
	/* errno_t getresuid(uint16_t *ruid,
	 *                   uint16_t *euid,
	 *                   uint16_t *suid) */
	.weak __asm32_int80_getresuid
INTERN_FUNCTION(__asm32_int80_getresuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getresuid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getresuid)

.section .text.x86.asm32_syscall_int80.poll
	/* ssize_t poll(struct pollfd *fds,
	 *              size_t nfds,
	 *              syscall_slong_t timeout) */
	.weak __asm32_int80_poll
INTERN_FUNCTION(__asm32_int80_poll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xa8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_poll
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_poll)

.section .text.x86.asm32_syscall_int80.setresgid
	/* errno_t setresgid(uint16_t rgid,
	 *                   uint16_t egid,
	 *                   uint16_t sgid) */
	.weak __asm32_int80_setresgid
INTERN_FUNCTION(__asm32_int80_setresgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xaa
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setresgid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setresgid)

.section .text.x86.asm32_syscall_int80.getresgid
	/* errno_t getresgid(uint16_t *rgid,
	 *                   uint16_t *egid,
	 *                   uint16_t *sgid) */
	.weak __asm32_int80_getresgid
INTERN_FUNCTION(__asm32_int80_getresgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xab
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getresgid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getresgid)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_int80.rt_sigaction
	/* errno_t rt_sigaction(syscall_ulong_t signo,
	 *                      struct sigaction const *act,
	 *                      struct sigaction *oact,
	 *                      size_t sigsetsize) */
	.weak __asm32_int80_rt_sigaction
INTERN_FUNCTION(__asm32_int80_rt_sigaction)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xae
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rt_sigaction
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
.section .text.x86.asm32_syscall_int80.rt_sigprocmask
	/* errno_t rt_sigprocmask(syscall_ulong_t how,
	 *                        struct __sigset_struct const *set,
	 *                        struct __sigset_struct *oset,
	 *                        size_t sigsetsize) */
	.weak __asm32_int80_rt_sigprocmask
INTERN_FUNCTION(__asm32_int80_rt_sigprocmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xaf
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rt_sigprocmask
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rt_sigprocmask)

.section .text.x86.asm32_syscall_int80.rt_sigpending
	/* errno_t rt_sigpending(struct __sigset_struct *set,
	 *                       size_t sigsetsize) */
	.weak __asm32_int80_rt_sigpending
INTERN_FUNCTION(__asm32_int80_rt_sigpending)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rt_sigpending
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rt_sigpending)

.section .text.x86.asm32_syscall_int80.rt_sigtimedwait
	/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set,
	 *                                 struct __siginfo_struct *info,
	 *                                 struct __timespec32 const *timeout,
	 *                                 size_t sigsetsize) */
	.weak __asm32_int80_rt_sigtimedwait
INTERN_FUNCTION(__asm32_int80_rt_sigtimedwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rt_sigtimedwait
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rt_sigtimedwait)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_int80.rt_sigqueueinfo
	/* errno_t rt_sigqueueinfo(pid_t tgid,
	 *                         syscall_ulong_t signo,
	 *                         struct __siginfo_struct const *uinfo) */
	.weak __asm32_int80_rt_sigqueueinfo
INTERN_FUNCTION(__asm32_int80_rt_sigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rt_sigqueueinfo
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rt_sigqueueinfo)

.section .text.x86.asm32_syscall_int80.rt_sigsuspend
	/* errno_t rt_sigsuspend(struct __sigset_struct const *set,
	 *                       size_t sigsetsize) */
	.weak __asm32_int80_rt_sigsuspend
INTERN_FUNCTION(__asm32_int80_rt_sigsuspend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rt_sigsuspend
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rt_sigsuspend)

.section .text.x86.asm32_syscall_int80.pread64
	/* ssize_t pread64(fd_t fd,
	 *                 void *buf,
	 *                 size_t bufsize,
	 *                 uint64_t offset) */
	.weak __asm32_int80_pread64
INTERN_FUNCTION(__asm32_int80_pread64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_pread64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pread64)

.section .text.x86.asm32_syscall_int80.pwrite64
	/* ssize_t pwrite64(fd_t fd,
	 *                  void const *buf,
	 *                  size_t bufsize,
	 *                  uint64_t offset) */
	.weak __asm32_int80_pwrite64
INTERN_FUNCTION(__asm32_int80_pwrite64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_pwrite64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pwrite64)

.section .text.x86.asm32_syscall_int80.chown
	/* errno_t chown(char const *filename,
	 *               uint16_t owner,
	 *               uint16_t group) */
	.weak __asm32_int80_chown
INTERN_FUNCTION(__asm32_int80_chown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_chown
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_chown)

.section .text.x86.asm32_syscall_int80.getcwd
	/* ssize_t getcwd(char *buf,
	 *                size_t size) */
	.weak __asm32_int80_getcwd
INTERN_FUNCTION(__asm32_int80_getcwd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xb7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getcwd
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getcwd)

.section .text.x86.asm32_syscall_int80.sigaltstack
	/* errno_t sigaltstack(struct sigaltstack const *ss,
	 *                     struct sigaltstack *oss) */
	.weak __asm32_int80_sigaltstack
INTERN_FUNCTION(__asm32_int80_sigaltstack)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xba
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sigaltstack
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sigaltstack)

.section .text.x86.asm32_syscall_int80.sendfile
	/* ssize_t sendfile(fd_t out_fd,
	 *                  fd_t in_fd,
	 *                  syscall_ulong_t *offset,
	 *                  size_t count) */
	.weak __asm32_int80_sendfile
INTERN_FUNCTION(__asm32_int80_sendfile)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xbb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sendfile
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sendfile)

.section .text.x86.asm32_syscall_int80.vfork
	/* pid_t vfork(void); */
	.weak __asm32_int80_vfork
INTERN_FUNCTION(__asm32_int80_vfork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xbe
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_vfork
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_vfork)

.section .text.x86.asm32_syscall_int80.mmap2
	/* void *mmap2(void *addr,
	 *             size_t len,
	 *             syscall_ulong_t prot,
	 *             syscall_ulong_t flags,
	 *             fd_t fd,
	 *             syscall_ulong_t pgoffset) */
	.weak __asm32_int80_mmap2
INTERN_FUNCTION(__asm32_int80_mmap2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mmap2
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mmap2)

.section .text.x86.asm32_syscall_int80.truncate64
	/* errno_t truncate64(char const *filename,
	 *                    uint64_t length) */
	.weak __asm32_int80_truncate64
INTERN_FUNCTION(__asm32_int80_truncate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_truncate64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_truncate64)

.section .text.x86.asm32_syscall_int80.ftruncate64
	/* errno_t ftruncate64(fd_t fd,
	 *                     uint64_t length) */
	.weak __asm32_int80_ftruncate64
INTERN_FUNCTION(__asm32_int80_ftruncate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ftruncate64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ftruncate64)

.section .text.x86.asm32_syscall_int80.linux_stat64
	/* errno_t linux_stat64(char const *filename,
	 *                      struct linux_stat64 *statbuf) */
	.weak __asm32_int80_linux_stat64
INTERN_FUNCTION(__asm32_int80_linux_stat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_stat64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_stat64)

.section .text.x86.asm32_syscall_int80.linux_lstat64
	/* errno_t linux_lstat64(char const *filename,
	 *                       struct linux_stat64 *statbuf) */
	.weak __asm32_int80_linux_lstat64
INTERN_FUNCTION(__asm32_int80_linux_lstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_lstat64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_lstat64)

.section .text.x86.asm32_syscall_int80.linux_fstat64
	/* errno_t linux_fstat64(fd_t fd,
	 *                       struct linux_stat64 *statbuf) */
	.weak __asm32_int80_linux_fstat64
INTERN_FUNCTION(__asm32_int80_linux_fstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_fstat64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_fstat64)

.section .text.x86.asm32_syscall_int80.lchown32
	/* errno_t lchown32(char const *filename,
	 *                  uint32_t owner,
	 *                  uint32_t group) */
	.weak __asm32_int80_lchown32
INTERN_FUNCTION(__asm32_int80_lchown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lchown32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lchown32)

.section .text.x86.asm32_syscall_int80.getuid32
	/* uint32_t getuid32(void); */
	.weak __asm32_int80_getuid32
INTERN_FUNCTION(__asm32_int80_getuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getuid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getuid32)

.section .text.x86.asm32_syscall_int80.getgid32
	/* uint32_t getgid32(void); */
	.weak __asm32_int80_getgid32
INTERN_FUNCTION(__asm32_int80_getgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getgid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getgid32)

.section .text.x86.asm32_syscall_int80.geteuid32
	/* uint32_t geteuid32(void); */
	.weak __asm32_int80_geteuid32
INTERN_FUNCTION(__asm32_int80_geteuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_geteuid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_geteuid32)

.section .text.x86.asm32_syscall_int80.getegid32
	/* uint32_t getegid32(void); */
	.weak __asm32_int80_getegid32
INTERN_FUNCTION(__asm32_int80_getegid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xca
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getegid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getegid32)

.section .text.x86.asm32_syscall_int80.setreuid32
	/* errno_t setreuid32(uint32_t ruid,
	 *                    uint32_t euid) */
	.weak __asm32_int80_setreuid32
INTERN_FUNCTION(__asm32_int80_setreuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xcb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setreuid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setreuid32)

.section .text.x86.asm32_syscall_int80.setregid32
	/* errno_t setregid32(uint32_t rgid,
	 *                    uint32_t egid) */
	.weak __asm32_int80_setregid32
INTERN_FUNCTION(__asm32_int80_setregid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xcc
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setregid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setregid32)

.section .text.x86.asm32_syscall_int80.getgroups32
	/* errno_t getgroups32(size_t size,
	 *                     [] uint32_t *list) */
	.weak __asm32_int80_getgroups32
INTERN_FUNCTION(__asm32_int80_getgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xcd
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getgroups32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getgroups32)

.section .text.x86.asm32_syscall_int80.setgroups32
	/* errno_t setgroups32(size_t count,
	 *                     uint32_t const *groups) */
	.weak __asm32_int80_setgroups32
INTERN_FUNCTION(__asm32_int80_setgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xce
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setgroups32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setgroups32)

.section .text.x86.asm32_syscall_int80.fchown32
	/* errno_t fchown32(fd_t fd,
	 *                  uint32_t owner,
	 *                  uint32_t group) */
	.weak __asm32_int80_fchown32
INTERN_FUNCTION(__asm32_int80_fchown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xcf
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fchown32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fchown32)

.section .text.x86.asm32_syscall_int80.setresuid32
	/* errno_t setresuid32(uint32_t ruid,
	 *                     uint32_t euid,
	 *                     uint32_t suid) */
	.weak __asm32_int80_setresuid32
INTERN_FUNCTION(__asm32_int80_setresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setresuid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setresuid32)

.section .text.x86.asm32_syscall_int80.getresuid32
	/* errno_t getresuid32(uint32_t *ruid,
	 *                     uint32_t *euid,
	 *                     uint32_t *suid) */
	.weak __asm32_int80_getresuid32
INTERN_FUNCTION(__asm32_int80_getresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getresuid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getresuid32)

.section .text.x86.asm32_syscall_int80.setresgid32
	/* errno_t setresgid32(uint32_t rgid,
	 *                     uint32_t egid,
	 *                     uint32_t sgid) */
	.weak __asm32_int80_setresgid32
INTERN_FUNCTION(__asm32_int80_setresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setresgid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setresgid32)

.section .text.x86.asm32_syscall_int80.getresgid32
	/* errno_t getresgid32(uint32_t *rgid,
	 *                     uint32_t *egid,
	 *                     uint32_t *sgid) */
	.weak __asm32_int80_getresgid32
INTERN_FUNCTION(__asm32_int80_getresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getresgid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getresgid32)

.section .text.x86.asm32_syscall_int80.chown32
	/* errno_t chown32(char const *filename,
	 *                 uint32_t owner,
	 *                 uint32_t group) */
	.weak __asm32_int80_chown32
INTERN_FUNCTION(__asm32_int80_chown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_chown32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_chown32)

.section .text.x86.asm32_syscall_int80.setuid32
	/* errno_t setuid32(uint32_t uid) */
	.weak __asm32_int80_setuid32
INTERN_FUNCTION(__asm32_int80_setuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_setuid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setuid32)

.section .text.x86.asm32_syscall_int80.setgid32
	/* errno_t setgid32(uint32_t gid) */
	.weak __asm32_int80_setgid32
INTERN_FUNCTION(__asm32_int80_setgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_setgid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setgid32)

.section .text.x86.asm32_syscall_int80.setfsuid32
	/* errno_t setfsuid32(uint32_t uid) */
	.weak __asm32_int80_setfsuid32
INTERN_FUNCTION(__asm32_int80_setfsuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_setfsuid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setfsuid32)

.section .text.x86.asm32_syscall_int80.setfsgid32
	/* errno_t setfsgid32(uint32_t gid) */
	.weak __asm32_int80_setfsgid32
INTERN_FUNCTION(__asm32_int80_setfsgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xd8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_setfsgid32
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setfsgid32)

.section .text.x86.asm32_syscall_int80.mincore
	/* errno_t mincore(void *start,
	 *                 size_t len,
	 *                 uint8_t *vec) */
	.weak __asm32_int80_mincore
INTERN_FUNCTION(__asm32_int80_mincore)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xda
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mincore
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mincore)

.section .text.x86.asm32_syscall_int80.madvise
	/* errno_t madvise(void *addr,
	 *                 size_t len,
	 *                 syscall_ulong_t advice) */
	.weak __asm32_int80_madvise
INTERN_FUNCTION(__asm32_int80_madvise)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xdb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_madvise
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_madvise)

.section .text.x86.asm32_syscall_int80.getdents64
	/* ssize_t getdents64(fd_t fd,
	 *                    struct linux_dirent64 *dirp,
	 *                    size_t count) */
	.weak __asm32_int80_getdents64
INTERN_FUNCTION(__asm32_int80_getdents64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xdc
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getdents64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getdents64)

.section .text.x86.asm32_syscall_int80.fcntl64
	/* syscall_slong_t fcntl64(fd_t fd,
	 *                         syscall_ulong_t command,
	 *                         void *arg) */
	.weak __asm32_int80_fcntl64
INTERN_FUNCTION(__asm32_int80_fcntl64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xdd
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fcntl64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fcntl64)

.section .text.x86.asm32_syscall_int80.gettid
	/* pid_t gettid(void); */
	.weak __asm32_int80_gettid
INTERN_FUNCTION(__asm32_int80_gettid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_gettid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_gettid)

.section .text.x86.asm32_syscall_int80.readahead
	/* ssize_t readahead(fd_t fd,
	 *                   uint64_t offset,
	 *                   size_t count) */
	.weak __asm32_int80_readahead
INTERN_FUNCTION(__asm32_int80_readahead)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_readahead
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_readahead)

.section .text.x86.asm32_syscall_int80.setxattr
	/* errno_t setxattr(char const *path,
	 *                  char const *name,
	 *                  void const *buf,
	 *                  size_t bufsize,
	 *                  syscall_ulong_t flags) */
	.weak __asm32_int80_setxattr
INTERN_FUNCTION(__asm32_int80_setxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setxattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setxattr)

.section .text.x86.asm32_syscall_int80.lsetxattr
	/* errno_t lsetxattr(char const *path,
	 *                   char const *name,
	 *                   void const *buf,
	 *                   size_t bufsize,
	 *                   syscall_ulong_t flags) */
	.weak __asm32_int80_lsetxattr
INTERN_FUNCTION(__asm32_int80_lsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lsetxattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lsetxattr)

.section .text.x86.asm32_syscall_int80.fsetxattr
	/* errno_t fsetxattr(fd_t fd,
	 *                   char const *name,
	 *                   void const *buf,
	 *                   size_t bufsize,
	 *                   syscall_ulong_t flags) */
	.weak __asm32_int80_fsetxattr
INTERN_FUNCTION(__asm32_int80_fsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fsetxattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fsetxattr)

.section .text.x86.asm32_syscall_int80.getxattr
	/* ssize_t getxattr(char const *path,
	 *                  char const *name,
	 *                  void *buf,
	 *                  size_t bufsize) */
	.weak __asm32_int80_getxattr
INTERN_FUNCTION(__asm32_int80_getxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getxattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getxattr)

.section .text.x86.asm32_syscall_int80.lgetxattr
	/* ssize_t lgetxattr(char const *path,
	 *                   char const *name,
	 *                   void *buf,
	 *                   size_t bufsize) */
	.weak __asm32_int80_lgetxattr
INTERN_FUNCTION(__asm32_int80_lgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe6
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lgetxattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lgetxattr)

.section .text.x86.asm32_syscall_int80.fgetxattr
	/* ssize_t fgetxattr(fd_t fd,
	 *                   char const *name,
	 *                   void *buf,
	 *                   size_t bufsize) */
	.weak __asm32_int80_fgetxattr
INTERN_FUNCTION(__asm32_int80_fgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe7
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fgetxattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fgetxattr)

.section .text.x86.asm32_syscall_int80.listxattr
	/* ssize_t listxattr(char const *path,
	 *                   char *listbuf,
	 *                   size_t listbufsize) */
	.weak __asm32_int80_listxattr
INTERN_FUNCTION(__asm32_int80_listxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe8
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_listxattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_listxattr)

.section .text.x86.asm32_syscall_int80.llistxattr
	/* ssize_t llistxattr(char const *path,
	 *                    char *listbuf,
	 *                    size_t listbufsize) */
	.weak __asm32_int80_llistxattr
INTERN_FUNCTION(__asm32_int80_llistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xe9
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_llistxattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_llistxattr)

.section .text.x86.asm32_syscall_int80.flistxattr
	/* ssize_t flistxattr(fd_t fd,
	 *                    char *listbuf,
	 *                    size_t listbufsize) */
	.weak __asm32_int80_flistxattr
INTERN_FUNCTION(__asm32_int80_flistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xea
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_flistxattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_flistxattr)

.section .text.x86.asm32_syscall_int80.removexattr
	/* errno_t removexattr(char const *path,
	 *                     char const *name) */
	.weak __asm32_int80_removexattr
INTERN_FUNCTION(__asm32_int80_removexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xeb
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_removexattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_removexattr)

.section .text.x86.asm32_syscall_int80.lremovexattr
	/* errno_t lremovexattr(char const *path,
	 *                      char const *name) */
	.weak __asm32_int80_lremovexattr
INTERN_FUNCTION(__asm32_int80_lremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xec
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lremovexattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lremovexattr)

.section .text.x86.asm32_syscall_int80.fremovexattr
	/* errno_t fremovexattr(int fd,
	 *                      char const *name) */
	.weak __asm32_int80_fremovexattr
INTERN_FUNCTION(__asm32_int80_fremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xed
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fremovexattr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fremovexattr)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_int80.tkill
	/* errno_t tkill(pid_t tid,
	 *               syscall_ulong_t signo) */
	.weak __asm32_int80_tkill
INTERN_FUNCTION(__asm32_int80_tkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xee
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_tkill
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_tkill)

.section .text.x86.asm32_syscall_int80.sendfile64
	/* ssize_t sendfile64(fd_t out_fd,
	 *                    fd_t in_fd,
	 *                    uint64_t *offset,
	 *                    size_t count) */
	.weak __asm32_int80_sendfile64
INTERN_FUNCTION(__asm32_int80_sendfile64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xef
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sendfile64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sendfile64)

.section .text.x86.asm32_syscall_int80.futex
	/* syscall_slong_t futex(uint32_t *uaddr,
	 *                       syscall_ulong_t futex_op,
	 *                       uint32_t val,
	 *                       struct __timespec32 const *timeout_or_val2,
	 *                       uint32_t *uaddr2,
	 *                       uint32_t val3) */
	.weak __asm32_int80_futex
INTERN_FUNCTION(__asm32_int80_futex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xf0
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_futex
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_futex)

.section .text.x86.asm32_syscall_int80.sched_setaffinity
	/* errno_t sched_setaffinity(pid_t pid,
	 *                           size_t cpusetsize,
	 *                           struct __cpu_set_struct const *cpuset) */
	.weak __asm32_int80_sched_setaffinity
INTERN_FUNCTION(__asm32_int80_sched_setaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xf1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sched_setaffinity
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_setaffinity)

.section .text.x86.asm32_syscall_int80.sched_getaffinity
	/* errno_t sched_getaffinity(pid_t pid,
	 *                           size_t cpusetsize,
	 *                           struct __cpu_set_struct *cpuset) */
	.weak __asm32_int80_sched_getaffinity
INTERN_FUNCTION(__asm32_int80_sched_getaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xf2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sched_getaffinity
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_getaffinity)

.section .text.x86.asm32_syscall_int80.exit_group
	/* void exit_group(syscall_ulong_t exit_code) */
	.weak __asm32_int80_exit_group
INTERN_FUNCTION(__asm32_int80_exit_group)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xfc
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_exit_group
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_exit_group)

.section .text.x86.asm32_syscall_int80.epoll_create
	/* fd_t epoll_create(syscall_ulong_t size) */
	.weak __asm32_int80_epoll_create
INTERN_FUNCTION(__asm32_int80_epoll_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xfe
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_epoll_create
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_epoll_create)

.section .text.x86.asm32_syscall_int80.epoll_ctl
	/* errno_t epoll_ctl(fd_t epfd,
	 *                   syscall_ulong_t op,
	 *                   fd_t fd,
	 *                   struct epoll_event *event) */
	.weak __asm32_int80_epoll_ctl
INTERN_FUNCTION(__asm32_int80_epoll_ctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xff
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_epoll_ctl
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_epoll_ctl)

.section .text.x86.asm32_syscall_int80.epoll_wait
	/* errno_t epoll_wait(fd_t epfd,
	 *                    struct epoll_event *events,
	 *                    syscall_ulong_t maxevents,
	 *                    syscall_slong_t timeout) */
	.weak __asm32_int80_epoll_wait
INTERN_FUNCTION(__asm32_int80_epoll_wait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x100
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_epoll_wait
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_epoll_wait)

.section .text.x86.asm32_syscall_int80.remap_file_pages
	/* errno_t remap_file_pages(void *start,
	 *                          size_t size,
	 *                          syscall_ulong_t prot,
	 *                          size_t pgoff,
	 *                          syscall_ulong_t flags) */
	.weak __asm32_int80_remap_file_pages
INTERN_FUNCTION(__asm32_int80_remap_file_pages)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x101
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_remap_file_pages
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_remap_file_pages)

.section .text.x86.asm32_syscall_int80.set_tid_address
	/* pid_t set_tid_address(pid_t *tidptr) */
	.weak __asm32_int80_set_tid_address
INTERN_FUNCTION(__asm32_int80_set_tid_address)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x102
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_set_tid_address
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_set_tid_address)

.section .text.x86.asm32_syscall_int80.timer_create
	/* errno_t timer_create(clockid_t clock_id,
	 *                      struct sigevent *evp,
	 *                      timer_t *timerid) */
	.weak __asm32_int80_timer_create
INTERN_FUNCTION(__asm32_int80_timer_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x103
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timer_create
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timer_create)

.section .text.x86.asm32_syscall_int80.timer_settime
	/* errno_t timer_settime(timer_t timerid,
	 *                       syscall_ulong_t flags,
	 *                       struct __itimerspec32 const *value,
	 *                       struct __itimerspec32 *ovalue) */
	.weak __asm32_int80_timer_settime
INTERN_FUNCTION(__asm32_int80_timer_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x104
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timer_settime
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timer_settime)

.section .text.x86.asm32_syscall_int80.timer_gettime
	/* errno_t timer_gettime(timer_t timerid,
	 *                       struct __itimerspec32 *value) */
	.weak __asm32_int80_timer_gettime
INTERN_FUNCTION(__asm32_int80_timer_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x105
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timer_gettime
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timer_gettime)

.section .text.x86.asm32_syscall_int80.timer_getoverrun
	/* syscall_slong_t timer_getoverrun(timer_t timerid) */
	.weak __asm32_int80_timer_getoverrun
INTERN_FUNCTION(__asm32_int80_timer_getoverrun)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x106
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_timer_getoverrun
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timer_getoverrun)

.section .text.x86.asm32_syscall_int80.timer_delete
	/* errno_t timer_delete(timer_t timerid) */
	.weak __asm32_int80_timer_delete
INTERN_FUNCTION(__asm32_int80_timer_delete)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x107
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_timer_delete
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timer_delete)

.section .text.x86.asm32_syscall_int80.clock_settime
	/* errno_t clock_settime(clockid_t clock_id,
	 *                       struct __timespec32 const *tp) */
	.weak __asm32_int80_clock_settime
INTERN_FUNCTION(__asm32_int80_clock_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x108
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_clock_settime
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_clock_settime)

.section .text.x86.asm32_syscall_int80.clock_gettime
	/* errno_t clock_gettime(clockid_t clock_id,
	 *                       struct __timespec32 *tp) */
	.weak __asm32_int80_clock_gettime
INTERN_FUNCTION(__asm32_int80_clock_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x109
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_clock_gettime
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_clock_gettime)

.section .text.x86.asm32_syscall_int80.clock_getres
	/* errno_t clock_getres(clockid_t clock_id,
	 *                      struct __timespec32 *res) */
	.weak __asm32_int80_clock_getres
INTERN_FUNCTION(__asm32_int80_clock_getres)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_clock_getres
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_clock_getres)

.section .text.x86.asm32_syscall_int80.clock_nanosleep
	/* errno_t clock_nanosleep(clockid_t clock_id,
	 *                         syscall_ulong_t flags,
	 *                         struct __timespec32 const *requested_time,
	 *                         struct __timespec32 *remaining) */
	.weak __asm32_int80_clock_nanosleep
INTERN_FUNCTION(__asm32_int80_clock_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_clock_nanosleep
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_clock_nanosleep)

.section .text.x86.asm32_syscall_int80.statfs64
	/* errno_t statfs64(char const *file,
	 *                  struct statfs64 *buf) */
	.weak __asm32_int80_statfs64
INTERN_FUNCTION(__asm32_int80_statfs64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_statfs64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_statfs64)

.section .text.x86.asm32_syscall_int80.fstatfs64
	/* errno_t fstatfs64(fd_t file,
	 *                   struct statfs64 *buf) */
	.weak __asm32_int80_fstatfs64
INTERN_FUNCTION(__asm32_int80_fstatfs64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fstatfs64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fstatfs64)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_int80.tgkill
	/* errno_t tgkill(pid_t tgid,
	 *                pid_t tid,
	 *                syscall_ulong_t signo) */
	.weak __asm32_int80_tgkill
INTERN_FUNCTION(__asm32_int80_tgkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_tgkill
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_tgkill)

.section .text.x86.asm32_syscall_int80.utimes
	/* errno_t utimes(char const *filename,
	 *                [2] struct __timeval32 const *times) */
	.weak __asm32_int80_utimes
INTERN_FUNCTION(__asm32_int80_utimes)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x10f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_utimes
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_utimes)

/* @param: options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
.section .text.x86.asm32_syscall_int80.waitid
	/* errno_t waitid(idtype_t idtype,
	 *                id_t id,
	 *                struct __siginfo_struct *infop,
	 *                syscall_ulong_t options,
	 *                struct rusage *ru) */
	.weak __asm32_int80_waitid
INTERN_FUNCTION(__asm32_int80_waitid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x11c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_waitid
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_waitid)

.section .text.x86.asm32_syscall_int80.ioprio_set
	/* errno_t ioprio_set(syscall_ulong_t which,
	 *                    syscall_ulong_t who,
	 *                    syscall_ulong_t ioprio) */
	.weak __asm32_int80_ioprio_set
INTERN_FUNCTION(__asm32_int80_ioprio_set)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x121
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ioprio_set
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ioprio_set)

.section .text.x86.asm32_syscall_int80.ioprio_get
	/* errno_t ioprio_get(syscall_ulong_t which,
	 *                    syscall_ulong_t who) */
	.weak __asm32_int80_ioprio_get
INTERN_FUNCTION(__asm32_int80_ioprio_get)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x122
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ioprio_get
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ioprio_get)

.section .text.x86.asm32_syscall_int80.openat
	/* fd_t openat(fd_t dirfd,
	 *             char const *filename,
	 *             oflag_t oflags,
	 *             mode_t mode) */
	.weak __asm32_int80_openat
INTERN_FUNCTION(__asm32_int80_openat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x127
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_openat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_openat)

.section .text.x86.asm32_syscall_int80.mkdirat
	/* errno_t mkdirat(fd_t dirfd,
	 *                 char const *pathname,
	 *                 mode_t mode) */
	.weak __asm32_int80_mkdirat
INTERN_FUNCTION(__asm32_int80_mkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x128
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mkdirat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mkdirat)

.section .text.x86.asm32_syscall_int80.mknodat
	/* errno_t mknodat(fd_t dirfd,
	 *                 char const *nodename,
	 *                 mode_t mode,
	 *                 dev_t dev) */
	.weak __asm32_int80_mknodat
INTERN_FUNCTION(__asm32_int80_mknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x129
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mknodat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.fchownat
	/* errno_t fchownat(fd_t dirfd,
	 *                  char const *filename,
	 *                  uint32_t owner,
	 *                  uint32_t group,
	 *                  atflag_t flags) */
	.weak __asm32_int80_fchownat
INTERN_FUNCTION(__asm32_int80_fchownat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fchownat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fchownat)

.section .text.x86.asm32_syscall_int80.futimesat
	/* errno_t futimesat(fd_t dirfd,
	 *                   const char *filename,
	 *                   [2] struct __timeval32 const *times) */
	.weak __asm32_int80_futimesat
INTERN_FUNCTION(__asm32_int80_futimesat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_futimesat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_futimesat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.linux_fstatat64
	/* errno_t linux_fstatat64(fd_t dirfd,
	 *                         char const *filename,
	 *                         struct linux_stat64 *statbuf,
	 *                         atflag_t flags) */
	.weak __asm32_int80_linux_fstatat64
INTERN_FUNCTION(__asm32_int80_linux_fstatat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linux_fstatat64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linux_fstatat64)

/* @param: flags: Set of `0|AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.unlinkat
	/* errno_t unlinkat(fd_t dirfd,
	 *                  char const *name,
	 *                  atflag_t flags) */
	.weak __asm32_int80_unlinkat
INTERN_FUNCTION(__asm32_int80_unlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_unlinkat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_unlinkat)

.section .text.x86.asm32_syscall_int80.renameat
	/* errno_t renameat(fd_t oldfd,
	 *                  char const *oldname,
	 *                  fd_t newfd,
	 *                  char const *newname_or_path) */
	.weak __asm32_int80_renameat
INTERN_FUNCTION(__asm32_int80_renameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_renameat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_renameat)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.linkat
	/* errno_t linkat(fd_t fromfd,
	 *                char const *existing_file,
	 *                fd_t tofd,
	 *                char const *target_path,
	 *                atflag_t flags) */
	.weak __asm32_int80_linkat
INTERN_FUNCTION(__asm32_int80_linkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x12f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_linkat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_linkat)

.section .text.x86.asm32_syscall_int80.symlinkat
	/* errno_t symlinkat(char const *link_text,
	 *                   fd_t tofd,
	 *                   char const *target_path) */
	.weak __asm32_int80_symlinkat
INTERN_FUNCTION(__asm32_int80_symlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x130
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_symlinkat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_symlinkat)

.section .text.x86.asm32_syscall_int80.readlinkat
	/* ssize_t readlinkat(fd_t dirfd,
	 *                    char const *path,
	 *                    char *buf,
	 *                    size_t buflen) */
	.weak __asm32_int80_readlinkat
INTERN_FUNCTION(__asm32_int80_readlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x131
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_readlinkat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_readlinkat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.fchmodat
	/* errno_t fchmodat(fd_t dirfd,
	 *                  char const *filename,
	 *                  mode_t mode,
	 *                  atflag_t flags) */
	.weak __asm32_int80_fchmodat
INTERN_FUNCTION(__asm32_int80_fchmodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x132
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fchmodat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.faccessat
	/* errno_t faccessat(fd_t dirfd,
	 *                   char const *filename,
	 *                   syscall_ulong_t type,
	 *                   atflag_t flags) */
	.weak __asm32_int80_faccessat
INTERN_FUNCTION(__asm32_int80_faccessat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x133
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_faccessat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_faccessat)

.section .text.x86.asm32_syscall_int80.pselect6
	/* ssize_t pselect6(size_t nfds,
	 *                  struct __fd_set_struct *readfds,
	 *                  struct __fd_set_struct *writefds,
	 *                  struct __fd_set_struct *exceptfds,
	 *                  struct __timespec32 const *timeout,
	 *                  void const *sigmask_sigset_and_len) */
	.weak __asm32_int80_pselect6
INTERN_FUNCTION(__asm32_int80_pselect6)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x134
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_pselect6
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pselect6)

.section .text.x86.asm32_syscall_int80.ppoll
	/* ssize_t ppoll(struct pollfd *fds,
	 *               size_t nfds,
	 *               struct __timespec32 const *timeout_ts,
	 *               struct __sigset_struct const *sigmask,
	 *               size_t sigsetsize) */
	.weak __asm32_int80_ppoll
INTERN_FUNCTION(__asm32_int80_ppoll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x135
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ppoll
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ppoll)

/* param flags: Set of `CLONE_*' */
.section .text.x86.asm32_syscall_int80.unshare
	/* errno_t unshare(syscall_ulong_t flags) */
	.weak __asm32_int80_unshare
INTERN_FUNCTION(__asm32_int80_unshare)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x136
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_unshare
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_unshare)

.section .text.x86.asm32_syscall_int80.splice
	/* ssize_t splice(fd_t fdin,
	 *                uint64_t *offin,
	 *                fd_t fdout,
	 *                uint64_t *offout,
	 *                size_t length,
	 *                syscall_ulong_t flags) */
	.weak __asm32_int80_splice
INTERN_FUNCTION(__asm32_int80_splice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x139
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_splice
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_splice)

.section .text.x86.asm32_syscall_int80.sync_file_range
	/* errno_t sync_file_range(fd_t fd,
	 *                         uint64_t offset,
	 *                         uint64_t count,
	 *                         syscall_ulong_t flags) */
	.weak __asm32_int80_sync_file_range
INTERN_FUNCTION(__asm32_int80_sync_file_range)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x13a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sync_file_range
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sync_file_range)

.section .text.x86.asm32_syscall_int80.tee
	/* ssize_t tee(fd_t fdin,
	 *             fd_t fdout,
	 *             size_t length,
	 *             syscall_ulong_t flags) */
	.weak __asm32_int80_tee
INTERN_FUNCTION(__asm32_int80_tee)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x13b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_tee
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_tee)

.section .text.x86.asm32_syscall_int80.vmsplice
	/* ssize_t vmsplice(fd_t fdout,
	 *                  struct iovec const *iov,
	 *                  size_t count,
	 *                  syscall_ulong_t flags) */
	.weak __asm32_int80_vmsplice
INTERN_FUNCTION(__asm32_int80_vmsplice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x13c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_vmsplice
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_vmsplice)

.section .text.x86.asm32_syscall_int80.getcpu
	/* errno_t getcpu(uint32_t *cpu,
	 *                uint32_t *node,
	 *                struct getcpu_cache *tcache) */
	.weak __asm32_int80_getcpu
INTERN_FUNCTION(__asm32_int80_getcpu)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x13e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getcpu
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getcpu)

.section .text.x86.asm32_syscall_int80.epoll_pwait
	/* errno_t epoll_pwait(fd_t epfd,
	 *                     struct epoll_event *events,
	 *                     syscall_ulong_t maxevents,
	 *                     syscall_slong_t timeout,
	 *                     struct __sigset_struct const *ss) */
	.weak __asm32_int80_epoll_pwait
INTERN_FUNCTION(__asm32_int80_epoll_pwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x13f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_epoll_pwait
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_epoll_pwait)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.utimensat
	/* errno_t utimensat(fd_t dirfd,
	 *                   char const *filename,
	 *                   [2-3] struct __timespec32 const *times,
	 *                   atflag_t flags) */
	.weak __asm32_int80_utimensat
INTERN_FUNCTION(__asm32_int80_utimensat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x140
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_utimensat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_utimensat)

.section .text.x86.asm32_syscall_int80.signalfd
	/* errno_t signalfd(fd_t fd,
	 *                  struct __sigset_struct const *sigmask,
	 *                  size_t sigsetsize) */
	.weak __asm32_int80_signalfd
INTERN_FUNCTION(__asm32_int80_signalfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x141
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_signalfd
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_signalfd)

/* Return file descriptor for new interval timer source */
.section .text.x86.asm32_syscall_int80.timerfd_create
	/* fd_t timerfd_create(clockid_t clock_id,
	 *                     syscall_ulong_t flags) */
	.weak __asm32_int80_timerfd_create
INTERN_FUNCTION(__asm32_int80_timerfd_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x142
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timerfd_create
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timerfd_create)

.section .text.x86.asm32_syscall_int80.eventfd
	/* fd_t eventfd(syscall_ulong_t initval) */
	.weak __asm32_int80_eventfd
INTERN_FUNCTION(__asm32_int80_eventfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x143
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_eventfd
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_eventfd)

.section .text.x86.asm32_syscall_int80.fallocate
	/* errno_t fallocate(fd_t fd,
	 *                   syscall_ulong_t mode,
	 *                   uint32_t offset,
	 *                   uint32_t length) */
	.weak __asm32_int80_fallocate
INTERN_FUNCTION(__asm32_int80_fallocate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x144
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fallocate
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
.section .text.x86.asm32_syscall_int80.timerfd_settime
	/* errno_t timerfd_settime(fd_t ufd,
	 *                         syscall_ulong_t flags,
	 *                         struct __itimerspec32 const *utmr,
	 *                         struct __itimerspec32 *otmr) */
	.weak __asm32_int80_timerfd_settime
INTERN_FUNCTION(__asm32_int80_timerfd_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x145
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timerfd_settime
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timerfd_settime)

/* Return the next expiration time of UFD */
.section .text.x86.asm32_syscall_int80.timerfd_gettime
	/* errno_t timerfd_gettime(fd_t ufd,
	 *                         struct __itimerspec32 *otmr) */
	.weak __asm32_int80_timerfd_gettime
INTERN_FUNCTION(__asm32_int80_timerfd_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x146
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timerfd_gettime
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timerfd_gettime)

.section .text.x86.asm32_syscall_int80.signalfd4
	/* errno_t signalfd4(fd_t fd,
	 *                   struct __sigset_struct const *sigmask,
	 *                   size_t sigsetsize,
	 *                   syscall_ulong_t flags) */
	.weak __asm32_int80_signalfd4
INTERN_FUNCTION(__asm32_int80_signalfd4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x147
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_signalfd4
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_signalfd4)

.section .text.x86.asm32_syscall_int80.eventfd2
	/* fd_t eventfd2(syscall_ulong_t initval,
	 *               syscall_ulong_t flags) */
	.weak __asm32_int80_eventfd2
INTERN_FUNCTION(__asm32_int80_eventfd2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x148
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_eventfd2
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_eventfd2)

.section .text.x86.asm32_syscall_int80.epoll_create1
	/* fd_t epoll_create1(syscall_ulong_t flags) */
	.weak __asm32_int80_epoll_create1
INTERN_FUNCTION(__asm32_int80_epoll_create1)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x149
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_epoll_create1
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
.section .text.x86.asm32_syscall_int80.dup3
	/* fd_t dup3(fd_t oldfd,
	 *           fd_t newfd,
	 *           oflag_t flags) */
	.weak __asm32_int80_dup3
INTERN_FUNCTION(__asm32_int80_dup3)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x14a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_dup3
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_dup3)

.section .text.x86.asm32_syscall_int80.pipe2
	/* errno_t pipe2([2] fd_t *pipedes,
	 *               oflag_t flags) */
	.weak __asm32_int80_pipe2
INTERN_FUNCTION(__asm32_int80_pipe2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x14b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_pipe2
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pipe2)

.section .text.x86.asm32_syscall_int80.preadv
	/* ssize_t preadv(fd_t fd,
	 *                struct iovec const *iovec,
	 *                size_t count,
	 *                uint64_t offset) */
	.weak __asm32_int80_preadv
INTERN_FUNCTION(__asm32_int80_preadv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x14d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_preadv
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_preadv)

.section .text.x86.asm32_syscall_int80.pwritev
	/* ssize_t pwritev(fd_t fd,
	 *                 struct iovec const *iovec,
	 *                 size_t count,
	 *                 uint64_t offset) */
	.weak __asm32_int80_pwritev
INTERN_FUNCTION(__asm32_int80_pwritev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x14e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_pwritev
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pwritev)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_int80.rt_tgsigqueueinfo
	/* errno_t rt_tgsigqueueinfo(pid_t tgid,
	 *                           pid_t tid,
	 *                           syscall_ulong_t signo,
	 *                           struct __siginfo_struct const *uinfo) */
	.weak __asm32_int80_rt_tgsigqueueinfo
INTERN_FUNCTION(__asm32_int80_rt_tgsigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x14f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rt_tgsigqueueinfo
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rt_tgsigqueueinfo)

.section .text.x86.asm32_syscall_int80.recvmmsg
	/* ssize_t recvmmsg(fd_t sockfd,
	 *                  struct mmsghdr *vmessages,
	 *                  size_t vlen,
	 *                  syscall_ulong_t flags,
	 *                  struct __timespec32 *tmo) */
	.weak __asm32_int80_recvmmsg
INTERN_FUNCTION(__asm32_int80_recvmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x151
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_recvmmsg
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_recvmmsg)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
.section .text.x86.asm32_syscall_int80.prlimit64
	/* errno_t prlimit64(pid_t pid,
	 *                   syscall_ulong_t resource,
	 *                   struct rlimit64 const *new_limit,
	 *                   struct rlimit64 *old_limit) */
	.weak __asm32_int80_prlimit64
INTERN_FUNCTION(__asm32_int80_prlimit64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x154
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_prlimit64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_prlimit64)

.section .text.x86.asm32_syscall_int80.name_to_handle_at
	/* errno_t name_to_handle_at(fd_t dirfd,
	 *                           char const *name,
	 *                           struct file_handle *handle,
	 *                           int32_t *mnt_id,
	 *                           syscall_ulong_t flags) */
	.weak __asm32_int80_name_to_handle_at
INTERN_FUNCTION(__asm32_int80_name_to_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x155
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_name_to_handle_at
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_name_to_handle_at)

.section .text.x86.asm32_syscall_int80.open_by_handle_at
	/* fd_t open_by_handle_at(fd_t mountdirfd,
	 *                        struct file_handle *handle,
	 *                        syscall_ulong_t flags) */
	.weak __asm32_int80_open_by_handle_at
INTERN_FUNCTION(__asm32_int80_open_by_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x156
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_open_by_handle_at
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_open_by_handle_at)

.section .text.x86.asm32_syscall_int80.syncfs
	/* errno_t syncfs(fd_t fd) */
	.weak __asm32_int80_syncfs
INTERN_FUNCTION(__asm32_int80_syncfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x158
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_syncfs
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_syncfs)

.section .text.x86.asm32_syscall_int80.sendmmsg
	/* ssize_t sendmmsg(fd_t sockfd,
	 *                  struct mmsghdr *vmessages,
	 *                  size_t vlen,
	 *                  syscall_ulong_t flags) */
	.weak __asm32_int80_sendmmsg
INTERN_FUNCTION(__asm32_int80_sendmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x159
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sendmmsg
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sendmmsg)

.section .text.x86.asm32_syscall_int80.setns
	/* errno_t setns(fd_t fd,
	 *               syscall_ulong_t nstype) */
	.weak __asm32_int80_setns
INTERN_FUNCTION(__asm32_int80_setns)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x15a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setns
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setns)

.section .text.x86.asm32_syscall_int80.process_vm_readv
	/* ssize_t process_vm_readv(pid_t pid,
	 *                          struct iovec const *lvec,
	 *                          size_t liovcnt,
	 *                          struct iovec const *rvec,
	 *                          size_t riovcnt,
	 *                          syscall_ulong_t flags) */
	.weak __asm32_int80_process_vm_readv
INTERN_FUNCTION(__asm32_int80_process_vm_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x15b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_process_vm_readv
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_process_vm_readv)

.section .text.x86.asm32_syscall_int80.process_vm_writev
	/* ssize_t process_vm_writev(pid_t pid,
	 *                           struct iovec const *lvec,
	 *                           size_t liovcnt,
	 *                           struct iovec const *rvec,
	 *                           size_t riovcnt,
	 *                           syscall_ulong_t flags) */
	.weak __asm32_int80_process_vm_writev
INTERN_FUNCTION(__asm32_int80_process_vm_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x15c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_process_vm_writev
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_process_vm_writev)

.section .text.x86.asm32_syscall_int80.kcmp
	/* syscall_slong_t kcmp(pid_t pid1,
	 *                      pid_t pid2,
	 *                      syscall_ulong_t type,
	 *                      syscall_ulong_t idx1,
	 *                      syscall_ulong_t idx2) */
	.weak __asm32_int80_kcmp
INTERN_FUNCTION(__asm32_int80_kcmp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x15d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_kcmp
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_kcmp)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
.section .text.x86.asm32_syscall_int80.renameat2
	/* errno_t renameat2(fd_t olddirfd,
	 *                   char const *oldpath,
	 *                   fd_t newdirfd,
	 *                   char const *newpath,
	 *                   syscall_ulong_t flags) */
	.weak __asm32_int80_renameat2
INTERN_FUNCTION(__asm32_int80_renameat2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x161
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_renameat2
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_renameat2)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.execveat
	/* errno_t execveat(fd_t dirfd,
	 *                  char const *pathname,
	 *                  char const *const *argv,
	 *                  char const *const *envp,
	 *                  atflag_t flags) */
	.weak __asm32_int80_execveat
INTERN_FUNCTION(__asm32_int80_execveat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x166
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_execveat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_execveat)

.section .text.x86.asm32_syscall_int80.socket
	/* fd_t socket(syscall_ulong_t domain,
	 *             syscall_ulong_t type,
	 *             syscall_ulong_t protocol) */
	.weak __asm32_int80_socket
INTERN_FUNCTION(__asm32_int80_socket)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x167
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_socket
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_socket)

.section .text.x86.asm32_syscall_int80.socketpair
	/* errno_t socketpair(syscall_ulong_t domain,
	 *                    syscall_ulong_t type,
	 *                    syscall_ulong_t protocol,
	 *                    [2] fd_t *fds) */
	.weak __asm32_int80_socketpair
INTERN_FUNCTION(__asm32_int80_socketpair)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x168
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_socketpair
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_socketpair)

.section .text.x86.asm32_syscall_int80.bind
	/* errno_t bind(fd_t sockfd,
	 *              struct sockaddr const *addr,
	 *              socklen_t addr_len) */
	.weak __asm32_int80_bind
INTERN_FUNCTION(__asm32_int80_bind)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x169
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_bind
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_bind)

.section .text.x86.asm32_syscall_int80.connect
	/* errno_t connect(fd_t sockfd,
	 *                 struct sockaddr const *addr,
	 *                 socklen_t addr_len) */
	.weak __asm32_int80_connect
INTERN_FUNCTION(__asm32_int80_connect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x16a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_connect
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_connect)

.section .text.x86.asm32_syscall_int80.listen
	/* errno_t listen(fd_t sockfd,
	 *                syscall_ulong_t max_backlog) */
	.weak __asm32_int80_listen
INTERN_FUNCTION(__asm32_int80_listen)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x16b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_listen
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_listen)

.section .text.x86.asm32_syscall_int80.accept4
	/* fd_t accept4(fd_t sockfd,
	 *              struct sockaddr *addr,
	 *              socklen_t *addr_len,
	 *              syscall_ulong_t flags) */
	.weak __asm32_int80_accept4
INTERN_FUNCTION(__asm32_int80_accept4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x16c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_accept4
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_accept4)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.x86.asm32_syscall_int80.getsockopt
	/* errno_t getsockopt(fd_t sockfd,
	 *                    syscall_ulong_t level,
	 *                    syscall_ulong_t optname,
	 *                    void *optval,
	 *                    socklen_t *optlen) */
	.weak __asm32_int80_getsockopt
INTERN_FUNCTION(__asm32_int80_getsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x16d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getsockopt
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.x86.asm32_syscall_int80.setsockopt
	/* errno_t setsockopt(fd_t sockfd,
	 *                    syscall_ulong_t level,
	 *                    syscall_ulong_t optname,
	 *                    void const *optval,
	 *                    socklen_t optlen) */
	.weak __asm32_int80_setsockopt
INTERN_FUNCTION(__asm32_int80_setsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x16e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setsockopt
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setsockopt)

.section .text.x86.asm32_syscall_int80.getsockname
	/* errno_t getsockname(fd_t sockfd,
	 *                     struct sockaddr *addr,
	 *                     socklen_t *addr_len) */
	.weak __asm32_int80_getsockname
INTERN_FUNCTION(__asm32_int80_getsockname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x16f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getsockname
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getsockname)

.section .text.x86.asm32_syscall_int80.getpeername
	/* errno_t getpeername(fd_t sockfd,
	 *                     struct sockaddr *addr,
	 *                     socklen_t *addr_len) */
	.weak __asm32_int80_getpeername
INTERN_FUNCTION(__asm32_int80_getpeername)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x170
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getpeername
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getpeername)

/* param flags: Set of `MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL|MSG_OOB' */
.section .text.x86.asm32_syscall_int80.sendto
	/* ssize_t sendto(fd_t sockfd,
	 *                void const *buf,
	 *                size_t bufsize,
	 *                syscall_ulong_t flags,
	 *                struct sockaddr const *addr,
	 *                socklen_t addr_len) */
	.weak __asm32_int80_sendto
INTERN_FUNCTION(__asm32_int80_sendto)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x171
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sendto
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sendto)

.section .text.x86.asm32_syscall_int80.sendmsg
	/* ssize_t sendmsg(fd_t sockfd,
	 *                 struct msghdr const *message,
	 *                 syscall_ulong_t flags) */
	.weak __asm32_int80_sendmsg
INTERN_FUNCTION(__asm32_int80_sendmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x172
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sendmsg
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sendmsg)

.section .text.x86.asm32_syscall_int80.recvfrom
	/* ssize_t recvfrom(fd_t sockfd,
	 *                  void *buf,
	 *                  size_t bufsize,
	 *                  syscall_ulong_t flags,
	 *                  struct sockaddr *addr,
	 *                  socklen_t *addr_len) */
	.weak __asm32_int80_recvfrom
INTERN_FUNCTION(__asm32_int80_recvfrom)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x173
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_recvfrom
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_recvfrom)

.section .text.x86.asm32_syscall_int80.recvmsg
	/* ssize_t recvmsg(fd_t sockfd,
	 *                 struct msghdr *message,
	 *                 syscall_ulong_t flags) */
	.weak __asm32_int80_recvmsg
INTERN_FUNCTION(__asm32_int80_recvmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x174
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_recvmsg
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_recvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
.section .text.x86.asm32_syscall_int80.shutdown
	/* errno_t shutdown(fd_t sockfd,
	 *                  syscall_ulong_t how) */
	.weak __asm32_int80_shutdown
INTERN_FUNCTION(__asm32_int80_shutdown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x175
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_shutdown
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_shutdown)

.section .text.x86.asm32_syscall_int80.hop
	/* syscall_slong_t hop(fd_t fd,
	 *                     syscall_ulong_t command,
	 *                     void *arg) */
	.weak __asm32_int80_hop
INTERN_FUNCTION(__asm32_int80_hop)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000001
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_hop
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_hop)

.section .text.x86.asm32_syscall_int80.hopf
	/* syscall_slong_t hopf(fd_t fd,
	 *                      syscall_ulong_t command,
	 *                      iomode_t mode,
	 *                      void *arg) */
	.weak __asm32_int80_hopf
INTERN_FUNCTION(__asm32_int80_hopf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000002
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_hopf
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_hopf)

.section .text.x86.asm32_syscall_int80.readf
	/* ssize_t readf(fd_t fd,
	 *               void *buf,
	 *               size_t bufsize,
	 *               iomode_t mode) */
	.weak __asm32_int80_readf
INTERN_FUNCTION(__asm32_int80_readf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000003
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_readf
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_readf)

.section .text.x86.asm32_syscall_int80.writef
	/* ssize_t writef(fd_t fd,
	 *                void const *buf,
	 *                size_t bufsize,
	 *                iomode_t mode) */
	.weak __asm32_int80_writef
INTERN_FUNCTION(__asm32_int80_writef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000004
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_writef
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_writef)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
.section .text.x86.asm32_syscall_int80.detach
	/* errno_t detach(pid_t pid) */
	.weak __asm32_int80_detach
INTERN_FUNCTION(__asm32_int80_detach)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000005
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_detach
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_detach)

/* Returns a bitset of all of the currently mounted dos-drives */
.section .text.x86.asm32_syscall_int80.getdrives
	/* syscall_slong_t getdrives(void); */
	.weak __asm32_int80_getdrives
INTERN_FUNCTION(__asm32_int80_getdrives)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000006
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_getdrives
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.frealpath4
	/* ssize_t frealpath4(fd_t fd,
	 *                    char *buf,
	 *                    size_t buflen,
	 *                    atflag_t flags) */
	.weak __asm32_int80_frealpath4
INTERN_FUNCTION(__asm32_int80_frealpath4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000007
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_frealpath4
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_frealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.frealpathat
	/* ssize_t frealpathat(fd_t dirfd,
	 *                     char const *filename,
	 *                     char *buf,
	 *                     size_t buflen,
	 *                     atflag_t flags) */
	.weak __asm32_int80_frealpathat
INTERN_FUNCTION(__asm32_int80_frealpathat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000008
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_frealpathat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_frealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
.section .text.x86.asm32_syscall_int80.rpc_schedule
	/* syscall_slong_t rpc_schedule(pid_t target,
	 *                              syscall_ulong_t flags,
	 *                              uint8_t const *program,
	 *                              void **arguments) */
	.weak __asm32_int80_rpc_schedule
INTERN_FUNCTION(__asm32_int80_rpc_schedule)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000009
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rpc_schedule
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rpc_schedule)

.section .text.x86.asm32_syscall_int80.sysctl
	/* syscall_slong_t sysctl(syscall_ulong_t command,
	 *                        void *arg) */
	.weak __asm32_int80_sysctl
INTERN_FUNCTION(__asm32_int80_sysctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sysctl
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
.section .text.x86.asm32_syscall_int80.openpty
	/* errno_t openpty(fd_t *amaster,
	 *                 fd_t *aslave,
	 *                 char *name,
	 *                 struct termios const *termp,
	 *                 struct winsize const *winp) */
	.weak __asm32_int80_openpty
INTERN_FUNCTION(__asm32_int80_openpty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_openpty
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_openpty)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.fchdirat
	/* errno_t fchdirat(fd_t dirfd,
	 *                  char const *path,
	 *                  atflag_t flags) */
	.weak __asm32_int80_fchdirat
INTERN_FUNCTION(__asm32_int80_fchdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fchdirat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fchdirat)

.section .text.x86.asm32_syscall_int80.time64
	/* time64_t time64(time64_t *timer) */
	.weak __asm32_int80_time64
INTERN_FUNCTION(__asm32_int80_time64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_time64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi %rcx /* addq $8, %rsp */
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_time64)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
.section .text.x86.asm32_syscall_int80.set_exception_handler
	/* errno_t set_exception_handler(syscall_ulong_t mode,
	 *                               except_handler_t handler,
	 *                               void *handler_sp) */
	.weak __asm32_int80_set_exception_handler
INTERN_FUNCTION(__asm32_int80_set_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_set_exception_handler
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
.section .text.x86.asm32_syscall_int80.get_exception_handler
	/* errno_t get_exception_handler(syscall_ulong_t *pmode,
	 *                               except_handler_t *phandler,
	 *                               void **phandler_sp) */
	.weak __asm32_int80_get_exception_handler
INTERN_FUNCTION(__asm32_int80_get_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000000f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_get_exception_handler
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_get_exception_handler)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
.section .text.x86.asm32_syscall_int80.set_library_listdef
	/* errno_t set_library_listdef(struct library_listdef const *listdef) */
	.weak __asm32_int80_set_library_listdef
INTERN_FUNCTION(__asm32_int80_set_library_listdef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000010
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_set_library_listdef
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_set_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
.section .text.x86.asm32_syscall_int80.debugtrap
	/* errno_t debugtrap(struct ucpustate const *state,
	 *                   struct debugtrap_reason const *reason) */
	.weak __asm32_int80_debugtrap
INTERN_FUNCTION(__asm32_int80_debugtrap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000011
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_debugtrap
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_debugtrap)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
.section .text.x86.asm32_syscall_int80.lfutex
	/* syscall_slong_t lfutex(uintptr_t *uaddr,
	 *                        syscall_ulong_t futex_op,
	 *                        uintptr_t val,
	 *                        struct __timespec64 const *timeout,
	 *                        uintptr_t val2) */
	.weak __asm32_int80_lfutex
INTERN_FUNCTION(__asm32_int80_lfutex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000012
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lfutex
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lfutex)

.section .text.x86.asm32_syscall_int80.lseek64
	/* int64_t lseek64(fd_t fd,
	 *                 int64_t offset,
	 *                 syscall_ulong_t whence) */
	.weak __asm32_int80_lseek64
INTERN_FUNCTION(__asm32_int80_lseek64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000013
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lseek64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi %rcx /* addq $8, %rsp */
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lseek64)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.x86.asm32_syscall_int80.lfutexexpr
	/* errno_t lfutexexpr(void *base,
	 *                    size_t exprc,
	 *                    struct lfutexexpr const *exprv,
	 *                    struct __timespec64 const *timeout,
	 *                    syscall_ulong_t timeout_flags) */
	.weak __asm32_int80_lfutexexpr
INTERN_FUNCTION(__asm32_int80_lfutexexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000014
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lfutexexpr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.x86.asm32_syscall_int80.lfutexlockexpr
	/* errno_t lfutexlockexpr(uintptr_t *ulockaddr,
	 *                        void *base,
	 *                        size_t exprc,
	 *                        struct lfutexexpr const *exprv,
	 *                        struct __timespec64 const *timeout,
	 *                        syscall_ulong_t timeout_flags) */
	.weak __asm32_int80_lfutexlockexpr
INTERN_FUNCTION(__asm32_int80_lfutexlockexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000015
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_lfutexlockexpr
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_lfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
.section .text.x86.asm32_syscall_int80.mktty
	/* fd_t mktty(fd_t keyboard,
	 *            fd_t display,
	 *            char const *name,
	 *            syscall_ulong_t rsvd) */
	.weak __asm32_int80_mktty
INTERN_FUNCTION(__asm32_int80_mktty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000016
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_mktty
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_mktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
.section .text.x86.asm32_syscall_int80.raiseat
	/* errno_t raiseat(struct ucpustate const *state,
	 *                 struct __siginfo_struct const *si) */
	.weak __asm32_int80_raiseat
INTERN_FUNCTION(__asm32_int80_raiseat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000017
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_raiseat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_raiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
.section .text.x86.asm32_syscall_int80.coredump
	/* errno_t coredump(struct ucpustate const *curr_state,
	 *                  struct ucpustate const *orig_state,
	 *                  void const *const *traceback_vector,
	 *                  size_t traceback_length,
	 *                  struct exception_data const *exception,
	 *                  syscall_ulong_t unwind_error) */
	.weak __asm32_int80_coredump
INTERN_FUNCTION(__asm32_int80_coredump)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000018
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_coredump
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_coredump)

.section .text.x86.asm32_syscall_int80.stime64
	/* errno_t stime64(time64_t const *t) */
	.weak __asm32_int80_stime64
INTERN_FUNCTION(__asm32_int80_stime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000019
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebx, %edi
	call   sys32_stime64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_stime64)

.section .text.x86.asm32_syscall_int80.utime64
	/* errno_t utime64(char const *filename,
	 *                 struct utimbuf64 const *times) */
	.weak __asm32_int80_utime64
INTERN_FUNCTION(__asm32_int80_utime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000001e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_utime64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_utime64)

.section .text.x86.asm32_syscall_int80.ioctlf
	/* syscall_slong_t ioctlf(fd_t fd,
	 *                        syscall_ulong_t command,
	 *                        iomode_t mode,
	 *                        void *arg) */
	.weak __asm32_int80_ioctlf
INTERN_FUNCTION(__asm32_int80_ioctlf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000036
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ioctlf
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ioctlf)

.section .text.x86.asm32_syscall_int80.fsmode
	/* uint64_t fsmode(uint64_t mode) */
	.weak __asm32_int80_fsmode
INTERN_FUNCTION(__asm32_int80_fsmode)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000003c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fsmode
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi %rcx /* addq $8, %rsp */
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fsmode)

.section .text.x86.asm32_syscall_int80.gettimeofday64
	/* errno_t gettimeofday64(struct __timeval64 *tv,
	 *                        struct timezone *tz) */
	.weak __asm32_int80_gettimeofday64
INTERN_FUNCTION(__asm32_int80_gettimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000004e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_gettimeofday64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_gettimeofday64)

.section .text.x86.asm32_syscall_int80.settimeofday64
	/* errno_t settimeofday64(struct __timeval64 const *tv,
	 *                        struct timezone const *tz) */
	.weak __asm32_int80_settimeofday64
INTERN_FUNCTION(__asm32_int80_settimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000004f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_settimeofday64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_settimeofday64)

.section .text.x86.asm32_syscall_int80.select64
	/* ssize_t select64(size_t nfds,
	 *                  struct __fd_set_struct *readfds,
	 *                  struct __fd_set_struct *writefds,
	 *                  struct __fd_set_struct *exceptfds,
	 *                  struct __timeval64 *timeout) */
	.weak __asm32_int80_select64
INTERN_FUNCTION(__asm32_int80_select64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000052
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_select64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_select64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
.section .text.x86.asm32_syscall_int80.maplibrary
	/* void *maplibrary(void *addr,
	 *                  syscall_ulong_t flags,
	 *                  fd_t fd,
	 *                  void *hdrv,
	 *                  size_t hdrc) */
	.weak __asm32_int80_maplibrary
INTERN_FUNCTION(__asm32_int80_maplibrary)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000056
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_maplibrary
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_maplibrary)

.section .text.x86.asm32_syscall_int80.setitimer64
	/* errno_t setitimer64(syscall_ulong_t which,
	 *                     struct __itimerval64 const *newval,
	 *                     struct __itimerval64 *oldval) */
	.weak __asm32_int80_setitimer64
INTERN_FUNCTION(__asm32_int80_setitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000068
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_setitimer64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_setitimer64)

.section .text.x86.asm32_syscall_int80.getitimer64
	/* errno_t getitimer64(syscall_ulong_t which,
	 *                     struct __itimerval64 *curr_value) */
	.weak __asm32_int80_getitimer64
INTERN_FUNCTION(__asm32_int80_getitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000069
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_getitimer64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_getitimer64)

.section .text.x86.asm32_syscall_int80.kreaddir
	/* ssize_t kreaddir(fd_t fd,
	 *                  struct dirent *buf,
	 *                  size_t bufsize,
	 *                  syscall_ulong_t mode) */
	.weak __asm32_int80_kreaddir
INTERN_FUNCTION(__asm32_int80_kreaddir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000008d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_kreaddir
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_kreaddir)

.section .text.x86.asm32_syscall_int80.readvf
	/* ssize_t readvf(fd_t fd,
	 *                struct iovec const *iovec,
	 *                size_t count,
	 *                iomode_t mode) */
	.weak __asm32_int80_readvf
INTERN_FUNCTION(__asm32_int80_readvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000091
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_readvf
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_readvf)

.section .text.x86.asm32_syscall_int80.writevf
	/* ssize_t writevf(fd_t fd,
	 *                 struct iovec const *iovec,
	 *                 size_t count,
	 *                 iomode_t mode) */
	.weak __asm32_int80_writevf
INTERN_FUNCTION(__asm32_int80_writevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000092
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_writevf
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_writevf)

.section .text.x86.asm32_syscall_int80.rpc_service
	/* syscall_slong_t rpc_service(void); */
	.weak __asm32_int80_rpc_service
INTERN_FUNCTION(__asm32_int80_rpc_service)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000009e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	call   sys32_rpc_service
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rpc_service)

.section .text.x86.asm32_syscall_int80.sched_rr_get_interval64
	/* errno_t sched_rr_get_interval64(pid_t pid,
	 *                                 struct __timespec64 *tms) */
	.weak __asm32_int80_sched_rr_get_interval64
INTERN_FUNCTION(__asm32_int80_sched_rr_get_interval64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000a1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_sched_rr_get_interval64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_sched_rr_get_interval64)

.section .text.x86.asm32_syscall_int80.nanosleep64
	/* errno_t nanosleep64(struct __timespec64 const *req,
	 *                     struct __timespec64 *rem) */
	.weak __asm32_int80_nanosleep64
INTERN_FUNCTION(__asm32_int80_nanosleep64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000a2
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_nanosleep64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_nanosleep64)

.section .text.x86.asm32_syscall_int80.rt_sigtimedwait64
	/* syscall_slong_t rt_sigtimedwait64(struct __sigset_struct const *set,
	 *                                   struct __siginfo_struct *info,
	 *                                   struct __timespec64 const *timeout,
	 *                                   size_t sigsetsize) */
	.weak __asm32_int80_rt_sigtimedwait64
INTERN_FUNCTION(__asm32_int80_rt_sigtimedwait64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000b1
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_rt_sigtimedwait64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_rt_sigtimedwait64)

.section .text.x86.asm32_syscall_int80.pread64f
	/* ssize_t pread64f(fd_t fd,
	 *                  void *buf,
	 *                  size_t bufsize,
	 *                  uint64_t offset,
	 *                  iomode_t mode) */
	.weak __asm32_int80_pread64f
INTERN_FUNCTION(__asm32_int80_pread64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000b4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_pread64f
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pread64f)

.section .text.x86.asm32_syscall_int80.pwrite64f
	/* ssize_t pwrite64f(fd_t fd,
	 *                   void const *buf,
	 *                   size_t bufsize,
	 *                   uint64_t offset,
	 *                   iomode_t mode) */
	.weak __asm32_int80_pwrite64f
INTERN_FUNCTION(__asm32_int80_pwrite64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000b5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_pwrite64f
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pwrite64f)

.section .text.x86.asm32_syscall_int80.kstat
	/* errno_t kstat(char const *filename,
	 *               struct stat *statbuf) */
	.weak __asm32_int80_kstat
INTERN_FUNCTION(__asm32_int80_kstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000c3
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_kstat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_kstat)

.section .text.x86.asm32_syscall_int80.klstat
	/* errno_t klstat(char const *filename,
	 *                struct stat *statbuf) */
	.weak __asm32_int80_klstat
INTERN_FUNCTION(__asm32_int80_klstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000c4
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_klstat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_klstat)

.section .text.x86.asm32_syscall_int80.kfstat
	/* errno_t kfstat(fd_t fd,
	 *                struct stat *statbuf) */
	.weak __asm32_int80_kfstat
INTERN_FUNCTION(__asm32_int80_kfstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000c5
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_kfstat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_kfstat)

.section .text.x86.asm32_syscall_int80.kreaddirf
	/* ssize_t kreaddirf(fd_t fd,
	 *                   struct dirent *buf,
	 *                   size_t bufsize,
	 *                   syscall_ulong_t mode,
	 *                   iomode_t iomode) */
	.weak __asm32_int80_kreaddirf
INTERN_FUNCTION(__asm32_int80_kreaddirf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x800000dc
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_kreaddirf
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_kreaddirf)

.section .text.x86.asm32_syscall_int80.timer_settime64
	/* errno_t timer_settime64(timer_t timerid,
	 *                         syscall_ulong_t flags,
	 *                         struct __itimerspec64 const *value,
	 *                         struct __itimerspec64 *ovalue) */
	.weak __asm32_int80_timer_settime64
INTERN_FUNCTION(__asm32_int80_timer_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000104
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timer_settime64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timer_settime64)

.section .text.x86.asm32_syscall_int80.timer_gettime64
	/* errno_t timer_gettime64(timer_t timerid,
	 *                         struct __itimerspec64 *value) */
	.weak __asm32_int80_timer_gettime64
INTERN_FUNCTION(__asm32_int80_timer_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000105
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timer_gettime64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timer_gettime64)

.section .text.x86.asm32_syscall_int80.clock_settime64
	/* errno_t clock_settime64(clockid_t clock_id,
	 *                         struct __timespec64 const *tp) */
	.weak __asm32_int80_clock_settime64
INTERN_FUNCTION(__asm32_int80_clock_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000108
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_clock_settime64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_clock_settime64)

.section .text.x86.asm32_syscall_int80.clock_gettime64
	/* errno_t clock_gettime64(clockid_t clock_id,
	 *                         struct __timespec64 *tp) */
	.weak __asm32_int80_clock_gettime64
INTERN_FUNCTION(__asm32_int80_clock_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000109
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_clock_gettime64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_clock_gettime64)

.section .text.x86.asm32_syscall_int80.clock_getres64
	/* errno_t clock_getres64(clockid_t clock_id,
	 *                        struct __timespec64 *res) */
	.weak __asm32_int80_clock_getres64
INTERN_FUNCTION(__asm32_int80_clock_getres64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000010a
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_clock_getres64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_clock_getres64)

.section .text.x86.asm32_syscall_int80.clock_nanosleep64
	/* errno_t clock_nanosleep64(clockid_t clock_id,
	 *                           syscall_ulong_t flags,
	 *                           struct __timespec64 const *requested_time,
	 *                           struct __timespec64 *remaining) */
	.weak __asm32_int80_clock_nanosleep64
INTERN_FUNCTION(__asm32_int80_clock_nanosleep64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000010b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_clock_nanosleep64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_clock_nanosleep64)

.section .text.x86.asm32_syscall_int80.utimes64
	/* errno_t utimes64(char const *filename,
	 *                  [2] struct __timeval64 const *times) */
	.weak __asm32_int80_utimes64
INTERN_FUNCTION(__asm32_int80_utimes64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000010f
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_utimes64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_utimes64)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.fmkdirat
	/* errno_t fmkdirat(fd_t dirfd,
	 *                  char const *pathname,
	 *                  mode_t mode,
	 *                  atflag_t flags) */
	.weak __asm32_int80_fmkdirat
INTERN_FUNCTION(__asm32_int80_fmkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000128
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fmkdirat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fmkdirat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.fmknodat
	/* errno_t fmknodat(fd_t dirfd,
	 *                  char const *nodename,
	 *                  mode_t mode,
	 *                  dev_t dev,
	 *                  atflag_t flags) */
	.weak __asm32_int80_fmknodat
INTERN_FUNCTION(__asm32_int80_fmknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000129
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fmknodat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fmknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.futimesat64
	/* errno_t futimesat64(fd_t dirfd,
	 *                     const char *filename,
	 *                     [2-3] struct __timeval64 const *times) */
	.weak __asm32_int80_futimesat64
INTERN_FUNCTION(__asm32_int80_futimesat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000012b
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_futimesat64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_futimesat64)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.kfstatat
	/* errno_t kfstatat(fd_t dirfd,
	 *                  char const *filename,
	 *                  struct stat *statbuf,
	 *                  atflag_t flags) */
	.weak __asm32_int80_kfstatat
INTERN_FUNCTION(__asm32_int80_kfstatat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000012c
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_kfstatat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_kfstatat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.frenameat
	/* errno_t frenameat(fd_t oldfd,
	 *                   char const *oldname,
	 *                   fd_t newfd,
	 *                   char const *newname_or_path,
	 *                   atflag_t flags) */
	.weak __asm32_int80_frenameat
INTERN_FUNCTION(__asm32_int80_frenameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000012e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_frenameat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_frenameat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.fsymlinkat
	/* errno_t fsymlinkat(char const *link_text,
	 *                    fd_t tofd,
	 *                    char const *target_path,
	 *                    atflag_t flags) */
	.weak __asm32_int80_fsymlinkat
INTERN_FUNCTION(__asm32_int80_fsymlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000130
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fsymlinkat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fsymlinkat)

/* @param: flags: Set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.freadlinkat
	/* ssize_t freadlinkat(fd_t dirfd,
	 *                     char const *path,
	 *                     char *buf,
	 *                     size_t buflen,
	 *                     atflag_t flags) */
	.weak __asm32_int80_freadlinkat
INTERN_FUNCTION(__asm32_int80_freadlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000131
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_freadlinkat
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_freadlinkat)

.section .text.x86.asm32_syscall_int80.pselect6_64
	/* ssize_t pselect6_64(size_t nfds,
	 *                     struct __fd_set_struct *readfds,
	 *                     struct __fd_set_struct *writefds,
	 *                     struct __fd_set_struct *exceptfds,
	 *                     struct __timespec64 const *timeout,
	 *                     void const *sigmask_sigset_and_len) */
	.weak __asm32_int80_pselect6_64
INTERN_FUNCTION(__asm32_int80_pselect6_64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000134
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_pselect6_64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pselect6_64)

.section .text.x86.asm32_syscall_int80.ppoll64
	/* ssize_t ppoll64(struct pollfd *fds,
	 *                 size_t nfds,
	 *                 struct __timespec64 const *timeout_ts,
	 *                 struct __sigset_struct const *sigmask,
	 *                 size_t sigsetsize) */
	.weak __asm32_int80_ppoll64
INTERN_FUNCTION(__asm32_int80_ppoll64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000135
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_ppoll64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_ppoll64)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.x86.asm32_syscall_int80.utimensat64
	/* errno_t utimensat64(fd_t dirfd,
	 *                     char const *filename,
	 *                     [2-3] struct __timespec64 const *times,
	 *                     atflag_t flags) */
	.weak __asm32_int80_utimensat64
INTERN_FUNCTION(__asm32_int80_utimensat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000140
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_utimensat64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_utimensat64)

.section .text.x86.asm32_syscall_int80.fallocate64
	/* errno_t fallocate64(fd_t fd,
	 *                     syscall_ulong_t mode,
	 *                     uint64_t offset,
	 *                     uint64_t length) */
	.weak __asm32_int80_fallocate64
INTERN_FUNCTION(__asm32_int80_fallocate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000144
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_fallocate64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_fallocate64)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
.section .text.x86.asm32_syscall_int80.timerfd_settime64
	/* errno_t timerfd_settime64(fd_t ufd,
	 *                           syscall_ulong_t flags,
	 *                           struct __itimerspec64 const *utmr,
	 *                           struct __itimerspec64 *otmr) */
	.weak __asm32_int80_timerfd_settime64
INTERN_FUNCTION(__asm32_int80_timerfd_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000145
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timerfd_settime64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timerfd_settime64)

/* Return the next expiration time of UFD */
.section .text.x86.asm32_syscall_int80.timerfd_gettime64
	/* errno_t timerfd_gettime64(fd_t ufd,
	 *                           struct __itimerspec64 *otmr) */
	.weak __asm32_int80_timerfd_gettime64
INTERN_FUNCTION(__asm32_int80_timerfd_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000146
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_timerfd_gettime64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_timerfd_gettime64)

.section .text.x86.asm32_syscall_int80.preadvf
	/* ssize_t preadvf(fd_t fd,
	 *                 struct iovec const *iovec,
	 *                 size_t count,
	 *                 uint64_t offset,
	 *                 iomode_t mode) */
	.weak __asm32_int80_preadvf
INTERN_FUNCTION(__asm32_int80_preadvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000014d
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_preadvf
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_preadvf)

.section .text.x86.asm32_syscall_int80.pwritevf
	/* ssize_t pwritevf(fd_t fd,
	 *                  struct iovec const *iovec,
	 *                  size_t count,
	 *                  uint64_t offset,
	 *                  iomode_t mode) */
	.weak __asm32_int80_pwritevf
INTERN_FUNCTION(__asm32_int80_pwritevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x8000014e
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %ebp, %r9d
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_pwritevf
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_pwritevf)

.section .text.x86.asm32_syscall_int80.recvmmsg64
	/* ssize_t recvmmsg64(fd_t sockfd,
	 *                    struct mmsghdr *vmessages,
	 *                    size_t vlen,
	 *                    syscall_ulong_t flags,
	 *                    struct __timespec64 *tmo) */
	.weak __asm32_int80_recvmmsg64
INTERN_FUNCTION(__asm32_int80_recvmmsg64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x80000151
	.cfi_iret_signal_frame
	pushq_cfi_r %rcx
	pushq_cfi_r %rdx
	pushq_cfi_r %rsi
	pushq_cfi_r %rdi
	movl   %edi, %r8d
	movl   %esi, %r10d
	movl   %ecx, %esi
	movl   %ebx, %edi
	call   sys32_recvmmsg64
	popq_cfi_r %rdi
	popq_cfi_r %rsi
	popq_cfi_r %rdx
	popq_cfi_r %rcx
	intr_exit_sysret
	.cfi_endproc
END(__asm32_int80_recvmmsg64)

.section .text.x86.asm32_syscall_sysenter.exit
	/* void exit(syscall_ulong_t status) */
	.weak __asm32_sysenter_exit
INTERN_FUNCTION(__asm32_sysenter_exit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000001
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_exit)

.section .text.x86.asm32_syscall_sysenter.fork
	/* pid_t fork(void); */
	.weak __asm32_sysenter_fork
INTERN_FUNCTION(__asm32_sysenter_fork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000002
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fork)

.section .text.x86.asm32_syscall_sysenter.read
	/* ssize_t read(fd_t fd,
	 *              void *buf,
	 *              size_t bufsize) */
	.weak __asm32_sysenter_read
INTERN_FUNCTION(__asm32_sysenter_read)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000003
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_read)

.section .text.x86.asm32_syscall_sysenter.write
	/* ssize_t write(fd_t fd,
	 *               void const *buf,
	 *               size_t bufsize) */
	.weak __asm32_sysenter_write
INTERN_FUNCTION(__asm32_sysenter_write)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000004
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_write)

.section .text.x86.asm32_syscall_sysenter.open
	/* fd_t open(char const *filename,
	 *           oflag_t oflags,
	 *           mode_t mode) */
	.weak __asm32_sysenter_open
INTERN_FUNCTION(__asm32_sysenter_open)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000005
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_open)

/* Close a given file descriptor/handle `FD' */
.section .text.x86.asm32_syscall_sysenter.close
	/* errno_t close(fd_t fd) */
	.weak __asm32_sysenter_close
INTERN_FUNCTION(__asm32_sysenter_close)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000006
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_close)

/* Wait for a child process:
 *  - `pid < -1':  Wait for any child process whose process group ID is `-PID'
 *  - `pid == -1': Wait for any child process
 *  - `pid == 0':  Wait for any child process whose process group ID is that of the caller
 *  - `pid > 0':   Wait for the child whose process ID is equal to `PID'
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
.section .text.x86.asm32_syscall_sysenter.waitpid
	/* pid_t waitpid(pid_t pid,
	 *               int32_t *stat_loc,
	 *               syscall_ulong_t options) */
	.weak __asm32_sysenter_waitpid
INTERN_FUNCTION(__asm32_sysenter_waitpid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000007
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_waitpid)

.section .text.x86.asm32_syscall_sysenter.creat
	/* fd_t creat(char const *filename,
	 *            mode_t mode) */
	.weak __asm32_sysenter_creat
INTERN_FUNCTION(__asm32_sysenter_creat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000008
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_creat)

.section .text.x86.asm32_syscall_sysenter.link
	/* errno_t link(char const *existing_file,
	 *              char const *link_file) */
	.weak __asm32_sysenter_link
INTERN_FUNCTION(__asm32_sysenter_link)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000009
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_link)

.section .text.x86.asm32_syscall_sysenter.unlink
	/* errno_t unlink(char const *filename) */
	.weak __asm32_sysenter_unlink
INTERN_FUNCTION(__asm32_sysenter_unlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000000a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_unlink)

.section .text.x86.asm32_syscall_sysenter.execve
	/* errno_t execve(char const *path,
	 *                char const *const *argv,
	 *                char const *const *envp) */
	.weak __asm32_sysenter_execve
INTERN_FUNCTION(__asm32_sysenter_execve)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000000b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_execve)

.section .text.x86.asm32_syscall_sysenter.chdir
	/* errno_t chdir(char const *path) */
	.weak __asm32_sysenter_chdir
INTERN_FUNCTION(__asm32_sysenter_chdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000000c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_chdir)

.section .text.x86.asm32_syscall_sysenter.time
	/* time32_t time(time32_t *timer) */
	.weak __asm32_sysenter_time
INTERN_FUNCTION(__asm32_sysenter_time)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000000d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_time)

.section .text.x86.asm32_syscall_sysenter.mknod
	/* errno_t mknod(char const *nodename,
	 *               mode_t mode,
	 *               dev_t dev) */
	.weak __asm32_sysenter_mknod
INTERN_FUNCTION(__asm32_sysenter_mknod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000000e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mknod)

.section .text.x86.asm32_syscall_sysenter.chmod
	/* errno_t chmod(char const *filename,
	 *               mode_t mode) */
	.weak __asm32_sysenter_chmod
INTERN_FUNCTION(__asm32_sysenter_chmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000000f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_chmod)

.section .text.x86.asm32_syscall_sysenter.lchown
	/* errno_t lchown(char const *filename,
	 *                uint16_t owner,
	 *                uint16_t group) */
	.weak __asm32_sysenter_lchown
INTERN_FUNCTION(__asm32_sysenter_lchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000010
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lchown)

.section .text.x86.asm32_syscall_sysenter.linux_oldstat
	/* errno_t linux_oldstat(char const *filename,
	 *                       struct linux_oldstat *statbuf) */
	.weak __asm32_sysenter_linux_oldstat
INTERN_FUNCTION(__asm32_sysenter_linux_oldstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000012
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_oldstat)

.section .text.x86.asm32_syscall_sysenter.lseek
	/* int32_t lseek(fd_t fd,
	 *               int32_t offset,
	 *               syscall_ulong_t whence) */
	.weak __asm32_sysenter_lseek
INTERN_FUNCTION(__asm32_sysenter_lseek)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000013
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lseek)

.section .text.x86.asm32_syscall_sysenter.getpid
	/* pid_t getpid(void); */
	.weak __asm32_sysenter_getpid
INTERN_FUNCTION(__asm32_sysenter_getpid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000014
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getpid)

.section .text.x86.asm32_syscall_sysenter.mount
	/* errno_t mount(char const *special_file,
	 *               char const *dir,
	 *               char const *fstype,
	 *               syscall_ulong_t rwflag,
	 *               void const *data) */
	.weak __asm32_sysenter_mount
INTERN_FUNCTION(__asm32_sysenter_mount)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000015
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mount)

.section .text.x86.asm32_syscall_sysenter.umount
	/* errno_t umount(char const *special_file) */
	.weak __asm32_sysenter_umount
INTERN_FUNCTION(__asm32_sysenter_umount)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000016
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_umount)

.section .text.x86.asm32_syscall_sysenter.setuid
	/* errno_t setuid(uint16_t uid) */
	.weak __asm32_sysenter_setuid
INTERN_FUNCTION(__asm32_sysenter_setuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000017
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setuid)

.section .text.x86.asm32_syscall_sysenter.getuid
	/* uint16_t getuid(void); */
	.weak __asm32_sysenter_getuid
INTERN_FUNCTION(__asm32_sysenter_getuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000018
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getuid)

.section .text.x86.asm32_syscall_sysenter.stime
	/* errno_t stime(time32_t const *t) */
	.weak __asm32_sysenter_stime
INTERN_FUNCTION(__asm32_sysenter_stime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000019
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_stime)

.section .text.x86.asm32_syscall_sysenter.ptrace
	/* syscall_slong_t ptrace(syscall_ulong_t request,
	 *                        pid_t pid,
	 *                        void *addr,
	 *                        void *data) */
	.weak __asm32_sysenter_ptrace
INTERN_FUNCTION(__asm32_sysenter_ptrace)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000001a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ptrace)

.section .text.x86.asm32_syscall_sysenter.alarm
	/* syscall_ulong_t alarm(syscall_ulong_t seconds) */
	.weak __asm32_sysenter_alarm
INTERN_FUNCTION(__asm32_sysenter_alarm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000001b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_alarm)

.section .text.x86.asm32_syscall_sysenter.linux_oldfstat
	/* errno_t linux_oldfstat(fd_t fd,
	 *                        struct linux_oldstat *statbuf) */
	.weak __asm32_sysenter_linux_oldfstat
INTERN_FUNCTION(__asm32_sysenter_linux_oldfstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000001c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_oldfstat)

.section .text.x86.asm32_syscall_sysenter.pause
	/* errno_t pause(void); */
	.weak __asm32_sysenter_pause
INTERN_FUNCTION(__asm32_sysenter_pause)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000001d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pause)

.section .text.x86.asm32_syscall_sysenter.utime
	/* errno_t utime(char const *filename,
	 *               struct __utimbuf32 const *times) */
	.weak __asm32_sysenter_utime
INTERN_FUNCTION(__asm32_sysenter_utime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000001e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_utime)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK' */
.section .text.x86.asm32_syscall_sysenter.access
	/* errno_t access(char const *filename,
	 *                syscall_ulong_t type) */
	.weak __asm32_sysenter_access
INTERN_FUNCTION(__asm32_sysenter_access)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000021
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_access)

.section .text.x86.asm32_syscall_sysenter.nice
	/* errno_t nice(syscall_slong_t inc) */
	.weak __asm32_sysenter_nice
INTERN_FUNCTION(__asm32_sysenter_nice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000022
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_nice)

.section .text.x86.asm32_syscall_sysenter.ftime
	/* errno_t ftime(struct timeb *tp) */
	.weak __asm32_sysenter_ftime
INTERN_FUNCTION(__asm32_sysenter_ftime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000023
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ftime)

.section .text.x86.asm32_syscall_sysenter.sync
	/* errno_t sync(void); */
	.weak __asm32_sysenter_sync
INTERN_FUNCTION(__asm32_sysenter_sync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000024
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sync)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_sysenter.kill
	/* errno_t kill(pid_t pid,
	 *              syscall_ulong_t signo) */
	.weak __asm32_sysenter_kill
INTERN_FUNCTION(__asm32_sysenter_kill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000025
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_kill)

.section .text.x86.asm32_syscall_sysenter.rename
	/* errno_t rename(char const *oldname,
	 *                char const *newname_or_path) */
	.weak __asm32_sysenter_rename
INTERN_FUNCTION(__asm32_sysenter_rename)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000026
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rename)

.section .text.x86.asm32_syscall_sysenter.mkdir
	/* errno_t mkdir(char const *pathname,
	 *               mode_t mode) */
	.weak __asm32_sysenter_mkdir
INTERN_FUNCTION(__asm32_sysenter_mkdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000027
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mkdir)

.section .text.x86.asm32_syscall_sysenter.rmdir
	/* errno_t rmdir(char const *path) */
	.weak __asm32_sysenter_rmdir
INTERN_FUNCTION(__asm32_sysenter_rmdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000028
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rmdir)

.section .text.x86.asm32_syscall_sysenter.dup
	/* fd_t dup(fd_t fd) */
	.weak __asm32_sysenter_dup
INTERN_FUNCTION(__asm32_sysenter_dup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000029
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_dup)

.section .text.x86.asm32_syscall_sysenter.pipe
	/* errno_t pipe([2] fd_t *pipedes) */
	.weak __asm32_sysenter_pipe
INTERN_FUNCTION(__asm32_sysenter_pipe)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000002a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pipe)

.section .text.x86.asm32_syscall_sysenter.times
	/* clock_t times(struct tms *buf) */
	.weak __asm32_sysenter_times
INTERN_FUNCTION(__asm32_sysenter_times)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000002b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_times)

.section .text.x86.asm32_syscall_sysenter.brk
	/* errno_t brk(void *addr) */
	.weak __asm32_sysenter_brk
INTERN_FUNCTION(__asm32_sysenter_brk)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000002d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_brk)

.section .text.x86.asm32_syscall_sysenter.setgid
	/* errno_t setgid(uint16_t gid) */
	.weak __asm32_sysenter_setgid
INTERN_FUNCTION(__asm32_sysenter_setgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000002e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setgid)

.section .text.x86.asm32_syscall_sysenter.getgid
	/* uint16_t getgid(void); */
	.weak __asm32_sysenter_getgid
INTERN_FUNCTION(__asm32_sysenter_getgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000002f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getgid)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_sysenter.signal
	/* sighandler_t signal(syscall_ulong_t signo,
	 *                     sighandler_t handler) */
	.weak __asm32_sysenter_signal
INTERN_FUNCTION(__asm32_sysenter_signal)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000030
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_signal)

.section .text.x86.asm32_syscall_sysenter.geteuid
	/* uint16_t geteuid(void); */
	.weak __asm32_sysenter_geteuid
INTERN_FUNCTION(__asm32_sysenter_geteuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000031
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_geteuid)

.section .text.x86.asm32_syscall_sysenter.getegid
	/* uint16_t getegid(void); */
	.weak __asm32_sysenter_getegid
INTERN_FUNCTION(__asm32_sysenter_getegid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000032
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getegid)

.section .text.x86.asm32_syscall_sysenter.acct
	/* errno_t acct(char const *filename) */
	.weak __asm32_sysenter_acct
INTERN_FUNCTION(__asm32_sysenter_acct)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000033
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_acct)

.section .text.x86.asm32_syscall_sysenter.umount2
	/* errno_t umount2(char const *special_file,
	 *                 syscall_ulong_t flags) */
	.weak __asm32_sysenter_umount2
INTERN_FUNCTION(__asm32_sysenter_umount2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000034
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_umount2)

.section .text.x86.asm32_syscall_sysenter.ioctl
	/* syscall_slong_t ioctl(fd_t fd,
	 *                       syscall_ulong_t request,
	 *                       void *arg) */
	.weak __asm32_sysenter_ioctl
INTERN_FUNCTION(__asm32_sysenter_ioctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000036
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ioctl)

.section .text.x86.asm32_syscall_sysenter.fcntl
	/* syscall_slong_t fcntl(fd_t fd,
	 *                       syscall_ulong_t cmd,
	 *                       void *arg) */
	.weak __asm32_sysenter_fcntl
INTERN_FUNCTION(__asm32_sysenter_fcntl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000037
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fcntl)

.section .text.x86.asm32_syscall_sysenter.setpgid
	/* errno_t setpgid(pid_t pid,
	 *                 pid_t pgid) */
	.weak __asm32_sysenter_setpgid
INTERN_FUNCTION(__asm32_sysenter_setpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000039
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setpgid)

.section .text.x86.asm32_syscall_sysenter.oldolduname
	/* errno_t oldolduname(struct linux_oldolduname *name) */
	.weak __asm32_sysenter_oldolduname
INTERN_FUNCTION(__asm32_sysenter_oldolduname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000003b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_oldolduname)

.section .text.x86.asm32_syscall_sysenter.umask
	/* mode_t umask(mode_t mode) */
	.weak __asm32_sysenter_umask
INTERN_FUNCTION(__asm32_sysenter_umask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000003c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_umask)

.section .text.x86.asm32_syscall_sysenter.chroot
	/* errno_t chroot(char const *path) */
	.weak __asm32_sysenter_chroot
INTERN_FUNCTION(__asm32_sysenter_chroot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000003d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_chroot)

.section .text.x86.asm32_syscall_sysenter.ustat
	/* errno_t ustat(dev_t dev,
	 *               struct ustat *ubuf) */
	.weak __asm32_sysenter_ustat
INTERN_FUNCTION(__asm32_sysenter_ustat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000003e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ustat)

.section .text.x86.asm32_syscall_sysenter.dup2
	/* fd_t dup2(fd_t oldfd,
	 *           fd_t newfd) */
	.weak __asm32_sysenter_dup2
INTERN_FUNCTION(__asm32_sysenter_dup2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000003f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_dup2)

.section .text.x86.asm32_syscall_sysenter.getppid
	/* pid_t getppid(void); */
	.weak __asm32_sysenter_getppid
INTERN_FUNCTION(__asm32_sysenter_getppid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000040
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getppid)

.section .text.x86.asm32_syscall_sysenter.getpgrp
	/* pid_t getpgrp(void); */
	.weak __asm32_sysenter_getpgrp
INTERN_FUNCTION(__asm32_sysenter_getpgrp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000041
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getpgrp)

.section .text.x86.asm32_syscall_sysenter.setsid
	/* pid_t setsid(void); */
	.weak __asm32_sysenter_setsid
INTERN_FUNCTION(__asm32_sysenter_setsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000042
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setsid)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_sysenter.sigaction
	/* errno_t sigaction(syscall_ulong_t signo,
	 *                   struct sigaction const *act,
	 *                   struct sigaction *oact) */
	.weak __asm32_sysenter_sigaction
INTERN_FUNCTION(__asm32_sysenter_sigaction)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000043
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sigaction)

.section .text.x86.asm32_syscall_sysenter.sgetmask
	/* syscall_ulong_t sgetmask(void); */
	.weak __asm32_sysenter_sgetmask
INTERN_FUNCTION(__asm32_sysenter_sgetmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000044
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sgetmask)

.section .text.x86.asm32_syscall_sysenter.ssetmask
	/* syscall_ulong_t ssetmask(syscall_ulong_t sigmask) */
	.weak __asm32_sysenter_ssetmask
INTERN_FUNCTION(__asm32_sysenter_ssetmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000045
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ssetmask)

.section .text.x86.asm32_syscall_sysenter.setreuid
	/* errno_t setreuid(uint16_t ruid,
	 *                  uint16_t euid) */
	.weak __asm32_sysenter_setreuid
INTERN_FUNCTION(__asm32_sysenter_setreuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000046
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setreuid)

.section .text.x86.asm32_syscall_sysenter.setregid
	/* errno_t setregid(uint16_t rgid,
	 *                  uint16_t egid) */
	.weak __asm32_sysenter_setregid
INTERN_FUNCTION(__asm32_sysenter_setregid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000047
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setregid)

.section .text.x86.asm32_syscall_sysenter.sigsuspend
	/* errno_t sigsuspend(struct __sigset_struct const *set) */
	.weak __asm32_sysenter_sigsuspend
INTERN_FUNCTION(__asm32_sysenter_sigsuspend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000048
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sigsuspend)

.section .text.x86.asm32_syscall_sysenter.sigpending
	/* errno_t sigpending(struct __sigset_struct *set) */
	.weak __asm32_sysenter_sigpending
INTERN_FUNCTION(__asm32_sysenter_sigpending)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000049
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sigpending)

.section .text.x86.asm32_syscall_sysenter.sethostname
	/* errno_t sethostname(char const *name,
	 *                     size_t len) */
	.weak __asm32_sysenter_sethostname
INTERN_FUNCTION(__asm32_sysenter_sethostname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000004a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sethostname)

.section .text.x86.asm32_syscall_sysenter.setrlimit
	/* errno_t setrlimit(syscall_ulong_t resource,
	 *                   struct rlimit const *rlimits) */
	.weak __asm32_sysenter_setrlimit
INTERN_FUNCTION(__asm32_sysenter_setrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000004b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setrlimit)

.section .text.x86.asm32_syscall_sysenter.getrlimit
	/* errno_t getrlimit(syscall_ulong_t resource,
	 *                   struct rlimit *rlimits) */
	.weak __asm32_sysenter_getrlimit
INTERN_FUNCTION(__asm32_sysenter_getrlimit)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000004c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getrlimit)

.section .text.x86.asm32_syscall_sysenter.getrusage
	/* errno_t getrusage(syscall_slong_t who,
	 *                   struct rusage *usage) */
	.weak __asm32_sysenter_getrusage
INTERN_FUNCTION(__asm32_sysenter_getrusage)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000004d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getrusage)

.section .text.x86.asm32_syscall_sysenter.gettimeofday
	/* errno_t gettimeofday(struct __timeval32 *tv,
	 *                      struct timezone *tz) */
	.weak __asm32_sysenter_gettimeofday
INTERN_FUNCTION(__asm32_sysenter_gettimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000004e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_gettimeofday)

.section .text.x86.asm32_syscall_sysenter.settimeofday
	/* errno_t settimeofday(struct __timeval32 const *tv,
	 *                      struct timezone const *tz) */
	.weak __asm32_sysenter_settimeofday
INTERN_FUNCTION(__asm32_sysenter_settimeofday)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000004f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_settimeofday)

.section .text.x86.asm32_syscall_sysenter.getgroups
	/* errno_t getgroups(size_t size,
	 *                   [] uint16_t *list) */
	.weak __asm32_sysenter_getgroups
INTERN_FUNCTION(__asm32_sysenter_getgroups)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000050
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getgroups)

.section .text.x86.asm32_syscall_sysenter.setgroups
	/* errno_t setgroups(size_t count,
	 *                   uint16_t const *groups) */
	.weak __asm32_sysenter_setgroups
INTERN_FUNCTION(__asm32_sysenter_setgroups)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000051
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setgroups)

.section .text.x86.asm32_syscall_sysenter.select
	/* ssize_t select(size_t nfds,
	 *                struct __fd_set_struct *readfds,
	 *                struct __fd_set_struct *writefds,
	 *                struct __fd_set_struct *exceptfds,
	 *                struct __timeval32 *timeout) */
	.weak __asm32_sysenter_select
INTERN_FUNCTION(__asm32_sysenter_select)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000052
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_select)

.section .text.x86.asm32_syscall_sysenter.symlink
	/* errno_t symlink(char const *link_text,
	 *                 char const *target_path) */
	.weak __asm32_sysenter_symlink
INTERN_FUNCTION(__asm32_sysenter_symlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000053
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_symlink)

.section .text.x86.asm32_syscall_sysenter.linux_oldlstat
	/* errno_t linux_oldlstat(char const *filename,
	 *                        struct linux_oldstat *statbuf) */
	.weak __asm32_sysenter_linux_oldlstat
INTERN_FUNCTION(__asm32_sysenter_linux_oldlstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000054
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_oldlstat)

.section .text.x86.asm32_syscall_sysenter.readlink
	/* ssize_t readlink(char const *path,
	 *                  char *buf,
	 *                  size_t buflen) */
	.weak __asm32_sysenter_readlink
INTERN_FUNCTION(__asm32_sysenter_readlink)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000055
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_readlink)

/* @param: swapflags: Set of `SWAP_FLAG_*' */
.section .text.x86.asm32_syscall_sysenter.swapon
	/* errno_t swapon(char const *pathname,
	 *                syscall_ulong_t swapflags) */
	.weak __asm32_sysenter_swapon
INTERN_FUNCTION(__asm32_sysenter_swapon)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000057
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_swapon)

/* @param: howto: One of the `RB_*' constants from <sys/reboot.h> */
.section .text.x86.asm32_syscall_sysenter.reboot
	/* errno_t reboot(syscall_ulong_t how) */
	.weak __asm32_sysenter_reboot
INTERN_FUNCTION(__asm32_sysenter_reboot)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000058
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_reboot)

/* Returns `0' to indicate end-of-directory; 1 to to indicate success */
.section .text.x86.asm32_syscall_sysenter.readdir
	/* errno_t readdir(fd_t fd,
	 *                 struct old_linux_dirent *dirp,
	 *                 size_t count) */
	.weak __asm32_sysenter_readdir
INTERN_FUNCTION(__asm32_sysenter_readdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000059
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_readdir)

/* @param: prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param: flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE|MAP_OFFSET64_POINTER' */
.section .text.x86.asm32_syscall_sysenter.mmap
	/* void *mmap(void *addr,
	 *            size_t len,
	 *            syscall_ulong_t prot,
	 *            syscall_ulong_t flags,
	 *            fd_t fd,
	 *            syscall_ulong_t offset) */
	.weak __asm32_sysenter_mmap
INTERN_FUNCTION(__asm32_sysenter_mmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000005a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mmap)

.section .text.x86.asm32_syscall_sysenter.munmap
	/* errno_t munmap(void *addr,
	 *                size_t len) */
	.weak __asm32_sysenter_munmap
INTERN_FUNCTION(__asm32_sysenter_munmap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000005b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_munmap)

.section .text.x86.asm32_syscall_sysenter.truncate
	/* errno_t truncate(char const *filename,
	 *                  syscall_ulong_t length) */
	.weak __asm32_sysenter_truncate
INTERN_FUNCTION(__asm32_sysenter_truncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000005c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_truncate)

.section .text.x86.asm32_syscall_sysenter.ftruncate
	/* errno_t ftruncate(fd_t fd,
	 *                   syscall_ulong_t length) */
	.weak __asm32_sysenter_ftruncate
INTERN_FUNCTION(__asm32_sysenter_ftruncate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000005d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ftruncate)

.section .text.x86.asm32_syscall_sysenter.fchmod
	/* errno_t fchmod(fd_t fd,
	 *                mode_t mode) */
	.weak __asm32_sysenter_fchmod
INTERN_FUNCTION(__asm32_sysenter_fchmod)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000005e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fchmod)

.section .text.x86.asm32_syscall_sysenter.fchown
	/* errno_t fchown(fd_t fd,
	 *                uint16_t owner,
	 *                uint16_t group) */
	.weak __asm32_sysenter_fchown
INTERN_FUNCTION(__asm32_sysenter_fchown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000005f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fchown)

.section .text.x86.asm32_syscall_sysenter.getpriority
	/* syscall_slong_t getpriority(syscall_ulong_t which,
	 *                             id_t who) */
	.weak __asm32_sysenter_getpriority
INTERN_FUNCTION(__asm32_sysenter_getpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000060
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getpriority)

.section .text.x86.asm32_syscall_sysenter.setpriority
	/* errno_t setpriority(syscall_ulong_t which,
	 *                     id_t who,
	 *                     syscall_ulong_t value) */
	.weak __asm32_sysenter_setpriority
INTERN_FUNCTION(__asm32_sysenter_setpriority)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000061
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setpriority)

.section .text.x86.asm32_syscall_sysenter.profil
	/* errno_t profil(uint16_t *sample_buffer,
	 *                size_t size,
	 *                size_t offset,
	 *                syscall_ulong_t scale) */
	.weak __asm32_sysenter_profil
INTERN_FUNCTION(__asm32_sysenter_profil)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000062
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_profil)

.section .text.x86.asm32_syscall_sysenter.statfs
	/* errno_t statfs(char const *file,
	 *                struct __statfs32 *buf) */
	.weak __asm32_sysenter_statfs
INTERN_FUNCTION(__asm32_sysenter_statfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000063
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_statfs)

.section .text.x86.asm32_syscall_sysenter.fstatfs
	/* errno_t fstatfs(fd_t file,
	 *                 struct __statfs32 *buf) */
	.weak __asm32_sysenter_fstatfs
INTERN_FUNCTION(__asm32_sysenter_fstatfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000064
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fstatfs)

.section .text.x86.asm32_syscall_sysenter.ioperm
	/* errno_t ioperm(syscall_ulong_t from,
	 *                syscall_ulong_t num,
	 *                syscall_ulong_t turn_on) */
	.weak __asm32_sysenter_ioperm
INTERN_FUNCTION(__asm32_sysenter_ioperm)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000065
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ioperm)

.section .text.x86.asm32_syscall_sysenter.socketcall
	/* errno_t socketcall(int call,
	 *                    unsigned long *args) */
	.weak __asm32_sysenter_socketcall
INTERN_FUNCTION(__asm32_sysenter_socketcall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000066
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_socketcall)

.section .text.x86.asm32_syscall_sysenter.syslog
	/* ssize_t syslog(syscall_ulong_t level,
	 *                char const *str,
	 *                size_t len) */
	.weak __asm32_sysenter_syslog
INTERN_FUNCTION(__asm32_sysenter_syslog)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000067
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_syslog)

.section .text.x86.asm32_syscall_sysenter.setitimer
	/* errno_t setitimer(syscall_ulong_t which,
	 *                   struct __itimerval32 const *newval,
	 *                   struct __itimerval32 *oldval) */
	.weak __asm32_sysenter_setitimer
INTERN_FUNCTION(__asm32_sysenter_setitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000068
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setitimer)

.section .text.x86.asm32_syscall_sysenter.getitimer
	/* errno_t getitimer(syscall_ulong_t which,
	 *                   struct __itimerval32 *curr_value) */
	.weak __asm32_sysenter_getitimer
INTERN_FUNCTION(__asm32_sysenter_getitimer)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000069
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getitimer)

.section .text.x86.asm32_syscall_sysenter.linux_stat32
	/* errno_t linux_stat32(char const *filename,
	 *                      struct linux_stat32 *statbuf) */
	.weak __asm32_sysenter_linux_stat32
INTERN_FUNCTION(__asm32_sysenter_linux_stat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000006a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_stat32)

.section .text.x86.asm32_syscall_sysenter.linux_lstat32
	/* errno_t linux_lstat32(char const *filename,
	 *                       struct linux_stat32 *statbuf) */
	.weak __asm32_sysenter_linux_lstat32
INTERN_FUNCTION(__asm32_sysenter_linux_lstat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000006b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_lstat32)

.section .text.x86.asm32_syscall_sysenter.linux_fstat32
	/* errno_t linux_fstat32(fd_t fd,
	 *                       struct linux_stat32 *statbuf) */
	.weak __asm32_sysenter_linux_fstat32
INTERN_FUNCTION(__asm32_sysenter_linux_fstat32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000006c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_fstat32)

.section .text.x86.asm32_syscall_sysenter.olduname
	/* errno_t olduname(struct linux_olduname *name) */
	.weak __asm32_sysenter_olduname
INTERN_FUNCTION(__asm32_sysenter_olduname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000006d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_olduname)

.section .text.x86.asm32_syscall_sysenter.iopl
	/* errno_t iopl(syscall_ulong_t level) */
	.weak __asm32_sysenter_iopl
INTERN_FUNCTION(__asm32_sysenter_iopl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000006e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_iopl)

.section .text.x86.asm32_syscall_sysenter.vhangup
	/* errno_t vhangup(void); */
	.weak __asm32_sysenter_vhangup
INTERN_FUNCTION(__asm32_sysenter_vhangup)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000006f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_vhangup)

/* Same as `waitpid(pid,STAT_LOC,OPTIONS)', though also fills in `USAGE' when non-NULL
 * @param: options: Set of `WNOHANG|WUNTRACED|WCONTINUED' (as a KOS extension, `WNOWAIT' is also accepted) */
.section .text.x86.asm32_syscall_sysenter.wait4
	/* pid_t wait4(pid_t pid,
	 *             int32_t *stat_loc,
	 *             syscall_ulong_t options,
	 *             struct rusage *usage) */
	.weak __asm32_sysenter_wait4
INTERN_FUNCTION(__asm32_sysenter_wait4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000072
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_wait4)

.section .text.x86.asm32_syscall_sysenter.swapoff
	/* errno_t swapoff(char const *pathname) */
	.weak __asm32_sysenter_swapoff
INTERN_FUNCTION(__asm32_sysenter_swapoff)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000073
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_swapoff)

.section .text.x86.asm32_syscall_sysenter.sysinfo
	/* errno_t sysinfo(struct sysinfo *info) */
	.weak __asm32_sysenter_sysinfo
INTERN_FUNCTION(__asm32_sysenter_sysinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000074
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sysinfo)

.section .text.x86.asm32_syscall_sysenter.fsync
	/* errno_t fsync(fd_t fd) */
	.weak __asm32_sysenter_fsync
INTERN_FUNCTION(__asm32_sysenter_fsync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000076
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fsync)

/* Restore the specified register state when returning from a signal handler
 * Note that the order and locations of arguments taken by this system call
 * are of great importance, as they must match what is encoded by the kernel
 * within `sighand_raise_signal()'
 * The order chosen is also important, as it is selected such that arguments
 * are only passed through registers that are preserved by CDECL */
.section .text.x86.asm32_syscall_sysenter.sigreturn
	/* void sigreturn(struct fpustate const *restore_fpu,
	 *                syscall_ulong_t unused1,
	 *                syscall_ulong_t unused2,
	 *                struct __sigset_struct const *restore_sigmask,
	 *                struct rpc_syscall_info *sc_info,
	 *                struct ucpustate const *restore_cpu) */
	.weak __asm32_sysenter_sigreturn
INTERN_FUNCTION(__asm32_sysenter_sigreturn)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000077
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sigreturn)

.section .text.x86.asm32_syscall_sysenter.clone
	/* pid_t clone(syscall_ulong_t flags,
	 *             void *child_stack,
	 *             pid_t *ptid,
	 *             uintptr_t newtls,
	 *             pid_t *ctid) */
	.weak __asm32_sysenter_clone
INTERN_FUNCTION(__asm32_sysenter_clone)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000078
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_clone)

.section .text.x86.asm32_syscall_sysenter.setdomainname
	/* errno_t setdomainname(char const *name,
	 *                       size_t len) */
	.weak __asm32_sysenter_setdomainname
INTERN_FUNCTION(__asm32_sysenter_setdomainname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000079
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setdomainname)

.section .text.x86.asm32_syscall_sysenter.uname
	/* errno_t uname(struct utsname *name) */
	.weak __asm32_sysenter_uname
INTERN_FUNCTION(__asm32_sysenter_uname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000007a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_uname)

.section .text.x86.asm32_syscall_sysenter.modify_ldt
	/* syscall_slong_t modify_ldt(syscall_ulong_t func,
	 *                            void *ptr,
	 *                            syscall_ulong_t bytecount) */
	.weak __asm32_sysenter_modify_ldt
INTERN_FUNCTION(__asm32_sysenter_modify_ldt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000007b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_modify_ldt)

/* @param: prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED' */
.section .text.x86.asm32_syscall_sysenter.mprotect
	/* errno_t mprotect(void *addr,
	 *                  size_t len,
	 *                  syscall_ulong_t prot) */
	.weak __asm32_sysenter_mprotect
INTERN_FUNCTION(__asm32_sysenter_mprotect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000007d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mprotect)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
.section .text.x86.asm32_syscall_sysenter.sigprocmask
	/* errno_t sigprocmask(syscall_ulong_t how,
	 *                     struct __sigset_struct const *set,
	 *                     struct __sigset_struct *oset) */
	.weak __asm32_sysenter_sigprocmask
INTERN_FUNCTION(__asm32_sysenter_sigprocmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000007e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sigprocmask)

.section .text.x86.asm32_syscall_sysenter.getpgid
	/* pid_t getpgid(pid_t pid) */
	.weak __asm32_sysenter_getpgid
INTERN_FUNCTION(__asm32_sysenter_getpgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000084
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getpgid)

.section .text.x86.asm32_syscall_sysenter.fchdir
	/* errno_t fchdir(fd_t fd) */
	.weak __asm32_sysenter_fchdir
INTERN_FUNCTION(__asm32_sysenter_fchdir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000085
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fchdir)

.section .text.x86.asm32_syscall_sysenter.setfsuid
	/* errno_t setfsuid(uint16_t uid) */
	.weak __asm32_sysenter_setfsuid
INTERN_FUNCTION(__asm32_sysenter_setfsuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000008a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setfsuid)

.section .text.x86.asm32_syscall_sysenter.setfsgid
	/* errno_t setfsgid(uint16_t gid) */
	.weak __asm32_sysenter_setfsgid
INTERN_FUNCTION(__asm32_sysenter_setfsgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000008b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setfsgid)

.section .text.x86.asm32_syscall_sysenter._llseek
	/* errno_t _llseek(fd_t fd,
	 *                 int64_t offset,
	 *                 uint64_t *result,
	 *                 syscall_ulong_t whence) */
	.weak __asm32_sysenter__llseek
INTERN_FUNCTION(__asm32_sysenter__llseek)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000008c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter__llseek)

.section .text.x86.asm32_syscall_sysenter.getdents
	/* ssize_t getdents(fd_t fd,
	 *                  struct linux_dirent *dirp,
	 *                  size_t count) */
	.weak __asm32_sysenter_getdents
INTERN_FUNCTION(__asm32_sysenter_getdents)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000008d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getdents)

.section .text.x86.asm32_syscall_sysenter.flock
	/* errno_t flock(fd_t fd,
	 *               syscall_ulong_t operation) */
	.weak __asm32_sysenter_flock
INTERN_FUNCTION(__asm32_sysenter_flock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000008f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_flock)

.section .text.x86.asm32_syscall_sysenter.msync
	/* errno_t msync(void *addr,
	 *               size_t len,
	 *               syscall_ulong_t flags) */
	.weak __asm32_sysenter_msync
INTERN_FUNCTION(__asm32_sysenter_msync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000090
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_msync)

.section .text.x86.asm32_syscall_sysenter.readv
	/* ssize_t readv(fd_t fd,
	 *               struct iovec const *iovec,
	 *               size_t count) */
	.weak __asm32_sysenter_readv
INTERN_FUNCTION(__asm32_sysenter_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000091
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_readv)

.section .text.x86.asm32_syscall_sysenter.writev
	/* ssize_t writev(fd_t fd,
	 *                struct iovec const *iovec,
	 *                size_t count) */
	.weak __asm32_sysenter_writev
INTERN_FUNCTION(__asm32_sysenter_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000092
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_writev)

.section .text.x86.asm32_syscall_sysenter.getsid
	/* pid_t getsid(pid_t pid) */
	.weak __asm32_sysenter_getsid
INTERN_FUNCTION(__asm32_sysenter_getsid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000093
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getsid)

.section .text.x86.asm32_syscall_sysenter.fdatasync
	/* errno_t fdatasync(fd_t fd) */
	.weak __asm32_sysenter_fdatasync
INTERN_FUNCTION(__asm32_sysenter_fdatasync)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000094
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fdatasync)

.section .text.x86.asm32_syscall_sysenter.mlock
	/* errno_t mlock(void const *addr,
	 *               size_t len) */
	.weak __asm32_sysenter_mlock
INTERN_FUNCTION(__asm32_sysenter_mlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000096
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mlock)

.section .text.x86.asm32_syscall_sysenter.munlock
	/* errno_t munlock(void const *addr,
	 *                 size_t len) */
	.weak __asm32_sysenter_munlock
INTERN_FUNCTION(__asm32_sysenter_munlock)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000097
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_munlock)

.section .text.x86.asm32_syscall_sysenter.mlockall
	/* errno_t mlockall(syscall_ulong_t flags) */
	.weak __asm32_sysenter_mlockall
INTERN_FUNCTION(__asm32_sysenter_mlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000098
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mlockall)

.section .text.x86.asm32_syscall_sysenter.munlockall
	/* errno_t munlockall(void); */
	.weak __asm32_sysenter_munlockall
INTERN_FUNCTION(__asm32_sysenter_munlockall)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000099
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_munlockall)

.section .text.x86.asm32_syscall_sysenter.sched_setparam
	/* errno_t sched_setparam(pid_t pid,
	 *                        struct sched_param const *param) */
	.weak __asm32_sysenter_sched_setparam
INTERN_FUNCTION(__asm32_sysenter_sched_setparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000009a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_setparam)

.section .text.x86.asm32_syscall_sysenter.sched_getparam
	/* errno_t sched_getparam(pid_t pid,
	 *                        struct sched_param *param) */
	.weak __asm32_sysenter_sched_getparam
INTERN_FUNCTION(__asm32_sysenter_sched_getparam)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000009b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_getparam)

.section .text.x86.asm32_syscall_sysenter.sched_setscheduler
	/* errno_t sched_setscheduler(pid_t pid,
	 *                            syscall_ulong_t policy,
	 *                            struct sched_param const *param) */
	.weak __asm32_sysenter_sched_setscheduler
INTERN_FUNCTION(__asm32_sysenter_sched_setscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000009c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_setscheduler)

.section .text.x86.asm32_syscall_sysenter.sched_getscheduler
	/* syscall_slong_t sched_getscheduler(pid_t pid) */
	.weak __asm32_sysenter_sched_getscheduler
INTERN_FUNCTION(__asm32_sysenter_sched_getscheduler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000009d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_getscheduler)

.section .text.x86.asm32_syscall_sysenter.sched_yield
	/* errno_t sched_yield(void); */
	.weak __asm32_sysenter_sched_yield
INTERN_FUNCTION(__asm32_sysenter_sched_yield)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000009e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_yield)

.section .text.x86.asm32_syscall_sysenter.sched_get_priority_max
	/* syscall_slong_t sched_get_priority_max(syscall_ulong_t algorithm) */
	.weak __asm32_sysenter_sched_get_priority_max
INTERN_FUNCTION(__asm32_sysenter_sched_get_priority_max)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000009f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_get_priority_max)

.section .text.x86.asm32_syscall_sysenter.sched_get_priority_min
	/* syscall_slong_t sched_get_priority_min(syscall_ulong_t algorithm) */
	.weak __asm32_sysenter_sched_get_priority_min
INTERN_FUNCTION(__asm32_sysenter_sched_get_priority_min)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000a0
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_get_priority_min)

.section .text.x86.asm32_syscall_sysenter.sched_rr_get_interval
	/* errno_t sched_rr_get_interval(pid_t pid,
	 *                               struct __timespec32 *tms) */
	.weak __asm32_sysenter_sched_rr_get_interval
INTERN_FUNCTION(__asm32_sysenter_sched_rr_get_interval)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000a1
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_rr_get_interval)

.section .text.x86.asm32_syscall_sysenter.nanosleep
	/* errno_t nanosleep(struct __timespec32 const *req,
	 *                   struct __timespec32 *rem) */
	.weak __asm32_sysenter_nanosleep
INTERN_FUNCTION(__asm32_sysenter_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000a2
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_nanosleep)

/* @param: flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
.section .text.x86.asm32_syscall_sysenter.mremap
	/* void *mremap(void *addr,
	 *              size_t old_len,
	 *              size_t new_len,
	 *              syscall_ulong_t flags,
	 *              void *new_address) */
	.weak __asm32_sysenter_mremap
INTERN_FUNCTION(__asm32_sysenter_mremap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000a3
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mremap)

.section .text.x86.asm32_syscall_sysenter.setresuid
	/* errno_t setresuid(uint16_t ruid,
	 *                   uint16_t euid,
	 *                   uint16_t suid) */
	.weak __asm32_sysenter_setresuid
INTERN_FUNCTION(__asm32_sysenter_setresuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000a4
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setresuid)

.section .text.x86.asm32_syscall_sysenter.getresuid
	/* errno_t getresuid(uint16_t *ruid,
	 *                   uint16_t *euid,
	 *                   uint16_t *suid) */
	.weak __asm32_sysenter_getresuid
INTERN_FUNCTION(__asm32_sysenter_getresuid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000a5
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getresuid)

.section .text.x86.asm32_syscall_sysenter.poll
	/* ssize_t poll(struct pollfd *fds,
	 *              size_t nfds,
	 *              syscall_slong_t timeout) */
	.weak __asm32_sysenter_poll
INTERN_FUNCTION(__asm32_sysenter_poll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000a8
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_poll)

.section .text.x86.asm32_syscall_sysenter.setresgid
	/* errno_t setresgid(uint16_t rgid,
	 *                   uint16_t egid,
	 *                   uint16_t sgid) */
	.weak __asm32_sysenter_setresgid
INTERN_FUNCTION(__asm32_sysenter_setresgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000aa
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setresgid)

.section .text.x86.asm32_syscall_sysenter.getresgid
	/* errno_t getresgid(uint16_t *rgid,
	 *                   uint16_t *egid,
	 *                   uint16_t *sgid) */
	.weak __asm32_sysenter_getresgid
INTERN_FUNCTION(__asm32_sysenter_getresgid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ab
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getresgid)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_sysenter.rt_sigaction
	/* errno_t rt_sigaction(syscall_ulong_t signo,
	 *                      struct sigaction const *act,
	 *                      struct sigaction *oact,
	 *                      size_t sigsetsize) */
	.weak __asm32_sysenter_rt_sigaction
INTERN_FUNCTION(__asm32_sysenter_rt_sigaction)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ae
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rt_sigaction)

/* @param: how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
.section .text.x86.asm32_syscall_sysenter.rt_sigprocmask
	/* errno_t rt_sigprocmask(syscall_ulong_t how,
	 *                        struct __sigset_struct const *set,
	 *                        struct __sigset_struct *oset,
	 *                        size_t sigsetsize) */
	.weak __asm32_sysenter_rt_sigprocmask
INTERN_FUNCTION(__asm32_sysenter_rt_sigprocmask)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000af
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rt_sigprocmask)

.section .text.x86.asm32_syscall_sysenter.rt_sigpending
	/* errno_t rt_sigpending(struct __sigset_struct *set,
	 *                       size_t sigsetsize) */
	.weak __asm32_sysenter_rt_sigpending
INTERN_FUNCTION(__asm32_sysenter_rt_sigpending)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000b0
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rt_sigpending)

.section .text.x86.asm32_syscall_sysenter.rt_sigtimedwait
	/* syscall_slong_t rt_sigtimedwait(struct __sigset_struct const *set,
	 *                                 struct __siginfo_struct *info,
	 *                                 struct __timespec32 const *timeout,
	 *                                 size_t sigsetsize) */
	.weak __asm32_sysenter_rt_sigtimedwait
INTERN_FUNCTION(__asm32_sysenter_rt_sigtimedwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000b1
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rt_sigtimedwait)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_sysenter.rt_sigqueueinfo
	/* errno_t rt_sigqueueinfo(pid_t tgid,
	 *                         syscall_ulong_t signo,
	 *                         struct __siginfo_struct const *uinfo) */
	.weak __asm32_sysenter_rt_sigqueueinfo
INTERN_FUNCTION(__asm32_sysenter_rt_sigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000b2
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rt_sigqueueinfo)

.section .text.x86.asm32_syscall_sysenter.rt_sigsuspend
	/* errno_t rt_sigsuspend(struct __sigset_struct const *set,
	 *                       size_t sigsetsize) */
	.weak __asm32_sysenter_rt_sigsuspend
INTERN_FUNCTION(__asm32_sysenter_rt_sigsuspend)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000b3
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rt_sigsuspend)

.section .text.x86.asm32_syscall_sysenter.pread64
	/* ssize_t pread64(fd_t fd,
	 *                 void *buf,
	 *                 size_t bufsize,
	 *                 uint64_t offset) */
	.weak __asm32_sysenter_pread64
INTERN_FUNCTION(__asm32_sysenter_pread64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000b4
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pread64)

.section .text.x86.asm32_syscall_sysenter.pwrite64
	/* ssize_t pwrite64(fd_t fd,
	 *                  void const *buf,
	 *                  size_t bufsize,
	 *                  uint64_t offset) */
	.weak __asm32_sysenter_pwrite64
INTERN_FUNCTION(__asm32_sysenter_pwrite64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000b5
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pwrite64)

.section .text.x86.asm32_syscall_sysenter.chown
	/* errno_t chown(char const *filename,
	 *               uint16_t owner,
	 *               uint16_t group) */
	.weak __asm32_sysenter_chown
INTERN_FUNCTION(__asm32_sysenter_chown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000b6
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_chown)

.section .text.x86.asm32_syscall_sysenter.getcwd
	/* ssize_t getcwd(char *buf,
	 *                size_t size) */
	.weak __asm32_sysenter_getcwd
INTERN_FUNCTION(__asm32_sysenter_getcwd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000b7
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getcwd)

.section .text.x86.asm32_syscall_sysenter.sigaltstack
	/* errno_t sigaltstack(struct sigaltstack const *ss,
	 *                     struct sigaltstack *oss) */
	.weak __asm32_sysenter_sigaltstack
INTERN_FUNCTION(__asm32_sysenter_sigaltstack)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ba
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sigaltstack)

.section .text.x86.asm32_syscall_sysenter.sendfile
	/* ssize_t sendfile(fd_t out_fd,
	 *                  fd_t in_fd,
	 *                  syscall_ulong_t *offset,
	 *                  size_t count) */
	.weak __asm32_sysenter_sendfile
INTERN_FUNCTION(__asm32_sysenter_sendfile)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000bb
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sendfile)

.section .text.x86.asm32_syscall_sysenter.vfork
	/* pid_t vfork(void); */
	.weak __asm32_sysenter_vfork
INTERN_FUNCTION(__asm32_sysenter_vfork)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000be
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_vfork)

.section .text.x86.asm32_syscall_sysenter.mmap2
	/* void *mmap2(void *addr,
	 *             size_t len,
	 *             syscall_ulong_t prot,
	 *             syscall_ulong_t flags,
	 *             fd_t fd,
	 *             syscall_ulong_t pgoffset) */
	.weak __asm32_sysenter_mmap2
INTERN_FUNCTION(__asm32_sysenter_mmap2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c0
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mmap2)

.section .text.x86.asm32_syscall_sysenter.truncate64
	/* errno_t truncate64(char const *filename,
	 *                    uint64_t length) */
	.weak __asm32_sysenter_truncate64
INTERN_FUNCTION(__asm32_sysenter_truncate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c1
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_truncate64)

.section .text.x86.asm32_syscall_sysenter.ftruncate64
	/* errno_t ftruncate64(fd_t fd,
	 *                     uint64_t length) */
	.weak __asm32_sysenter_ftruncate64
INTERN_FUNCTION(__asm32_sysenter_ftruncate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c2
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ftruncate64)

.section .text.x86.asm32_syscall_sysenter.linux_stat64
	/* errno_t linux_stat64(char const *filename,
	 *                      struct linux_stat64 *statbuf) */
	.weak __asm32_sysenter_linux_stat64
INTERN_FUNCTION(__asm32_sysenter_linux_stat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c3
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_stat64)

.section .text.x86.asm32_syscall_sysenter.linux_lstat64
	/* errno_t linux_lstat64(char const *filename,
	 *                       struct linux_stat64 *statbuf) */
	.weak __asm32_sysenter_linux_lstat64
INTERN_FUNCTION(__asm32_sysenter_linux_lstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c4
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_lstat64)

.section .text.x86.asm32_syscall_sysenter.linux_fstat64
	/* errno_t linux_fstat64(fd_t fd,
	 *                       struct linux_stat64 *statbuf) */
	.weak __asm32_sysenter_linux_fstat64
INTERN_FUNCTION(__asm32_sysenter_linux_fstat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c5
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_fstat64)

.section .text.x86.asm32_syscall_sysenter.lchown32
	/* errno_t lchown32(char const *filename,
	 *                  uint32_t owner,
	 *                  uint32_t group) */
	.weak __asm32_sysenter_lchown32
INTERN_FUNCTION(__asm32_sysenter_lchown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c6
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lchown32)

.section .text.x86.asm32_syscall_sysenter.getuid32
	/* uint32_t getuid32(void); */
	.weak __asm32_sysenter_getuid32
INTERN_FUNCTION(__asm32_sysenter_getuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c7
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getuid32)

.section .text.x86.asm32_syscall_sysenter.getgid32
	/* uint32_t getgid32(void); */
	.weak __asm32_sysenter_getgid32
INTERN_FUNCTION(__asm32_sysenter_getgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c8
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getgid32)

.section .text.x86.asm32_syscall_sysenter.geteuid32
	/* uint32_t geteuid32(void); */
	.weak __asm32_sysenter_geteuid32
INTERN_FUNCTION(__asm32_sysenter_geteuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000c9
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_geteuid32)

.section .text.x86.asm32_syscall_sysenter.getegid32
	/* uint32_t getegid32(void); */
	.weak __asm32_sysenter_getegid32
INTERN_FUNCTION(__asm32_sysenter_getegid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ca
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getegid32)

.section .text.x86.asm32_syscall_sysenter.setreuid32
	/* errno_t setreuid32(uint32_t ruid,
	 *                    uint32_t euid) */
	.weak __asm32_sysenter_setreuid32
INTERN_FUNCTION(__asm32_sysenter_setreuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000cb
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setreuid32)

.section .text.x86.asm32_syscall_sysenter.setregid32
	/* errno_t setregid32(uint32_t rgid,
	 *                    uint32_t egid) */
	.weak __asm32_sysenter_setregid32
INTERN_FUNCTION(__asm32_sysenter_setregid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000cc
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setregid32)

.section .text.x86.asm32_syscall_sysenter.getgroups32
	/* errno_t getgroups32(size_t size,
	 *                     [] uint32_t *list) */
	.weak __asm32_sysenter_getgroups32
INTERN_FUNCTION(__asm32_sysenter_getgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000cd
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getgroups32)

.section .text.x86.asm32_syscall_sysenter.setgroups32
	/* errno_t setgroups32(size_t count,
	 *                     uint32_t const *groups) */
	.weak __asm32_sysenter_setgroups32
INTERN_FUNCTION(__asm32_sysenter_setgroups32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ce
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setgroups32)

.section .text.x86.asm32_syscall_sysenter.fchown32
	/* errno_t fchown32(fd_t fd,
	 *                  uint32_t owner,
	 *                  uint32_t group) */
	.weak __asm32_sysenter_fchown32
INTERN_FUNCTION(__asm32_sysenter_fchown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000cf
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fchown32)

.section .text.x86.asm32_syscall_sysenter.setresuid32
	/* errno_t setresuid32(uint32_t ruid,
	 *                     uint32_t euid,
	 *                     uint32_t suid) */
	.weak __asm32_sysenter_setresuid32
INTERN_FUNCTION(__asm32_sysenter_setresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000d0
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setresuid32)

.section .text.x86.asm32_syscall_sysenter.getresuid32
	/* errno_t getresuid32(uint32_t *ruid,
	 *                     uint32_t *euid,
	 *                     uint32_t *suid) */
	.weak __asm32_sysenter_getresuid32
INTERN_FUNCTION(__asm32_sysenter_getresuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000d1
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getresuid32)

.section .text.x86.asm32_syscall_sysenter.setresgid32
	/* errno_t setresgid32(uint32_t rgid,
	 *                     uint32_t egid,
	 *                     uint32_t sgid) */
	.weak __asm32_sysenter_setresgid32
INTERN_FUNCTION(__asm32_sysenter_setresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000d2
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setresgid32)

.section .text.x86.asm32_syscall_sysenter.getresgid32
	/* errno_t getresgid32(uint32_t *rgid,
	 *                     uint32_t *egid,
	 *                     uint32_t *sgid) */
	.weak __asm32_sysenter_getresgid32
INTERN_FUNCTION(__asm32_sysenter_getresgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000d3
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getresgid32)

.section .text.x86.asm32_syscall_sysenter.chown32
	/* errno_t chown32(char const *filename,
	 *                 uint32_t owner,
	 *                 uint32_t group) */
	.weak __asm32_sysenter_chown32
INTERN_FUNCTION(__asm32_sysenter_chown32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000d4
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_chown32)

.section .text.x86.asm32_syscall_sysenter.setuid32
	/* errno_t setuid32(uint32_t uid) */
	.weak __asm32_sysenter_setuid32
INTERN_FUNCTION(__asm32_sysenter_setuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000d5
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setuid32)

.section .text.x86.asm32_syscall_sysenter.setgid32
	/* errno_t setgid32(uint32_t gid) */
	.weak __asm32_sysenter_setgid32
INTERN_FUNCTION(__asm32_sysenter_setgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000d6
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setgid32)

.section .text.x86.asm32_syscall_sysenter.setfsuid32
	/* errno_t setfsuid32(uint32_t uid) */
	.weak __asm32_sysenter_setfsuid32
INTERN_FUNCTION(__asm32_sysenter_setfsuid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000d7
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setfsuid32)

.section .text.x86.asm32_syscall_sysenter.setfsgid32
	/* errno_t setfsgid32(uint32_t gid) */
	.weak __asm32_sysenter_setfsgid32
INTERN_FUNCTION(__asm32_sysenter_setfsgid32)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000d8
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setfsgid32)

.section .text.x86.asm32_syscall_sysenter.mincore
	/* errno_t mincore(void *start,
	 *                 size_t len,
	 *                 uint8_t *vec) */
	.weak __asm32_sysenter_mincore
INTERN_FUNCTION(__asm32_sysenter_mincore)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000da
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mincore)

.section .text.x86.asm32_syscall_sysenter.madvise
	/* errno_t madvise(void *addr,
	 *                 size_t len,
	 *                 syscall_ulong_t advice) */
	.weak __asm32_sysenter_madvise
INTERN_FUNCTION(__asm32_sysenter_madvise)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000db
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_madvise)

.section .text.x86.asm32_syscall_sysenter.getdents64
	/* ssize_t getdents64(fd_t fd,
	 *                    struct linux_dirent64 *dirp,
	 *                    size_t count) */
	.weak __asm32_sysenter_getdents64
INTERN_FUNCTION(__asm32_sysenter_getdents64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000dc
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getdents64)

.section .text.x86.asm32_syscall_sysenter.fcntl64
	/* syscall_slong_t fcntl64(fd_t fd,
	 *                         syscall_ulong_t command,
	 *                         void *arg) */
	.weak __asm32_sysenter_fcntl64
INTERN_FUNCTION(__asm32_sysenter_fcntl64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000dd
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fcntl64)

.section .text.x86.asm32_syscall_sysenter.gettid
	/* pid_t gettid(void); */
	.weak __asm32_sysenter_gettid
INTERN_FUNCTION(__asm32_sysenter_gettid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e0
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_gettid)

.section .text.x86.asm32_syscall_sysenter.readahead
	/* ssize_t readahead(fd_t fd,
	 *                   uint64_t offset,
	 *                   size_t count) */
	.weak __asm32_sysenter_readahead
INTERN_FUNCTION(__asm32_sysenter_readahead)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e1
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_readahead)

.section .text.x86.asm32_syscall_sysenter.setxattr
	/* errno_t setxattr(char const *path,
	 *                  char const *name,
	 *                  void const *buf,
	 *                  size_t bufsize,
	 *                  syscall_ulong_t flags) */
	.weak __asm32_sysenter_setxattr
INTERN_FUNCTION(__asm32_sysenter_setxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e2
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setxattr)

.section .text.x86.asm32_syscall_sysenter.lsetxattr
	/* errno_t lsetxattr(char const *path,
	 *                   char const *name,
	 *                   void const *buf,
	 *                   size_t bufsize,
	 *                   syscall_ulong_t flags) */
	.weak __asm32_sysenter_lsetxattr
INTERN_FUNCTION(__asm32_sysenter_lsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e3
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lsetxattr)

.section .text.x86.asm32_syscall_sysenter.fsetxattr
	/* errno_t fsetxattr(fd_t fd,
	 *                   char const *name,
	 *                   void const *buf,
	 *                   size_t bufsize,
	 *                   syscall_ulong_t flags) */
	.weak __asm32_sysenter_fsetxattr
INTERN_FUNCTION(__asm32_sysenter_fsetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e4
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fsetxattr)

.section .text.x86.asm32_syscall_sysenter.getxattr
	/* ssize_t getxattr(char const *path,
	 *                  char const *name,
	 *                  void *buf,
	 *                  size_t bufsize) */
	.weak __asm32_sysenter_getxattr
INTERN_FUNCTION(__asm32_sysenter_getxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e5
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getxattr)

.section .text.x86.asm32_syscall_sysenter.lgetxattr
	/* ssize_t lgetxattr(char const *path,
	 *                   char const *name,
	 *                   void *buf,
	 *                   size_t bufsize) */
	.weak __asm32_sysenter_lgetxattr
INTERN_FUNCTION(__asm32_sysenter_lgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e6
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lgetxattr)

.section .text.x86.asm32_syscall_sysenter.fgetxattr
	/* ssize_t fgetxattr(fd_t fd,
	 *                   char const *name,
	 *                   void *buf,
	 *                   size_t bufsize) */
	.weak __asm32_sysenter_fgetxattr
INTERN_FUNCTION(__asm32_sysenter_fgetxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e7
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fgetxattr)

.section .text.x86.asm32_syscall_sysenter.listxattr
	/* ssize_t listxattr(char const *path,
	 *                   char *listbuf,
	 *                   size_t listbufsize) */
	.weak __asm32_sysenter_listxattr
INTERN_FUNCTION(__asm32_sysenter_listxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e8
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_listxattr)

.section .text.x86.asm32_syscall_sysenter.llistxattr
	/* ssize_t llistxattr(char const *path,
	 *                    char *listbuf,
	 *                    size_t listbufsize) */
	.weak __asm32_sysenter_llistxattr
INTERN_FUNCTION(__asm32_sysenter_llistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000e9
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_llistxattr)

.section .text.x86.asm32_syscall_sysenter.flistxattr
	/* ssize_t flistxattr(fd_t fd,
	 *                    char *listbuf,
	 *                    size_t listbufsize) */
	.weak __asm32_sysenter_flistxattr
INTERN_FUNCTION(__asm32_sysenter_flistxattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ea
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_flistxattr)

.section .text.x86.asm32_syscall_sysenter.removexattr
	/* errno_t removexattr(char const *path,
	 *                     char const *name) */
	.weak __asm32_sysenter_removexattr
INTERN_FUNCTION(__asm32_sysenter_removexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000eb
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_removexattr)

.section .text.x86.asm32_syscall_sysenter.lremovexattr
	/* errno_t lremovexattr(char const *path,
	 *                      char const *name) */
	.weak __asm32_sysenter_lremovexattr
INTERN_FUNCTION(__asm32_sysenter_lremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ec
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lremovexattr)

.section .text.x86.asm32_syscall_sysenter.fremovexattr
	/* errno_t fremovexattr(int fd,
	 *                      char const *name) */
	.weak __asm32_sysenter_fremovexattr
INTERN_FUNCTION(__asm32_sysenter_fremovexattr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ed
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fremovexattr)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_sysenter.tkill
	/* errno_t tkill(pid_t tid,
	 *               syscall_ulong_t signo) */
	.weak __asm32_sysenter_tkill
INTERN_FUNCTION(__asm32_sysenter_tkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ee
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_tkill)

.section .text.x86.asm32_syscall_sysenter.sendfile64
	/* ssize_t sendfile64(fd_t out_fd,
	 *                    fd_t in_fd,
	 *                    uint64_t *offset,
	 *                    size_t count) */
	.weak __asm32_sysenter_sendfile64
INTERN_FUNCTION(__asm32_sysenter_sendfile64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ef
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sendfile64)

.section .text.x86.asm32_syscall_sysenter.futex
	/* syscall_slong_t futex(uint32_t *uaddr,
	 *                       syscall_ulong_t futex_op,
	 *                       uint32_t val,
	 *                       struct __timespec32 const *timeout_or_val2,
	 *                       uint32_t *uaddr2,
	 *                       uint32_t val3) */
	.weak __asm32_sysenter_futex
INTERN_FUNCTION(__asm32_sysenter_futex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000f0
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_futex)

.section .text.x86.asm32_syscall_sysenter.sched_setaffinity
	/* errno_t sched_setaffinity(pid_t pid,
	 *                           size_t cpusetsize,
	 *                           struct __cpu_set_struct const *cpuset) */
	.weak __asm32_sysenter_sched_setaffinity
INTERN_FUNCTION(__asm32_sysenter_sched_setaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000f1
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_setaffinity)

.section .text.x86.asm32_syscall_sysenter.sched_getaffinity
	/* errno_t sched_getaffinity(pid_t pid,
	 *                           size_t cpusetsize,
	 *                           struct __cpu_set_struct *cpuset) */
	.weak __asm32_sysenter_sched_getaffinity
INTERN_FUNCTION(__asm32_sysenter_sched_getaffinity)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000f2
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_getaffinity)

.section .text.x86.asm32_syscall_sysenter.exit_group
	/* void exit_group(syscall_ulong_t exit_code) */
	.weak __asm32_sysenter_exit_group
INTERN_FUNCTION(__asm32_sysenter_exit_group)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000fc
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_exit_group)

.section .text.x86.asm32_syscall_sysenter.epoll_create
	/* fd_t epoll_create(syscall_ulong_t size) */
	.weak __asm32_sysenter_epoll_create
INTERN_FUNCTION(__asm32_sysenter_epoll_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000fe
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_epoll_create)

.section .text.x86.asm32_syscall_sysenter.epoll_ctl
	/* errno_t epoll_ctl(fd_t epfd,
	 *                   syscall_ulong_t op,
	 *                   fd_t fd,
	 *                   struct epoll_event *event) */
	.weak __asm32_sysenter_epoll_ctl
INTERN_FUNCTION(__asm32_sysenter_epoll_ctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x400000ff
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_epoll_ctl)

.section .text.x86.asm32_syscall_sysenter.epoll_wait
	/* errno_t epoll_wait(fd_t epfd,
	 *                    struct epoll_event *events,
	 *                    syscall_ulong_t maxevents,
	 *                    syscall_slong_t timeout) */
	.weak __asm32_sysenter_epoll_wait
INTERN_FUNCTION(__asm32_sysenter_epoll_wait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000100
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_epoll_wait)

.section .text.x86.asm32_syscall_sysenter.remap_file_pages
	/* errno_t remap_file_pages(void *start,
	 *                          size_t size,
	 *                          syscall_ulong_t prot,
	 *                          size_t pgoff,
	 *                          syscall_ulong_t flags) */
	.weak __asm32_sysenter_remap_file_pages
INTERN_FUNCTION(__asm32_sysenter_remap_file_pages)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000101
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_remap_file_pages)

.section .text.x86.asm32_syscall_sysenter.set_tid_address
	/* pid_t set_tid_address(pid_t *tidptr) */
	.weak __asm32_sysenter_set_tid_address
INTERN_FUNCTION(__asm32_sysenter_set_tid_address)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000102
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_set_tid_address)

.section .text.x86.asm32_syscall_sysenter.timer_create
	/* errno_t timer_create(clockid_t clock_id,
	 *                      struct sigevent *evp,
	 *                      timer_t *timerid) */
	.weak __asm32_sysenter_timer_create
INTERN_FUNCTION(__asm32_sysenter_timer_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000103
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timer_create)

.section .text.x86.asm32_syscall_sysenter.timer_settime
	/* errno_t timer_settime(timer_t timerid,
	 *                       syscall_ulong_t flags,
	 *                       struct __itimerspec32 const *value,
	 *                       struct __itimerspec32 *ovalue) */
	.weak __asm32_sysenter_timer_settime
INTERN_FUNCTION(__asm32_sysenter_timer_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000104
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timer_settime)

.section .text.x86.asm32_syscall_sysenter.timer_gettime
	/* errno_t timer_gettime(timer_t timerid,
	 *                       struct __itimerspec32 *value) */
	.weak __asm32_sysenter_timer_gettime
INTERN_FUNCTION(__asm32_sysenter_timer_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000105
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timer_gettime)

.section .text.x86.asm32_syscall_sysenter.timer_getoverrun
	/* syscall_slong_t timer_getoverrun(timer_t timerid) */
	.weak __asm32_sysenter_timer_getoverrun
INTERN_FUNCTION(__asm32_sysenter_timer_getoverrun)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000106
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timer_getoverrun)

.section .text.x86.asm32_syscall_sysenter.timer_delete
	/* errno_t timer_delete(timer_t timerid) */
	.weak __asm32_sysenter_timer_delete
INTERN_FUNCTION(__asm32_sysenter_timer_delete)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000107
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timer_delete)

.section .text.x86.asm32_syscall_sysenter.clock_settime
	/* errno_t clock_settime(clockid_t clock_id,
	 *                       struct __timespec32 const *tp) */
	.weak __asm32_sysenter_clock_settime
INTERN_FUNCTION(__asm32_sysenter_clock_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000108
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_clock_settime)

.section .text.x86.asm32_syscall_sysenter.clock_gettime
	/* errno_t clock_gettime(clockid_t clock_id,
	 *                       struct __timespec32 *tp) */
	.weak __asm32_sysenter_clock_gettime
INTERN_FUNCTION(__asm32_sysenter_clock_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000109
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_clock_gettime)

.section .text.x86.asm32_syscall_sysenter.clock_getres
	/* errno_t clock_getres(clockid_t clock_id,
	 *                      struct __timespec32 *res) */
	.weak __asm32_sysenter_clock_getres
INTERN_FUNCTION(__asm32_sysenter_clock_getres)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000010a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_clock_getres)

.section .text.x86.asm32_syscall_sysenter.clock_nanosleep
	/* errno_t clock_nanosleep(clockid_t clock_id,
	 *                         syscall_ulong_t flags,
	 *                         struct __timespec32 const *requested_time,
	 *                         struct __timespec32 *remaining) */
	.weak __asm32_sysenter_clock_nanosleep
INTERN_FUNCTION(__asm32_sysenter_clock_nanosleep)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000010b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_clock_nanosleep)

.section .text.x86.asm32_syscall_sysenter.statfs64
	/* errno_t statfs64(char const *file,
	 *                  struct statfs64 *buf) */
	.weak __asm32_sysenter_statfs64
INTERN_FUNCTION(__asm32_sysenter_statfs64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000010c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_statfs64)

.section .text.x86.asm32_syscall_sysenter.fstatfs64
	/* errno_t fstatfs64(fd_t file,
	 *                   struct statfs64 *buf) */
	.weak __asm32_sysenter_fstatfs64
INTERN_FUNCTION(__asm32_sysenter_fstatfs64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000010d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fstatfs64)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_sysenter.tgkill
	/* errno_t tgkill(pid_t tgid,
	 *                pid_t tid,
	 *                syscall_ulong_t signo) */
	.weak __asm32_sysenter_tgkill
INTERN_FUNCTION(__asm32_sysenter_tgkill)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000010e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_tgkill)

.section .text.x86.asm32_syscall_sysenter.utimes
	/* errno_t utimes(char const *filename,
	 *                [2] struct __timeval32 const *times) */
	.weak __asm32_sysenter_utimes
INTERN_FUNCTION(__asm32_sysenter_utimes)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000010f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_utimes)

/* @param: options: At least one of `WEXITED|WSTOPPED|WCONTINUED', optionally or'd with `WNOHANG|WNOWAIT' */
.section .text.x86.asm32_syscall_sysenter.waitid
	/* errno_t waitid(idtype_t idtype,
	 *                id_t id,
	 *                struct __siginfo_struct *infop,
	 *                syscall_ulong_t options,
	 *                struct rusage *ru) */
	.weak __asm32_sysenter_waitid
INTERN_FUNCTION(__asm32_sysenter_waitid)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000011c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_waitid)

.section .text.x86.asm32_syscall_sysenter.ioprio_set
	/* errno_t ioprio_set(syscall_ulong_t which,
	 *                    syscall_ulong_t who,
	 *                    syscall_ulong_t ioprio) */
	.weak __asm32_sysenter_ioprio_set
INTERN_FUNCTION(__asm32_sysenter_ioprio_set)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000121
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ioprio_set)

.section .text.x86.asm32_syscall_sysenter.ioprio_get
	/* errno_t ioprio_get(syscall_ulong_t which,
	 *                    syscall_ulong_t who) */
	.weak __asm32_sysenter_ioprio_get
INTERN_FUNCTION(__asm32_sysenter_ioprio_get)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000122
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ioprio_get)

.section .text.x86.asm32_syscall_sysenter.openat
	/* fd_t openat(fd_t dirfd,
	 *             char const *filename,
	 *             oflag_t oflags,
	 *             mode_t mode) */
	.weak __asm32_sysenter_openat
INTERN_FUNCTION(__asm32_sysenter_openat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000127
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_openat)

.section .text.x86.asm32_syscall_sysenter.mkdirat
	/* errno_t mkdirat(fd_t dirfd,
	 *                 char const *pathname,
	 *                 mode_t mode) */
	.weak __asm32_sysenter_mkdirat
INTERN_FUNCTION(__asm32_sysenter_mkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000128
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mkdirat)

.section .text.x86.asm32_syscall_sysenter.mknodat
	/* errno_t mknodat(fd_t dirfd,
	 *                 char const *nodename,
	 *                 mode_t mode,
	 *                 dev_t dev) */
	.weak __asm32_sysenter_mknodat
INTERN_FUNCTION(__asm32_sysenter_mknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000129
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.fchownat
	/* errno_t fchownat(fd_t dirfd,
	 *                  char const *filename,
	 *                  uint32_t owner,
	 *                  uint32_t group,
	 *                  atflag_t flags) */
	.weak __asm32_sysenter_fchownat
INTERN_FUNCTION(__asm32_sysenter_fchownat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000012a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fchownat)

.section .text.x86.asm32_syscall_sysenter.futimesat
	/* errno_t futimesat(fd_t dirfd,
	 *                   const char *filename,
	 *                   [2] struct __timeval32 const *times) */
	.weak __asm32_sysenter_futimesat
INTERN_FUNCTION(__asm32_sysenter_futimesat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000012b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_futimesat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.linux_fstatat64
	/* errno_t linux_fstatat64(fd_t dirfd,
	 *                         char const *filename,
	 *                         struct linux_stat64 *statbuf,
	 *                         atflag_t flags) */
	.weak __asm32_sysenter_linux_fstatat64
INTERN_FUNCTION(__asm32_sysenter_linux_fstatat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000012c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linux_fstatat64)

/* @param: flags: Set of `0|AT_REMOVEDIR|AT_REMOVEREG|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.unlinkat
	/* errno_t unlinkat(fd_t dirfd,
	 *                  char const *name,
	 *                  atflag_t flags) */
	.weak __asm32_sysenter_unlinkat
INTERN_FUNCTION(__asm32_sysenter_unlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000012d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_unlinkat)

.section .text.x86.asm32_syscall_sysenter.renameat
	/* errno_t renameat(fd_t oldfd,
	 *                  char const *oldname,
	 *                  fd_t newfd,
	 *                  char const *newname_or_path) */
	.weak __asm32_sysenter_renameat
INTERN_FUNCTION(__asm32_sysenter_renameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000012e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_renameat)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_FOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.linkat
	/* errno_t linkat(fd_t fromfd,
	 *                char const *existing_file,
	 *                fd_t tofd,
	 *                char const *target_path,
	 *                atflag_t flags) */
	.weak __asm32_sysenter_linkat
INTERN_FUNCTION(__asm32_sysenter_linkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000012f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_linkat)

.section .text.x86.asm32_syscall_sysenter.symlinkat
	/* errno_t symlinkat(char const *link_text,
	 *                   fd_t tofd,
	 *                   char const *target_path) */
	.weak __asm32_sysenter_symlinkat
INTERN_FUNCTION(__asm32_sysenter_symlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000130
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_symlinkat)

.section .text.x86.asm32_syscall_sysenter.readlinkat
	/* ssize_t readlinkat(fd_t dirfd,
	 *                    char const *path,
	 *                    char *buf,
	 *                    size_t buflen) */
	.weak __asm32_sysenter_readlinkat
INTERN_FUNCTION(__asm32_sysenter_readlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000131
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_readlinkat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.fchmodat
	/* errno_t fchmodat(fd_t dirfd,
	 *                  char const *filename,
	 *                  mode_t mode,
	 *                  atflag_t flags) */
	.weak __asm32_sysenter_fchmodat
INTERN_FUNCTION(__asm32_sysenter_fchmodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000132
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fchmodat)

/* @param: type: Set of `R_OK|W_OK|X_OK' or `F_OK'
 * @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_EACCESS|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.faccessat
	/* errno_t faccessat(fd_t dirfd,
	 *                   char const *filename,
	 *                   syscall_ulong_t type,
	 *                   atflag_t flags) */
	.weak __asm32_sysenter_faccessat
INTERN_FUNCTION(__asm32_sysenter_faccessat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000133
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_faccessat)

.section .text.x86.asm32_syscall_sysenter.pselect6
	/* ssize_t pselect6(size_t nfds,
	 *                  struct __fd_set_struct *readfds,
	 *                  struct __fd_set_struct *writefds,
	 *                  struct __fd_set_struct *exceptfds,
	 *                  struct __timespec32 const *timeout,
	 *                  void const *sigmask_sigset_and_len) */
	.weak __asm32_sysenter_pselect6
INTERN_FUNCTION(__asm32_sysenter_pselect6)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000134
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pselect6)

.section .text.x86.asm32_syscall_sysenter.ppoll
	/* ssize_t ppoll(struct pollfd *fds,
	 *               size_t nfds,
	 *               struct __timespec32 const *timeout_ts,
	 *               struct __sigset_struct const *sigmask,
	 *               size_t sigsetsize) */
	.weak __asm32_sysenter_ppoll
INTERN_FUNCTION(__asm32_sysenter_ppoll)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000135
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ppoll)

/* param flags: Set of `CLONE_*' */
.section .text.x86.asm32_syscall_sysenter.unshare
	/* errno_t unshare(syscall_ulong_t flags) */
	.weak __asm32_sysenter_unshare
INTERN_FUNCTION(__asm32_sysenter_unshare)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000136
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_unshare)

.section .text.x86.asm32_syscall_sysenter.splice
	/* ssize_t splice(fd_t fdin,
	 *                uint64_t *offin,
	 *                fd_t fdout,
	 *                uint64_t *offout,
	 *                size_t length,
	 *                syscall_ulong_t flags) */
	.weak __asm32_sysenter_splice
INTERN_FUNCTION(__asm32_sysenter_splice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000139
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_splice)

.section .text.x86.asm32_syscall_sysenter.sync_file_range
	/* errno_t sync_file_range(fd_t fd,
	 *                         uint64_t offset,
	 *                         uint64_t count,
	 *                         syscall_ulong_t flags) */
	.weak __asm32_sysenter_sync_file_range
INTERN_FUNCTION(__asm32_sysenter_sync_file_range)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000013a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sync_file_range)

.section .text.x86.asm32_syscall_sysenter.tee
	/* ssize_t tee(fd_t fdin,
	 *             fd_t fdout,
	 *             size_t length,
	 *             syscall_ulong_t flags) */
	.weak __asm32_sysenter_tee
INTERN_FUNCTION(__asm32_sysenter_tee)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000013b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_tee)

.section .text.x86.asm32_syscall_sysenter.vmsplice
	/* ssize_t vmsplice(fd_t fdout,
	 *                  struct iovec const *iov,
	 *                  size_t count,
	 *                  syscall_ulong_t flags) */
	.weak __asm32_sysenter_vmsplice
INTERN_FUNCTION(__asm32_sysenter_vmsplice)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000013c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_vmsplice)

.section .text.x86.asm32_syscall_sysenter.getcpu
	/* errno_t getcpu(uint32_t *cpu,
	 *                uint32_t *node,
	 *                struct getcpu_cache *tcache) */
	.weak __asm32_sysenter_getcpu
INTERN_FUNCTION(__asm32_sysenter_getcpu)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000013e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getcpu)

.section .text.x86.asm32_syscall_sysenter.epoll_pwait
	/* errno_t epoll_pwait(fd_t epfd,
	 *                     struct epoll_event *events,
	 *                     syscall_ulong_t maxevents,
	 *                     syscall_slong_t timeout,
	 *                     struct __sigset_struct const *ss) */
	.weak __asm32_sysenter_epoll_pwait
INTERN_FUNCTION(__asm32_sysenter_epoll_pwait)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000013f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_epoll_pwait)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.utimensat
	/* errno_t utimensat(fd_t dirfd,
	 *                   char const *filename,
	 *                   [2-3] struct __timespec32 const *times,
	 *                   atflag_t flags) */
	.weak __asm32_sysenter_utimensat
INTERN_FUNCTION(__asm32_sysenter_utimensat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000140
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_utimensat)

.section .text.x86.asm32_syscall_sysenter.signalfd
	/* errno_t signalfd(fd_t fd,
	 *                  struct __sigset_struct const *sigmask,
	 *                  size_t sigsetsize) */
	.weak __asm32_sysenter_signalfd
INTERN_FUNCTION(__asm32_sysenter_signalfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000141
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_signalfd)

/* Return file descriptor for new interval timer source */
.section .text.x86.asm32_syscall_sysenter.timerfd_create
	/* fd_t timerfd_create(clockid_t clock_id,
	 *                     syscall_ulong_t flags) */
	.weak __asm32_sysenter_timerfd_create
INTERN_FUNCTION(__asm32_sysenter_timerfd_create)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000142
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timerfd_create)

.section .text.x86.asm32_syscall_sysenter.eventfd
	/* fd_t eventfd(syscall_ulong_t initval) */
	.weak __asm32_sysenter_eventfd
INTERN_FUNCTION(__asm32_sysenter_eventfd)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000143
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_eventfd)

.section .text.x86.asm32_syscall_sysenter.fallocate
	/* errno_t fallocate(fd_t fd,
	 *                   syscall_ulong_t mode,
	 *                   uint32_t offset,
	 *                   uint32_t length) */
	.weak __asm32_sysenter_fallocate
INTERN_FUNCTION(__asm32_sysenter_fallocate)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000144
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fallocate)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
.section .text.x86.asm32_syscall_sysenter.timerfd_settime
	/* errno_t timerfd_settime(fd_t ufd,
	 *                         syscall_ulong_t flags,
	 *                         struct __itimerspec32 const *utmr,
	 *                         struct __itimerspec32 *otmr) */
	.weak __asm32_sysenter_timerfd_settime
INTERN_FUNCTION(__asm32_sysenter_timerfd_settime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000145
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timerfd_settime)

/* Return the next expiration time of UFD */
.section .text.x86.asm32_syscall_sysenter.timerfd_gettime
	/* errno_t timerfd_gettime(fd_t ufd,
	 *                         struct __itimerspec32 *otmr) */
	.weak __asm32_sysenter_timerfd_gettime
INTERN_FUNCTION(__asm32_sysenter_timerfd_gettime)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000146
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timerfd_gettime)

.section .text.x86.asm32_syscall_sysenter.signalfd4
	/* errno_t signalfd4(fd_t fd,
	 *                   struct __sigset_struct const *sigmask,
	 *                   size_t sigsetsize,
	 *                   syscall_ulong_t flags) */
	.weak __asm32_sysenter_signalfd4
INTERN_FUNCTION(__asm32_sysenter_signalfd4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000147
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_signalfd4)

.section .text.x86.asm32_syscall_sysenter.eventfd2
	/* fd_t eventfd2(syscall_ulong_t initval,
	 *               syscall_ulong_t flags) */
	.weak __asm32_sysenter_eventfd2
INTERN_FUNCTION(__asm32_sysenter_eventfd2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000148
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_eventfd2)

.section .text.x86.asm32_syscall_sysenter.epoll_create1
	/* fd_t epoll_create1(syscall_ulong_t flags) */
	.weak __asm32_sysenter_epoll_create1
INTERN_FUNCTION(__asm32_sysenter_epoll_create1)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000149
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_epoll_create1)

/* @param: flags:  Set of `O_CLOEXEC|O_CLOFORK' */
.section .text.x86.asm32_syscall_sysenter.dup3
	/* fd_t dup3(fd_t oldfd,
	 *           fd_t newfd,
	 *           oflag_t flags) */
	.weak __asm32_sysenter_dup3
INTERN_FUNCTION(__asm32_sysenter_dup3)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000014a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_dup3)

.section .text.x86.asm32_syscall_sysenter.pipe2
	/* errno_t pipe2([2] fd_t *pipedes,
	 *               oflag_t flags) */
	.weak __asm32_sysenter_pipe2
INTERN_FUNCTION(__asm32_sysenter_pipe2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000014b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pipe2)

.section .text.x86.asm32_syscall_sysenter.preadv
	/* ssize_t preadv(fd_t fd,
	 *                struct iovec const *iovec,
	 *                size_t count,
	 *                uint64_t offset) */
	.weak __asm32_sysenter_preadv
INTERN_FUNCTION(__asm32_sysenter_preadv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000014d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_preadv)

.section .text.x86.asm32_syscall_sysenter.pwritev
	/* ssize_t pwritev(fd_t fd,
	 *                 struct iovec const *iovec,
	 *                 size_t count,
	 *                 uint64_t offset) */
	.weak __asm32_sysenter_pwritev
INTERN_FUNCTION(__asm32_sysenter_pwritev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000014e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pwritev)

/* @param: signo: One of `SIG*' */
.section .text.x86.asm32_syscall_sysenter.rt_tgsigqueueinfo
	/* errno_t rt_tgsigqueueinfo(pid_t tgid,
	 *                           pid_t tid,
	 *                           syscall_ulong_t signo,
	 *                           struct __siginfo_struct const *uinfo) */
	.weak __asm32_sysenter_rt_tgsigqueueinfo
INTERN_FUNCTION(__asm32_sysenter_rt_tgsigqueueinfo)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000014f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rt_tgsigqueueinfo)

.section .text.x86.asm32_syscall_sysenter.recvmmsg
	/* ssize_t recvmmsg(fd_t sockfd,
	 *                  struct mmsghdr *vmessages,
	 *                  size_t vlen,
	 *                  syscall_ulong_t flags,
	 *                  struct __timespec32 *tmo) */
	.weak __asm32_sysenter_recvmmsg
INTERN_FUNCTION(__asm32_sysenter_recvmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000151
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_recvmmsg)

/* @param: resource: One of `RLIMIT_*' from <bits/resource.h> */
.section .text.x86.asm32_syscall_sysenter.prlimit64
	/* errno_t prlimit64(pid_t pid,
	 *                   syscall_ulong_t resource,
	 *                   struct rlimit64 const *new_limit,
	 *                   struct rlimit64 *old_limit) */
	.weak __asm32_sysenter_prlimit64
INTERN_FUNCTION(__asm32_sysenter_prlimit64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000154
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_prlimit64)

.section .text.x86.asm32_syscall_sysenter.name_to_handle_at
	/* errno_t name_to_handle_at(fd_t dirfd,
	 *                           char const *name,
	 *                           struct file_handle *handle,
	 *                           int32_t *mnt_id,
	 *                           syscall_ulong_t flags) */
	.weak __asm32_sysenter_name_to_handle_at
INTERN_FUNCTION(__asm32_sysenter_name_to_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000155
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_name_to_handle_at)

.section .text.x86.asm32_syscall_sysenter.open_by_handle_at
	/* fd_t open_by_handle_at(fd_t mountdirfd,
	 *                        struct file_handle *handle,
	 *                        syscall_ulong_t flags) */
	.weak __asm32_sysenter_open_by_handle_at
INTERN_FUNCTION(__asm32_sysenter_open_by_handle_at)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000156
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_open_by_handle_at)

.section .text.x86.asm32_syscall_sysenter.syncfs
	/* errno_t syncfs(fd_t fd) */
	.weak __asm32_sysenter_syncfs
INTERN_FUNCTION(__asm32_sysenter_syncfs)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000158
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_syncfs)

.section .text.x86.asm32_syscall_sysenter.sendmmsg
	/* ssize_t sendmmsg(fd_t sockfd,
	 *                  struct mmsghdr *vmessages,
	 *                  size_t vlen,
	 *                  syscall_ulong_t flags) */
	.weak __asm32_sysenter_sendmmsg
INTERN_FUNCTION(__asm32_sysenter_sendmmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000159
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sendmmsg)

.section .text.x86.asm32_syscall_sysenter.setns
	/* errno_t setns(fd_t fd,
	 *               syscall_ulong_t nstype) */
	.weak __asm32_sysenter_setns
INTERN_FUNCTION(__asm32_sysenter_setns)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000015a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setns)

.section .text.x86.asm32_syscall_sysenter.process_vm_readv
	/* ssize_t process_vm_readv(pid_t pid,
	 *                          struct iovec const *lvec,
	 *                          size_t liovcnt,
	 *                          struct iovec const *rvec,
	 *                          size_t riovcnt,
	 *                          syscall_ulong_t flags) */
	.weak __asm32_sysenter_process_vm_readv
INTERN_FUNCTION(__asm32_sysenter_process_vm_readv)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000015b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_process_vm_readv)

.section .text.x86.asm32_syscall_sysenter.process_vm_writev
	/* ssize_t process_vm_writev(pid_t pid,
	 *                           struct iovec const *lvec,
	 *                           size_t liovcnt,
	 *                           struct iovec const *rvec,
	 *                           size_t riovcnt,
	 *                           syscall_ulong_t flags) */
	.weak __asm32_sysenter_process_vm_writev
INTERN_FUNCTION(__asm32_sysenter_process_vm_writev)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000015c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_process_vm_writev)

.section .text.x86.asm32_syscall_sysenter.kcmp
	/* syscall_slong_t kcmp(pid_t pid1,
	 *                      pid_t pid2,
	 *                      syscall_ulong_t type,
	 *                      syscall_ulong_t idx1,
	 *                      syscall_ulong_t idx2) */
	.weak __asm32_sysenter_kcmp
INTERN_FUNCTION(__asm32_sysenter_kcmp)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000015d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_kcmp)

/* @param: flags: Set of `RENAME_EXCHANGE,RENAME_NOREPLACE,RENAME_WHITEOUT' */
.section .text.x86.asm32_syscall_sysenter.renameat2
	/* errno_t renameat2(fd_t olddirfd,
	 *                   char const *oldpath,
	 *                   fd_t newdirfd,
	 *                   char const *newpath,
	 *                   syscall_ulong_t flags) */
	.weak __asm32_sysenter_renameat2
INTERN_FUNCTION(__asm32_sysenter_renameat2)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000161
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_renameat2)

/* @param: flags: Set of `0|AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.execveat
	/* errno_t execveat(fd_t dirfd,
	 *                  char const *pathname,
	 *                  char const *const *argv,
	 *                  char const *const *envp,
	 *                  atflag_t flags) */
	.weak __asm32_sysenter_execveat
INTERN_FUNCTION(__asm32_sysenter_execveat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000166
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_execveat)

.section .text.x86.asm32_syscall_sysenter.socket
	/* fd_t socket(syscall_ulong_t domain,
	 *             syscall_ulong_t type,
	 *             syscall_ulong_t protocol) */
	.weak __asm32_sysenter_socket
INTERN_FUNCTION(__asm32_sysenter_socket)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000167
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_socket)

.section .text.x86.asm32_syscall_sysenter.socketpair
	/* errno_t socketpair(syscall_ulong_t domain,
	 *                    syscall_ulong_t type,
	 *                    syscall_ulong_t protocol,
	 *                    [2] fd_t *fds) */
	.weak __asm32_sysenter_socketpair
INTERN_FUNCTION(__asm32_sysenter_socketpair)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000168
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_socketpair)

.section .text.x86.asm32_syscall_sysenter.bind
	/* errno_t bind(fd_t sockfd,
	 *              struct sockaddr const *addr,
	 *              socklen_t addr_len) */
	.weak __asm32_sysenter_bind
INTERN_FUNCTION(__asm32_sysenter_bind)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000169
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_bind)

.section .text.x86.asm32_syscall_sysenter.connect
	/* errno_t connect(fd_t sockfd,
	 *                 struct sockaddr const *addr,
	 *                 socklen_t addr_len) */
	.weak __asm32_sysenter_connect
INTERN_FUNCTION(__asm32_sysenter_connect)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000016a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_connect)

.section .text.x86.asm32_syscall_sysenter.listen
	/* errno_t listen(fd_t sockfd,
	 *                syscall_ulong_t max_backlog) */
	.weak __asm32_sysenter_listen
INTERN_FUNCTION(__asm32_sysenter_listen)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000016b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_listen)

.section .text.x86.asm32_syscall_sysenter.accept4
	/* fd_t accept4(fd_t sockfd,
	 *              struct sockaddr *addr,
	 *              socklen_t *addr_len,
	 *              syscall_ulong_t flags) */
	.weak __asm32_sysenter_accept4
INTERN_FUNCTION(__asm32_sysenter_accept4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000016c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_accept4)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.x86.asm32_syscall_sysenter.getsockopt
	/* errno_t getsockopt(fd_t sockfd,
	 *                    syscall_ulong_t level,
	 *                    syscall_ulong_t optname,
	 *                    void *optval,
	 *                    socklen_t *optlen) */
	.weak __asm32_sysenter_getsockopt
INTERN_FUNCTION(__asm32_sysenter_getsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000016d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getsockopt)

/* @param: level:   One of `SOL_*' (e.g.: `SOL_SOCKET')
 * @param: optname: Dependent on `level' */
.section .text.x86.asm32_syscall_sysenter.setsockopt
	/* errno_t setsockopt(fd_t sockfd,
	 *                    syscall_ulong_t level,
	 *                    syscall_ulong_t optname,
	 *                    void const *optval,
	 *                    socklen_t optlen) */
	.weak __asm32_sysenter_setsockopt
INTERN_FUNCTION(__asm32_sysenter_setsockopt)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000016e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setsockopt)

.section .text.x86.asm32_syscall_sysenter.getsockname
	/* errno_t getsockname(fd_t sockfd,
	 *                     struct sockaddr *addr,
	 *                     socklen_t *addr_len) */
	.weak __asm32_sysenter_getsockname
INTERN_FUNCTION(__asm32_sysenter_getsockname)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x4000016f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getsockname)

.section .text.x86.asm32_syscall_sysenter.getpeername
	/* errno_t getpeername(fd_t sockfd,
	 *                     struct sockaddr *addr,
	 *                     socklen_t *addr_len) */
	.weak __asm32_sysenter_getpeername
INTERN_FUNCTION(__asm32_sysenter_getpeername)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000170
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getpeername)

/* param flags: Set of `MSG_CONFIRM|MSG_DONTROUTE|MSG_DONTWAIT|MSG_EOR|MSG_MORE|MSG_NOSIGNAL|MSG_OOB' */
.section .text.x86.asm32_syscall_sysenter.sendto
	/* ssize_t sendto(fd_t sockfd,
	 *                void const *buf,
	 *                size_t bufsize,
	 *                syscall_ulong_t flags,
	 *                struct sockaddr const *addr,
	 *                socklen_t addr_len) */
	.weak __asm32_sysenter_sendto
INTERN_FUNCTION(__asm32_sysenter_sendto)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000171
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sendto)

.section .text.x86.asm32_syscall_sysenter.sendmsg
	/* ssize_t sendmsg(fd_t sockfd,
	 *                 struct msghdr const *message,
	 *                 syscall_ulong_t flags) */
	.weak __asm32_sysenter_sendmsg
INTERN_FUNCTION(__asm32_sysenter_sendmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000172
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sendmsg)

.section .text.x86.asm32_syscall_sysenter.recvfrom
	/* ssize_t recvfrom(fd_t sockfd,
	 *                  void *buf,
	 *                  size_t bufsize,
	 *                  syscall_ulong_t flags,
	 *                  struct sockaddr *addr,
	 *                  socklen_t *addr_len) */
	.weak __asm32_sysenter_recvfrom
INTERN_FUNCTION(__asm32_sysenter_recvfrom)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000173
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_recvfrom)

.section .text.x86.asm32_syscall_sysenter.recvmsg
	/* ssize_t recvmsg(fd_t sockfd,
	 *                 struct msghdr *message,
	 *                 syscall_ulong_t flags) */
	.weak __asm32_sysenter_recvmsg
INTERN_FUNCTION(__asm32_sysenter_recvmsg)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000174
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_recvmsg)

/* @param: how: One of `SHUT_RD', `SHUT_WR' or `SHUT_RDWR' */
.section .text.x86.asm32_syscall_sysenter.shutdown
	/* errno_t shutdown(fd_t sockfd,
	 *                  syscall_ulong_t how) */
	.weak __asm32_sysenter_shutdown
INTERN_FUNCTION(__asm32_sysenter_shutdown)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0x40000175
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_shutdown)

.section .text.x86.asm32_syscall_sysenter.hop
	/* syscall_slong_t hop(fd_t fd,
	 *                     syscall_ulong_t command,
	 *                     void *arg) */
	.weak __asm32_sysenter_hop
INTERN_FUNCTION(__asm32_sysenter_hop)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000001
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_hop)

.section .text.x86.asm32_syscall_sysenter.hopf
	/* syscall_slong_t hopf(fd_t fd,
	 *                      syscall_ulong_t command,
	 *                      iomode_t mode,
	 *                      void *arg) */
	.weak __asm32_sysenter_hopf
INTERN_FUNCTION(__asm32_sysenter_hopf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000002
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_hopf)

.section .text.x86.asm32_syscall_sysenter.readf
	/* ssize_t readf(fd_t fd,
	 *               void *buf,
	 *               size_t bufsize,
	 *               iomode_t mode) */
	.weak __asm32_sysenter_readf
INTERN_FUNCTION(__asm32_sysenter_readf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000003
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_readf)

.section .text.x86.asm32_syscall_sysenter.writef
	/* ssize_t writef(fd_t fd,
	 *                void const *buf,
	 *                size_t bufsize,
	 *                iomode_t mode) */
	.weak __asm32_sysenter_writef
INTERN_FUNCTION(__asm32_sysenter_writef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000004
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_writef)

/* >> detach(2)
 * Detach the descriptor of `PID' from the thread that
 * would have received a signal when it changes state,
 * as well as prevent the thread from turning into a
 * zombie once it dies.
 * For simplicity, think of it like this:
 *   - pthread_create()  -->  clone()
 *   - pthread_join()    -->  wait()
 *   - pthread_detach()  -->  detach()  // Linux's missing link, now implemented
 * A total of 4 special cases exists to alter the behavior of this function:
 *   - PID == 0 || PID == gettid():
 *     Detach the calling thread from the set of running children within
 *     its own process. Note however that when this is done by the main
 *     thread of the process, gettid() will equal getpid(), and the behavior
 *     will be different.
 *   - PID == getpid():
 *     Detach the calling process from its parent, essentially daemonizing
 *     the calling process the same way a double-fork would:
 *     >> if (fork() == 0) {
 *     >> 	if (fork() == 0) {
 *     >> 		// This is a daemonized process
 *     >> 		// aka. the parent process no longer knows
 *     >> 		// about us, and also can't wait(2) on us.
 *     >> 		...
 *     >> 	}
 *     >> 	exit(0);
 *     >> }
 *     Same as:
 *     >> if (fork() == 0) {
 *     >> 	detach(0); // or `detach(getpid())', since 0 --> gettid() and gettid() == getpid()
 *     >> 	// This is a daemonized process
 *     >> 	// aka. the parent process no longer knows
 *     >> 	// about us, and also can't wait(2) on us.
 *     >> 	...
 *     >> }
 *   - PID == -1:
 *     Detach all child processes/threads of the calling process, essentially
 *     turning its chain of children into a clean slate that no longer contains
 *     any wait(2)able child threads or processes.
 *     If no waitable children existed, `ECHILD' is set; else `0' is returned.
 * Before any of this is done, the thread referred to by `PID' is one of the following:
 *   - The leader of the process that called `fork()' or `clone()' without
 *    `CLONE_PARENT' to create the thread referred to by `PID'
 *   - The creator of the process containing a thread that called
 *    `clone()' with `CLONE_PARENT', which then created the thread
 *     referred to by `PID'.
 *   - Even if the thread doesn't deliver a signal upon it terminating,
 *     the process that would have received such a signal is still relevant.
 *   -> In other words: The thread `PID' must be one of your children,
 *                      or you had to have been assigned as its child.
 * If the calling thread isn't part of that process that will receive
 * the signal if the thread dies without being detached first, then
 * the call fails by throwing an `E_ILLEGAL_OPERATION'.
 * If the thread had already been detached, then the call fails by
 * throwing an `E_ILLEGAL_OPERATION' as well.
 * Upon success, the thread referred to by `PID' will clean up its own
 * PID descriptor without the need of anyone to wait() for it, a behavior
 * that linux implements using `CLONE_THREAD' (which you shouldn't use,
 * because it's flawed by design)
 * Once detached, any further use of PID results in a race condition
 * (which linux neglects to mention for `CLONE_THREAD'), because there
 * is no way of ensuring that PID still refers to the original thread,
 * as another thread may have been created using the same PID, after
 * the detached thread exited.
 * NOTE: If a thread is crated using clone() with `CLONE_DETACHED' set,
 *       it will behave effectively as though this function had already
 *       be called.
 * NOTE: If the thread already has terminated, detaching it will kill
 *       its zombie the same way wait() would.
 * NOTE: Passing ZERO(0) for `PID' will detach the calling thread.
 *       However, this operation fails if the calling thread isn't
 *       part of the same process as the parent process of the thread.
 *       In other words, the child of a fork() can't do this, and
 *       neither can the spawnee of clone(CLONE_THREAD|CLONE_PARENT),
 *       clone(0) or clone(CLONE_PARENT).
 * @return: -EPERM:             The calling process isn't the recipient of signals
 *                              delivered when `PID' changes state. This can either
 *                              be because `PID' has already been detached, or because
 *                              YOU CAN'T DETACH SOMEONE ELSE'S THREAD!
 *                              Another possibility is that the thread was already
 *                              detached, then exited, following which a new thread
 *                              got created and had been assigned the PID of your
 *                              ancient, no longer existent thread.
 * @return: -ECHILD:           `PID' was equal to `-1', but no waitable children existed
 * @throw: E_PROCESS_EXITED:    The process referred to by `PID' doesn't exist.
 *                              This could mean that it had already been detached
 *                              and exited, or that the `PID' is just invalid (which
 *                              would also be the case if it was valid at some point) */
.section .text.x86.asm32_syscall_sysenter.detach
	/* errno_t detach(pid_t pid) */
	.weak __asm32_sysenter_detach
INTERN_FUNCTION(__asm32_sysenter_detach)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000005
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_detach)

/* Returns a bitset of all of the currently mounted dos-drives */
.section .text.x86.asm32_syscall_sysenter.getdrives
	/* syscall_slong_t getdrives(void); */
	.weak __asm32_sysenter_getdrives
INTERN_FUNCTION(__asm32_sysenter_getdrives)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000006
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getdrives)

/* You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.frealpath4
	/* ssize_t frealpath4(fd_t fd,
	 *                    char *buf,
	 *                    size_t buflen,
	 *                    atflag_t flags) */
	.weak __asm32_sysenter_frealpath4
INTERN_FUNCTION(__asm32_sysenter_frealpath4)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000007
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_frealpath4)

/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is dereferenced,
 * causing the pointed-to file location to be retrieved. - Otherwise, the
 * location of the link is printed instead.
 * You may pass `AT_READLINK_REQSIZE' to always have the function return
 * the required buffer size, rather than the used size.
 * @param: flags: Set of `0|AT_ALTPATH|AT_SYMLINK_NOFOLLOW|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.frealpathat
	/* ssize_t frealpathat(fd_t dirfd,
	 *                     char const *filename,
	 *                     char *buf,
	 *                     size_t buflen,
	 *                     atflag_t flags) */
	.weak __asm32_sysenter_frealpathat
INTERN_FUNCTION(__asm32_sysenter_frealpathat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000008
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_frealpathat)

/* Schedule an RPC for execution on the specified `target' thread.
 * @param: target:    The targeted thread.
 * @param: flags:     RPC flags (one of `RPC_SCHEDULE_*', or'd with a set of `RPC_SCHEDULE_FLAG_*')
 * @param: program:   An RPC loader program (vector of `RPC_PROGRAM_OP_*')
 * @param: arguments: Arguments for the RPC loader program.
 * @return: 1:  The specified `target' thread has already terminated.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno')
 * @throws: E_PROCESS_EXITED:  `target' does not reference a valid process
 * @throws: E_INVALID_ARGUMENT: The given `flag' is invalid. */
.section .text.x86.asm32_syscall_sysenter.rpc_schedule
	/* syscall_slong_t rpc_schedule(pid_t target,
	 *                              syscall_ulong_t flags,
	 *                              uint8_t const *program,
	 *                              void **arguments) */
	.weak __asm32_sysenter_rpc_schedule
INTERN_FUNCTION(__asm32_sysenter_rpc_schedule)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000009
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rpc_schedule)

.section .text.x86.asm32_syscall_sysenter.sysctl
	/* syscall_slong_t sysctl(syscall_ulong_t command,
	 *                        void *arg) */
	.weak __asm32_sysenter_sysctl
INTERN_FUNCTION(__asm32_sysenter_sysctl)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000000a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sysctl)

/* Create a new pseudo-terminal driver and store handles to both the master and slave ends of the connection in the given pointers. */
.section .text.x86.asm32_syscall_sysenter.openpty
	/* errno_t openpty(fd_t *amaster,
	 *                 fd_t *aslave,
	 *                 char *name,
	 *                 struct termios const *termp,
	 *                 struct winsize const *winp) */
	.weak __asm32_sysenter_openpty
INTERN_FUNCTION(__asm32_sysenter_openpty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000000b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_openpty)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.fchdirat
	/* errno_t fchdirat(fd_t dirfd,
	 *                  char const *path,
	 *                  atflag_t flags) */
	.weak __asm32_sysenter_fchdirat
INTERN_FUNCTION(__asm32_sysenter_fchdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000000c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fchdirat)

.section .text.x86.asm32_syscall_sysenter.time64
	/* time64_t time64(time64_t *timer) */
	.weak __asm32_sysenter_time64
INTERN_FUNCTION(__asm32_sysenter_time64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000000d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_time64)

/* Set the exception handler mode for the calling thread.
 * Examples:
 *   Set mode #3 from you `main()': `set_exception_handler(EXCEPT_HANDLER_MODE_SIGHAND,NULL,NULL)'
 *   Configure mode #2 in libc:     `set_exception_handler(EXCEPT_HANDLER_MODE_ENABLED | EXCEPT_HANDLER_FLAG_SETHANDLER,&kernel_except_handler,NULL)'
 * @param: MODE:       One of `EXCEPT_HANDLER_MODE_*', optionally or'd with `EXCEPT_HANDLER_FLAG_*'
 * @param: HANDLER:    When `EXCEPT_HANDLER_FLAG_SETHANDLER' is set, the address of the exception handler to use
 * @param: HANDLER_SP: When `EXCEPT_HANDLER_FLAG_SETSTACK' is set, the address of the exception handler stack
 * @return: 0 :        Success.
 * @return: -1:EINVAL: The given MODE is invalid */
.section .text.x86.asm32_syscall_sysenter.set_exception_handler
	/* errno_t set_exception_handler(syscall_ulong_t mode,
	 *                               except_handler_t handler,
	 *                               void *handler_sp) */
	.weak __asm32_sysenter_set_exception_handler
INTERN_FUNCTION(__asm32_sysenter_set_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000000e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_set_exception_handler)

/* Get the current exception handler mode for the calling thread.
 * @param: PMODE:       When non-NULL, store the current mode, which is encoded as:
 *                       - One of `EXCEPT_HANDLER_MODE_(DISABLED|ENABLED|SIGHAND)'
 *                       - Or'd with a set of `EXCEPT_HANDLER_FLAG_(ONESHOT|SETHANDLER|SETSTACK)'
 * @param: PHANDLER:    The address of the user-space exception handler.
 *                      Note that when no handler has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETHANDLER)'),
 *                      then this pointer is set to `NULL'.
 * @param: PHANDLER_SP: The starting address of the user-space exception handler stack.
 *                      Note that when no stack has been set (`!(*PMODE & EXCEPT_HANDLER_FLAG_SETSTACK)'),
 *                      or when the stack was defined to re-use the previous stack,
 *                      then this pointer is set to `EXCEPT_HANDLER_SP_CURRENT'.
 * @return: 0 :         Success.
 * @return: -1:EFAULT:  One of the given pointers is non-NULL and faulty */
.section .text.x86.asm32_syscall_sysenter.get_exception_handler
	/* errno_t get_exception_handler(syscall_ulong_t *pmode,
	 *                               except_handler_t *phandler,
	 *                               void **phandler_sp) */
	.weak __asm32_sysenter_get_exception_handler
INTERN_FUNCTION(__asm32_sysenter_get_exception_handler)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000000f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_get_exception_handler)

/* Set per-vm meta-data for allowing the kernel to enumerate loaded code modules */
.section .text.x86.asm32_syscall_sysenter.set_library_listdef
	/* errno_t set_library_listdef(struct library_listdef const *listdef) */
	.weak __asm32_sysenter_set_library_listdef
INTERN_FUNCTION(__asm32_sysenter_set_library_listdef)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000010
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_set_library_listdef)

/* Trigger a debugger trap `trapno', optionally extended with `regs'
 * at either the system call return location, or at the given `state'
 * In the later case, this system call will by default return to the
 * given `state', though given the purpose of this system call being
 * to inform a connected debugger of some breakable event, allowing
 * it to do whatever it wishes before execution is resumed.
 * @param: reason:   When non-NULL, the reason for the debug trap (else: use `SIGTRAP:DEBUGTRAP_REASON_NONE')
 * @param: state:    When non-NULL, the CPU state where the trap should return to by default
 * @return: -EOK:    `state' was NULL and the trap returned successfully
 * @return: -ENOENT: No debugger is connected to the calling process/process-group/system */
.section .text.x86.asm32_syscall_sysenter.debugtrap
	/* errno_t debugtrap(struct ucpustate const *state,
	 *                   struct debugtrap_reason const *reason) */
	.weak __asm32_sysenter_debugtrap
INTERN_FUNCTION(__asm32_sysenter_debugtrap)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000011
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_debugtrap)

/* >> lfutex(2)
 * Provide the bottom-most API for implementing user-space synchronization on KOS
 * @param: futex_op: One of:
 *    - LFUTEX_WAKE:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKE, size_t val = count)
 *    - LFUTEX_WAKEMASK:           (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAKEMASK, size_t val = count, struct timespec64 const *timeout = mask_and, uintptr_t val2 = mask_or)
 *    - LFUTEX_NOP:                (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_NOP)
 *    - LFUTEX_WAIT:               (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT, uintptr_t val = ignored, struct timespec const *timeout)
 *    - LFUTEX_WAIT_LOCK:          (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_LOCK, uintptr_t val = lock_value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_UNTIL:         (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_ABOVE:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_ABOVE, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BELOW:   (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BELOW, uintptr_t val = value, struct timespec const *timeout)
 *    - LFUTEX_WAIT_WHILE_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_UNTIL_BITMASK: (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_BITMASK, uintptr_t val = bitmask, struct timespec const *timeout, uintptr_t val2 = setmask)
 *    - LFUTEX_WAIT_WHILE_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_WHILE_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 *    - LFUTEX_WAIT_UNTIL_CMPXCH:  (uintptr_t *uaddr, syscall_ulong_t futex_op = LFUTEX_WAIT_UNTIL_CMPXCH, uintptr_t val = oldval, struct timespec const *timeout, uintptr_t val2 = newval)
 * @param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @return: * : Depending on `futex_op'
 * @return: -1:EFAULT:    A faulty pointer was given
 * @throw:  E_INVALID_ARGUMENT: The given `futex_op' is invalid
 * @throw:  E_INTERRUPT:        A blocking futex-wait operation was interrupted
 * @return: -ETIMEDOUT:         A blocking futex-wait operation has timed out */
.section .text.x86.asm32_syscall_sysenter.lfutex
	/* syscall_slong_t lfutex(uintptr_t *uaddr,
	 *                        syscall_ulong_t futex_op,
	 *                        uintptr_t val,
	 *                        struct __timespec64 const *timeout,
	 *                        uintptr_t val2) */
	.weak __asm32_sysenter_lfutex
INTERN_FUNCTION(__asm32_sysenter_lfutex)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000012
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lfutex)

.section .text.x86.asm32_syscall_sysenter.lseek64
	/* int64_t lseek64(fd_t fd,
	 *                 int64_t offset,
	 *                 syscall_ulong_t whence) */
	.weak __asm32_sysenter_lseek64
INTERN_FUNCTION(__asm32_sysenter_lseek64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000013
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lseek64)

/* >> lfutexexpr(2)
 * The lfutexexpr() system call can be used to specify arbitrarily complex
 * expressions that must atomically (in relation to other futex operations)
 * hold true before the scheduler will suspend the calling thread, as well as
 * have the calling thread wait for any number of futex objects associated with
 * any address that is checked as part of the expression. (s.a. `lfutex()')
 * Notes:
 *   - This is the only futex function that can be used to wait on multiple futex
 *     objects (i.e. resume execution when `LFUTEX_WAKE' is called on _any_ of them)
 *   - For more precise control over waiting on futex objects, as well as waiting on
 *     futexes in conjunction with waiting on other things such as files, see the
 *     documentation on this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.x86.asm32_syscall_sysenter.lfutexexpr
	/* errno_t lfutexexpr(void *base,
	 *                    size_t exprc,
	 *                    struct lfutexexpr const *exprv,
	 *                    struct __timespec64 const *timeout,
	 *                    syscall_ulong_t timeout_flags) */
	.weak __asm32_sysenter_lfutexexpr
INTERN_FUNCTION(__asm32_sysenter_lfutexexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000014
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lfutexexpr)

/* >> lfutexlockexpr(2)
 * A function that is similar to `lfutexexpr()', but allows for the use of one central
 * locking futex that is used for waiting and may be distinct from any other given futex
 * object pointer.
 * Notes:
 *   - This function only has the calling thread wait on a single futex `ulockaddr',
 *     rather than having it wait on an arbitrary number of futexes, as would be the case when
 *     the `lfutexexpr()' function is used.
 *   - For more precise control over waiting on futex objects, as well as waiting on futexes
 *     in conjunction with waiting on other things such as files, see the documentation on
 *     this topic (lfutex() and select()) at the top of <kos/futex.h>
 * @param: ulockaddr:     Address of the futex lock to-be used / The futex on which to wait
 * @param: base:          Base pointer added to the `fe_offset' fields of given expressions
 * @param: exprv:         Vector of expressions for which to check
 * @param: exprc:         Number of expressions given in `exprv'
 * @param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
 * @param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
 * @return: * : The first non-zero return value from executing all of the given `exprv'
 *              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*' functions
 *              to see their possible return values, which are always `0' when they would
 *              perform a wait operation, and usually `1' otherwise) or `0' if the calling
 *              thread had to perform a wait operation, at which point this function returning
 *              that value means that you've once again been re-awoken.
 * @return: -1:EFAULT:    A faulty pointer was given
 * @return: -1:EINVAL:    One of the given commands is invalid, or `exprc' was `0'
 * @return: -1:EINTR:     A blocking futex-wait operation was interrupted
 * @return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out */
.section .text.x86.asm32_syscall_sysenter.lfutexlockexpr
	/* errno_t lfutexlockexpr(uintptr_t *ulockaddr,
	 *                        void *base,
	 *                        size_t exprc,
	 *                        struct lfutexexpr const *exprv,
	 *                        struct __timespec64 const *timeout,
	 *                        syscall_ulong_t timeout_flags) */
	.weak __asm32_sysenter_lfutexlockexpr
INTERN_FUNCTION(__asm32_sysenter_lfutexlockexpr)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000015
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_lfutexlockexpr)

/* Create and return a new tty terminal controller connected to the given keyboard and display
 * The newly created device automatically gets assigned an arbitrary device number, before
 * being made available under a file `/dev/${name}' (or rather: as ${name} within the devfs)
 * @param: reserved: Reserved set of flags (Must pass `0'; for future expansion) */
.section .text.x86.asm32_syscall_sysenter.mktty
	/* fd_t mktty(fd_t keyboard,
	 *            fd_t display,
	 *            char const *name,
	 *            syscall_ulong_t rsvd) */
	.weak __asm32_sysenter_mktty
INTERN_FUNCTION(__asm32_sysenter_mktty)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000016
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_mktty)

/* Raise a signal within the calling thread alongside the given CPU state
 * This system call is used when translating exceptions into POSIX signal in error mode #4
 * @param: state: The state state at which to raise the signal, or `NULL' if the signal should
 *                be raised for the caller's source location. Note that only in the later case
 *                will this function return to its caller. - When `state' is non-NULL, it will
 *                return to the text location described by it.
 * TODO: Add a flags argument to control if the current signal mask
 *       should be ignored (currently, it's always being ignored) */
.section .text.x86.asm32_syscall_sysenter.raiseat
	/* errno_t raiseat(struct ucpustate const *state,
	 *                 struct __siginfo_struct const *si) */
	.weak __asm32_sysenter_raiseat
INTERN_FUNCTION(__asm32_sysenter_raiseat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000017
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_raiseat)

/* Trigger a coredump of the calling process.
 * @param: curr_state:       The state as is still valid after any possible unwinding has already been done
 *                           Note that this state does not necessarily point to the location that originally
 *                           caused the problem that escalated into a coredump, but is the last valid stack-
 *                           unwind location at which unwinding could no longer continue.
 *                           When `NULL', `orig_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 * @param: orig_state:       The original CPU state at where the associated `exception' got triggered
 *                           When `NULL', `curr_state' is used instead, and `traceback_vector' and `traceback_length' are ignored.
 *                           When `curr_state' is also `NULL', then the current CPU state is used instead.
 * @param: traceback_vector: (potentially incomplete) vector of additional program pointers that were
 *                           travered when the stack was walked from `orig_state' to `curr_state'
 *                           Note that earlier entires within this vector are further up the call-stack, with
 *                           traceback_vector[0] being meant to be the call-site of the function of `orig_state'.
 *                           Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] == ucpustate_getpc(curr_state)',
 *                           it can be assumed that the traceback is complete and contains all travered instruction locations.
 *                           In this case, a traceback displayed to a human should not include the text location at
 *                           `traceback_vector[traceback_length-1]', since that location would also be printed when
 *                           unwinding is completed for the purposes of displaying a traceback.
 * @param: traceback_length: The number of program counters stored within `traceback_vector'
 * @param: exception:        The exception that resulted in the coredump (or `NULL' to get the same behavior as `E_OK')
 *                           Note that when `unwind_error == UNWIND_SUCCESS', this argument is interpreted as `siginfo_t *',
 *                           allowing coredumps to also be triggerred for unhandled signals.
 * @param: unwind_error:     The unwind error that caused the coredump, or `UNWIND_NOTHROW' if unwinding
 *                           was never actually performed, and `exception' is actually a `siginfo_t *' */
.section .text.x86.asm32_syscall_sysenter.coredump
	/* errno_t coredump(struct ucpustate const *curr_state,
	 *                  struct ucpustate const *orig_state,
	 *                  void const *const *traceback_vector,
	 *                  size_t traceback_length,
	 *                  struct exception_data const *exception,
	 *                  syscall_ulong_t unwind_error) */
	.weak __asm32_sysenter_coredump
INTERN_FUNCTION(__asm32_sysenter_coredump)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000018
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_coredump)

.section .text.x86.asm32_syscall_sysenter.stime64
	/* errno_t stime64(time64_t const *t) */
	.weak __asm32_sysenter_stime64
INTERN_FUNCTION(__asm32_sysenter_stime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000019
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_stime64)

.section .text.x86.asm32_syscall_sysenter.utime64
	/* errno_t utime64(char const *filename,
	 *                 struct utimbuf64 const *times) */
	.weak __asm32_sysenter_utime64
INTERN_FUNCTION(__asm32_sysenter_utime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000001e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_utime64)

.section .text.x86.asm32_syscall_sysenter.ioctlf
	/* syscall_slong_t ioctlf(fd_t fd,
	 *                        syscall_ulong_t command,
	 *                        iomode_t mode,
	 *                        void *arg) */
	.weak __asm32_sysenter_ioctlf
INTERN_FUNCTION(__asm32_sysenter_ioctlf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000036
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ioctlf)

.section .text.x86.asm32_syscall_sysenter.fsmode
	/* uint64_t fsmode(uint64_t mode) */
	.weak __asm32_sysenter_fsmode
INTERN_FUNCTION(__asm32_sysenter_fsmode)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000003c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fsmode)

.section .text.x86.asm32_syscall_sysenter.gettimeofday64
	/* errno_t gettimeofday64(struct __timeval64 *tv,
	 *                        struct timezone *tz) */
	.weak __asm32_sysenter_gettimeofday64
INTERN_FUNCTION(__asm32_sysenter_gettimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000004e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_gettimeofday64)

.section .text.x86.asm32_syscall_sysenter.settimeofday64
	/* errno_t settimeofday64(struct __timeval64 const *tv,
	 *                        struct timezone const *tz) */
	.weak __asm32_sysenter_settimeofday64
INTERN_FUNCTION(__asm32_sysenter_settimeofday64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000004f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_settimeofday64)

.section .text.x86.asm32_syscall_sysenter.select64
	/* ssize_t select64(size_t nfds,
	 *                  struct __fd_set_struct *readfds,
	 *                  struct __fd_set_struct *writefds,
	 *                  struct __fd_set_struct *exceptfds,
	 *                  struct __timeval64 *timeout) */
	.weak __asm32_sysenter_select64
INTERN_FUNCTION(__asm32_sysenter_select64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000052
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_select64)

/* Map the segments of a given library into memory
 * @param: addr:  Hint address (ignored unless `MAP_FIXED' is passed)
 * @param: flags: Set of `MAP_FIXED|MAP_LOCKED|MAP_NONBLOCK|
 *                       MAP_NORESERVE|MAP_POPULATE|MAP_SYNC|MAP_DONT_MAP|
 *                       MAP_DONT_OVERRIDE'
 * @param: fd:    A handle for the library file being mapped
 *                (must be a file or vm_datablock/inode)
 * @param: hdrv:  Pointer to a vector of `Elf32_Phdr' or `Elf64_Phdr'
 *                (depending on the caller running in 32- or 64-bit mode)
 * @param: hdrc:  The number of program headers */
.section .text.x86.asm32_syscall_sysenter.maplibrary
	/* void *maplibrary(void *addr,
	 *                  syscall_ulong_t flags,
	 *                  fd_t fd,
	 *                  void *hdrv,
	 *                  size_t hdrc) */
	.weak __asm32_sysenter_maplibrary
INTERN_FUNCTION(__asm32_sysenter_maplibrary)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000056
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_maplibrary)

.section .text.x86.asm32_syscall_sysenter.setitimer64
	/* errno_t setitimer64(syscall_ulong_t which,
	 *                     struct __itimerval64 const *newval,
	 *                     struct __itimerval64 *oldval) */
	.weak __asm32_sysenter_setitimer64
INTERN_FUNCTION(__asm32_sysenter_setitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000068
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_setitimer64)

.section .text.x86.asm32_syscall_sysenter.getitimer64
	/* errno_t getitimer64(syscall_ulong_t which,
	 *                     struct __itimerval64 *curr_value) */
	.weak __asm32_sysenter_getitimer64
INTERN_FUNCTION(__asm32_sysenter_getitimer64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000069
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_getitimer64)

.section .text.x86.asm32_syscall_sysenter.kreaddir
	/* ssize_t kreaddir(fd_t fd,
	 *                  struct dirent *buf,
	 *                  size_t bufsize,
	 *                  syscall_ulong_t mode) */
	.weak __asm32_sysenter_kreaddir
INTERN_FUNCTION(__asm32_sysenter_kreaddir)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000008d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_kreaddir)

.section .text.x86.asm32_syscall_sysenter.readvf
	/* ssize_t readvf(fd_t fd,
	 *                struct iovec const *iovec,
	 *                size_t count,
	 *                iomode_t mode) */
	.weak __asm32_sysenter_readvf
INTERN_FUNCTION(__asm32_sysenter_readvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000091
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_readvf)

.section .text.x86.asm32_syscall_sysenter.writevf
	/* ssize_t writevf(fd_t fd,
	 *                 struct iovec const *iovec,
	 *                 size_t count,
	 *                 iomode_t mode) */
	.weak __asm32_sysenter_writevf
INTERN_FUNCTION(__asm32_sysenter_writevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000092
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_writevf)

.section .text.x86.asm32_syscall_sysenter.rpc_service
	/* syscall_slong_t rpc_service(void); */
	.weak __asm32_sysenter_rpc_service
INTERN_FUNCTION(__asm32_sysenter_rpc_service)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000009e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rpc_service)

.section .text.x86.asm32_syscall_sysenter.sched_rr_get_interval64
	/* errno_t sched_rr_get_interval64(pid_t pid,
	 *                                 struct __timespec64 *tms) */
	.weak __asm32_sysenter_sched_rr_get_interval64
INTERN_FUNCTION(__asm32_sysenter_sched_rr_get_interval64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc00000a1
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_sched_rr_get_interval64)

.section .text.x86.asm32_syscall_sysenter.nanosleep64
	/* errno_t nanosleep64(struct __timespec64 const *req,
	 *                     struct __timespec64 *rem) */
	.weak __asm32_sysenter_nanosleep64
INTERN_FUNCTION(__asm32_sysenter_nanosleep64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc00000a2
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_nanosleep64)

.section .text.x86.asm32_syscall_sysenter.rt_sigtimedwait64
	/* syscall_slong_t rt_sigtimedwait64(struct __sigset_struct const *set,
	 *                                   struct __siginfo_struct *info,
	 *                                   struct __timespec64 const *timeout,
	 *                                   size_t sigsetsize) */
	.weak __asm32_sysenter_rt_sigtimedwait64
INTERN_FUNCTION(__asm32_sysenter_rt_sigtimedwait64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc00000b1
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_rt_sigtimedwait64)

.section .text.x86.asm32_syscall_sysenter.pread64f
	/* ssize_t pread64f(fd_t fd,
	 *                  void *buf,
	 *                  size_t bufsize,
	 *                  uint64_t offset,
	 *                  iomode_t mode) */
	.weak __asm32_sysenter_pread64f
INTERN_FUNCTION(__asm32_sysenter_pread64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc00000b4
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pread64f)

.section .text.x86.asm32_syscall_sysenter.pwrite64f
	/* ssize_t pwrite64f(fd_t fd,
	 *                   void const *buf,
	 *                   size_t bufsize,
	 *                   uint64_t offset,
	 *                   iomode_t mode) */
	.weak __asm32_sysenter_pwrite64f
INTERN_FUNCTION(__asm32_sysenter_pwrite64f)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc00000b5
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pwrite64f)

.section .text.x86.asm32_syscall_sysenter.kstat
	/* errno_t kstat(char const *filename,
	 *               struct stat *statbuf) */
	.weak __asm32_sysenter_kstat
INTERN_FUNCTION(__asm32_sysenter_kstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc00000c3
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_kstat)

.section .text.x86.asm32_syscall_sysenter.klstat
	/* errno_t klstat(char const *filename,
	 *                struct stat *statbuf) */
	.weak __asm32_sysenter_klstat
INTERN_FUNCTION(__asm32_sysenter_klstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc00000c4
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_klstat)

.section .text.x86.asm32_syscall_sysenter.kfstat
	/* errno_t kfstat(fd_t fd,
	 *                struct stat *statbuf) */
	.weak __asm32_sysenter_kfstat
INTERN_FUNCTION(__asm32_sysenter_kfstat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc00000c5
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_kfstat)

.section .text.x86.asm32_syscall_sysenter.kreaddirf
	/* ssize_t kreaddirf(fd_t fd,
	 *                   struct dirent *buf,
	 *                   size_t bufsize,
	 *                   syscall_ulong_t mode,
	 *                   iomode_t iomode) */
	.weak __asm32_sysenter_kreaddirf
INTERN_FUNCTION(__asm32_sysenter_kreaddirf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc00000dc
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_kreaddirf)

.section .text.x86.asm32_syscall_sysenter.timer_settime64
	/* errno_t timer_settime64(timer_t timerid,
	 *                         syscall_ulong_t flags,
	 *                         struct __itimerspec64 const *value,
	 *                         struct __itimerspec64 *ovalue) */
	.weak __asm32_sysenter_timer_settime64
INTERN_FUNCTION(__asm32_sysenter_timer_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000104
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timer_settime64)

.section .text.x86.asm32_syscall_sysenter.timer_gettime64
	/* errno_t timer_gettime64(timer_t timerid,
	 *                         struct __itimerspec64 *value) */
	.weak __asm32_sysenter_timer_gettime64
INTERN_FUNCTION(__asm32_sysenter_timer_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000105
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timer_gettime64)

.section .text.x86.asm32_syscall_sysenter.clock_settime64
	/* errno_t clock_settime64(clockid_t clock_id,
	 *                         struct __timespec64 const *tp) */
	.weak __asm32_sysenter_clock_settime64
INTERN_FUNCTION(__asm32_sysenter_clock_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000108
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_clock_settime64)

.section .text.x86.asm32_syscall_sysenter.clock_gettime64
	/* errno_t clock_gettime64(clockid_t clock_id,
	 *                         struct __timespec64 *tp) */
	.weak __asm32_sysenter_clock_gettime64
INTERN_FUNCTION(__asm32_sysenter_clock_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000109
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_clock_gettime64)

.section .text.x86.asm32_syscall_sysenter.clock_getres64
	/* errno_t clock_getres64(clockid_t clock_id,
	 *                        struct __timespec64 *res) */
	.weak __asm32_sysenter_clock_getres64
INTERN_FUNCTION(__asm32_sysenter_clock_getres64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000010a
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_clock_getres64)

.section .text.x86.asm32_syscall_sysenter.clock_nanosleep64
	/* errno_t clock_nanosleep64(clockid_t clock_id,
	 *                           syscall_ulong_t flags,
	 *                           struct __timespec64 const *requested_time,
	 *                           struct __timespec64 *remaining) */
	.weak __asm32_sysenter_clock_nanosleep64
INTERN_FUNCTION(__asm32_sysenter_clock_nanosleep64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000010b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_clock_nanosleep64)

.section .text.x86.asm32_syscall_sysenter.utimes64
	/* errno_t utimes64(char const *filename,
	 *                  [2] struct __timeval64 const *times) */
	.weak __asm32_sysenter_utimes64
INTERN_FUNCTION(__asm32_sysenter_utimes64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000010f
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_utimes64)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.fmkdirat
	/* errno_t fmkdirat(fd_t dirfd,
	 *                  char const *pathname,
	 *                  mode_t mode,
	 *                  atflag_t flags) */
	.weak __asm32_sysenter_fmkdirat
INTERN_FUNCTION(__asm32_sysenter_fmkdirat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000128
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fmkdirat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.fmknodat
	/* errno_t fmknodat(fd_t dirfd,
	 *                  char const *nodename,
	 *                  mode_t mode,
	 *                  dev_t dev,
	 *                  atflag_t flags) */
	.weak __asm32_sysenter_fmknodat
INTERN_FUNCTION(__asm32_sysenter_fmknodat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000129
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fmknodat)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.futimesat64
	/* errno_t futimesat64(fd_t dirfd,
	 *                     const char *filename,
	 *                     [2-3] struct __timeval64 const *times) */
	.weak __asm32_sysenter_futimesat64
INTERN_FUNCTION(__asm32_sysenter_futimesat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000012b
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_futimesat64)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.kfstatat
	/* errno_t kfstatat(fd_t dirfd,
	 *                  char const *filename,
	 *                  struct stat *statbuf,
	 *                  atflag_t flags) */
	.weak __asm32_sysenter_kfstatat
INTERN_FUNCTION(__asm32_sysenter_kfstatat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000012c
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_kfstatat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.frenameat
	/* errno_t frenameat(fd_t oldfd,
	 *                   char const *oldname,
	 *                   fd_t newfd,
	 *                   char const *newname_or_path,
	 *                   atflag_t flags) */
	.weak __asm32_sysenter_frenameat
INTERN_FUNCTION(__asm32_sysenter_frenameat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000012e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_frenameat)

/* @param: flags: Set of `0|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.fsymlinkat
	/* errno_t fsymlinkat(char const *link_text,
	 *                    fd_t tofd,
	 *                    char const *target_path,
	 *                    atflag_t flags) */
	.weak __asm32_sysenter_fsymlinkat
INTERN_FUNCTION(__asm32_sysenter_fsymlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000130
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fsymlinkat)

/* @param: flags: Set of `0|AT_READLINK_REQSIZE|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.freadlinkat
	/* ssize_t freadlinkat(fd_t dirfd,
	 *                     char const *path,
	 *                     char *buf,
	 *                     size_t buflen,
	 *                     atflag_t flags) */
	.weak __asm32_sysenter_freadlinkat
INTERN_FUNCTION(__asm32_sysenter_freadlinkat)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000131
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_freadlinkat)

.section .text.x86.asm32_syscall_sysenter.pselect6_64
	/* ssize_t pselect6_64(size_t nfds,
	 *                     struct __fd_set_struct *readfds,
	 *                     struct __fd_set_struct *writefds,
	 *                     struct __fd_set_struct *exceptfds,
	 *                     struct __timespec64 const *timeout,
	 *                     void const *sigmask_sigset_and_len) */
	.weak __asm32_sysenter_pselect6_64
INTERN_FUNCTION(__asm32_sysenter_pselect6_64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000134
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pselect6_64)

.section .text.x86.asm32_syscall_sysenter.ppoll64
	/* ssize_t ppoll64(struct pollfd *fds,
	 *                 size_t nfds,
	 *                 struct __timespec64 const *timeout_ts,
	 *                 struct __sigset_struct const *sigmask,
	 *                 size_t sigsetsize) */
	.weak __asm32_sysenter_ppoll64
INTERN_FUNCTION(__asm32_sysenter_ppoll64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000135
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_ppoll64)

/* @param: flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
.section .text.x86.asm32_syscall_sysenter.utimensat64
	/* errno_t utimensat64(fd_t dirfd,
	 *                     char const *filename,
	 *                     [2-3] struct __timespec64 const *times,
	 *                     atflag_t flags) */
	.weak __asm32_sysenter_utimensat64
INTERN_FUNCTION(__asm32_sysenter_utimensat64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000140
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_utimensat64)

.section .text.x86.asm32_syscall_sysenter.fallocate64
	/* errno_t fallocate64(fd_t fd,
	 *                     syscall_ulong_t mode,
	 *                     uint64_t offset,
	 *                     uint64_t length) */
	.weak __asm32_sysenter_fallocate64
INTERN_FUNCTION(__asm32_sysenter_fallocate64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000144
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_fallocate64)

/* Set next expiration time of interval timer source UFD to UTMR.
 * If FLAGS has the TFD_TIMER_ABSTIME flag set the timeout value
 * is absolute. Optionally return the old expiration time in OTMR */
.section .text.x86.asm32_syscall_sysenter.timerfd_settime64
	/* errno_t timerfd_settime64(fd_t ufd,
	 *                           syscall_ulong_t flags,
	 *                           struct __itimerspec64 const *utmr,
	 *                           struct __itimerspec64 *otmr) */
	.weak __asm32_sysenter_timerfd_settime64
INTERN_FUNCTION(__asm32_sysenter_timerfd_settime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000145
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timerfd_settime64)

/* Return the next expiration time of UFD */
.section .text.x86.asm32_syscall_sysenter.timerfd_gettime64
	/* errno_t timerfd_gettime64(fd_t ufd,
	 *                           struct __itimerspec64 *otmr) */
	.weak __asm32_sysenter_timerfd_gettime64
INTERN_FUNCTION(__asm32_sysenter_timerfd_gettime64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000146
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_timerfd_gettime64)

.section .text.x86.asm32_syscall_sysenter.preadvf
	/* ssize_t preadvf(fd_t fd,
	 *                 struct iovec const *iovec,
	 *                 size_t count,
	 *                 uint64_t offset,
	 *                 iomode_t mode) */
	.weak __asm32_sysenter_preadvf
INTERN_FUNCTION(__asm32_sysenter_preadvf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000014d
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_preadvf)

.section .text.x86.asm32_syscall_sysenter.pwritevf
	/* ssize_t pwritevf(fd_t fd,
	 *                  struct iovec const *iovec,
	 *                  size_t count,
	 *                  uint64_t offset,
	 *                  iomode_t mode) */
	.weak __asm32_sysenter_pwritevf
INTERN_FUNCTION(__asm32_sysenter_pwritevf)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc000014e
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_pwritevf)

.section .text.x86.asm32_syscall_sysenter.recvmmsg64
	/* ssize_t recvmmsg64(fd_t sockfd,
	 *                    struct mmsghdr *vmessages,
	 *                    size_t vlen,
	 *                    syscall_ulong_t flags,
	 *                    struct __timespec64 *tmo) */
	.weak __asm32_sysenter_recvmmsg64
INTERN_FUNCTION(__asm32_sysenter_recvmmsg64)
	.cfi_startproc simple
	.cfi_personality 0, x86_syscall_personality
	.cfi_lsda 0, 0xc0000151
	.cfi_iret_signal_frame
	/* TODO: print_x64_386sysenter_wrapper() */
	.cfi_endproc
END(__asm32_sysenter_recvmmsg64)

