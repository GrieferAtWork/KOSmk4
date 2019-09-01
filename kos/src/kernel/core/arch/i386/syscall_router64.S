/* HASH 0xd4bf69ff */
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
#include <asm/cfi.h>
#include <asm/cpu-flags.h>
#include <sys/syscall.h>
#include <kos/kernel/cpu-state.h>
#include <errno.h>


INTERN(__asm32_int80_invalid)
INTERN(__asm32_sysenter_invalid)
INTERN(__asm64_syscall_invalid)



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
EXTERN(sys32_timerfd_create)
EXTERN(sys32_eventfd)
EXTERN(sys32_fallocate)
EXTERN(sys32_timerfd_settime)
EXTERN(sys32_timerfd_gettime)
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
EXTERN(sys32_lfutexlock)
EXTERN(sys32_lfutexexpr)
EXTERN(sys32_lfutexlockexpr)
EXTERN(sys32_mktty)
EXTERN(sys32_raiseat)
EXTERN(sys32_stime64)
EXTERN(sys32_coredump)
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
EXTERN(sys_timerfd_create)
EXTERN(sys_eventfd)
EXTERN(sys_fallocate)
EXTERN(sys_timerfd_settime)
EXTERN(sys_timerfd_gettime)
EXTERN(sys_accept4)
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
EXTERN(sys_lfutexlock)
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



INTERN(__asm64_syscall_read)
INTERN(__asm64_syscall_write)
INTERN(__asm64_syscall_open)
INTERN(__asm64_syscall_close)
INTERN(__asm64_syscall_linux_stat64)
INTERN(__asm64_syscall_linux_fstat64)
INTERN(__asm64_syscall_linux_lstat64)
INTERN(__asm64_syscall_poll)
INTERN(__asm64_syscall_lseek64)
INTERN(__asm64_syscall_mmap)
INTERN(__asm64_syscall_mprotect)
INTERN(__asm64_syscall_munmap)
INTERN(__asm64_syscall_brk)
INTERN(__asm64_syscall_rt_sigaction)
INTERN(__asm64_syscall_rt_sigprocmask)
INTERN(__asm64_syscall_rt_sigreturn)
INTERN(__asm64_syscall_ioctl)
INTERN(__asm64_syscall_pread64)
INTERN(__asm64_syscall_pwrite64)
INTERN(__asm64_syscall_readv)
INTERN(__asm64_syscall_writev)
INTERN(__asm64_syscall_access)
INTERN(__asm64_syscall_pipe)
INTERN(__asm64_syscall_select)
INTERN(__asm64_syscall_sched_yield)
INTERN(__asm64_syscall_mremap)
INTERN(__asm64_syscall_msync)
INTERN(__asm64_syscall_mincore)
INTERN(__asm64_syscall_madvise)
INTERN(__asm64_syscall_dup)
INTERN(__asm64_syscall_dup2)
INTERN(__asm64_syscall_pause)
INTERN(__asm64_syscall_nanosleep)
INTERN(__asm64_syscall_getitimer)
INTERN(__asm64_syscall_alarm)
INTERN(__asm64_syscall_setitimer)
INTERN(__asm64_syscall_getpid)
INTERN(__asm64_syscall_sendfile)
INTERN(__asm64_syscall_socket)
INTERN(__asm64_syscall_connect)
INTERN(__asm64_syscall_sendto)
INTERN(__asm64_syscall_recvfrom)
INTERN(__asm64_syscall_sendmsg)
INTERN(__asm64_syscall_recvmsg)
INTERN(__asm64_syscall_shutdown)
INTERN(__asm64_syscall_bind)
INTERN(__asm64_syscall_listen)
INTERN(__asm64_syscall_getsockname)
INTERN(__asm64_syscall_getpeername)
INTERN(__asm64_syscall_socketpair)
INTERN(__asm64_syscall_setsockopt)
INTERN(__asm64_syscall_getsockopt)
INTERN(__asm64_syscall_clone)
INTERN(__asm64_syscall_fork)
INTERN(__asm64_syscall_vfork)
INTERN(__asm64_syscall_execve)
INTERN(__asm64_syscall_exit)
INTERN(__asm64_syscall_wait4)
INTERN(__asm64_syscall_kill)
INTERN(__asm64_syscall_uname)
INTERN(__asm64_syscall_fcntl)
INTERN(__asm64_syscall_flock)
INTERN(__asm64_syscall_fsync)
INTERN(__asm64_syscall_fdatasync)
INTERN(__asm64_syscall_truncate)
INTERN(__asm64_syscall_ftruncate)
INTERN(__asm64_syscall_getdents)
INTERN(__asm64_syscall_getcwd)
INTERN(__asm64_syscall_chdir)
INTERN(__asm64_syscall_fchdir)
INTERN(__asm64_syscall_rename)
INTERN(__asm64_syscall_mkdir)
INTERN(__asm64_syscall_rmdir)
INTERN(__asm64_syscall_creat)
INTERN(__asm64_syscall_link)
INTERN(__asm64_syscall_unlink)
INTERN(__asm64_syscall_symlink)
INTERN(__asm64_syscall_readlink)
INTERN(__asm64_syscall_chmod)
INTERN(__asm64_syscall_fchmod)
INTERN(__asm64_syscall_chown)
INTERN(__asm64_syscall_fchown)
INTERN(__asm64_syscall_lchown)
INTERN(__asm64_syscall_umask)
INTERN(__asm64_syscall_gettimeofday)
INTERN(__asm64_syscall_getrlimit)
INTERN(__asm64_syscall_getrusage)
INTERN(__asm64_syscall_sysinfo)
INTERN(__asm64_syscall_times)
INTERN(__asm64_syscall_ptrace)
INTERN(__asm64_syscall_getuid32)
INTERN(__asm64_syscall_syslog)
INTERN(__asm64_syscall_getgid32)
INTERN(__asm64_syscall_setuid32)
INTERN(__asm64_syscall_setgid32)
INTERN(__asm64_syscall_geteuid32)
INTERN(__asm64_syscall_getegid32)
INTERN(__asm64_syscall_setpgid)
INTERN(__asm64_syscall_getppid)
INTERN(__asm64_syscall_getpgrp)
INTERN(__asm64_syscall_setsid)
INTERN(__asm64_syscall_setreuid32)
INTERN(__asm64_syscall_setregid32)
INTERN(__asm64_syscall_getgroups32)
INTERN(__asm64_syscall_setgroups32)
INTERN(__asm64_syscall_setresuid32)
INTERN(__asm64_syscall_getresuid32)
INTERN(__asm64_syscall_setresgid32)
INTERN(__asm64_syscall_getresgid32)
INTERN(__asm64_syscall_getpgid)
INTERN(__asm64_syscall_setfsuid32)
INTERN(__asm64_syscall_setfsgid32)
INTERN(__asm64_syscall_getsid)
INTERN(__asm64_syscall_rt_sigpending)
INTERN(__asm64_syscall_rt_sigtimedwait)
INTERN(__asm64_syscall_rt_sigqueueinfo)
INTERN(__asm64_syscall_rt_sigsuspend)
INTERN(__asm64_syscall_sigaltstack)
INTERN(__asm64_syscall_utime)
INTERN(__asm64_syscall_mknod)
INTERN(__asm64_syscall_ustat)
INTERN(__asm64_syscall_statfs)
INTERN(__asm64_syscall_fstatfs)
INTERN(__asm64_syscall_getpriority)
INTERN(__asm64_syscall_setpriority)
INTERN(__asm64_syscall_sched_setparam)
INTERN(__asm64_syscall_sched_getparam)
INTERN(__asm64_syscall_sched_setscheduler)
INTERN(__asm64_syscall_sched_getscheduler)
INTERN(__asm64_syscall_sched_get_priority_max)
INTERN(__asm64_syscall_sched_get_priority_min)
INTERN(__asm64_syscall_sched_rr_get_interval)
INTERN(__asm64_syscall_mlock)
INTERN(__asm64_syscall_munlock)
INTERN(__asm64_syscall_mlockall)
INTERN(__asm64_syscall_munlockall)
INTERN(__asm64_syscall_vhangup)
INTERN(__asm64_syscall_modify_ldt)
INTERN(__asm64_syscall_setrlimit)
INTERN(__asm64_syscall_chroot)
INTERN(__asm64_syscall_sync)
INTERN(__asm64_syscall_acct)
INTERN(__asm64_syscall_settimeofday)
INTERN(__asm64_syscall_mount)
INTERN(__asm64_syscall_umount2)
INTERN(__asm64_syscall_swapon)
INTERN(__asm64_syscall_swapoff)
INTERN(__asm64_syscall_reboot)
INTERN(__asm64_syscall_sethostname)
INTERN(__asm64_syscall_setdomainname)
INTERN(__asm64_syscall_iopl)
INTERN(__asm64_syscall_ioperm)
INTERN(__asm64_syscall_gettid)
INTERN(__asm64_syscall_readahead)
INTERN(__asm64_syscall_setxattr)
INTERN(__asm64_syscall_lsetxattr)
INTERN(__asm64_syscall_fsetxattr)
INTERN(__asm64_syscall_getxattr)
INTERN(__asm64_syscall_lgetxattr)
INTERN(__asm64_syscall_fgetxattr)
INTERN(__asm64_syscall_listxattr)
INTERN(__asm64_syscall_llistxattr)
INTERN(__asm64_syscall_flistxattr)
INTERN(__asm64_syscall_removexattr)
INTERN(__asm64_syscall_lremovexattr)
INTERN(__asm64_syscall_fremovexattr)
INTERN(__asm64_syscall_tkill)
INTERN(__asm64_syscall_time)
INTERN(__asm64_syscall_futex)
INTERN(__asm64_syscall_sched_setaffinity)
INTERN(__asm64_syscall_sched_getaffinity)
INTERN(__asm64_syscall_epoll_create)
INTERN(__asm64_syscall_epoll_ctl_old)
INTERN(__asm64_syscall_epoll_wait_old)
INTERN(__asm64_syscall_remap_file_pages)
INTERN(__asm64_syscall_getdents64)
INTERN(__asm64_syscall_set_tid_address)
INTERN(__asm64_syscall_timer_create)
INTERN(__asm64_syscall_timer_settime)
INTERN(__asm64_syscall_timer_gettime)
INTERN(__asm64_syscall_timer_getoverrun)
INTERN(__asm64_syscall_timer_delete)
INTERN(__asm64_syscall_clock_settime)
INTERN(__asm64_syscall_clock_gettime)
INTERN(__asm64_syscall_clock_getres)
INTERN(__asm64_syscall_clock_nanosleep)
INTERN(__asm64_syscall_exit_group)
INTERN(__asm64_syscall_epoll_wait)
INTERN(__asm64_syscall_epoll_ctl)
INTERN(__asm64_syscall_tgkill)
INTERN(__asm64_syscall_utimes)
INTERN(__asm64_syscall_waitid)
INTERN(__asm64_syscall_ioprio_set)
INTERN(__asm64_syscall_ioprio_get)
INTERN(__asm64_syscall_openat)
INTERN(__asm64_syscall_mkdirat)
INTERN(__asm64_syscall_mknodat)
INTERN(__asm64_syscall_fchownat)
INTERN(__asm64_syscall_futimesat)
INTERN(__asm64_syscall_fstatat)
INTERN(__asm64_syscall_unlinkat)
INTERN(__asm64_syscall_renameat)
INTERN(__asm64_syscall_linkat)
INTERN(__asm64_syscall_symlinkat)
INTERN(__asm64_syscall_readlinkat)
INTERN(__asm64_syscall_fchmodat)
INTERN(__asm64_syscall_faccessat)
INTERN(__asm64_syscall_pselect6)
INTERN(__asm64_syscall_ppoll)
INTERN(__asm64_syscall_unshare)
INTERN(__asm64_syscall_splice)
INTERN(__asm64_syscall_tee)
INTERN(__asm64_syscall_sync_file_range)
INTERN(__asm64_syscall_vmsplice)
INTERN(__asm64_syscall_utimensat)
INTERN(__asm64_syscall_epoll_pwait)
INTERN(__asm64_syscall_timerfd_create)
INTERN(__asm64_syscall_eventfd)
INTERN(__asm64_syscall_fallocate)
INTERN(__asm64_syscall_timerfd_settime)
INTERN(__asm64_syscall_timerfd_gettime)
INTERN(__asm64_syscall_accept4)
INTERN(__asm64_syscall_eventfd2)
INTERN(__asm64_syscall_epoll_create1)
INTERN(__asm64_syscall_dup3)
INTERN(__asm64_syscall_pipe2)
INTERN(__asm64_syscall_preadv)
INTERN(__asm64_syscall_pwritev)
INTERN(__asm64_syscall_rt_tgsigqueueinfo)
INTERN(__asm64_syscall_recvmmsg)
INTERN(__asm64_syscall_prlimit64)
INTERN(__asm64_syscall_name_to_handle_at)
INTERN(__asm64_syscall_open_by_handle_at)
INTERN(__asm64_syscall_syncfs)
INTERN(__asm64_syscall_sendmmsg)
INTERN(__asm64_syscall_setns)
INTERN(__asm64_syscall_getcpu)
INTERN(__asm64_syscall_process_vm_readv)
INTERN(__asm64_syscall_process_vm_writev)
INTERN(__asm64_syscall_kcmp)
INTERN(__asm64_syscall_renameat2)
INTERN(__asm64_syscall_execveat)
INTERN(__asm64_syscall_readf)
INTERN(__asm64_syscall_writef)
INTERN(__asm64_syscall_hop)
INTERN(__asm64_syscall_hopf)
INTERN(__asm64_syscall_kstat)
INTERN(__asm64_syscall_kfstat)
INTERN(__asm64_syscall_klstat)
INTERN(__asm64_syscall_detach)
INTERN(__asm64_syscall_getdrives)
INTERN(__asm64_syscall_frealpath4)
INTERN(__asm64_syscall_frealpathat)
INTERN(__asm64_syscall_rpc_schedule)
INTERN(__asm64_syscall_sysctl)
INTERN(__asm64_syscall_openpty)
INTERN(__asm64_syscall_set_exception_handler)
INTERN(__asm64_syscall_get_exception_handler)
INTERN(__asm64_syscall_ioctlf)
INTERN(__asm64_syscall_pread64f)
INTERN(__asm64_syscall_pwrite64f)
INTERN(__asm64_syscall_readvf)
INTERN(__asm64_syscall_writevf)
INTERN(__asm64_syscall_set_library_listdef)
INTERN(__asm64_syscall_debugtrap)
INTERN(__asm64_syscall_select64)
INTERN(__asm64_syscall_rpc_service)
INTERN(__asm64_syscall_lfutex)
INTERN(__asm64_syscall_lfutexlock)
INTERN(__asm64_syscall_lfutexexpr)
INTERN(__asm64_syscall_lfutexlockexpr)
INTERN(__asm64_syscall_mktty)
INTERN(__asm64_syscall_raiseat)
INTERN(__asm64_syscall_coredump)
INTERN(__asm64_syscall_getitimer64)
INTERN(__asm64_syscall_setitimer64)
INTERN(__asm64_syscall_kreaddir)
INTERN(__asm64_syscall_fchdirat)
INTERN(__asm64_syscall_fsmode)
INTERN(__asm64_syscall_gettimeofday64)
INTERN(__asm64_syscall_utime64)
INTERN(__asm64_syscall_maplibrary)
INTERN(__asm64_syscall_settimeofday64)
INTERN(__asm64_syscall_time64)
INTERN(__asm64_syscall_kreaddirf)
INTERN(__asm64_syscall_utimes64)
INTERN(__asm64_syscall_fmkdirat)
INTERN(__asm64_syscall_fmknodat)
INTERN(__asm64_syscall_futimesat64)
INTERN(__asm64_syscall_kfstatat)
INTERN(__asm64_syscall_frenameat)
INTERN(__asm64_syscall_fsymlinkat)
INTERN(__asm64_syscall_freadlinkat)
INTERN(__asm64_syscall_fallocate64)
INTERN(__asm64_syscall_preadvf)
INTERN(__asm64_syscall_pwritevf)



INTERN(__asm32_int80_exit)
INTERN(__asm32_int80_fork)
INTERN(__asm32_int80_read)
INTERN(__asm32_int80_write)
INTERN(__asm32_int80_open)
INTERN(__asm32_int80_close)
INTERN(__asm32_int80_waitpid)
INTERN(__asm32_int80_creat)
INTERN(__asm32_int80_link)
INTERN(__asm32_int80_unlink)
INTERN(__asm32_int80_execve)
INTERN(__asm32_int80_chdir)
INTERN(__asm32_int80_time)
INTERN(__asm32_int80_mknod)
INTERN(__asm32_int80_chmod)
INTERN(__asm32_int80_lchown)
INTERN(__asm32_int80_linux_oldstat)
INTERN(__asm32_int80_lseek)
INTERN(__asm32_int80_getpid)
INTERN(__asm32_int80_mount)
INTERN(__asm32_int80_umount)
INTERN(__asm32_int80_setuid)
INTERN(__asm32_int80_getuid)
INTERN(__asm32_int80_stime)
INTERN(__asm32_int80_ptrace)
INTERN(__asm32_int80_alarm)
INTERN(__asm32_int80_linux_oldfstat)
INTERN(__asm32_int80_pause)
INTERN(__asm32_int80_utime)
INTERN(__asm32_int80_access)
INTERN(__asm32_int80_nice)
INTERN(__asm32_int80_ftime)
INTERN(__asm32_int80_sync)
INTERN(__asm32_int80_kill)
INTERN(__asm32_int80_rename)
INTERN(__asm32_int80_mkdir)
INTERN(__asm32_int80_rmdir)
INTERN(__asm32_int80_dup)
INTERN(__asm32_int80_pipe)
INTERN(__asm32_int80_times)
INTERN(__asm32_int80_brk)
INTERN(__asm32_int80_setgid)
INTERN(__asm32_int80_getgid)
INTERN(__asm32_int80_signal)
INTERN(__asm32_int80_geteuid)
INTERN(__asm32_int80_getegid)
INTERN(__asm32_int80_acct)
INTERN(__asm32_int80_umount2)
INTERN(__asm32_int80_ioctl)
INTERN(__asm32_int80_fcntl)
INTERN(__asm32_int80_setpgid)
INTERN(__asm32_int80_oldolduname)
INTERN(__asm32_int80_umask)
INTERN(__asm32_int80_chroot)
INTERN(__asm32_int80_ustat)
INTERN(__asm32_int80_dup2)
INTERN(__asm32_int80_getppid)
INTERN(__asm32_int80_getpgrp)
INTERN(__asm32_int80_setsid)
INTERN(__asm32_int80_sigaction)
INTERN(__asm32_int80_sgetmask)
INTERN(__asm32_int80_ssetmask)
INTERN(__asm32_int80_setreuid)
INTERN(__asm32_int80_setregid)
INTERN(__asm32_int80_sigsuspend)
INTERN(__asm32_int80_sigpending)
INTERN(__asm32_int80_sethostname)
INTERN(__asm32_int80_setrlimit)
INTERN(__asm32_int80_getrlimit)
INTERN(__asm32_int80_getrusage)
INTERN(__asm32_int80_gettimeofday)
INTERN(__asm32_int80_settimeofday)
INTERN(__asm32_int80_getgroups)
INTERN(__asm32_int80_setgroups)
INTERN(__asm32_int80_select)
INTERN(__asm32_int80_symlink)
INTERN(__asm32_int80_linux_oldlstat)
INTERN(__asm32_int80_readlink)
INTERN(__asm32_int80_swapon)
INTERN(__asm32_int80_reboot)
INTERN(__asm32_int80_readdir)
INTERN(__asm32_int80_mmap)
INTERN(__asm32_int80_munmap)
INTERN(__asm32_int80_truncate)
INTERN(__asm32_int80_ftruncate)
INTERN(__asm32_int80_fchmod)
INTERN(__asm32_int80_fchown)
INTERN(__asm32_int80_getpriority)
INTERN(__asm32_int80_setpriority)
INTERN(__asm32_int80_profil)
INTERN(__asm32_int80_statfs)
INTERN(__asm32_int80_fstatfs)
INTERN(__asm32_int80_ioperm)
INTERN(__asm32_int80_socketcall)
INTERN(__asm32_int80_syslog)
INTERN(__asm32_int80_setitimer)
INTERN(__asm32_int80_getitimer)
INTERN(__asm32_int80_linux_stat32)
INTERN(__asm32_int80_linux_lstat32)
INTERN(__asm32_int80_linux_fstat32)
INTERN(__asm32_int80_olduname)
INTERN(__asm32_int80_iopl)
INTERN(__asm32_int80_vhangup)
INTERN(__asm32_int80_wait4)
INTERN(__asm32_int80_swapoff)
INTERN(__asm32_int80_sysinfo)
INTERN(__asm32_int80_fsync)
INTERN(__asm32_int80_sigreturn)
INTERN(__asm32_int80_clone)
INTERN(__asm32_int80_setdomainname)
INTERN(__asm32_int80_uname)
INTERN(__asm32_int80_modify_ldt)
INTERN(__asm32_int80_mprotect)
INTERN(__asm32_int80_sigprocmask)
INTERN(__asm32_int80_getpgid)
INTERN(__asm32_int80_fchdir)
INTERN(__asm32_int80_setfsuid)
INTERN(__asm32_int80_setfsgid)
INTERN(__asm32_int80__llseek)
INTERN(__asm32_int80_getdents)
INTERN(__asm32_int80_flock)
INTERN(__asm32_int80_msync)
INTERN(__asm32_int80_readv)
INTERN(__asm32_int80_writev)
INTERN(__asm32_int80_getsid)
INTERN(__asm32_int80_fdatasync)
INTERN(__asm32_int80_mlock)
INTERN(__asm32_int80_munlock)
INTERN(__asm32_int80_mlockall)
INTERN(__asm32_int80_munlockall)
INTERN(__asm32_int80_sched_setparam)
INTERN(__asm32_int80_sched_getparam)
INTERN(__asm32_int80_sched_setscheduler)
INTERN(__asm32_int80_sched_getscheduler)
INTERN(__asm32_int80_sched_yield)
INTERN(__asm32_int80_sched_get_priority_max)
INTERN(__asm32_int80_sched_get_priority_min)
INTERN(__asm32_int80_sched_rr_get_interval)
INTERN(__asm32_int80_nanosleep)
INTERN(__asm32_int80_mremap)
INTERN(__asm32_int80_setresuid)
INTERN(__asm32_int80_getresuid)
INTERN(__asm32_int80_poll)
INTERN(__asm32_int80_setresgid)
INTERN(__asm32_int80_getresgid)
INTERN(__asm32_int80_rt_sigaction)
INTERN(__asm32_int80_rt_sigprocmask)
INTERN(__asm32_int80_rt_sigpending)
INTERN(__asm32_int80_rt_sigtimedwait)
INTERN(__asm32_int80_rt_sigqueueinfo)
INTERN(__asm32_int80_rt_sigsuspend)
INTERN(__asm32_int80_pread64)
INTERN(__asm32_int80_pwrite64)
INTERN(__asm32_int80_chown)
INTERN(__asm32_int80_getcwd)
INTERN(__asm32_int80_sigaltstack)
INTERN(__asm32_int80_sendfile)
INTERN(__asm32_int80_vfork)
INTERN(__asm32_int80_mmap2)
INTERN(__asm32_int80_truncate64)
INTERN(__asm32_int80_ftruncate64)
INTERN(__asm32_int80_linux_stat64)
INTERN(__asm32_int80_linux_lstat64)
INTERN(__asm32_int80_linux_fstat64)
INTERN(__asm32_int80_lchown32)
INTERN(__asm32_int80_getuid32)
INTERN(__asm32_int80_getgid32)
INTERN(__asm32_int80_geteuid32)
INTERN(__asm32_int80_getegid32)
INTERN(__asm32_int80_setreuid32)
INTERN(__asm32_int80_setregid32)
INTERN(__asm32_int80_getgroups32)
INTERN(__asm32_int80_setgroups32)
INTERN(__asm32_int80_fchown32)
INTERN(__asm32_int80_setresuid32)
INTERN(__asm32_int80_getresuid32)
INTERN(__asm32_int80_setresgid32)
INTERN(__asm32_int80_getresgid32)
INTERN(__asm32_int80_chown32)
INTERN(__asm32_int80_setuid32)
INTERN(__asm32_int80_setgid32)
INTERN(__asm32_int80_setfsuid32)
INTERN(__asm32_int80_setfsgid32)
INTERN(__asm32_int80_mincore)
INTERN(__asm32_int80_madvise)
INTERN(__asm32_int80_getdents64)
INTERN(__asm32_int80_fcntl64)
INTERN(__asm32_int80_gettid)
INTERN(__asm32_int80_readahead)
INTERN(__asm32_int80_setxattr)
INTERN(__asm32_int80_lsetxattr)
INTERN(__asm32_int80_fsetxattr)
INTERN(__asm32_int80_getxattr)
INTERN(__asm32_int80_lgetxattr)
INTERN(__asm32_int80_fgetxattr)
INTERN(__asm32_int80_listxattr)
INTERN(__asm32_int80_llistxattr)
INTERN(__asm32_int80_flistxattr)
INTERN(__asm32_int80_removexattr)
INTERN(__asm32_int80_lremovexattr)
INTERN(__asm32_int80_fremovexattr)
INTERN(__asm32_int80_tkill)
INTERN(__asm32_int80_sendfile64)
INTERN(__asm32_int80_futex)
INTERN(__asm32_int80_sched_setaffinity)
INTERN(__asm32_int80_sched_getaffinity)
INTERN(__asm32_int80_exit_group)
INTERN(__asm32_int80_epoll_create)
INTERN(__asm32_int80_epoll_ctl)
INTERN(__asm32_int80_epoll_wait)
INTERN(__asm32_int80_remap_file_pages)
INTERN(__asm32_int80_set_tid_address)
INTERN(__asm32_int80_timer_create)
INTERN(__asm32_int80_timer_settime)
INTERN(__asm32_int80_timer_gettime)
INTERN(__asm32_int80_timer_getoverrun)
INTERN(__asm32_int80_timer_delete)
INTERN(__asm32_int80_clock_settime)
INTERN(__asm32_int80_clock_gettime)
INTERN(__asm32_int80_clock_getres)
INTERN(__asm32_int80_clock_nanosleep)
INTERN(__asm32_int80_statfs64)
INTERN(__asm32_int80_fstatfs64)
INTERN(__asm32_int80_tgkill)
INTERN(__asm32_int80_utimes)
INTERN(__asm32_int80_waitid)
INTERN(__asm32_int80_ioprio_set)
INTERN(__asm32_int80_ioprio_get)
INTERN(__asm32_int80_openat)
INTERN(__asm32_int80_mkdirat)
INTERN(__asm32_int80_mknodat)
INTERN(__asm32_int80_fchownat)
INTERN(__asm32_int80_futimesat)
INTERN(__asm32_int80_linux_fstatat64)
INTERN(__asm32_int80_unlinkat)
INTERN(__asm32_int80_renameat)
INTERN(__asm32_int80_linkat)
INTERN(__asm32_int80_symlinkat)
INTERN(__asm32_int80_readlinkat)
INTERN(__asm32_int80_fchmodat)
INTERN(__asm32_int80_faccessat)
INTERN(__asm32_int80_pselect6)
INTERN(__asm32_int80_ppoll)
INTERN(__asm32_int80_unshare)
INTERN(__asm32_int80_splice)
INTERN(__asm32_int80_sync_file_range)
INTERN(__asm32_int80_tee)
INTERN(__asm32_int80_vmsplice)
INTERN(__asm32_int80_getcpu)
INTERN(__asm32_int80_epoll_pwait)
INTERN(__asm32_int80_utimensat)
INTERN(__asm32_int80_timerfd_create)
INTERN(__asm32_int80_eventfd)
INTERN(__asm32_int80_fallocate)
INTERN(__asm32_int80_timerfd_settime)
INTERN(__asm32_int80_timerfd_gettime)
INTERN(__asm32_int80_eventfd2)
INTERN(__asm32_int80_epoll_create1)
INTERN(__asm32_int80_dup3)
INTERN(__asm32_int80_pipe2)
INTERN(__asm32_int80_preadv)
INTERN(__asm32_int80_pwritev)
INTERN(__asm32_int80_rt_tgsigqueueinfo)
INTERN(__asm32_int80_recvmmsg)
INTERN(__asm32_int80_prlimit64)
INTERN(__asm32_int80_name_to_handle_at)
INTERN(__asm32_int80_open_by_handle_at)
INTERN(__asm32_int80_syncfs)
INTERN(__asm32_int80_sendmmsg)
INTERN(__asm32_int80_setns)
INTERN(__asm32_int80_process_vm_readv)
INTERN(__asm32_int80_process_vm_writev)
INTERN(__asm32_int80_kcmp)
INTERN(__asm32_int80_renameat2)
INTERN(__asm32_int80_execveat)
INTERN(__asm32_int80_socket)
INTERN(__asm32_int80_socketpair)
INTERN(__asm32_int80_bind)
INTERN(__asm32_int80_connect)
INTERN(__asm32_int80_listen)
INTERN(__asm32_int80_accept4)
INTERN(__asm32_int80_getsockopt)
INTERN(__asm32_int80_setsockopt)
INTERN(__asm32_int80_getsockname)
INTERN(__asm32_int80_getpeername)
INTERN(__asm32_int80_sendto)
INTERN(__asm32_int80_sendmsg)
INTERN(__asm32_int80_recvfrom)
INTERN(__asm32_int80_recvmsg)
INTERN(__asm32_int80_shutdown)
INTERN(__asm32_int80_hop)
INTERN(__asm32_int80_hopf)
INTERN(__asm32_int80_readf)
INTERN(__asm32_int80_writef)
INTERN(__asm32_int80_detach)
INTERN(__asm32_int80_getdrives)
INTERN(__asm32_int80_frealpath4)
INTERN(__asm32_int80_frealpathat)
INTERN(__asm32_int80_rpc_schedule)
INTERN(__asm32_int80_sysctl)
INTERN(__asm32_int80_openpty)
INTERN(__asm32_int80_fchdirat)
INTERN(__asm32_int80_time64)
INTERN(__asm32_int80_set_exception_handler)
INTERN(__asm32_int80_get_exception_handler)
INTERN(__asm32_int80_set_library_listdef)
INTERN(__asm32_int80_debugtrap)
INTERN(__asm32_int80_lfutex)
INTERN(__asm32_int80_lseek64)
INTERN(__asm32_int80_lfutexlock)
INTERN(__asm32_int80_lfutexexpr)
INTERN(__asm32_int80_lfutexlockexpr)
INTERN(__asm32_int80_mktty)
INTERN(__asm32_int80_raiseat)
INTERN(__asm32_int80_stime64)
INTERN(__asm32_int80_coredump)
INTERN(__asm32_int80_utime64)
INTERN(__asm32_int80_ioctlf)
INTERN(__asm32_int80_fsmode)
INTERN(__asm32_int80_gettimeofday64)
INTERN(__asm32_int80_settimeofday64)
INTERN(__asm32_int80_select64)
INTERN(__asm32_int80_maplibrary)
INTERN(__asm32_int80_setitimer64)
INTERN(__asm32_int80_getitimer64)
INTERN(__asm32_int80_kreaddir)
INTERN(__asm32_int80_readvf)
INTERN(__asm32_int80_writevf)
INTERN(__asm32_int80_rpc_service)
INTERN(__asm32_int80_sched_rr_get_interval64)
INTERN(__asm32_int80_nanosleep64)
INTERN(__asm32_int80_rt_sigtimedwait64)
INTERN(__asm32_int80_pread64f)
INTERN(__asm32_int80_pwrite64f)
INTERN(__asm32_int80_kstat)
INTERN(__asm32_int80_klstat)
INTERN(__asm32_int80_kfstat)
INTERN(__asm32_int80_kreaddirf)
INTERN(__asm32_int80_timer_settime64)
INTERN(__asm32_int80_timer_gettime64)
INTERN(__asm32_int80_clock_settime64)
INTERN(__asm32_int80_clock_gettime64)
INTERN(__asm32_int80_clock_getres64)
INTERN(__asm32_int80_clock_nanosleep64)
INTERN(__asm32_int80_utimes64)
INTERN(__asm32_int80_fmkdirat)
INTERN(__asm32_int80_fmknodat)
INTERN(__asm32_int80_futimesat64)
INTERN(__asm32_int80_kfstatat)
INTERN(__asm32_int80_frenameat)
INTERN(__asm32_int80_fsymlinkat)
INTERN(__asm32_int80_freadlinkat)
INTERN(__asm32_int80_pselect6_64)
INTERN(__asm32_int80_ppoll64)
INTERN(__asm32_int80_utimensat64)
INTERN(__asm32_int80_fallocate64)
INTERN(__asm32_int80_timerfd_settime64)
INTERN(__asm32_int80_timerfd_gettime64)
INTERN(__asm32_int80_preadvf)
INTERN(__asm32_int80_pwritevf)
INTERN(__asm32_int80_recvmmsg64)



INTERN(__asm32_sysenter_exit)
INTERN(__asm32_sysenter_fork)
INTERN(__asm32_sysenter_read)
INTERN(__asm32_sysenter_write)
INTERN(__asm32_sysenter_open)
INTERN(__asm32_sysenter_close)
INTERN(__asm32_sysenter_waitpid)
INTERN(__asm32_sysenter_creat)
INTERN(__asm32_sysenter_link)
INTERN(__asm32_sysenter_unlink)
INTERN(__asm32_sysenter_execve)
INTERN(__asm32_sysenter_chdir)
INTERN(__asm32_sysenter_time)
INTERN(__asm32_sysenter_mknod)
INTERN(__asm32_sysenter_chmod)
INTERN(__asm32_sysenter_lchown)
INTERN(__asm32_sysenter_linux_oldstat)
INTERN(__asm32_sysenter_lseek)
INTERN(__asm32_sysenter_getpid)
INTERN(__asm32_sysenter_mount)
INTERN(__asm32_sysenter_umount)
INTERN(__asm32_sysenter_setuid)
INTERN(__asm32_sysenter_getuid)
INTERN(__asm32_sysenter_stime)
INTERN(__asm32_sysenter_ptrace)
INTERN(__asm32_sysenter_alarm)
INTERN(__asm32_sysenter_linux_oldfstat)
INTERN(__asm32_sysenter_pause)
INTERN(__asm32_sysenter_utime)
INTERN(__asm32_sysenter_access)
INTERN(__asm32_sysenter_nice)
INTERN(__asm32_sysenter_ftime)
INTERN(__asm32_sysenter_sync)
INTERN(__asm32_sysenter_kill)
INTERN(__asm32_sysenter_rename)
INTERN(__asm32_sysenter_mkdir)
INTERN(__asm32_sysenter_rmdir)
INTERN(__asm32_sysenter_dup)
INTERN(__asm32_sysenter_pipe)
INTERN(__asm32_sysenter_times)
INTERN(__asm32_sysenter_brk)
INTERN(__asm32_sysenter_setgid)
INTERN(__asm32_sysenter_getgid)
INTERN(__asm32_sysenter_signal)
INTERN(__asm32_sysenter_geteuid)
INTERN(__asm32_sysenter_getegid)
INTERN(__asm32_sysenter_acct)
INTERN(__asm32_sysenter_umount2)
INTERN(__asm32_sysenter_ioctl)
INTERN(__asm32_sysenter_fcntl)
INTERN(__asm32_sysenter_setpgid)
INTERN(__asm32_sysenter_oldolduname)
INTERN(__asm32_sysenter_umask)
INTERN(__asm32_sysenter_chroot)
INTERN(__asm32_sysenter_ustat)
INTERN(__asm32_sysenter_dup2)
INTERN(__asm32_sysenter_getppid)
INTERN(__asm32_sysenter_getpgrp)
INTERN(__asm32_sysenter_setsid)
INTERN(__asm32_sysenter_sigaction)
INTERN(__asm32_sysenter_sgetmask)
INTERN(__asm32_sysenter_ssetmask)
INTERN(__asm32_sysenter_setreuid)
INTERN(__asm32_sysenter_setregid)
INTERN(__asm32_sysenter_sigsuspend)
INTERN(__asm32_sysenter_sigpending)
INTERN(__asm32_sysenter_sethostname)
INTERN(__asm32_sysenter_setrlimit)
INTERN(__asm32_sysenter_getrlimit)
INTERN(__asm32_sysenter_getrusage)
INTERN(__asm32_sysenter_gettimeofday)
INTERN(__asm32_sysenter_settimeofday)
INTERN(__asm32_sysenter_getgroups)
INTERN(__asm32_sysenter_setgroups)
INTERN(__asm32_sysenter_select)
INTERN(__asm32_sysenter_symlink)
INTERN(__asm32_sysenter_linux_oldlstat)
INTERN(__asm32_sysenter_readlink)
INTERN(__asm32_sysenter_swapon)
INTERN(__asm32_sysenter_reboot)
INTERN(__asm32_sysenter_readdir)
INTERN(__asm32_sysenter_mmap)
INTERN(__asm32_sysenter_munmap)
INTERN(__asm32_sysenter_truncate)
INTERN(__asm32_sysenter_ftruncate)
INTERN(__asm32_sysenter_fchmod)
INTERN(__asm32_sysenter_fchown)
INTERN(__asm32_sysenter_getpriority)
INTERN(__asm32_sysenter_setpriority)
INTERN(__asm32_sysenter_profil)
INTERN(__asm32_sysenter_statfs)
INTERN(__asm32_sysenter_fstatfs)
INTERN(__asm32_sysenter_ioperm)
INTERN(__asm32_sysenter_socketcall)
INTERN(__asm32_sysenter_syslog)
INTERN(__asm32_sysenter_setitimer)
INTERN(__asm32_sysenter_getitimer)
INTERN(__asm32_sysenter_linux_stat32)
INTERN(__asm32_sysenter_linux_lstat32)
INTERN(__asm32_sysenter_linux_fstat32)
INTERN(__asm32_sysenter_olduname)
INTERN(__asm32_sysenter_iopl)
INTERN(__asm32_sysenter_vhangup)
INTERN(__asm32_sysenter_wait4)
INTERN(__asm32_sysenter_swapoff)
INTERN(__asm32_sysenter_sysinfo)
INTERN(__asm32_sysenter_fsync)
INTERN(__asm32_sysenter_sigreturn)
INTERN(__asm32_sysenter_clone)
INTERN(__asm32_sysenter_setdomainname)
INTERN(__asm32_sysenter_uname)
INTERN(__asm32_sysenter_modify_ldt)
INTERN(__asm32_sysenter_mprotect)
INTERN(__asm32_sysenter_sigprocmask)
INTERN(__asm32_sysenter_getpgid)
INTERN(__asm32_sysenter_fchdir)
INTERN(__asm32_sysenter_setfsuid)
INTERN(__asm32_sysenter_setfsgid)
INTERN(__asm32_sysenter__llseek)
INTERN(__asm32_sysenter_getdents)
INTERN(__asm32_sysenter_flock)
INTERN(__asm32_sysenter_msync)
INTERN(__asm32_sysenter_readv)
INTERN(__asm32_sysenter_writev)
INTERN(__asm32_sysenter_getsid)
INTERN(__asm32_sysenter_fdatasync)
INTERN(__asm32_sysenter_mlock)
INTERN(__asm32_sysenter_munlock)
INTERN(__asm32_sysenter_mlockall)
INTERN(__asm32_sysenter_munlockall)
INTERN(__asm32_sysenter_sched_setparam)
INTERN(__asm32_sysenter_sched_getparam)
INTERN(__asm32_sysenter_sched_setscheduler)
INTERN(__asm32_sysenter_sched_getscheduler)
INTERN(__asm32_sysenter_sched_yield)
INTERN(__asm32_sysenter_sched_get_priority_max)
INTERN(__asm32_sysenter_sched_get_priority_min)
INTERN(__asm32_sysenter_sched_rr_get_interval)
INTERN(__asm32_sysenter_nanosleep)
INTERN(__asm32_sysenter_mremap)
INTERN(__asm32_sysenter_setresuid)
INTERN(__asm32_sysenter_getresuid)
INTERN(__asm32_sysenter_poll)
INTERN(__asm32_sysenter_setresgid)
INTERN(__asm32_sysenter_getresgid)
INTERN(__asm32_sysenter_rt_sigaction)
INTERN(__asm32_sysenter_rt_sigprocmask)
INTERN(__asm32_sysenter_rt_sigpending)
INTERN(__asm32_sysenter_rt_sigtimedwait)
INTERN(__asm32_sysenter_rt_sigqueueinfo)
INTERN(__asm32_sysenter_rt_sigsuspend)
INTERN(__asm32_sysenter_pread64)
INTERN(__asm32_sysenter_pwrite64)
INTERN(__asm32_sysenter_chown)
INTERN(__asm32_sysenter_getcwd)
INTERN(__asm32_sysenter_sigaltstack)
INTERN(__asm32_sysenter_sendfile)
INTERN(__asm32_sysenter_vfork)
INTERN(__asm32_sysenter_mmap2)
INTERN(__asm32_sysenter_truncate64)
INTERN(__asm32_sysenter_ftruncate64)
INTERN(__asm32_sysenter_linux_stat64)
INTERN(__asm32_sysenter_linux_lstat64)
INTERN(__asm32_sysenter_linux_fstat64)
INTERN(__asm32_sysenter_lchown32)
INTERN(__asm32_sysenter_getuid32)
INTERN(__asm32_sysenter_getgid32)
INTERN(__asm32_sysenter_geteuid32)
INTERN(__asm32_sysenter_getegid32)
INTERN(__asm32_sysenter_setreuid32)
INTERN(__asm32_sysenter_setregid32)
INTERN(__asm32_sysenter_getgroups32)
INTERN(__asm32_sysenter_setgroups32)
INTERN(__asm32_sysenter_fchown32)
INTERN(__asm32_sysenter_setresuid32)
INTERN(__asm32_sysenter_getresuid32)
INTERN(__asm32_sysenter_setresgid32)
INTERN(__asm32_sysenter_getresgid32)
INTERN(__asm32_sysenter_chown32)
INTERN(__asm32_sysenter_setuid32)
INTERN(__asm32_sysenter_setgid32)
INTERN(__asm32_sysenter_setfsuid32)
INTERN(__asm32_sysenter_setfsgid32)
INTERN(__asm32_sysenter_mincore)
INTERN(__asm32_sysenter_madvise)
INTERN(__asm32_sysenter_getdents64)
INTERN(__asm32_sysenter_fcntl64)
INTERN(__asm32_sysenter_gettid)
INTERN(__asm32_sysenter_readahead)
INTERN(__asm32_sysenter_setxattr)
INTERN(__asm32_sysenter_lsetxattr)
INTERN(__asm32_sysenter_fsetxattr)
INTERN(__asm32_sysenter_getxattr)
INTERN(__asm32_sysenter_lgetxattr)
INTERN(__asm32_sysenter_fgetxattr)
INTERN(__asm32_sysenter_listxattr)
INTERN(__asm32_sysenter_llistxattr)
INTERN(__asm32_sysenter_flistxattr)
INTERN(__asm32_sysenter_removexattr)
INTERN(__asm32_sysenter_lremovexattr)
INTERN(__asm32_sysenter_fremovexattr)
INTERN(__asm32_sysenter_tkill)
INTERN(__asm32_sysenter_sendfile64)
INTERN(__asm32_sysenter_futex)
INTERN(__asm32_sysenter_sched_setaffinity)
INTERN(__asm32_sysenter_sched_getaffinity)
INTERN(__asm32_sysenter_exit_group)
INTERN(__asm32_sysenter_epoll_create)
INTERN(__asm32_sysenter_epoll_ctl)
INTERN(__asm32_sysenter_epoll_wait)
INTERN(__asm32_sysenter_remap_file_pages)
INTERN(__asm32_sysenter_set_tid_address)
INTERN(__asm32_sysenter_timer_create)
INTERN(__asm32_sysenter_timer_settime)
INTERN(__asm32_sysenter_timer_gettime)
INTERN(__asm32_sysenter_timer_getoverrun)
INTERN(__asm32_sysenter_timer_delete)
INTERN(__asm32_sysenter_clock_settime)
INTERN(__asm32_sysenter_clock_gettime)
INTERN(__asm32_sysenter_clock_getres)
INTERN(__asm32_sysenter_clock_nanosleep)
INTERN(__asm32_sysenter_statfs64)
INTERN(__asm32_sysenter_fstatfs64)
INTERN(__asm32_sysenter_tgkill)
INTERN(__asm32_sysenter_utimes)
INTERN(__asm32_sysenter_waitid)
INTERN(__asm32_sysenter_ioprio_set)
INTERN(__asm32_sysenter_ioprio_get)
INTERN(__asm32_sysenter_openat)
INTERN(__asm32_sysenter_mkdirat)
INTERN(__asm32_sysenter_mknodat)
INTERN(__asm32_sysenter_fchownat)
INTERN(__asm32_sysenter_futimesat)
INTERN(__asm32_sysenter_linux_fstatat64)
INTERN(__asm32_sysenter_unlinkat)
INTERN(__asm32_sysenter_renameat)
INTERN(__asm32_sysenter_linkat)
INTERN(__asm32_sysenter_symlinkat)
INTERN(__asm32_sysenter_readlinkat)
INTERN(__asm32_sysenter_fchmodat)
INTERN(__asm32_sysenter_faccessat)
INTERN(__asm32_sysenter_pselect6)
INTERN(__asm32_sysenter_ppoll)
INTERN(__asm32_sysenter_unshare)
INTERN(__asm32_sysenter_splice)
INTERN(__asm32_sysenter_sync_file_range)
INTERN(__asm32_sysenter_tee)
INTERN(__asm32_sysenter_vmsplice)
INTERN(__asm32_sysenter_getcpu)
INTERN(__asm32_sysenter_epoll_pwait)
INTERN(__asm32_sysenter_utimensat)
INTERN(__asm32_sysenter_timerfd_create)
INTERN(__asm32_sysenter_eventfd)
INTERN(__asm32_sysenter_fallocate)
INTERN(__asm32_sysenter_timerfd_settime)
INTERN(__asm32_sysenter_timerfd_gettime)
INTERN(__asm32_sysenter_eventfd2)
INTERN(__asm32_sysenter_epoll_create1)
INTERN(__asm32_sysenter_dup3)
INTERN(__asm32_sysenter_pipe2)
INTERN(__asm32_sysenter_preadv)
INTERN(__asm32_sysenter_pwritev)
INTERN(__asm32_sysenter_rt_tgsigqueueinfo)
INTERN(__asm32_sysenter_recvmmsg)
INTERN(__asm32_sysenter_prlimit64)
INTERN(__asm32_sysenter_name_to_handle_at)
INTERN(__asm32_sysenter_open_by_handle_at)
INTERN(__asm32_sysenter_syncfs)
INTERN(__asm32_sysenter_sendmmsg)
INTERN(__asm32_sysenter_setns)
INTERN(__asm32_sysenter_process_vm_readv)
INTERN(__asm32_sysenter_process_vm_writev)
INTERN(__asm32_sysenter_kcmp)
INTERN(__asm32_sysenter_renameat2)
INTERN(__asm32_sysenter_execveat)
INTERN(__asm32_sysenter_socket)
INTERN(__asm32_sysenter_socketpair)
INTERN(__asm32_sysenter_bind)
INTERN(__asm32_sysenter_connect)
INTERN(__asm32_sysenter_listen)
INTERN(__asm32_sysenter_accept4)
INTERN(__asm32_sysenter_getsockopt)
INTERN(__asm32_sysenter_setsockopt)
INTERN(__asm32_sysenter_getsockname)
INTERN(__asm32_sysenter_getpeername)
INTERN(__asm32_sysenter_sendto)
INTERN(__asm32_sysenter_sendmsg)
INTERN(__asm32_sysenter_recvfrom)
INTERN(__asm32_sysenter_recvmsg)
INTERN(__asm32_sysenter_shutdown)
INTERN(__asm32_sysenter_hop)
INTERN(__asm32_sysenter_hopf)
INTERN(__asm32_sysenter_readf)
INTERN(__asm32_sysenter_writef)
INTERN(__asm32_sysenter_detach)
INTERN(__asm32_sysenter_getdrives)
INTERN(__asm32_sysenter_frealpath4)
INTERN(__asm32_sysenter_frealpathat)
INTERN(__asm32_sysenter_rpc_schedule)
INTERN(__asm32_sysenter_sysctl)
INTERN(__asm32_sysenter_openpty)
INTERN(__asm32_sysenter_fchdirat)
INTERN(__asm32_sysenter_time64)
INTERN(__asm32_sysenter_set_exception_handler)
INTERN(__asm32_sysenter_get_exception_handler)
INTERN(__asm32_sysenter_set_library_listdef)
INTERN(__asm32_sysenter_debugtrap)
INTERN(__asm32_sysenter_lfutex)
INTERN(__asm32_sysenter_lseek64)
INTERN(__asm32_sysenter_lfutexlock)
INTERN(__asm32_sysenter_lfutexexpr)
INTERN(__asm32_sysenter_lfutexlockexpr)
INTERN(__asm32_sysenter_mktty)
INTERN(__asm32_sysenter_raiseat)
INTERN(__asm32_sysenter_stime64)
INTERN(__asm32_sysenter_coredump)
INTERN(__asm32_sysenter_utime64)
INTERN(__asm32_sysenter_ioctlf)
INTERN(__asm32_sysenter_fsmode)
INTERN(__asm32_sysenter_gettimeofday64)
INTERN(__asm32_sysenter_settimeofday64)
INTERN(__asm32_sysenter_select64)
INTERN(__asm32_sysenter_maplibrary)
INTERN(__asm32_sysenter_setitimer64)
INTERN(__asm32_sysenter_getitimer64)
INTERN(__asm32_sysenter_kreaddir)
INTERN(__asm32_sysenter_readvf)
INTERN(__asm32_sysenter_writevf)
INTERN(__asm32_sysenter_rpc_service)
INTERN(__asm32_sysenter_sched_rr_get_interval64)
INTERN(__asm32_sysenter_nanosleep64)
INTERN(__asm32_sysenter_rt_sigtimedwait64)
INTERN(__asm32_sysenter_pread64f)
INTERN(__asm32_sysenter_pwrite64f)
INTERN(__asm32_sysenter_kstat)
INTERN(__asm32_sysenter_klstat)
INTERN(__asm32_sysenter_kfstat)
INTERN(__asm32_sysenter_kreaddirf)
INTERN(__asm32_sysenter_timer_settime64)
INTERN(__asm32_sysenter_timer_gettime64)
INTERN(__asm32_sysenter_clock_settime64)
INTERN(__asm32_sysenter_clock_gettime64)
INTERN(__asm32_sysenter_clock_getres64)
INTERN(__asm32_sysenter_clock_nanosleep64)
INTERN(__asm32_sysenter_utimes64)
INTERN(__asm32_sysenter_fmkdirat)
INTERN(__asm32_sysenter_fmknodat)
INTERN(__asm32_sysenter_futimesat64)
INTERN(__asm32_sysenter_kfstatat)
INTERN(__asm32_sysenter_frenameat)
INTERN(__asm32_sysenter_fsymlinkat)
INTERN(__asm32_sysenter_freadlinkat)
INTERN(__asm32_sysenter_pselect6_64)
INTERN(__asm32_sysenter_ppoll64)
INTERN(__asm32_sysenter_utimensat64)
INTERN(__asm32_sysenter_fallocate64)
INTERN(__asm32_sysenter_timerfd_settime64)
INTERN(__asm32_sysenter_timerfd_gettime64)
INTERN(__asm32_sysenter_preadvf)
INTERN(__asm32_sysenter_pwritevf)
INTERN(__asm32_sysenter_recvmmsg64)



/****************************************************************************/
/* 64-bit System call router for <syscall> and <int 80h>                    */
/****************************************************************************/
.section .rodata.x86.syscall64.router
PUBLIC_OBJECT(__asm64_syscallrouter)
	.quad __asm64_syscall_read                   /* 0 */
	.quad __asm64_syscall_write                  /* 1 */
	.quad __asm64_syscall_open                   /* 2 */
	.quad __asm64_syscall_close                  /* 3 */
	.quad __asm64_syscall_linux_stat64           /* 4 */
	.quad __asm64_syscall_linux_fstat64          /* 5 */
	.quad __asm64_syscall_linux_lstat64          /* 6 */
	.quad __asm64_syscall_poll                   /* 7 */
	.quad __asm64_syscall_lseek64                /* 8 */
	.quad __asm64_syscall_mmap                   /* 9 */
	.quad __asm64_syscall_mprotect               /* 10 */
	.quad __asm64_syscall_munmap                 /* 11 */
	.quad __asm64_syscall_brk                    /* 12 */
	.quad __asm64_syscall_rt_sigaction           /* 13 */
	.quad __asm64_syscall_rt_sigprocmask         /* 14 */
	.quad __asm64_syscall_rt_sigreturn           /* 15 */
	.quad __asm64_syscall_ioctl                  /* 16 */
	.quad __asm64_syscall_pread64                /* 17 */
	.quad __asm64_syscall_pwrite64               /* 18 */
	.quad __asm64_syscall_readv                  /* 19 */
	.quad __asm64_syscall_writev                 /* 20 */
	.quad __asm64_syscall_access                 /* 21 */
	.quad __asm64_syscall_pipe                   /* 22 */
	.quad __asm64_syscall_select                 /* 23 */
	.quad __asm64_syscall_sched_yield            /* 24 */
	.quad __asm64_syscall_mremap                 /* 25 */
	.quad __asm64_syscall_msync                  /* 26 */
	.quad __asm64_syscall_mincore                /* 27 */
	.quad __asm64_syscall_madvise                /* 28 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_dup                    /* 32 */
	.quad __asm64_syscall_dup2                   /* 33 */
	.quad __asm64_syscall_pause                  /* 34 */
	.quad __asm64_syscall_nanosleep              /* 35 */
	.quad __asm64_syscall_getitimer              /* 36 */
	.quad __asm64_syscall_alarm                  /* 37 */
	.quad __asm64_syscall_setitimer              /* 38 */
	.quad __asm64_syscall_getpid                 /* 39 */
	.quad __asm64_syscall_sendfile               /* 40 */
	.quad __asm64_syscall_socket                 /* 41 */
	.quad __asm64_syscall_connect                /* 42 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_sendto                 /* 44 */
	.quad __asm64_syscall_recvfrom               /* 45 */
	.quad __asm64_syscall_sendmsg                /* 46 */
	.quad __asm64_syscall_recvmsg                /* 47 */
	.quad __asm64_syscall_shutdown               /* 48 */
	.quad __asm64_syscall_bind                   /* 49 */
	.quad __asm64_syscall_listen                 /* 50 */
	.quad __asm64_syscall_getsockname            /* 51 */
	.quad __asm64_syscall_getpeername            /* 52 */
	.quad __asm64_syscall_socketpair             /* 53 */
	.quad __asm64_syscall_setsockopt             /* 54 */
	.quad __asm64_syscall_getsockopt             /* 55 */
	.quad __asm64_syscall_clone                  /* 56 */
	.quad __asm64_syscall_fork                   /* 57 */
	.quad __asm64_syscall_vfork                  /* 58 */
	.quad __asm64_syscall_execve                 /* 59 */
	.quad __asm64_syscall_exit                   /* 60 */
	.quad __asm64_syscall_wait4                  /* 61 */
	.quad __asm64_syscall_kill                   /* 62 */
	.quad __asm64_syscall_uname                  /* 63 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_fcntl                  /* 72 */
	.quad __asm64_syscall_flock                  /* 73 */
	.quad __asm64_syscall_fsync                  /* 74 */
	.quad __asm64_syscall_fdatasync              /* 75 */
	.quad __asm64_syscall_truncate               /* 76 */
	.quad __asm64_syscall_ftruncate              /* 77 */
	.quad __asm64_syscall_getdents               /* 78 */
	.quad __asm64_syscall_getcwd                 /* 79 */
	.quad __asm64_syscall_chdir                  /* 80 */
	.quad __asm64_syscall_fchdir                 /* 81 */
	.quad __asm64_syscall_rename                 /* 82 */
	.quad __asm64_syscall_mkdir                  /* 83 */
	.quad __asm64_syscall_rmdir                  /* 84 */
	.quad __asm64_syscall_creat                  /* 85 */
	.quad __asm64_syscall_link                   /* 86 */
	.quad __asm64_syscall_unlink                 /* 87 */
	.quad __asm64_syscall_symlink                /* 88 */
	.quad __asm64_syscall_readlink               /* 89 */
	.quad __asm64_syscall_chmod                  /* 90 */
	.quad __asm64_syscall_fchmod                 /* 91 */
	.quad __asm64_syscall_chown                  /* 92 */
	.quad __asm64_syscall_fchown                 /* 93 */
	.quad __asm64_syscall_lchown                 /* 94 */
	.quad __asm64_syscall_umask                  /* 95 */
	.quad __asm64_syscall_gettimeofday           /* 96 */
	.quad __asm64_syscall_getrlimit              /* 97 */
	.quad __asm64_syscall_getrusage              /* 98 */
	.quad __asm64_syscall_sysinfo                /* 99 */
	.quad __asm64_syscall_times                  /* 100 */
	.quad __asm64_syscall_ptrace                 /* 101 */
	.quad __asm64_syscall_getuid32               /* 102 */
	.quad __asm64_syscall_syslog                 /* 103 */
	.quad __asm64_syscall_getgid32               /* 104 */
	.quad __asm64_syscall_setuid32               /* 105 */
	.quad __asm64_syscall_setgid32               /* 106 */
	.quad __asm64_syscall_geteuid32              /* 107 */
	.quad __asm64_syscall_getegid32              /* 108 */
	.quad __asm64_syscall_setpgid                /* 109 */
	.quad __asm64_syscall_getppid                /* 110 */
	.quad __asm64_syscall_getpgrp                /* 111 */
	.quad __asm64_syscall_setsid                 /* 112 */
	.quad __asm64_syscall_setreuid32             /* 113 */
	.quad __asm64_syscall_setregid32             /* 114 */
	.quad __asm64_syscall_getgroups32            /* 115 */
	.quad __asm64_syscall_setgroups32            /* 116 */
	.quad __asm64_syscall_setresuid32            /* 117 */
	.quad __asm64_syscall_getresuid32            /* 118 */
	.quad __asm64_syscall_setresgid32            /* 119 */
	.quad __asm64_syscall_getresgid32            /* 120 */
	.quad __asm64_syscall_getpgid                /* 121 */
	.quad __asm64_syscall_setfsuid32             /* 122 */
	.quad __asm64_syscall_setfsgid32             /* 123 */
	.quad __asm64_syscall_getsid                 /* 124 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_rt_sigpending          /* 127 */
	.quad __asm64_syscall_rt_sigtimedwait        /* 128 */
	.quad __asm64_syscall_rt_sigqueueinfo        /* 129 */
	.quad __asm64_syscall_rt_sigsuspend          /* 130 */
	.quad __asm64_syscall_sigaltstack            /* 131 */
	.quad __asm64_syscall_utime                  /* 132 */
	.quad __asm64_syscall_mknod                  /* 133 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_ustat                  /* 136 */
	.quad __asm64_syscall_statfs                 /* 137 */
	.quad __asm64_syscall_fstatfs                /* 138 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_getpriority            /* 140 */
	.quad __asm64_syscall_setpriority            /* 141 */
	.quad __asm64_syscall_sched_setparam         /* 142 */
	.quad __asm64_syscall_sched_getparam         /* 143 */
	.quad __asm64_syscall_sched_setscheduler     /* 144 */
	.quad __asm64_syscall_sched_getscheduler     /* 145 */
	.quad __asm64_syscall_sched_get_priority_max /* 146 */
	.quad __asm64_syscall_sched_get_priority_min /* 147 */
	.quad __asm64_syscall_sched_rr_get_interval  /* 148 */
	.quad __asm64_syscall_mlock                  /* 149 */
	.quad __asm64_syscall_munlock                /* 150 */
	.quad __asm64_syscall_mlockall               /* 151 */
	.quad __asm64_syscall_munlockall             /* 152 */
	.quad __asm64_syscall_vhangup                /* 153 */
	.quad __asm64_syscall_modify_ldt             /* 154 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_setrlimit              /* 160 */
	.quad __asm64_syscall_chroot                 /* 161 */
	.quad __asm64_syscall_sync                   /* 162 */
	.quad __asm64_syscall_acct                   /* 163 */
	.quad __asm64_syscall_settimeofday           /* 164 */
	.quad __asm64_syscall_mount                  /* 165 */
	.quad __asm64_syscall_umount2                /* 166 */
	.quad __asm64_syscall_swapon                 /* 167 */
	.quad __asm64_syscall_swapoff                /* 168 */
	.quad __asm64_syscall_reboot                 /* 169 */
	.quad __asm64_syscall_sethostname            /* 170 */
	.quad __asm64_syscall_setdomainname          /* 171 */
	.quad __asm64_syscall_iopl                   /* 172 */
	.quad __asm64_syscall_ioperm                 /* 173 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_gettid                 /* 186 */
	.quad __asm64_syscall_readahead              /* 187 */
	.quad __asm64_syscall_setxattr               /* 188 */
	.quad __asm64_syscall_lsetxattr              /* 189 */
	.quad __asm64_syscall_fsetxattr              /* 190 */
	.quad __asm64_syscall_getxattr               /* 191 */
	.quad __asm64_syscall_lgetxattr              /* 192 */
	.quad __asm64_syscall_fgetxattr              /* 193 */
	.quad __asm64_syscall_listxattr              /* 194 */
	.quad __asm64_syscall_llistxattr             /* 195 */
	.quad __asm64_syscall_flistxattr             /* 196 */
	.quad __asm64_syscall_removexattr            /* 197 */
	.quad __asm64_syscall_lremovexattr           /* 198 */
	.quad __asm64_syscall_fremovexattr           /* 199 */
	.quad __asm64_syscall_tkill                  /* 200 */
	.quad __asm64_syscall_time                   /* 201 */
	.quad __asm64_syscall_futex                  /* 202 */
	.quad __asm64_syscall_sched_setaffinity      /* 203 */
	.quad __asm64_syscall_sched_getaffinity      /* 204 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_epoll_create           /* 213 */
	.quad __asm64_syscall_epoll_ctl_old          /* 214 */
	.quad __asm64_syscall_epoll_wait_old         /* 215 */
	.quad __asm64_syscall_remap_file_pages       /* 216 */
	.quad __asm64_syscall_getdents64             /* 217 */
	.quad __asm64_syscall_set_tid_address        /* 218 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_timer_create           /* 222 */
	.quad __asm64_syscall_timer_settime          /* 223 */
	.quad __asm64_syscall_timer_gettime          /* 224 */
	.quad __asm64_syscall_timer_getoverrun       /* 225 */
	.quad __asm64_syscall_timer_delete           /* 226 */
	.quad __asm64_syscall_clock_settime          /* 227 */
	.quad __asm64_syscall_clock_gettime          /* 228 */
	.quad __asm64_syscall_clock_getres           /* 229 */
	.quad __asm64_syscall_clock_nanosleep        /* 230 */
	.quad __asm64_syscall_exit_group             /* 231 */
	.quad __asm64_syscall_epoll_wait             /* 232 */
	.quad __asm64_syscall_epoll_ctl              /* 233 */
	.quad __asm64_syscall_tgkill                 /* 234 */
	.quad __asm64_syscall_utimes                 /* 235 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_waitid                 /* 247 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_ioprio_set             /* 251 */
	.quad __asm64_syscall_ioprio_get             /* 252 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_openat                 /* 257 */
	.quad __asm64_syscall_mkdirat                /* 258 */
	.quad __asm64_syscall_mknodat                /* 259 */
	.quad __asm64_syscall_fchownat               /* 260 */
	.quad __asm64_syscall_futimesat              /* 261 */
	.quad __asm64_syscall_fstatat                /* 262 */
	.quad __asm64_syscall_unlinkat               /* 263 */
	.quad __asm64_syscall_renameat               /* 264 */
	.quad __asm64_syscall_linkat                 /* 265 */
	.quad __asm64_syscall_symlinkat              /* 266 */
	.quad __asm64_syscall_readlinkat             /* 267 */
	.quad __asm64_syscall_fchmodat               /* 268 */
	.quad __asm64_syscall_faccessat              /* 269 */
	.quad __asm64_syscall_pselect6               /* 270 */
	.quad __asm64_syscall_ppoll                  /* 271 */
	.quad __asm64_syscall_unshare                /* 272 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_splice                 /* 275 */
	.quad __asm64_syscall_tee                    /* 276 */
	.quad __asm64_syscall_sync_file_range        /* 277 */
	.quad __asm64_syscall_vmsplice               /* 278 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_utimensat              /* 280 */
	.quad __asm64_syscall_epoll_pwait            /* 281 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_timerfd_create         /* 283 */
	.quad __asm64_syscall_eventfd                /* 284 */
	.quad __asm64_syscall_fallocate              /* 285 */
	.quad __asm64_syscall_timerfd_settime        /* 286 */
	.quad __asm64_syscall_timerfd_gettime        /* 287 */
	.quad __asm64_syscall_accept4                /* 288 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_eventfd2               /* 290 */
	.quad __asm64_syscall_epoll_create1          /* 291 */
	.quad __asm64_syscall_dup3                   /* 292 */
	.quad __asm64_syscall_pipe2                  /* 293 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_preadv                 /* 295 */
	.quad __asm64_syscall_pwritev                /* 296 */
	.quad __asm64_syscall_rt_tgsigqueueinfo      /* 297 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_recvmmsg               /* 299 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_prlimit64              /* 302 */
	.quad __asm64_syscall_name_to_handle_at      /* 303 */
	.quad __asm64_syscall_open_by_handle_at      /* 304 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_syncfs                 /* 306 */
	.quad __asm64_syscall_sendmmsg               /* 307 */
	.quad __asm64_syscall_setns                  /* 308 */
	.quad __asm64_syscall_getcpu                 /* 309 */
	.quad __asm64_syscall_process_vm_readv       /* 310 */
	.quad __asm64_syscall_process_vm_writev      /* 311 */
	.quad __asm64_syscall_kcmp                   /* 312 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_renameat2              /* 316 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_execveat               /* 322 */
END(__asm64_syscallrouter)


PUBLIC_OBJECT(__asm64_exsyscallrouter)
	.quad __asm64_syscall_readf                 /* 0x80000000 */
	.quad __asm64_syscall_writef                /* 0x80000001 */
	.quad __asm64_syscall_hop                   /* 0x80000002 */
	.quad __asm64_syscall_hopf                  /* 0x80000003 */
	.quad __asm64_syscall_kstat                 /* 0x80000004 */
	.quad __asm64_syscall_kfstat                /* 0x80000005 */
	.quad __asm64_syscall_klstat                /* 0x80000006 */
	.quad __asm64_syscall_detach                /* 0x80000007 */
	.quad __asm64_syscall_getdrives             /* 0x80000008 */
	.quad __asm64_syscall_frealpath4            /* 0x80000009 */
	.quad __asm64_syscall_frealpathat           /* 0x8000000a */
	.quad __asm64_syscall_rpc_schedule          /* 0x8000000b */
	.quad __asm64_syscall_sysctl                /* 0x8000000c */
	.quad __asm64_syscall_openpty               /* 0x8000000d */
	.quad __asm64_syscall_set_exception_handler /* 0x8000000e */
	.quad __asm64_syscall_get_exception_handler /* 0x8000000f */
	.quad __asm64_syscall_ioctlf                /* 0x80000010 */
	.quad __asm64_syscall_pread64f              /* 0x80000011 */
	.quad __asm64_syscall_pwrite64f             /* 0x80000012 */
	.quad __asm64_syscall_readvf                /* 0x80000013 */
	.quad __asm64_syscall_writevf               /* 0x80000014 */
	.quad __asm64_syscall_set_library_listdef   /* 0x80000015 */
	.quad __asm64_syscall_debugtrap             /* 0x80000016 */
	.quad __asm64_syscall_select64              /* 0x80000017 */
	.quad __asm64_syscall_rpc_service           /* 0x80000018 */
	.quad __asm64_syscall_lfutex                /* 0x80000019 */
	.quad __asm64_syscall_lfutexlock            /* 0x8000001a */
	.quad __asm64_syscall_lfutexexpr            /* 0x8000001b */
	.quad __asm64_syscall_lfutexlockexpr        /* 0x8000001c */
	.quad __asm64_syscall_mktty                 /* 0x8000001d */
	.quad __asm64_syscall_raiseat               /* 0x8000001e */
	.quad __asm64_syscall_coredump              /* 0x8000001f */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_getitimer64           /* 0x80000024 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_setitimer64           /* 0x80000026 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_kreaddir              /* 0x8000004e */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_fchdirat              /* 0x80000050 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_fsmode                /* 0x8000005f */
	.quad __asm64_syscall_gettimeofday64        /* 0x80000060 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_utime64               /* 0x80000084 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_maplibrary            /* 0x80000086 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_settimeofday64        /* 0x800000a4 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_time64                /* 0x800000c9 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_kreaddirf             /* 0x800000d9 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_utimes64              /* 0x800000eb */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_fmkdirat              /* 0x80000102 */
	.quad __asm64_syscall_fmknodat              /* 0x80000103 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_futimesat64           /* 0x80000105 */
	.quad __asm64_syscall_kfstatat              /* 0x80000106 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_frenameat             /* 0x80000108 */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_fsymlinkat            /* 0x8000010a */
	.quad __asm64_syscall_freadlinkat           /* 0x8000010b */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_fallocate64           /* 0x8000011d */
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_invalid
	.quad __asm64_syscall_preadvf               /* 0x80000127 */
	.quad __asm64_syscall_pwritevf              /* 0x80000128 */
END(__asm64_exsyscallrouter)


/****************************************************************************/
/* 64-bit System call router for high-level C-implementations               */
/****************************************************************************/
.section .rodata.x86.syscall64.c_router
PUBLIC_OBJECT(__c64_syscallrouter)
	.quad sys_read                   /* 0 */
	.quad sys_write                  /* 1 */
	.quad sys_open                   /* 2 */
	.quad sys_close                  /* 3 */
	.quad sys_linux_stat64           /* 4 */
	.quad sys_linux_fstat64          /* 5 */
	.quad sys_linux_lstat64          /* 6 */
	.quad sys_poll                   /* 7 */
	.quad sys_lseek64                /* 8 */
	.quad sys_mmap                   /* 9 */
	.quad sys_mprotect               /* 10 */
	.quad sys_munmap                 /* 11 */
	.quad sys_brk                    /* 12 */
	.quad sys_rt_sigaction           /* 13 */
	.quad sys_rt_sigprocmask         /* 14 */
	.quad sys_rt_sigreturn           /* 15 */
	.quad sys_ioctl                  /* 16 */
	.quad sys_pread64                /* 17 */
	.quad sys_pwrite64               /* 18 */
	.quad sys_readv                  /* 19 */
	.quad sys_writev                 /* 20 */
	.quad sys_access                 /* 21 */
	.quad sys_pipe                   /* 22 */
	.quad sys_select                 /* 23 */
	.quad sys_sched_yield            /* 24 */
	.quad sys_mremap                 /* 25 */
	.quad sys_msync                  /* 26 */
	.quad sys_mincore                /* 27 */
	.quad sys_madvise                /* 28 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_dup                    /* 32 */
	.quad sys_dup2                   /* 33 */
	.quad sys_pause                  /* 34 */
	.quad sys_nanosleep              /* 35 */
	.quad sys_getitimer              /* 36 */
	.quad sys_alarm                  /* 37 */
	.quad sys_setitimer              /* 38 */
	.quad sys_getpid                 /* 39 */
	.quad sys_sendfile               /* 40 */
	.quad sys_socket                 /* 41 */
	.quad sys_connect                /* 42 */
	.quad sys_invalid0
	.quad sys_sendto                 /* 44 */
	.quad sys_recvfrom               /* 45 */
	.quad sys_sendmsg                /* 46 */
	.quad sys_recvmsg                /* 47 */
	.quad sys_shutdown               /* 48 */
	.quad sys_bind                   /* 49 */
	.quad sys_listen                 /* 50 */
	.quad sys_getsockname            /* 51 */
	.quad sys_getpeername            /* 52 */
	.quad sys_socketpair             /* 53 */
	.quad sys_setsockopt             /* 54 */
	.quad sys_getsockopt             /* 55 */
	.quad sys_clone                  /* 56 */
	.quad sys_fork                   /* 57 */
	.quad sys_vfork                  /* 58 */
	.quad sys_execve                 /* 59 */
	.quad sys_exit                   /* 60 */
	.quad sys_wait4                  /* 61 */
	.quad sys_kill                   /* 62 */
	.quad sys_uname                  /* 63 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_fcntl                  /* 72 */
	.quad sys_flock                  /* 73 */
	.quad sys_fsync                  /* 74 */
	.quad sys_fdatasync              /* 75 */
	.quad sys_truncate               /* 76 */
	.quad sys_ftruncate              /* 77 */
	.quad sys_getdents               /* 78 */
	.quad sys_getcwd                 /* 79 */
	.quad sys_chdir                  /* 80 */
	.quad sys_fchdir                 /* 81 */
	.quad sys_rename                 /* 82 */
	.quad sys_mkdir                  /* 83 */
	.quad sys_rmdir                  /* 84 */
	.quad sys_creat                  /* 85 */
	.quad sys_link                   /* 86 */
	.quad sys_unlink                 /* 87 */
	.quad sys_symlink                /* 88 */
	.quad sys_readlink               /* 89 */
	.quad sys_chmod                  /* 90 */
	.quad sys_fchmod                 /* 91 */
	.quad sys_chown                  /* 92 */
	.quad sys_fchown                 /* 93 */
	.quad sys_lchown                 /* 94 */
	.quad sys_umask                  /* 95 */
	.quad sys_gettimeofday           /* 96 */
	.quad sys_getrlimit              /* 97 */
	.quad sys_getrusage              /* 98 */
	.quad sys_sysinfo                /* 99 */
	.quad sys_times                  /* 100 */
	.quad sys_ptrace                 /* 101 */
	.quad sys_getuid32               /* 102 */
	.quad sys_syslog                 /* 103 */
	.quad sys_getgid32               /* 104 */
	.quad sys_setuid32               /* 105 */
	.quad sys_setgid32               /* 106 */
	.quad sys_geteuid32              /* 107 */
	.quad sys_getegid32              /* 108 */
	.quad sys_setpgid                /* 109 */
	.quad sys_getppid                /* 110 */
	.quad sys_getpgrp                /* 111 */
	.quad sys_setsid                 /* 112 */
	.quad sys_setreuid32             /* 113 */
	.quad sys_setregid32             /* 114 */
	.quad sys_getgroups32            /* 115 */
	.quad sys_setgroups32            /* 116 */
	.quad sys_setresuid32            /* 117 */
	.quad sys_getresuid32            /* 118 */
	.quad sys_setresgid32            /* 119 */
	.quad sys_getresgid32            /* 120 */
	.quad sys_getpgid                /* 121 */
	.quad sys_setfsuid32             /* 122 */
	.quad sys_setfsgid32             /* 123 */
	.quad sys_getsid                 /* 124 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_rt_sigpending          /* 127 */
	.quad sys_rt_sigtimedwait        /* 128 */
	.quad sys_rt_sigqueueinfo        /* 129 */
	.quad sys_rt_sigsuspend          /* 130 */
	.quad sys_sigaltstack            /* 131 */
	.quad sys_utime                  /* 132 */
	.quad sys_mknod                  /* 133 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_ustat                  /* 136 */
	.quad sys_statfs                 /* 137 */
	.quad sys_fstatfs                /* 138 */
	.quad sys_invalid0
	.quad sys_getpriority            /* 140 */
	.quad sys_setpriority            /* 141 */
	.quad sys_sched_setparam         /* 142 */
	.quad sys_sched_getparam         /* 143 */
	.quad sys_sched_setscheduler     /* 144 */
	.quad sys_sched_getscheduler     /* 145 */
	.quad sys_sched_get_priority_max /* 146 */
	.quad sys_sched_get_priority_min /* 147 */
	.quad sys_sched_rr_get_interval  /* 148 */
	.quad sys_mlock                  /* 149 */
	.quad sys_munlock                /* 150 */
	.quad sys_mlockall               /* 151 */
	.quad sys_munlockall             /* 152 */
	.quad sys_vhangup                /* 153 */
	.quad sys_modify_ldt             /* 154 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_setrlimit              /* 160 */
	.quad sys_chroot                 /* 161 */
	.quad sys_sync                   /* 162 */
	.quad sys_acct                   /* 163 */
	.quad sys_settimeofday           /* 164 */
	.quad sys_mount                  /* 165 */
	.quad sys_umount2                /* 166 */
	.quad sys_swapon                 /* 167 */
	.quad sys_swapoff                /* 168 */
	.quad sys_reboot                 /* 169 */
	.quad sys_sethostname            /* 170 */
	.quad sys_setdomainname          /* 171 */
	.quad sys_iopl                   /* 172 */
	.quad sys_ioperm                 /* 173 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_gettid                 /* 186 */
	.quad sys_readahead              /* 187 */
	.quad sys_setxattr               /* 188 */
	.quad sys_lsetxattr              /* 189 */
	.quad sys_fsetxattr              /* 190 */
	.quad sys_getxattr               /* 191 */
	.quad sys_lgetxattr              /* 192 */
	.quad sys_fgetxattr              /* 193 */
	.quad sys_listxattr              /* 194 */
	.quad sys_llistxattr             /* 195 */
	.quad sys_flistxattr             /* 196 */
	.quad sys_removexattr            /* 197 */
	.quad sys_lremovexattr           /* 198 */
	.quad sys_fremovexattr           /* 199 */
	.quad sys_tkill                  /* 200 */
	.quad sys_time                   /* 201 */
	.quad sys_futex                  /* 202 */
	.quad sys_sched_setaffinity      /* 203 */
	.quad sys_sched_getaffinity      /* 204 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_epoll_create           /* 213 */
	.quad sys_epoll_ctl_old          /* 214 */
	.quad sys_epoll_wait_old         /* 215 */
	.quad sys_remap_file_pages       /* 216 */
	.quad sys_getdents64             /* 217 */
	.quad sys_set_tid_address        /* 218 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_timer_create           /* 222 */
	.quad sys_timer_settime          /* 223 */
	.quad sys_timer_gettime          /* 224 */
	.quad sys_timer_getoverrun       /* 225 */
	.quad sys_timer_delete           /* 226 */
	.quad sys_clock_settime          /* 227 */
	.quad sys_clock_gettime          /* 228 */
	.quad sys_clock_getres           /* 229 */
	.quad sys_clock_nanosleep        /* 230 */
	.quad sys_exit_group             /* 231 */
	.quad sys_epoll_wait             /* 232 */
	.quad sys_epoll_ctl              /* 233 */
	.quad sys_tgkill                 /* 234 */
	.quad sys_utimes                 /* 235 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_waitid                 /* 247 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_ioprio_set             /* 251 */
	.quad sys_ioprio_get             /* 252 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_openat                 /* 257 */
	.quad sys_mkdirat                /* 258 */
	.quad sys_mknodat                /* 259 */
	.quad sys_fchownat               /* 260 */
	.quad sys_futimesat              /* 261 */
	.quad sys_fstatat                /* 262 */
	.quad sys_unlinkat               /* 263 */
	.quad sys_renameat               /* 264 */
	.quad sys_linkat                 /* 265 */
	.quad sys_symlinkat              /* 266 */
	.quad sys_readlinkat             /* 267 */
	.quad sys_fchmodat               /* 268 */
	.quad sys_faccessat              /* 269 */
	.quad sys_pselect6               /* 270 */
	.quad sys_ppoll                  /* 271 */
	.quad sys_unshare                /* 272 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_splice                 /* 275 */
	.quad sys_tee                    /* 276 */
	.quad sys_sync_file_range        /* 277 */
	.quad sys_vmsplice               /* 278 */
	.quad sys_invalid0
	.quad sys_utimensat              /* 280 */
	.quad sys_epoll_pwait            /* 281 */
	.quad sys_invalid0
	.quad sys_timerfd_create         /* 283 */
	.quad sys_eventfd                /* 284 */
	.quad sys_fallocate              /* 285 */
	.quad sys_timerfd_settime        /* 286 */
	.quad sys_timerfd_gettime        /* 287 */
	.quad sys_accept4                /* 288 */
	.quad sys_invalid0
	.quad sys_eventfd2               /* 290 */
	.quad sys_epoll_create1          /* 291 */
	.quad sys_dup3                   /* 292 */
	.quad sys_pipe2                  /* 293 */
	.quad sys_invalid0
	.quad sys_preadv                 /* 295 */
	.quad sys_pwritev                /* 296 */
	.quad sys_rt_tgsigqueueinfo      /* 297 */
	.quad sys_invalid0
	.quad sys_recvmmsg               /* 299 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_prlimit64              /* 302 */
	.quad sys_name_to_handle_at      /* 303 */
	.quad sys_open_by_handle_at      /* 304 */
	.quad sys_invalid0
	.quad sys_syncfs                 /* 306 */
	.quad sys_sendmmsg               /* 307 */
	.quad sys_setns                  /* 308 */
	.quad sys_getcpu                 /* 309 */
	.quad sys_process_vm_readv       /* 310 */
	.quad sys_process_vm_writev      /* 311 */
	.quad sys_kcmp                   /* 312 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_renameat2              /* 316 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_execveat               /* 322 */
END(__c64_syscallrouter)


PUBLIC_OBJECT(__c64_exsyscallrouter)
	.quad sys_readf                 /* 0x80000000 */
	.quad sys_writef                /* 0x80000001 */
	.quad sys_hop                   /* 0x80000002 */
	.quad sys_hopf                  /* 0x80000003 */
	.quad sys_kstat                 /* 0x80000004 */
	.quad sys_kfstat                /* 0x80000005 */
	.quad sys_klstat                /* 0x80000006 */
	.quad sys_detach                /* 0x80000007 */
	.quad sys_getdrives             /* 0x80000008 */
	.quad sys_frealpath4            /* 0x80000009 */
	.quad sys_frealpathat           /* 0x8000000a */
	.quad sys_rpc_schedule          /* 0x8000000b */
	.quad sys_sysctl                /* 0x8000000c */
	.quad sys_openpty               /* 0x8000000d */
	.quad sys_set_exception_handler /* 0x8000000e */
	.quad sys_get_exception_handler /* 0x8000000f */
	.quad sys_ioctlf                /* 0x80000010 */
	.quad sys_pread64f              /* 0x80000011 */
	.quad sys_pwrite64f             /* 0x80000012 */
	.quad sys_readvf                /* 0x80000013 */
	.quad sys_writevf               /* 0x80000014 */
	.quad sys_set_library_listdef   /* 0x80000015 */
	.quad sys_debugtrap             /* 0x80000016 */
	.quad sys_select64              /* 0x80000017 */
	.quad sys_rpc_service           /* 0x80000018 */
	.quad sys_lfutex                /* 0x80000019 */
	.quad sys_lfutexlock            /* 0x8000001a */
	.quad sys_lfutexexpr            /* 0x8000001b */
	.quad sys_lfutexlockexpr        /* 0x8000001c */
	.quad sys_mktty                 /* 0x8000001d */
	.quad sys_raiseat               /* 0x8000001e */
	.quad sys_coredump              /* 0x8000001f */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_getitimer64           /* 0x80000024 */
	.quad sys_invalid0
	.quad sys_setitimer64           /* 0x80000026 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_kreaddir              /* 0x8000004e */
	.quad sys_invalid0
	.quad sys_fchdirat              /* 0x80000050 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_fsmode                /* 0x8000005f */
	.quad sys_gettimeofday64        /* 0x80000060 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_utime64               /* 0x80000084 */
	.quad sys_invalid0
	.quad sys_maplibrary            /* 0x80000086 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_settimeofday64        /* 0x800000a4 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_time64                /* 0x800000c9 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_kreaddirf             /* 0x800000d9 */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_utimes64              /* 0x800000eb */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_fmkdirat              /* 0x80000102 */
	.quad sys_fmknodat              /* 0x80000103 */
	.quad sys_invalid0
	.quad sys_futimesat64           /* 0x80000105 */
	.quad sys_kfstatat              /* 0x80000106 */
	.quad sys_invalid0
	.quad sys_frenameat             /* 0x80000108 */
	.quad sys_invalid0
	.quad sys_fsymlinkat            /* 0x8000010a */
	.quad sys_freadlinkat           /* 0x8000010b */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_fallocate64           /* 0x8000011d */
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_invalid0
	.quad sys_preadvf               /* 0x80000127 */
	.quad sys_pwritevf              /* 0x80000128 */
END(__c64_exsyscallrouter)


/****************************************************************************/
/* 32-bit System call router for <int 80h>                                  */
/****************************************************************************/
.section .rodata.x86.syscall32.router_int80
PUBLIC_OBJECT(__asm32_syscallrouter_int80)
	.quad __asm32_int80_invalid
	.quad __asm32_int80_exit                   /* 1 */
	.quad __asm32_int80_fork                   /* 2 */
	.quad __asm32_int80_read                   /* 3 */
	.quad __asm32_int80_write                  /* 4 */
	.quad __asm32_int80_open                   /* 5 */
	.quad __asm32_int80_close                  /* 6 */
	.quad __asm32_int80_waitpid                /* 7 */
	.quad __asm32_int80_creat                  /* 8 */
	.quad __asm32_int80_link                   /* 9 */
	.quad __asm32_int80_unlink                 /* 10 */
	.quad __asm32_int80_execve                 /* 11 */
	.quad __asm32_int80_chdir                  /* 12 */
	.quad __asm32_int80_time                   /* 13 */
	.quad __asm32_int80_mknod                  /* 14 */
	.quad __asm32_int80_chmod                  /* 15 */
	.quad __asm32_int80_lchown                 /* 16 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_linux_oldstat          /* 18 */
	.quad __asm32_int80_lseek                  /* 19 */
	.quad __asm32_int80_getpid                 /* 20 */
	.quad __asm32_int80_mount                  /* 21 */
	.quad __asm32_int80_umount                 /* 22 */
	.quad __asm32_int80_setuid                 /* 23 */
	.quad __asm32_int80_getuid                 /* 24 */
	.quad __asm32_int80_stime                  /* 25 */
	.quad __asm32_int80_ptrace                 /* 26 */
	.quad __asm32_int80_alarm                  /* 27 */
	.quad __asm32_int80_linux_oldfstat         /* 28 */
	.quad __asm32_int80_pause                  /* 29 */
	.quad __asm32_int80_utime                  /* 30 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_access                 /* 33 */
	.quad __asm32_int80_nice                   /* 34 */
	.quad __asm32_int80_ftime                  /* 35 */
	.quad __asm32_int80_sync                   /* 36 */
	.quad __asm32_int80_kill                   /* 37 */
	.quad __asm32_int80_rename                 /* 38 */
	.quad __asm32_int80_mkdir                  /* 39 */
	.quad __asm32_int80_rmdir                  /* 40 */
	.quad __asm32_int80_dup                    /* 41 */
	.quad __asm32_int80_pipe                   /* 42 */
	.quad __asm32_int80_times                  /* 43 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_brk                    /* 45 */
	.quad __asm32_int80_setgid                 /* 46 */
	.quad __asm32_int80_getgid                 /* 47 */
	.quad __asm32_int80_signal                 /* 48 */
	.quad __asm32_int80_geteuid                /* 49 */
	.quad __asm32_int80_getegid                /* 50 */
	.quad __asm32_int80_acct                   /* 51 */
	.quad __asm32_int80_umount2                /* 52 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_ioctl                  /* 54 */
	.quad __asm32_int80_fcntl                  /* 55 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_setpgid                /* 57 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_oldolduname            /* 59 */
	.quad __asm32_int80_umask                  /* 60 */
	.quad __asm32_int80_chroot                 /* 61 */
	.quad __asm32_int80_ustat                  /* 62 */
	.quad __asm32_int80_dup2                   /* 63 */
	.quad __asm32_int80_getppid                /* 64 */
	.quad __asm32_int80_getpgrp                /* 65 */
	.quad __asm32_int80_setsid                 /* 66 */
	.quad __asm32_int80_sigaction              /* 67 */
	.quad __asm32_int80_sgetmask               /* 68 */
	.quad __asm32_int80_ssetmask               /* 69 */
	.quad __asm32_int80_setreuid               /* 70 */
	.quad __asm32_int80_setregid               /* 71 */
	.quad __asm32_int80_sigsuspend             /* 72 */
	.quad __asm32_int80_sigpending             /* 73 */
	.quad __asm32_int80_sethostname            /* 74 */
	.quad __asm32_int80_setrlimit              /* 75 */
	.quad __asm32_int80_getrlimit              /* 76 */
	.quad __asm32_int80_getrusage              /* 77 */
	.quad __asm32_int80_gettimeofday           /* 78 */
	.quad __asm32_int80_settimeofday           /* 79 */
	.quad __asm32_int80_getgroups              /* 80 */
	.quad __asm32_int80_setgroups              /* 81 */
	.quad __asm32_int80_select                 /* 82 */
	.quad __asm32_int80_symlink                /* 83 */
	.quad __asm32_int80_linux_oldlstat         /* 84 */
	.quad __asm32_int80_readlink               /* 85 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_swapon                 /* 87 */
	.quad __asm32_int80_reboot                 /* 88 */
	.quad __asm32_int80_readdir                /* 89 */
	.quad __asm32_int80_mmap                   /* 90 */
	.quad __asm32_int80_munmap                 /* 91 */
	.quad __asm32_int80_truncate               /* 92 */
	.quad __asm32_int80_ftruncate              /* 93 */
	.quad __asm32_int80_fchmod                 /* 94 */
	.quad __asm32_int80_fchown                 /* 95 */
	.quad __asm32_int80_getpriority            /* 96 */
	.quad __asm32_int80_setpriority            /* 97 */
	.quad __asm32_int80_profil                 /* 98 */
	.quad __asm32_int80_statfs                 /* 99 */
	.quad __asm32_int80_fstatfs                /* 100 */
	.quad __asm32_int80_ioperm                 /* 101 */
	.quad __asm32_int80_socketcall             /* 102 */
	.quad __asm32_int80_syslog                 /* 103 */
	.quad __asm32_int80_setitimer              /* 104 */
	.quad __asm32_int80_getitimer              /* 105 */
	.quad __asm32_int80_linux_stat32           /* 106 */
	.quad __asm32_int80_linux_lstat32          /* 107 */
	.quad __asm32_int80_linux_fstat32          /* 108 */
	.quad __asm32_int80_olduname               /* 109 */
	.quad __asm32_int80_iopl                   /* 110 */
	.quad __asm32_int80_vhangup                /* 111 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_wait4                  /* 114 */
	.quad __asm32_int80_swapoff                /* 115 */
	.quad __asm32_int80_sysinfo                /* 116 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_fsync                  /* 118 */
	.quad __asm32_int80_sigreturn              /* 119 */
	.quad __asm32_int80_clone                  /* 120 */
	.quad __asm32_int80_setdomainname          /* 121 */
	.quad __asm32_int80_uname                  /* 122 */
	.quad __asm32_int80_modify_ldt             /* 123 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_mprotect               /* 125 */
	.quad __asm32_int80_sigprocmask            /* 126 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_getpgid                /* 132 */
	.quad __asm32_int80_fchdir                 /* 133 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_setfsuid               /* 138 */
	.quad __asm32_int80_setfsgid               /* 139 */
	.quad __asm32_int80__llseek                /* 140 */
	.quad __asm32_int80_getdents               /* 141 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_flock                  /* 143 */
	.quad __asm32_int80_msync                  /* 144 */
	.quad __asm32_int80_readv                  /* 145 */
	.quad __asm32_int80_writev                 /* 146 */
	.quad __asm32_int80_getsid                 /* 147 */
	.quad __asm32_int80_fdatasync              /* 148 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_mlock                  /* 150 */
	.quad __asm32_int80_munlock                /* 151 */
	.quad __asm32_int80_mlockall               /* 152 */
	.quad __asm32_int80_munlockall             /* 153 */
	.quad __asm32_int80_sched_setparam         /* 154 */
	.quad __asm32_int80_sched_getparam         /* 155 */
	.quad __asm32_int80_sched_setscheduler     /* 156 */
	.quad __asm32_int80_sched_getscheduler     /* 157 */
	.quad __asm32_int80_sched_yield            /* 158 */
	.quad __asm32_int80_sched_get_priority_max /* 159 */
	.quad __asm32_int80_sched_get_priority_min /* 160 */
	.quad __asm32_int80_sched_rr_get_interval  /* 161 */
	.quad __asm32_int80_nanosleep              /* 162 */
	.quad __asm32_int80_mremap                 /* 163 */
	.quad __asm32_int80_setresuid              /* 164 */
	.quad __asm32_int80_getresuid              /* 165 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_poll                   /* 168 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_setresgid              /* 170 */
	.quad __asm32_int80_getresgid              /* 171 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_rt_sigaction           /* 174 */
	.quad __asm32_int80_rt_sigprocmask         /* 175 */
	.quad __asm32_int80_rt_sigpending          /* 176 */
	.quad __asm32_int80_rt_sigtimedwait        /* 177 */
	.quad __asm32_int80_rt_sigqueueinfo        /* 178 */
	.quad __asm32_int80_rt_sigsuspend          /* 179 */
	.quad __asm32_int80_pread64                /* 180 */
	.quad __asm32_int80_pwrite64               /* 181 */
	.quad __asm32_int80_chown                  /* 182 */
	.quad __asm32_int80_getcwd                 /* 183 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_sigaltstack            /* 186 */
	.quad __asm32_int80_sendfile               /* 187 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_vfork                  /* 190 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_mmap2                  /* 192 */
	.quad __asm32_int80_truncate64             /* 193 */
	.quad __asm32_int80_ftruncate64            /* 194 */
	.quad __asm32_int80_linux_stat64           /* 195 */
	.quad __asm32_int80_linux_lstat64          /* 196 */
	.quad __asm32_int80_linux_fstat64          /* 197 */
	.quad __asm32_int80_lchown32               /* 198 */
	.quad __asm32_int80_getuid32               /* 199 */
	.quad __asm32_int80_getgid32               /* 200 */
	.quad __asm32_int80_geteuid32              /* 201 */
	.quad __asm32_int80_getegid32              /* 202 */
	.quad __asm32_int80_setreuid32             /* 203 */
	.quad __asm32_int80_setregid32             /* 204 */
	.quad __asm32_int80_getgroups32            /* 205 */
	.quad __asm32_int80_setgroups32            /* 206 */
	.quad __asm32_int80_fchown32               /* 207 */
	.quad __asm32_int80_setresuid32            /* 208 */
	.quad __asm32_int80_getresuid32            /* 209 */
	.quad __asm32_int80_setresgid32            /* 210 */
	.quad __asm32_int80_getresgid32            /* 211 */
	.quad __asm32_int80_chown32                /* 212 */
	.quad __asm32_int80_setuid32               /* 213 */
	.quad __asm32_int80_setgid32               /* 214 */
	.quad __asm32_int80_setfsuid32             /* 215 */
	.quad __asm32_int80_setfsgid32             /* 216 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_mincore                /* 218 */
	.quad __asm32_int80_madvise                /* 219 */
	.quad __asm32_int80_getdents64             /* 220 */
	.quad __asm32_int80_fcntl64                /* 221 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_gettid                 /* 224 */
	.quad __asm32_int80_readahead              /* 225 */
	.quad __asm32_int80_setxattr               /* 226 */
	.quad __asm32_int80_lsetxattr              /* 227 */
	.quad __asm32_int80_fsetxattr              /* 228 */
	.quad __asm32_int80_getxattr               /* 229 */
	.quad __asm32_int80_lgetxattr              /* 230 */
	.quad __asm32_int80_fgetxattr              /* 231 */
	.quad __asm32_int80_listxattr              /* 232 */
	.quad __asm32_int80_llistxattr             /* 233 */
	.quad __asm32_int80_flistxattr             /* 234 */
	.quad __asm32_int80_removexattr            /* 235 */
	.quad __asm32_int80_lremovexattr           /* 236 */
	.quad __asm32_int80_fremovexattr           /* 237 */
	.quad __asm32_int80_tkill                  /* 238 */
	.quad __asm32_int80_sendfile64             /* 239 */
	.quad __asm32_int80_futex                  /* 240 */
	.quad __asm32_int80_sched_setaffinity      /* 241 */
	.quad __asm32_int80_sched_getaffinity      /* 242 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_exit_group             /* 252 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_epoll_create           /* 254 */
	.quad __asm32_int80_epoll_ctl              /* 255 */
	.quad __asm32_int80_epoll_wait             /* 256 */
	.quad __asm32_int80_remap_file_pages       /* 257 */
	.quad __asm32_int80_set_tid_address        /* 258 */
	.quad __asm32_int80_timer_create           /* 259 */
	.quad __asm32_int80_timer_settime          /* 260 */
	.quad __asm32_int80_timer_gettime          /* 261 */
	.quad __asm32_int80_timer_getoverrun       /* 262 */
	.quad __asm32_int80_timer_delete           /* 263 */
	.quad __asm32_int80_clock_settime          /* 264 */
	.quad __asm32_int80_clock_gettime          /* 265 */
	.quad __asm32_int80_clock_getres           /* 266 */
	.quad __asm32_int80_clock_nanosleep        /* 267 */
	.quad __asm32_int80_statfs64               /* 268 */
	.quad __asm32_int80_fstatfs64              /* 269 */
	.quad __asm32_int80_tgkill                 /* 270 */
	.quad __asm32_int80_utimes                 /* 271 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_waitid                 /* 284 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_ioprio_set             /* 289 */
	.quad __asm32_int80_ioprio_get             /* 290 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_openat                 /* 295 */
	.quad __asm32_int80_mkdirat                /* 296 */
	.quad __asm32_int80_mknodat                /* 297 */
	.quad __asm32_int80_fchownat               /* 298 */
	.quad __asm32_int80_futimesat              /* 299 */
	.quad __asm32_int80_linux_fstatat64        /* 300 */
	.quad __asm32_int80_unlinkat               /* 301 */
	.quad __asm32_int80_renameat               /* 302 */
	.quad __asm32_int80_linkat                 /* 303 */
	.quad __asm32_int80_symlinkat              /* 304 */
	.quad __asm32_int80_readlinkat             /* 305 */
	.quad __asm32_int80_fchmodat               /* 306 */
	.quad __asm32_int80_faccessat              /* 307 */
	.quad __asm32_int80_pselect6               /* 308 */
	.quad __asm32_int80_ppoll                  /* 309 */
	.quad __asm32_int80_unshare                /* 310 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_splice                 /* 313 */
	.quad __asm32_int80_sync_file_range        /* 314 */
	.quad __asm32_int80_tee                    /* 315 */
	.quad __asm32_int80_vmsplice               /* 316 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_getcpu                 /* 318 */
	.quad __asm32_int80_epoll_pwait            /* 319 */
	.quad __asm32_int80_utimensat              /* 320 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_timerfd_create         /* 322 */
	.quad __asm32_int80_eventfd                /* 323 */
	.quad __asm32_int80_fallocate              /* 324 */
	.quad __asm32_int80_timerfd_settime        /* 325 */
	.quad __asm32_int80_timerfd_gettime        /* 326 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_eventfd2               /* 328 */
	.quad __asm32_int80_epoll_create1          /* 329 */
	.quad __asm32_int80_dup3                   /* 330 */
	.quad __asm32_int80_pipe2                  /* 331 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_preadv                 /* 333 */
	.quad __asm32_int80_pwritev                /* 334 */
	.quad __asm32_int80_rt_tgsigqueueinfo      /* 335 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_recvmmsg               /* 337 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_prlimit64              /* 340 */
	.quad __asm32_int80_name_to_handle_at      /* 341 */
	.quad __asm32_int80_open_by_handle_at      /* 342 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_syncfs                 /* 344 */
	.quad __asm32_int80_sendmmsg               /* 345 */
	.quad __asm32_int80_setns                  /* 346 */
	.quad __asm32_int80_process_vm_readv       /* 347 */
	.quad __asm32_int80_process_vm_writev      /* 348 */
	.quad __asm32_int80_kcmp                   /* 349 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_renameat2              /* 353 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_execveat               /* 358 */
	.quad __asm32_int80_socket                 /* 359 */
	.quad __asm32_int80_socketpair             /* 360 */
	.quad __asm32_int80_bind                   /* 361 */
	.quad __asm32_int80_connect                /* 362 */
	.quad __asm32_int80_listen                 /* 363 */
	.quad __asm32_int80_accept4                /* 364 */
	.quad __asm32_int80_getsockopt             /* 365 */
	.quad __asm32_int80_setsockopt             /* 366 */
	.quad __asm32_int80_getsockname            /* 367 */
	.quad __asm32_int80_getpeername            /* 368 */
	.quad __asm32_int80_sendto                 /* 369 */
	.quad __asm32_int80_sendmsg                /* 370 */
	.quad __asm32_int80_recvfrom               /* 371 */
	.quad __asm32_int80_recvmsg                /* 372 */
	.quad __asm32_int80_shutdown               /* 373 */
END(__asm32_syscallrouter_int80)


PUBLIC_OBJECT(__asm32_exsyscallrouter_int80)
	.quad __asm32_int80_hop                     /* 0x80000001 */
	.quad __asm32_int80_hopf                    /* 0x80000002 */
	.quad __asm32_int80_readf                   /* 0x80000003 */
	.quad __asm32_int80_writef                  /* 0x80000004 */
	.quad __asm32_int80_detach                  /* 0x80000005 */
	.quad __asm32_int80_getdrives               /* 0x80000006 */
	.quad __asm32_int80_frealpath4              /* 0x80000007 */
	.quad __asm32_int80_frealpathat             /* 0x80000008 */
	.quad __asm32_int80_rpc_schedule            /* 0x80000009 */
	.quad __asm32_int80_sysctl                  /* 0x8000000a */
	.quad __asm32_int80_openpty                 /* 0x8000000b */
	.quad __asm32_int80_fchdirat                /* 0x8000000c */
	.quad __asm32_int80_time64                  /* 0x8000000d */
	.quad __asm32_int80_set_exception_handler   /* 0x8000000e */
	.quad __asm32_int80_get_exception_handler   /* 0x8000000f */
	.quad __asm32_int80_set_library_listdef     /* 0x80000010 */
	.quad __asm32_int80_debugtrap               /* 0x80000011 */
	.quad __asm32_int80_lfutex                  /* 0x80000012 */
	.quad __asm32_int80_lseek64                 /* 0x80000013 */
	.quad __asm32_int80_lfutexlock              /* 0x80000014 */
	.quad __asm32_int80_lfutexexpr              /* 0x80000015 */
	.quad __asm32_int80_lfutexlockexpr          /* 0x80000016 */
	.quad __asm32_int80_mktty                   /* 0x80000017 */
	.quad __asm32_int80_raiseat                 /* 0x80000018 */
	.quad __asm32_int80_stime64                 /* 0x80000019 */
	.quad __asm32_int80_coredump                /* 0x8000001a */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_utime64                 /* 0x8000001e */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_ioctlf                  /* 0x80000036 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_fsmode                  /* 0x8000003c */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_gettimeofday64          /* 0x8000004e */
	.quad __asm32_int80_settimeofday64          /* 0x8000004f */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_select64                /* 0x80000052 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_maplibrary              /* 0x80000056 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_setitimer64             /* 0x80000068 */
	.quad __asm32_int80_getitimer64             /* 0x80000069 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_kreaddir                /* 0x8000008d */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_readvf                  /* 0x80000091 */
	.quad __asm32_int80_writevf                 /* 0x80000092 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_rpc_service             /* 0x8000009e */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_sched_rr_get_interval64 /* 0x800000a1 */
	.quad __asm32_int80_nanosleep64             /* 0x800000a2 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_rt_sigtimedwait64       /* 0x800000b1 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_pread64f                /* 0x800000b4 */
	.quad __asm32_int80_pwrite64f               /* 0x800000b5 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_kstat                   /* 0x800000c3 */
	.quad __asm32_int80_klstat                  /* 0x800000c4 */
	.quad __asm32_int80_kfstat                  /* 0x800000c5 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_kreaddirf               /* 0x800000dc */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_timer_settime64         /* 0x80000104 */
	.quad __asm32_int80_timer_gettime64         /* 0x80000105 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_clock_settime64         /* 0x80000108 */
	.quad __asm32_int80_clock_gettime64         /* 0x80000109 */
	.quad __asm32_int80_clock_getres64          /* 0x8000010a */
	.quad __asm32_int80_clock_nanosleep64       /* 0x8000010b */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_utimes64                /* 0x8000010f */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_fmkdirat                /* 0x80000128 */
	.quad __asm32_int80_fmknodat                /* 0x80000129 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_futimesat64             /* 0x8000012b */
	.quad __asm32_int80_kfstatat                /* 0x8000012c */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_frenameat               /* 0x8000012e */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_fsymlinkat              /* 0x80000130 */
	.quad __asm32_int80_freadlinkat             /* 0x80000131 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_pselect6_64             /* 0x80000134 */
	.quad __asm32_int80_ppoll64                 /* 0x80000135 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_utimensat64             /* 0x80000140 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_fallocate64             /* 0x80000144 */
	.quad __asm32_int80_timerfd_settime64       /* 0x80000145 */
	.quad __asm32_int80_timerfd_gettime64       /* 0x80000146 */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_preadvf                 /* 0x8000014d */
	.quad __asm32_int80_pwritevf                /* 0x8000014e */
	.quad __asm32_int80_invalid
	.quad __asm32_int80_invalid
	.quad __asm32_int80_recvmmsg64              /* 0x80000151 */
END(__asm32_exsyscallrouter_int80)


/****************************************************************************/
/* 32-bit System call router for <sysenter>                                 */
/****************************************************************************/
.section .rodata.x86.syscall32.router_sysenter
PUBLIC_OBJECT(__asm32_syscallrouter_sysenter)
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_exit                   /* 1 */
	.quad __asm32_sysenter_fork                   /* 2 */
	.quad __asm32_sysenter_read                   /* 3 */
	.quad __asm32_sysenter_write                  /* 4 */
	.quad __asm32_sysenter_open                   /* 5 */
	.quad __asm32_sysenter_close                  /* 6 */
	.quad __asm32_sysenter_waitpid                /* 7 */
	.quad __asm32_sysenter_creat                  /* 8 */
	.quad __asm32_sysenter_link                   /* 9 */
	.quad __asm32_sysenter_unlink                 /* 10 */
	.quad __asm32_sysenter_execve                 /* 11 */
	.quad __asm32_sysenter_chdir                  /* 12 */
	.quad __asm32_sysenter_time                   /* 13 */
	.quad __asm32_sysenter_mknod                  /* 14 */
	.quad __asm32_sysenter_chmod                  /* 15 */
	.quad __asm32_sysenter_lchown                 /* 16 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_linux_oldstat          /* 18 */
	.quad __asm32_sysenter_lseek                  /* 19 */
	.quad __asm32_sysenter_getpid                 /* 20 */
	.quad __asm32_sysenter_mount                  /* 21 */
	.quad __asm32_sysenter_umount                 /* 22 */
	.quad __asm32_sysenter_setuid                 /* 23 */
	.quad __asm32_sysenter_getuid                 /* 24 */
	.quad __asm32_sysenter_stime                  /* 25 */
	.quad __asm32_sysenter_ptrace                 /* 26 */
	.quad __asm32_sysenter_alarm                  /* 27 */
	.quad __asm32_sysenter_linux_oldfstat         /* 28 */
	.quad __asm32_sysenter_pause                  /* 29 */
	.quad __asm32_sysenter_utime                  /* 30 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_access                 /* 33 */
	.quad __asm32_sysenter_nice                   /* 34 */
	.quad __asm32_sysenter_ftime                  /* 35 */
	.quad __asm32_sysenter_sync                   /* 36 */
	.quad __asm32_sysenter_kill                   /* 37 */
	.quad __asm32_sysenter_rename                 /* 38 */
	.quad __asm32_sysenter_mkdir                  /* 39 */
	.quad __asm32_sysenter_rmdir                  /* 40 */
	.quad __asm32_sysenter_dup                    /* 41 */
	.quad __asm32_sysenter_pipe                   /* 42 */
	.quad __asm32_sysenter_times                  /* 43 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_brk                    /* 45 */
	.quad __asm32_sysenter_setgid                 /* 46 */
	.quad __asm32_sysenter_getgid                 /* 47 */
	.quad __asm32_sysenter_signal                 /* 48 */
	.quad __asm32_sysenter_geteuid                /* 49 */
	.quad __asm32_sysenter_getegid                /* 50 */
	.quad __asm32_sysenter_acct                   /* 51 */
	.quad __asm32_sysenter_umount2                /* 52 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_ioctl                  /* 54 */
	.quad __asm32_sysenter_fcntl                  /* 55 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_setpgid                /* 57 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_oldolduname            /* 59 */
	.quad __asm32_sysenter_umask                  /* 60 */
	.quad __asm32_sysenter_chroot                 /* 61 */
	.quad __asm32_sysenter_ustat                  /* 62 */
	.quad __asm32_sysenter_dup2                   /* 63 */
	.quad __asm32_sysenter_getppid                /* 64 */
	.quad __asm32_sysenter_getpgrp                /* 65 */
	.quad __asm32_sysenter_setsid                 /* 66 */
	.quad __asm32_sysenter_sigaction              /* 67 */
	.quad __asm32_sysenter_sgetmask               /* 68 */
	.quad __asm32_sysenter_ssetmask               /* 69 */
	.quad __asm32_sysenter_setreuid               /* 70 */
	.quad __asm32_sysenter_setregid               /* 71 */
	.quad __asm32_sysenter_sigsuspend             /* 72 */
	.quad __asm32_sysenter_sigpending             /* 73 */
	.quad __asm32_sysenter_sethostname            /* 74 */
	.quad __asm32_sysenter_setrlimit              /* 75 */
	.quad __asm32_sysenter_getrlimit              /* 76 */
	.quad __asm32_sysenter_getrusage              /* 77 */
	.quad __asm32_sysenter_gettimeofday           /* 78 */
	.quad __asm32_sysenter_settimeofday           /* 79 */
	.quad __asm32_sysenter_getgroups              /* 80 */
	.quad __asm32_sysenter_setgroups              /* 81 */
	.quad __asm32_sysenter_select                 /* 82 */
	.quad __asm32_sysenter_symlink                /* 83 */
	.quad __asm32_sysenter_linux_oldlstat         /* 84 */
	.quad __asm32_sysenter_readlink               /* 85 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_swapon                 /* 87 */
	.quad __asm32_sysenter_reboot                 /* 88 */
	.quad __asm32_sysenter_readdir                /* 89 */
	.quad __asm32_sysenter_mmap                   /* 90 */
	.quad __asm32_sysenter_munmap                 /* 91 */
	.quad __asm32_sysenter_truncate               /* 92 */
	.quad __asm32_sysenter_ftruncate              /* 93 */
	.quad __asm32_sysenter_fchmod                 /* 94 */
	.quad __asm32_sysenter_fchown                 /* 95 */
	.quad __asm32_sysenter_getpriority            /* 96 */
	.quad __asm32_sysenter_setpriority            /* 97 */
	.quad __asm32_sysenter_profil                 /* 98 */
	.quad __asm32_sysenter_statfs                 /* 99 */
	.quad __asm32_sysenter_fstatfs                /* 100 */
	.quad __asm32_sysenter_ioperm                 /* 101 */
	.quad __asm32_sysenter_socketcall             /* 102 */
	.quad __asm32_sysenter_syslog                 /* 103 */
	.quad __asm32_sysenter_setitimer              /* 104 */
	.quad __asm32_sysenter_getitimer              /* 105 */
	.quad __asm32_sysenter_linux_stat32           /* 106 */
	.quad __asm32_sysenter_linux_lstat32          /* 107 */
	.quad __asm32_sysenter_linux_fstat32          /* 108 */
	.quad __asm32_sysenter_olduname               /* 109 */
	.quad __asm32_sysenter_iopl                   /* 110 */
	.quad __asm32_sysenter_vhangup                /* 111 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_wait4                  /* 114 */
	.quad __asm32_sysenter_swapoff                /* 115 */
	.quad __asm32_sysenter_sysinfo                /* 116 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_fsync                  /* 118 */
	.quad __asm32_sysenter_sigreturn              /* 119 */
	.quad __asm32_sysenter_clone                  /* 120 */
	.quad __asm32_sysenter_setdomainname          /* 121 */
	.quad __asm32_sysenter_uname                  /* 122 */
	.quad __asm32_sysenter_modify_ldt             /* 123 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_mprotect               /* 125 */
	.quad __asm32_sysenter_sigprocmask            /* 126 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_getpgid                /* 132 */
	.quad __asm32_sysenter_fchdir                 /* 133 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_setfsuid               /* 138 */
	.quad __asm32_sysenter_setfsgid               /* 139 */
	.quad __asm32_sysenter__llseek                /* 140 */
	.quad __asm32_sysenter_getdents               /* 141 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_flock                  /* 143 */
	.quad __asm32_sysenter_msync                  /* 144 */
	.quad __asm32_sysenter_readv                  /* 145 */
	.quad __asm32_sysenter_writev                 /* 146 */
	.quad __asm32_sysenter_getsid                 /* 147 */
	.quad __asm32_sysenter_fdatasync              /* 148 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_mlock                  /* 150 */
	.quad __asm32_sysenter_munlock                /* 151 */
	.quad __asm32_sysenter_mlockall               /* 152 */
	.quad __asm32_sysenter_munlockall             /* 153 */
	.quad __asm32_sysenter_sched_setparam         /* 154 */
	.quad __asm32_sysenter_sched_getparam         /* 155 */
	.quad __asm32_sysenter_sched_setscheduler     /* 156 */
	.quad __asm32_sysenter_sched_getscheduler     /* 157 */
	.quad __asm32_sysenter_sched_yield            /* 158 */
	.quad __asm32_sysenter_sched_get_priority_max /* 159 */
	.quad __asm32_sysenter_sched_get_priority_min /* 160 */
	.quad __asm32_sysenter_sched_rr_get_interval  /* 161 */
	.quad __asm32_sysenter_nanosleep              /* 162 */
	.quad __asm32_sysenter_mremap                 /* 163 */
	.quad __asm32_sysenter_setresuid              /* 164 */
	.quad __asm32_sysenter_getresuid              /* 165 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_poll                   /* 168 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_setresgid              /* 170 */
	.quad __asm32_sysenter_getresgid              /* 171 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_rt_sigaction           /* 174 */
	.quad __asm32_sysenter_rt_sigprocmask         /* 175 */
	.quad __asm32_sysenter_rt_sigpending          /* 176 */
	.quad __asm32_sysenter_rt_sigtimedwait        /* 177 */
	.quad __asm32_sysenter_rt_sigqueueinfo        /* 178 */
	.quad __asm32_sysenter_rt_sigsuspend          /* 179 */
	.quad __asm32_sysenter_pread64                /* 180 */
	.quad __asm32_sysenter_pwrite64               /* 181 */
	.quad __asm32_sysenter_chown                  /* 182 */
	.quad __asm32_sysenter_getcwd                 /* 183 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_sigaltstack            /* 186 */
	.quad __asm32_sysenter_sendfile               /* 187 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_vfork                  /* 190 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_mmap2                  /* 192 */
	.quad __asm32_sysenter_truncate64             /* 193 */
	.quad __asm32_sysenter_ftruncate64            /* 194 */
	.quad __asm32_sysenter_linux_stat64           /* 195 */
	.quad __asm32_sysenter_linux_lstat64          /* 196 */
	.quad __asm32_sysenter_linux_fstat64          /* 197 */
	.quad __asm32_sysenter_lchown32               /* 198 */
	.quad __asm32_sysenter_getuid32               /* 199 */
	.quad __asm32_sysenter_getgid32               /* 200 */
	.quad __asm32_sysenter_geteuid32              /* 201 */
	.quad __asm32_sysenter_getegid32              /* 202 */
	.quad __asm32_sysenter_setreuid32             /* 203 */
	.quad __asm32_sysenter_setregid32             /* 204 */
	.quad __asm32_sysenter_getgroups32            /* 205 */
	.quad __asm32_sysenter_setgroups32            /* 206 */
	.quad __asm32_sysenter_fchown32               /* 207 */
	.quad __asm32_sysenter_setresuid32            /* 208 */
	.quad __asm32_sysenter_getresuid32            /* 209 */
	.quad __asm32_sysenter_setresgid32            /* 210 */
	.quad __asm32_sysenter_getresgid32            /* 211 */
	.quad __asm32_sysenter_chown32                /* 212 */
	.quad __asm32_sysenter_setuid32               /* 213 */
	.quad __asm32_sysenter_setgid32               /* 214 */
	.quad __asm32_sysenter_setfsuid32             /* 215 */
	.quad __asm32_sysenter_setfsgid32             /* 216 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_mincore                /* 218 */
	.quad __asm32_sysenter_madvise                /* 219 */
	.quad __asm32_sysenter_getdents64             /* 220 */
	.quad __asm32_sysenter_fcntl64                /* 221 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_gettid                 /* 224 */
	.quad __asm32_sysenter_readahead              /* 225 */
	.quad __asm32_sysenter_setxattr               /* 226 */
	.quad __asm32_sysenter_lsetxattr              /* 227 */
	.quad __asm32_sysenter_fsetxattr              /* 228 */
	.quad __asm32_sysenter_getxattr               /* 229 */
	.quad __asm32_sysenter_lgetxattr              /* 230 */
	.quad __asm32_sysenter_fgetxattr              /* 231 */
	.quad __asm32_sysenter_listxattr              /* 232 */
	.quad __asm32_sysenter_llistxattr             /* 233 */
	.quad __asm32_sysenter_flistxattr             /* 234 */
	.quad __asm32_sysenter_removexattr            /* 235 */
	.quad __asm32_sysenter_lremovexattr           /* 236 */
	.quad __asm32_sysenter_fremovexattr           /* 237 */
	.quad __asm32_sysenter_tkill                  /* 238 */
	.quad __asm32_sysenter_sendfile64             /* 239 */
	.quad __asm32_sysenter_futex                  /* 240 */
	.quad __asm32_sysenter_sched_setaffinity      /* 241 */
	.quad __asm32_sysenter_sched_getaffinity      /* 242 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_exit_group             /* 252 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_epoll_create           /* 254 */
	.quad __asm32_sysenter_epoll_ctl              /* 255 */
	.quad __asm32_sysenter_epoll_wait             /* 256 */
	.quad __asm32_sysenter_remap_file_pages       /* 257 */
	.quad __asm32_sysenter_set_tid_address        /* 258 */
	.quad __asm32_sysenter_timer_create           /* 259 */
	.quad __asm32_sysenter_timer_settime          /* 260 */
	.quad __asm32_sysenter_timer_gettime          /* 261 */
	.quad __asm32_sysenter_timer_getoverrun       /* 262 */
	.quad __asm32_sysenter_timer_delete           /* 263 */
	.quad __asm32_sysenter_clock_settime          /* 264 */
	.quad __asm32_sysenter_clock_gettime          /* 265 */
	.quad __asm32_sysenter_clock_getres           /* 266 */
	.quad __asm32_sysenter_clock_nanosleep        /* 267 */
	.quad __asm32_sysenter_statfs64               /* 268 */
	.quad __asm32_sysenter_fstatfs64              /* 269 */
	.quad __asm32_sysenter_tgkill                 /* 270 */
	.quad __asm32_sysenter_utimes                 /* 271 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_waitid                 /* 284 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_ioprio_set             /* 289 */
	.quad __asm32_sysenter_ioprio_get             /* 290 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_openat                 /* 295 */
	.quad __asm32_sysenter_mkdirat                /* 296 */
	.quad __asm32_sysenter_mknodat                /* 297 */
	.quad __asm32_sysenter_fchownat               /* 298 */
	.quad __asm32_sysenter_futimesat              /* 299 */
	.quad __asm32_sysenter_linux_fstatat64        /* 300 */
	.quad __asm32_sysenter_unlinkat               /* 301 */
	.quad __asm32_sysenter_renameat               /* 302 */
	.quad __asm32_sysenter_linkat                 /* 303 */
	.quad __asm32_sysenter_symlinkat              /* 304 */
	.quad __asm32_sysenter_readlinkat             /* 305 */
	.quad __asm32_sysenter_fchmodat               /* 306 */
	.quad __asm32_sysenter_faccessat              /* 307 */
	.quad __asm32_sysenter_pselect6               /* 308 */
	.quad __asm32_sysenter_ppoll                  /* 309 */
	.quad __asm32_sysenter_unshare                /* 310 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_splice                 /* 313 */
	.quad __asm32_sysenter_sync_file_range        /* 314 */
	.quad __asm32_sysenter_tee                    /* 315 */
	.quad __asm32_sysenter_vmsplice               /* 316 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_getcpu                 /* 318 */
	.quad __asm32_sysenter_epoll_pwait            /* 319 */
	.quad __asm32_sysenter_utimensat              /* 320 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_timerfd_create         /* 322 */
	.quad __asm32_sysenter_eventfd                /* 323 */
	.quad __asm32_sysenter_fallocate              /* 324 */
	.quad __asm32_sysenter_timerfd_settime        /* 325 */
	.quad __asm32_sysenter_timerfd_gettime        /* 326 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_eventfd2               /* 328 */
	.quad __asm32_sysenter_epoll_create1          /* 329 */
	.quad __asm32_sysenter_dup3                   /* 330 */
	.quad __asm32_sysenter_pipe2                  /* 331 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_preadv                 /* 333 */
	.quad __asm32_sysenter_pwritev                /* 334 */
	.quad __asm32_sysenter_rt_tgsigqueueinfo      /* 335 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_recvmmsg               /* 337 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_prlimit64              /* 340 */
	.quad __asm32_sysenter_name_to_handle_at      /* 341 */
	.quad __asm32_sysenter_open_by_handle_at      /* 342 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_syncfs                 /* 344 */
	.quad __asm32_sysenter_sendmmsg               /* 345 */
	.quad __asm32_sysenter_setns                  /* 346 */
	.quad __asm32_sysenter_process_vm_readv       /* 347 */
	.quad __asm32_sysenter_process_vm_writev      /* 348 */
	.quad __asm32_sysenter_kcmp                   /* 349 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_renameat2              /* 353 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_execveat               /* 358 */
	.quad __asm32_sysenter_socket                 /* 359 */
	.quad __asm32_sysenter_socketpair             /* 360 */
	.quad __asm32_sysenter_bind                   /* 361 */
	.quad __asm32_sysenter_connect                /* 362 */
	.quad __asm32_sysenter_listen                 /* 363 */
	.quad __asm32_sysenter_accept4                /* 364 */
	.quad __asm32_sysenter_getsockopt             /* 365 */
	.quad __asm32_sysenter_setsockopt             /* 366 */
	.quad __asm32_sysenter_getsockname            /* 367 */
	.quad __asm32_sysenter_getpeername            /* 368 */
	.quad __asm32_sysenter_sendto                 /* 369 */
	.quad __asm32_sysenter_sendmsg                /* 370 */
	.quad __asm32_sysenter_recvfrom               /* 371 */
	.quad __asm32_sysenter_recvmsg                /* 372 */
	.quad __asm32_sysenter_shutdown               /* 373 */
END(__asm32_syscallrouter_sysenter)


PUBLIC_OBJECT(__asm32_exsyscallrouter_sysenter)
	.quad __asm32_sysenter_hop                     /* 0x80000001 */
	.quad __asm32_sysenter_hopf                    /* 0x80000002 */
	.quad __asm32_sysenter_readf                   /* 0x80000003 */
	.quad __asm32_sysenter_writef                  /* 0x80000004 */
	.quad __asm32_sysenter_detach                  /* 0x80000005 */
	.quad __asm32_sysenter_getdrives               /* 0x80000006 */
	.quad __asm32_sysenter_frealpath4              /* 0x80000007 */
	.quad __asm32_sysenter_frealpathat             /* 0x80000008 */
	.quad __asm32_sysenter_rpc_schedule            /* 0x80000009 */
	.quad __asm32_sysenter_sysctl                  /* 0x8000000a */
	.quad __asm32_sysenter_openpty                 /* 0x8000000b */
	.quad __asm32_sysenter_fchdirat                /* 0x8000000c */
	.quad __asm32_sysenter_time64                  /* 0x8000000d */
	.quad __asm32_sysenter_set_exception_handler   /* 0x8000000e */
	.quad __asm32_sysenter_get_exception_handler   /* 0x8000000f */
	.quad __asm32_sysenter_set_library_listdef     /* 0x80000010 */
	.quad __asm32_sysenter_debugtrap               /* 0x80000011 */
	.quad __asm32_sysenter_lfutex                  /* 0x80000012 */
	.quad __asm32_sysenter_lseek64                 /* 0x80000013 */
	.quad __asm32_sysenter_lfutexlock              /* 0x80000014 */
	.quad __asm32_sysenter_lfutexexpr              /* 0x80000015 */
	.quad __asm32_sysenter_lfutexlockexpr          /* 0x80000016 */
	.quad __asm32_sysenter_mktty                   /* 0x80000017 */
	.quad __asm32_sysenter_raiseat                 /* 0x80000018 */
	.quad __asm32_sysenter_stime64                 /* 0x80000019 */
	.quad __asm32_sysenter_coredump                /* 0x8000001a */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_utime64                 /* 0x8000001e */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_ioctlf                  /* 0x80000036 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_fsmode                  /* 0x8000003c */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_gettimeofday64          /* 0x8000004e */
	.quad __asm32_sysenter_settimeofday64          /* 0x8000004f */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_select64                /* 0x80000052 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_maplibrary              /* 0x80000056 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_setitimer64             /* 0x80000068 */
	.quad __asm32_sysenter_getitimer64             /* 0x80000069 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_kreaddir                /* 0x8000008d */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_readvf                  /* 0x80000091 */
	.quad __asm32_sysenter_writevf                 /* 0x80000092 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_rpc_service             /* 0x8000009e */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_sched_rr_get_interval64 /* 0x800000a1 */
	.quad __asm32_sysenter_nanosleep64             /* 0x800000a2 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_rt_sigtimedwait64       /* 0x800000b1 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_pread64f                /* 0x800000b4 */
	.quad __asm32_sysenter_pwrite64f               /* 0x800000b5 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_kstat                   /* 0x800000c3 */
	.quad __asm32_sysenter_klstat                  /* 0x800000c4 */
	.quad __asm32_sysenter_kfstat                  /* 0x800000c5 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_kreaddirf               /* 0x800000dc */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_timer_settime64         /* 0x80000104 */
	.quad __asm32_sysenter_timer_gettime64         /* 0x80000105 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_clock_settime64         /* 0x80000108 */
	.quad __asm32_sysenter_clock_gettime64         /* 0x80000109 */
	.quad __asm32_sysenter_clock_getres64          /* 0x8000010a */
	.quad __asm32_sysenter_clock_nanosleep64       /* 0x8000010b */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_utimes64                /* 0x8000010f */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_fmkdirat                /* 0x80000128 */
	.quad __asm32_sysenter_fmknodat                /* 0x80000129 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_futimesat64             /* 0x8000012b */
	.quad __asm32_sysenter_kfstatat                /* 0x8000012c */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_frenameat               /* 0x8000012e */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_fsymlinkat              /* 0x80000130 */
	.quad __asm32_sysenter_freadlinkat             /* 0x80000131 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_pselect6_64             /* 0x80000134 */
	.quad __asm32_sysenter_ppoll64                 /* 0x80000135 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_utimensat64             /* 0x80000140 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_fallocate64             /* 0x80000144 */
	.quad __asm32_sysenter_timerfd_settime64       /* 0x80000145 */
	.quad __asm32_sysenter_timerfd_gettime64       /* 0x80000146 */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_preadvf                 /* 0x8000014d */
	.quad __asm32_sysenter_pwritevf                /* 0x8000014e */
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_invalid
	.quad __asm32_sysenter_recvmmsg64              /* 0x80000151 */
END(__asm32_exsyscallrouter_sysenter)


/****************************************************************************/
/* 32-bit System call router for high-level C-implementations               */
/****************************************************************************/
.section .rodata.x86.syscall32.c_router
PUBLIC_OBJECT(__c32_syscallrouter)
	.quad sys32_invalid0
	.quad sys32_exit                   /* 1 */
	.quad sys32_fork                   /* 2 */
	.quad sys32_read                   /* 3 */
	.quad sys32_write                  /* 4 */
	.quad sys32_open                   /* 5 */
	.quad sys32_close                  /* 6 */
	.quad sys32_waitpid                /* 7 */
	.quad sys32_creat                  /* 8 */
	.quad sys32_link                   /* 9 */
	.quad sys32_unlink                 /* 10 */
	.quad sys32_execve                 /* 11 */
	.quad sys32_chdir                  /* 12 */
	.quad sys32_time                   /* 13 */
	.quad sys32_mknod                  /* 14 */
	.quad sys32_chmod                  /* 15 */
	.quad sys32_lchown                 /* 16 */
	.quad sys32_invalid0
	.quad sys32_linux_oldstat          /* 18 */
	.quad sys32_lseek                  /* 19 */
	.quad sys32_getpid                 /* 20 */
	.quad sys32_mount                  /* 21 */
	.quad sys32_umount                 /* 22 */
	.quad sys32_setuid                 /* 23 */
	.quad sys32_getuid                 /* 24 */
	.quad sys32_stime                  /* 25 */
	.quad sys32_ptrace                 /* 26 */
	.quad sys32_alarm                  /* 27 */
	.quad sys32_linux_oldfstat         /* 28 */
	.quad sys32_pause                  /* 29 */
	.quad sys32_utime                  /* 30 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_access                 /* 33 */
	.quad sys32_nice                   /* 34 */
	.quad sys32_ftime                  /* 35 */
	.quad sys32_sync                   /* 36 */
	.quad sys32_kill                   /* 37 */
	.quad sys32_rename                 /* 38 */
	.quad sys32_mkdir                  /* 39 */
	.quad sys32_rmdir                  /* 40 */
	.quad sys32_dup                    /* 41 */
	.quad sys32_pipe                   /* 42 */
	.quad sys32_times                  /* 43 */
	.quad sys32_invalid0
	.quad sys32_brk                    /* 45 */
	.quad sys32_setgid                 /* 46 */
	.quad sys32_getgid                 /* 47 */
	.quad sys32_signal                 /* 48 */
	.quad sys32_geteuid                /* 49 */
	.quad sys32_getegid                /* 50 */
	.quad sys32_acct                   /* 51 */
	.quad sys32_umount2                /* 52 */
	.quad sys32_invalid0
	.quad sys32_ioctl                  /* 54 */
	.quad sys32_fcntl                  /* 55 */
	.quad sys32_invalid0
	.quad sys32_setpgid                /* 57 */
	.quad sys32_invalid0
	.quad sys32_oldolduname            /* 59 */
	.quad sys32_umask                  /* 60 */
	.quad sys32_chroot                 /* 61 */
	.quad sys32_ustat                  /* 62 */
	.quad sys32_dup2                   /* 63 */
	.quad sys32_getppid                /* 64 */
	.quad sys32_getpgrp                /* 65 */
	.quad sys32_setsid                 /* 66 */
	.quad sys32_sigaction              /* 67 */
	.quad sys32_sgetmask               /* 68 */
	.quad sys32_ssetmask               /* 69 */
	.quad sys32_setreuid               /* 70 */
	.quad sys32_setregid               /* 71 */
	.quad sys32_sigsuspend             /* 72 */
	.quad sys32_sigpending             /* 73 */
	.quad sys32_sethostname            /* 74 */
	.quad sys32_setrlimit              /* 75 */
	.quad sys32_getrlimit              /* 76 */
	.quad sys32_getrusage              /* 77 */
	.quad sys32_gettimeofday           /* 78 */
	.quad sys32_settimeofday           /* 79 */
	.quad sys32_getgroups              /* 80 */
	.quad sys32_setgroups              /* 81 */
	.quad sys32_select                 /* 82 */
	.quad sys32_symlink                /* 83 */
	.quad sys32_linux_oldlstat         /* 84 */
	.quad sys32_readlink               /* 85 */
	.quad sys32_invalid0
	.quad sys32_swapon                 /* 87 */
	.quad sys32_reboot                 /* 88 */
	.quad sys32_readdir                /* 89 */
	.quad sys32_mmap                   /* 90 */
	.quad sys32_munmap                 /* 91 */
	.quad sys32_truncate               /* 92 */
	.quad sys32_ftruncate              /* 93 */
	.quad sys32_fchmod                 /* 94 */
	.quad sys32_fchown                 /* 95 */
	.quad sys32_getpriority            /* 96 */
	.quad sys32_setpriority            /* 97 */
	.quad sys32_profil                 /* 98 */
	.quad sys32_statfs                 /* 99 */
	.quad sys32_fstatfs                /* 100 */
	.quad sys32_ioperm                 /* 101 */
	.quad sys32_socketcall             /* 102 */
	.quad sys32_syslog                 /* 103 */
	.quad sys32_setitimer              /* 104 */
	.quad sys32_getitimer              /* 105 */
	.quad sys32_linux_stat32           /* 106 */
	.quad sys32_linux_lstat32          /* 107 */
	.quad sys32_linux_fstat32          /* 108 */
	.quad sys32_olduname               /* 109 */
	.quad sys32_iopl                   /* 110 */
	.quad sys32_vhangup                /* 111 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_wait4                  /* 114 */
	.quad sys32_swapoff                /* 115 */
	.quad sys32_sysinfo                /* 116 */
	.quad sys32_invalid0
	.quad sys32_fsync                  /* 118 */
	.quad sys32_sigreturn              /* 119 */
	.quad sys32_clone                  /* 120 */
	.quad sys32_setdomainname          /* 121 */
	.quad sys32_uname                  /* 122 */
	.quad sys32_modify_ldt             /* 123 */
	.quad sys32_invalid0
	.quad sys32_mprotect               /* 125 */
	.quad sys32_sigprocmask            /* 126 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_getpgid                /* 132 */
	.quad sys32_fchdir                 /* 133 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_setfsuid               /* 138 */
	.quad sys32_setfsgid               /* 139 */
	.quad sys32__llseek                /* 140 */
	.quad sys32_getdents               /* 141 */
	.quad sys32_invalid0
	.quad sys32_flock                  /* 143 */
	.quad sys32_msync                  /* 144 */
	.quad sys32_readv                  /* 145 */
	.quad sys32_writev                 /* 146 */
	.quad sys32_getsid                 /* 147 */
	.quad sys32_fdatasync              /* 148 */
	.quad sys32_invalid0
	.quad sys32_mlock                  /* 150 */
	.quad sys32_munlock                /* 151 */
	.quad sys32_mlockall               /* 152 */
	.quad sys32_munlockall             /* 153 */
	.quad sys32_sched_setparam         /* 154 */
	.quad sys32_sched_getparam         /* 155 */
	.quad sys32_sched_setscheduler     /* 156 */
	.quad sys32_sched_getscheduler     /* 157 */
	.quad sys32_sched_yield            /* 158 */
	.quad sys32_sched_get_priority_max /* 159 */
	.quad sys32_sched_get_priority_min /* 160 */
	.quad sys32_sched_rr_get_interval  /* 161 */
	.quad sys32_nanosleep              /* 162 */
	.quad sys32_mremap                 /* 163 */
	.quad sys32_setresuid              /* 164 */
	.quad sys32_getresuid              /* 165 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_poll                   /* 168 */
	.quad sys32_invalid0
	.quad sys32_setresgid              /* 170 */
	.quad sys32_getresgid              /* 171 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_rt_sigaction           /* 174 */
	.quad sys32_rt_sigprocmask         /* 175 */
	.quad sys32_rt_sigpending          /* 176 */
	.quad sys32_rt_sigtimedwait        /* 177 */
	.quad sys32_rt_sigqueueinfo        /* 178 */
	.quad sys32_rt_sigsuspend          /* 179 */
	.quad sys32_pread64                /* 180 */
	.quad sys32_pwrite64               /* 181 */
	.quad sys32_chown                  /* 182 */
	.quad sys32_getcwd                 /* 183 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_sigaltstack            /* 186 */
	.quad sys32_sendfile               /* 187 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_vfork                  /* 190 */
	.quad sys32_invalid0
	.quad sys32_mmap2                  /* 192 */
	.quad sys32_truncate64             /* 193 */
	.quad sys32_ftruncate64            /* 194 */
	.quad sys32_linux_stat64           /* 195 */
	.quad sys32_linux_lstat64          /* 196 */
	.quad sys32_linux_fstat64          /* 197 */
	.quad sys32_lchown32               /* 198 */
	.quad sys32_getuid32               /* 199 */
	.quad sys32_getgid32               /* 200 */
	.quad sys32_geteuid32              /* 201 */
	.quad sys32_getegid32              /* 202 */
	.quad sys32_setreuid32             /* 203 */
	.quad sys32_setregid32             /* 204 */
	.quad sys32_getgroups32            /* 205 */
	.quad sys32_setgroups32            /* 206 */
	.quad sys32_fchown32               /* 207 */
	.quad sys32_setresuid32            /* 208 */
	.quad sys32_getresuid32            /* 209 */
	.quad sys32_setresgid32            /* 210 */
	.quad sys32_getresgid32            /* 211 */
	.quad sys32_chown32                /* 212 */
	.quad sys32_setuid32               /* 213 */
	.quad sys32_setgid32               /* 214 */
	.quad sys32_setfsuid32             /* 215 */
	.quad sys32_setfsgid32             /* 216 */
	.quad sys32_invalid0
	.quad sys32_mincore                /* 218 */
	.quad sys32_madvise                /* 219 */
	.quad sys32_getdents64             /* 220 */
	.quad sys32_fcntl64                /* 221 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_gettid                 /* 224 */
	.quad sys32_readahead              /* 225 */
	.quad sys32_setxattr               /* 226 */
	.quad sys32_lsetxattr              /* 227 */
	.quad sys32_fsetxattr              /* 228 */
	.quad sys32_getxattr               /* 229 */
	.quad sys32_lgetxattr              /* 230 */
	.quad sys32_fgetxattr              /* 231 */
	.quad sys32_listxattr              /* 232 */
	.quad sys32_llistxattr             /* 233 */
	.quad sys32_flistxattr             /* 234 */
	.quad sys32_removexattr            /* 235 */
	.quad sys32_lremovexattr           /* 236 */
	.quad sys32_fremovexattr           /* 237 */
	.quad sys32_tkill                  /* 238 */
	.quad sys32_sendfile64             /* 239 */
	.quad sys32_futex                  /* 240 */
	.quad sys32_sched_setaffinity      /* 241 */
	.quad sys32_sched_getaffinity      /* 242 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_exit_group             /* 252 */
	.quad sys32_invalid0
	.quad sys32_epoll_create           /* 254 */
	.quad sys32_epoll_ctl              /* 255 */
	.quad sys32_epoll_wait             /* 256 */
	.quad sys32_remap_file_pages       /* 257 */
	.quad sys32_set_tid_address        /* 258 */
	.quad sys32_timer_create           /* 259 */
	.quad sys32_timer_settime          /* 260 */
	.quad sys32_timer_gettime          /* 261 */
	.quad sys32_timer_getoverrun       /* 262 */
	.quad sys32_timer_delete           /* 263 */
	.quad sys32_clock_settime          /* 264 */
	.quad sys32_clock_gettime          /* 265 */
	.quad sys32_clock_getres           /* 266 */
	.quad sys32_clock_nanosleep        /* 267 */
	.quad sys32_statfs64               /* 268 */
	.quad sys32_fstatfs64              /* 269 */
	.quad sys32_tgkill                 /* 270 */
	.quad sys32_utimes                 /* 271 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_waitid                 /* 284 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_ioprio_set             /* 289 */
	.quad sys32_ioprio_get             /* 290 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_openat                 /* 295 */
	.quad sys32_mkdirat                /* 296 */
	.quad sys32_mknodat                /* 297 */
	.quad sys32_fchownat               /* 298 */
	.quad sys32_futimesat              /* 299 */
	.quad sys32_linux_fstatat64        /* 300 */
	.quad sys32_unlinkat               /* 301 */
	.quad sys32_renameat               /* 302 */
	.quad sys32_linkat                 /* 303 */
	.quad sys32_symlinkat              /* 304 */
	.quad sys32_readlinkat             /* 305 */
	.quad sys32_fchmodat               /* 306 */
	.quad sys32_faccessat              /* 307 */
	.quad sys32_pselect6               /* 308 */
	.quad sys32_ppoll                  /* 309 */
	.quad sys32_unshare                /* 310 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_splice                 /* 313 */
	.quad sys32_sync_file_range        /* 314 */
	.quad sys32_tee                    /* 315 */
	.quad sys32_vmsplice               /* 316 */
	.quad sys32_invalid0
	.quad sys32_getcpu                 /* 318 */
	.quad sys32_epoll_pwait            /* 319 */
	.quad sys32_utimensat              /* 320 */
	.quad sys32_invalid0
	.quad sys32_timerfd_create         /* 322 */
	.quad sys32_eventfd                /* 323 */
	.quad sys32_fallocate              /* 324 */
	.quad sys32_timerfd_settime        /* 325 */
	.quad sys32_timerfd_gettime        /* 326 */
	.quad sys32_invalid0
	.quad sys32_eventfd2               /* 328 */
	.quad sys32_epoll_create1          /* 329 */
	.quad sys32_dup3                   /* 330 */
	.quad sys32_pipe2                  /* 331 */
	.quad sys32_invalid0
	.quad sys32_preadv                 /* 333 */
	.quad sys32_pwritev                /* 334 */
	.quad sys32_rt_tgsigqueueinfo      /* 335 */
	.quad sys32_invalid0
	.quad sys32_recvmmsg               /* 337 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_prlimit64              /* 340 */
	.quad sys32_name_to_handle_at      /* 341 */
	.quad sys32_open_by_handle_at      /* 342 */
	.quad sys32_invalid0
	.quad sys32_syncfs                 /* 344 */
	.quad sys32_sendmmsg               /* 345 */
	.quad sys32_setns                  /* 346 */
	.quad sys32_process_vm_readv       /* 347 */
	.quad sys32_process_vm_writev      /* 348 */
	.quad sys32_kcmp                   /* 349 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_renameat2              /* 353 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_execveat               /* 358 */
	.quad sys32_socket                 /* 359 */
	.quad sys32_socketpair             /* 360 */
	.quad sys32_bind                   /* 361 */
	.quad sys32_connect                /* 362 */
	.quad sys32_listen                 /* 363 */
	.quad sys32_accept4                /* 364 */
	.quad sys32_getsockopt             /* 365 */
	.quad sys32_setsockopt             /* 366 */
	.quad sys32_getsockname            /* 367 */
	.quad sys32_getpeername            /* 368 */
	.quad sys32_sendto                 /* 369 */
	.quad sys32_sendmsg                /* 370 */
	.quad sys32_recvfrom               /* 371 */
	.quad sys32_recvmsg                /* 372 */
	.quad sys32_shutdown               /* 373 */
END(__c32_syscallrouter)


PUBLIC_OBJECT(__c32_exsyscallrouter)
	.quad sys32_hop                     /* 0x80000001 */
	.quad sys32_hopf                    /* 0x80000002 */
	.quad sys32_readf                   /* 0x80000003 */
	.quad sys32_writef                  /* 0x80000004 */
	.quad sys32_detach                  /* 0x80000005 */
	.quad sys32_getdrives               /* 0x80000006 */
	.quad sys32_frealpath4              /* 0x80000007 */
	.quad sys32_frealpathat             /* 0x80000008 */
	.quad sys32_rpc_schedule            /* 0x80000009 */
	.quad sys32_sysctl                  /* 0x8000000a */
	.quad sys32_openpty                 /* 0x8000000b */
	.quad sys32_fchdirat                /* 0x8000000c */
	.quad sys32_time64                  /* 0x8000000d */
	.quad sys32_set_exception_handler   /* 0x8000000e */
	.quad sys32_get_exception_handler   /* 0x8000000f */
	.quad sys32_set_library_listdef     /* 0x80000010 */
	.quad sys32_debugtrap               /* 0x80000011 */
	.quad sys32_lfutex                  /* 0x80000012 */
	.quad sys32_lseek64                 /* 0x80000013 */
	.quad sys32_lfutexlock              /* 0x80000014 */
	.quad sys32_lfutexexpr              /* 0x80000015 */
	.quad sys32_lfutexlockexpr          /* 0x80000016 */
	.quad sys32_mktty                   /* 0x80000017 */
	.quad sys32_raiseat                 /* 0x80000018 */
	.quad sys32_stime64                 /* 0x80000019 */
	.quad sys32_coredump                /* 0x8000001a */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_utime64                 /* 0x8000001e */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_ioctlf                  /* 0x80000036 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_fsmode                  /* 0x8000003c */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_gettimeofday64          /* 0x8000004e */
	.quad sys32_settimeofday64          /* 0x8000004f */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_select64                /* 0x80000052 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_maplibrary              /* 0x80000056 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_setitimer64             /* 0x80000068 */
	.quad sys32_getitimer64             /* 0x80000069 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_kreaddir                /* 0x8000008d */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_readvf                  /* 0x80000091 */
	.quad sys32_writevf                 /* 0x80000092 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_rpc_service             /* 0x8000009e */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_sched_rr_get_interval64 /* 0x800000a1 */
	.quad sys32_nanosleep64             /* 0x800000a2 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_rt_sigtimedwait64       /* 0x800000b1 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_pread64f                /* 0x800000b4 */
	.quad sys32_pwrite64f               /* 0x800000b5 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_kstat                   /* 0x800000c3 */
	.quad sys32_klstat                  /* 0x800000c4 */
	.quad sys32_kfstat                  /* 0x800000c5 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_kreaddirf               /* 0x800000dc */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_timer_settime64         /* 0x80000104 */
	.quad sys32_timer_gettime64         /* 0x80000105 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_clock_settime64         /* 0x80000108 */
	.quad sys32_clock_gettime64         /* 0x80000109 */
	.quad sys32_clock_getres64          /* 0x8000010a */
	.quad sys32_clock_nanosleep64       /* 0x8000010b */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_utimes64                /* 0x8000010f */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_fmkdirat                /* 0x80000128 */
	.quad sys32_fmknodat                /* 0x80000129 */
	.quad sys32_invalid0
	.quad sys32_futimesat64             /* 0x8000012b */
	.quad sys32_kfstatat                /* 0x8000012c */
	.quad sys32_invalid0
	.quad sys32_frenameat               /* 0x8000012e */
	.quad sys32_invalid0
	.quad sys32_fsymlinkat              /* 0x80000130 */
	.quad sys32_freadlinkat             /* 0x80000131 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_pselect6_64             /* 0x80000134 */
	.quad sys32_ppoll64                 /* 0x80000135 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_utimensat64             /* 0x80000140 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_fallocate64             /* 0x80000144 */
	.quad sys32_timerfd_settime64       /* 0x80000145 */
	.quad sys32_timerfd_gettime64       /* 0x80000146 */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_preadvf                 /* 0x8000014d */
	.quad sys32_pwritevf                /* 0x8000014e */
	.quad sys32_invalid0
	.quad sys32_invalid0
	.quad sys32_recvmmsg64              /* 0x80000151 */
END(__c32_exsyscallrouter)


