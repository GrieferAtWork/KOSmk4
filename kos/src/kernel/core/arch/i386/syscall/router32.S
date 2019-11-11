/* HASH CRC-32:0x56c406f0 */
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



EXTERN(sys_exit)
EXTERN(sys_fork)
EXTERN(sys_read)
EXTERN(sys_write)
EXTERN(sys_open)
EXTERN(sys_close)
EXTERN(sys_waitpid)
EXTERN(sys_creat)
EXTERN(sys_link)
EXTERN(sys_unlink)
EXTERN(sys_execve)
EXTERN(sys_chdir)
EXTERN(sys_time)
EXTERN(sys_mknod)
EXTERN(sys_chmod)
EXTERN(sys_lchown)
EXTERN(sys_linux_oldstat)
EXTERN(sys_lseek)
EXTERN(sys_getpid)
EXTERN(sys_mount)
EXTERN(sys_umount)
EXTERN(sys_setuid)
EXTERN(sys_getuid)
EXTERN(sys_stime)
EXTERN(sys_ptrace)
EXTERN(sys_alarm)
EXTERN(sys_linux_oldfstat)
EXTERN(sys_pause)
EXTERN(sys_utime)
EXTERN(sys_access)
EXTERN(sys_nice)
EXTERN(sys_ftime)
EXTERN(sys_sync)
EXTERN(sys_kill)
EXTERN(sys_rename)
EXTERN(sys_mkdir)
EXTERN(sys_rmdir)
EXTERN(sys_dup)
EXTERN(sys_pipe)
EXTERN(sys_times)
EXTERN(sys_brk)
EXTERN(sys_setgid)
EXTERN(sys_getgid)
EXTERN(sys_signal)
EXTERN(sys_geteuid)
EXTERN(sys_getegid)
EXTERN(sys_acct)
EXTERN(sys_umount2)
EXTERN(sys_ioctl)
EXTERN(sys_fcntl)
EXTERN(sys_setpgid)
EXTERN(sys_oldolduname)
EXTERN(sys_umask)
EXTERN(sys_chroot)
EXTERN(sys_ustat)
EXTERN(sys_dup2)
EXTERN(sys_getppid)
EXTERN(sys_getpgrp)
EXTERN(sys_setsid)
EXTERN(sys_sigaction)
EXTERN(sys_sgetmask)
EXTERN(sys_ssetmask)
EXTERN(sys_setreuid)
EXTERN(sys_setregid)
EXTERN(sys_sigsuspend)
EXTERN(sys_sigpending)
EXTERN(sys_sethostname)
EXTERN(sys_setrlimit)
EXTERN(sys_getrlimit)
EXTERN(sys_getrusage)
EXTERN(sys_gettimeofday)
EXTERN(sys_settimeofday)
EXTERN(sys_getgroups)
EXTERN(sys_setgroups)
EXTERN(sys_select)
EXTERN(sys_symlink)
EXTERN(sys_linux_oldlstat)
EXTERN(sys_readlink)
EXTERN(sys_swapon)
EXTERN(sys_reboot)
EXTERN(sys_readdir)
EXTERN(sys_mmap)
EXTERN(sys_munmap)
EXTERN(sys_truncate)
EXTERN(sys_ftruncate)
EXTERN(sys_fchmod)
EXTERN(sys_fchown)
EXTERN(sys_getpriority)
EXTERN(sys_setpriority)
EXTERN(sys_profil)
EXTERN(sys_statfs)
EXTERN(sys_fstatfs)
EXTERN(sys_ioperm)
EXTERN(sys_socketcall)
EXTERN(sys_syslog)
EXTERN(sys_setitimer)
EXTERN(sys_getitimer)
EXTERN(sys_linux_stat32)
EXTERN(sys_linux_lstat32)
EXTERN(sys_linux_fstat32)
EXTERN(sys_olduname)
EXTERN(sys_iopl)
EXTERN(sys_vhangup)
EXTERN(sys_wait4)
EXTERN(sys_swapoff)
EXTERN(sys_sysinfo)
EXTERN(sys_fsync)
EXTERN(sys_sigreturn)
EXTERN(sys_clone)
EXTERN(sys_setdomainname)
EXTERN(sys_uname)
EXTERN(sys_modify_ldt)
EXTERN(sys_mprotect)
EXTERN(sys_sigprocmask)
EXTERN(sys_getpgid)
EXTERN(sys_fchdir)
EXTERN(sys_setfsuid)
EXTERN(sys_setfsgid)
EXTERN(sys__llseek)
EXTERN(sys_getdents)
EXTERN(sys_flock)
EXTERN(sys_msync)
EXTERN(sys_readv)
EXTERN(sys_writev)
EXTERN(sys_getsid)
EXTERN(sys_fdatasync)
EXTERN(sys_mlock)
EXTERN(sys_munlock)
EXTERN(sys_mlockall)
EXTERN(sys_munlockall)
EXTERN(sys_sched_setparam)
EXTERN(sys_sched_getparam)
EXTERN(sys_sched_setscheduler)
EXTERN(sys_sched_getscheduler)
EXTERN(sys_sched_yield)
EXTERN(sys_sched_get_priority_max)
EXTERN(sys_sched_get_priority_min)
EXTERN(sys_sched_rr_get_interval)
EXTERN(sys_nanosleep)
EXTERN(sys_mremap)
EXTERN(sys_setresuid)
EXTERN(sys_getresuid)
EXTERN(sys_poll)
EXTERN(sys_setresgid)
EXTERN(sys_getresgid)
EXTERN(sys_rt_sigaction)
EXTERN(sys_rt_sigprocmask)
EXTERN(sys_rt_sigpending)
EXTERN(sys_rt_sigtimedwait)
EXTERN(sys_rt_sigqueueinfo)
EXTERN(sys_rt_sigsuspend)
EXTERN(sys_pread64)
EXTERN(sys_pwrite64)
EXTERN(sys_chown)
EXTERN(sys_getcwd)
EXTERN(sys_sigaltstack)
EXTERN(sys_sendfile)
EXTERN(sys_vfork)
EXTERN(sys_mmap2)
EXTERN(sys_truncate64)
EXTERN(sys_ftruncate64)
EXTERN(sys_linux_stat64)
EXTERN(sys_linux_lstat64)
EXTERN(sys_linux_fstat64)
EXTERN(sys_lchown32)
EXTERN(sys_getuid32)
EXTERN(sys_getgid32)
EXTERN(sys_geteuid32)
EXTERN(sys_getegid32)
EXTERN(sys_setreuid32)
EXTERN(sys_setregid32)
EXTERN(sys_getgroups32)
EXTERN(sys_setgroups32)
EXTERN(sys_fchown32)
EXTERN(sys_setresuid32)
EXTERN(sys_getresuid32)
EXTERN(sys_setresgid32)
EXTERN(sys_getresgid32)
EXTERN(sys_chown32)
EXTERN(sys_setuid32)
EXTERN(sys_setgid32)
EXTERN(sys_setfsuid32)
EXTERN(sys_setfsgid32)
EXTERN(sys_mincore)
EXTERN(sys_madvise)
EXTERN(sys_getdents64)
EXTERN(sys_fcntl64)
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
EXTERN(sys_sendfile64)
EXTERN(sys_futex)
EXTERN(sys_sched_setaffinity)
EXTERN(sys_sched_getaffinity)
EXTERN(sys_exit_group)
EXTERN(sys_epoll_create)
EXTERN(sys_epoll_ctl)
EXTERN(sys_epoll_wait)
EXTERN(sys_remap_file_pages)
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
EXTERN(sys_statfs64)
EXTERN(sys_fstatfs64)
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
EXTERN(sys_linux_fstatat64)
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
EXTERN(sys_sync_file_range)
EXTERN(sys_tee)
EXTERN(sys_vmsplice)
EXTERN(sys_getcpu)
EXTERN(sys_epoll_pwait)
EXTERN(sys_utimensat)
EXTERN(sys_signalfd)
EXTERN(sys_timerfd_create)
EXTERN(sys_eventfd)
EXTERN(sys_fallocate)
EXTERN(sys_timerfd_settime)
EXTERN(sys_timerfd_gettime)
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
EXTERN(sys_process_vm_readv)
EXTERN(sys_process_vm_writev)
EXTERN(sys_kcmp)
EXTERN(sys_renameat2)
EXTERN(sys_execveat)
EXTERN(sys_socket)
EXTERN(sys_socketpair)
EXTERN(sys_bind)
EXTERN(sys_connect)
EXTERN(sys_listen)
EXTERN(sys_accept4)
EXTERN(sys_getsockopt)
EXTERN(sys_setsockopt)
EXTERN(sys_getsockname)
EXTERN(sys_getpeername)
EXTERN(sys_sendto)
EXTERN(sys_sendmsg)
EXTERN(sys_recvfrom)
EXTERN(sys_recvmsg)
EXTERN(sys_shutdown)
EXTERN(sys_hop)
EXTERN(sys_hopf)
EXTERN(sys_readf)
EXTERN(sys_writef)
EXTERN(sys_detach)
EXTERN(sys_getdrives)
EXTERN(sys_frealpath4)
EXTERN(sys_frealpathat)
EXTERN(sys_rpc_schedule)
EXTERN(sys_sysctl)
EXTERN(sys_openpty)
EXTERN(sys_fchdirat)
EXTERN(sys_time64)
EXTERN(sys_set_exception_handler)
EXTERN(sys_get_exception_handler)
EXTERN(sys_set_library_listdef)
EXTERN(sys_debugtrap)
EXTERN(sys_lfutex)
EXTERN(sys_lseek64)
EXTERN(sys_lfutexexpr)
EXTERN(sys_lfutexlockexpr)
EXTERN(sys_mktty)
EXTERN(sys_raiseat)
EXTERN(sys_coredump)
EXTERN(sys_stime64)
EXTERN(sys_utime64)
EXTERN(sys_ioctlf)
EXTERN(sys_fsmode)
EXTERN(sys_gettimeofday64)
EXTERN(sys_settimeofday64)
EXTERN(sys_select64)
EXTERN(sys_maplibrary)
EXTERN(sys_setitimer64)
EXTERN(sys_getitimer64)
EXTERN(sys_kreaddir)
EXTERN(sys_readvf)
EXTERN(sys_writevf)
EXTERN(sys_rpc_service)
EXTERN(sys_sched_rr_get_interval64)
EXTERN(sys_nanosleep64)
EXTERN(sys_rt_sigtimedwait64)
EXTERN(sys_pread64f)
EXTERN(sys_pwrite64f)
EXTERN(sys_kstat)
EXTERN(sys_klstat)
EXTERN(sys_kfstat)
EXTERN(sys_kreaddirf)
EXTERN(sys_timer_settime64)
EXTERN(sys_timer_gettime64)
EXTERN(sys_clock_settime64)
EXTERN(sys_clock_gettime64)
EXTERN(sys_clock_getres64)
EXTERN(sys_clock_nanosleep64)
EXTERN(sys_utimes64)
EXTERN(sys_fmkdirat)
EXTERN(sys_fmknodat)
EXTERN(sys_futimesat64)
EXTERN(sys_kfstatat)
EXTERN(sys_frenameat)
EXTERN(sys_fsymlinkat)
EXTERN(sys_freadlinkat)
EXTERN(sys_pselect6_64)
EXTERN(sys_ppoll64)
EXTERN(sys_utimensat64)
EXTERN(sys_fallocate64)
EXTERN(sys_timerfd_settime64)
EXTERN(sys_timerfd_gettime64)
EXTERN(sys_preadvf)
EXTERN(sys_pwritevf)
EXTERN(sys_recvmmsg64)



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
INTERN(__asm32_int80_signalfd)
INTERN(__asm32_int80_timerfd_create)
INTERN(__asm32_int80_eventfd)
INTERN(__asm32_int80_fallocate)
INTERN(__asm32_int80_timerfd_settime)
INTERN(__asm32_int80_timerfd_gettime)
INTERN(__asm32_int80_signalfd4)
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
INTERN(__asm32_int80_lfutexexpr)
INTERN(__asm32_int80_lfutexlockexpr)
INTERN(__asm32_int80_mktty)
INTERN(__asm32_int80_raiseat)
INTERN(__asm32_int80_coredump)
INTERN(__asm32_int80_stime64)
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
INTERN(__asm32_sysenter_signalfd)
INTERN(__asm32_sysenter_timerfd_create)
INTERN(__asm32_sysenter_eventfd)
INTERN(__asm32_sysenter_fallocate)
INTERN(__asm32_sysenter_timerfd_settime)
INTERN(__asm32_sysenter_timerfd_gettime)
INTERN(__asm32_sysenter_signalfd4)
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
INTERN(__asm32_sysenter_lfutexexpr)
INTERN(__asm32_sysenter_lfutexlockexpr)
INTERN(__asm32_sysenter_mktty)
INTERN(__asm32_sysenter_raiseat)
INTERN(__asm32_sysenter_coredump)
INTERN(__asm32_sysenter_stime64)
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
/* 32-bit System call router for <int 80h>                                  */
/****************************************************************************/
.section .rodata.x86.syscall32.router_int80
PUBLIC_OBJECT(__asm32_syscallrouter_int80)
	.long __asm32_int80_invalid
	.long __asm32_int80_exit                   /* 1 */
	.long __asm32_int80_fork                   /* 2 */
	.long __asm32_int80_read                   /* 3 */
	.long __asm32_int80_write                  /* 4 */
	.long __asm32_int80_open                   /* 5 */
	.long __asm32_int80_close                  /* 6 */
	.long __asm32_int80_waitpid                /* 7 */
	.long __asm32_int80_creat                  /* 8 */
	.long __asm32_int80_link                   /* 9 */
	.long __asm32_int80_unlink                 /* 10 */
	.long __asm32_int80_execve                 /* 11 */
	.long __asm32_int80_chdir                  /* 12 */
	.long __asm32_int80_time                   /* 13 */
	.long __asm32_int80_mknod                  /* 14 */
	.long __asm32_int80_chmod                  /* 15 */
	.long __asm32_int80_lchown                 /* 16 */
	.long __asm32_int80_invalid
	.long __asm32_int80_linux_oldstat          /* 18 */
	.long __asm32_int80_lseek                  /* 19 */
	.long __asm32_int80_getpid                 /* 20 */
	.long __asm32_int80_mount                  /* 21 */
	.long __asm32_int80_umount                 /* 22 */
	.long __asm32_int80_setuid                 /* 23 */
	.long __asm32_int80_getuid                 /* 24 */
	.long __asm32_int80_stime                  /* 25 */
	.long __asm32_int80_ptrace                 /* 26 */
	.long __asm32_int80_alarm                  /* 27 */
	.long __asm32_int80_linux_oldfstat         /* 28 */
	.long __asm32_int80_pause                  /* 29 */
	.long __asm32_int80_utime                  /* 30 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_access                 /* 33 */
	.long __asm32_int80_nice                   /* 34 */
	.long __asm32_int80_ftime                  /* 35 */
	.long __asm32_int80_sync                   /* 36 */
	.long __asm32_int80_kill                   /* 37 */
	.long __asm32_int80_rename                 /* 38 */
	.long __asm32_int80_mkdir                  /* 39 */
	.long __asm32_int80_rmdir                  /* 40 */
	.long __asm32_int80_dup                    /* 41 */
	.long __asm32_int80_pipe                   /* 42 */
	.long __asm32_int80_times                  /* 43 */
	.long __asm32_int80_invalid
	.long __asm32_int80_brk                    /* 45 */
	.long __asm32_int80_setgid                 /* 46 */
	.long __asm32_int80_getgid                 /* 47 */
	.long __asm32_int80_signal                 /* 48 */
	.long __asm32_int80_geteuid                /* 49 */
	.long __asm32_int80_getegid                /* 50 */
	.long __asm32_int80_acct                   /* 51 */
	.long __asm32_int80_umount2                /* 52 */
	.long __asm32_int80_invalid
	.long __asm32_int80_ioctl                  /* 54 */
	.long __asm32_int80_fcntl                  /* 55 */
	.long __asm32_int80_invalid
	.long __asm32_int80_setpgid                /* 57 */
	.long __asm32_int80_invalid
	.long __asm32_int80_oldolduname            /* 59 */
	.long __asm32_int80_umask                  /* 60 */
	.long __asm32_int80_chroot                 /* 61 */
	.long __asm32_int80_ustat                  /* 62 */
	.long __asm32_int80_dup2                   /* 63 */
	.long __asm32_int80_getppid                /* 64 */
	.long __asm32_int80_getpgrp                /* 65 */
	.long __asm32_int80_setsid                 /* 66 */
	.long __asm32_int80_sigaction              /* 67 */
	.long __asm32_int80_sgetmask               /* 68 */
	.long __asm32_int80_ssetmask               /* 69 */
	.long __asm32_int80_setreuid               /* 70 */
	.long __asm32_int80_setregid               /* 71 */
	.long __asm32_int80_sigsuspend             /* 72 */
	.long __asm32_int80_sigpending             /* 73 */
	.long __asm32_int80_sethostname            /* 74 */
	.long __asm32_int80_setrlimit              /* 75 */
	.long __asm32_int80_getrlimit              /* 76 */
	.long __asm32_int80_getrusage              /* 77 */
	.long __asm32_int80_gettimeofday           /* 78 */
	.long __asm32_int80_settimeofday           /* 79 */
	.long __asm32_int80_getgroups              /* 80 */
	.long __asm32_int80_setgroups              /* 81 */
	.long __asm32_int80_select                 /* 82 */
	.long __asm32_int80_symlink                /* 83 */
	.long __asm32_int80_linux_oldlstat         /* 84 */
	.long __asm32_int80_readlink               /* 85 */
	.long __asm32_int80_invalid
	.long __asm32_int80_swapon                 /* 87 */
	.long __asm32_int80_reboot                 /* 88 */
	.long __asm32_int80_readdir                /* 89 */
	.long __asm32_int80_mmap                   /* 90 */
	.long __asm32_int80_munmap                 /* 91 */
	.long __asm32_int80_truncate               /* 92 */
	.long __asm32_int80_ftruncate              /* 93 */
	.long __asm32_int80_fchmod                 /* 94 */
	.long __asm32_int80_fchown                 /* 95 */
	.long __asm32_int80_getpriority            /* 96 */
	.long __asm32_int80_setpriority            /* 97 */
	.long __asm32_int80_profil                 /* 98 */
	.long __asm32_int80_statfs                 /* 99 */
	.long __asm32_int80_fstatfs                /* 100 */
	.long __asm32_int80_ioperm                 /* 101 */
	.long __asm32_int80_socketcall             /* 102 */
	.long __asm32_int80_syslog                 /* 103 */
	.long __asm32_int80_setitimer              /* 104 */
	.long __asm32_int80_getitimer              /* 105 */
	.long __asm32_int80_linux_stat32           /* 106 */
	.long __asm32_int80_linux_lstat32          /* 107 */
	.long __asm32_int80_linux_fstat32          /* 108 */
	.long __asm32_int80_olduname               /* 109 */
	.long __asm32_int80_iopl                   /* 110 */
	.long __asm32_int80_vhangup                /* 111 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_wait4                  /* 114 */
	.long __asm32_int80_swapoff                /* 115 */
	.long __asm32_int80_sysinfo                /* 116 */
	.long __asm32_int80_invalid
	.long __asm32_int80_fsync                  /* 118 */
	.long __asm32_int80_sigreturn              /* 119 */
	.long __asm32_int80_clone                  /* 120 */
	.long __asm32_int80_setdomainname          /* 121 */
	.long __asm32_int80_uname                  /* 122 */
	.long __asm32_int80_modify_ldt             /* 123 */
	.long __asm32_int80_invalid
	.long __asm32_int80_mprotect               /* 125 */
	.long __asm32_int80_sigprocmask            /* 126 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_getpgid                /* 132 */
	.long __asm32_int80_fchdir                 /* 133 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_setfsuid               /* 138 */
	.long __asm32_int80_setfsgid               /* 139 */
	.long __asm32_int80__llseek                /* 140 */
	.long __asm32_int80_getdents               /* 141 */
	.long __asm32_int80_invalid
	.long __asm32_int80_flock                  /* 143 */
	.long __asm32_int80_msync                  /* 144 */
	.long __asm32_int80_readv                  /* 145 */
	.long __asm32_int80_writev                 /* 146 */
	.long __asm32_int80_getsid                 /* 147 */
	.long __asm32_int80_fdatasync              /* 148 */
	.long __asm32_int80_invalid
	.long __asm32_int80_mlock                  /* 150 */
	.long __asm32_int80_munlock                /* 151 */
	.long __asm32_int80_mlockall               /* 152 */
	.long __asm32_int80_munlockall             /* 153 */
	.long __asm32_int80_sched_setparam         /* 154 */
	.long __asm32_int80_sched_getparam         /* 155 */
	.long __asm32_int80_sched_setscheduler     /* 156 */
	.long __asm32_int80_sched_getscheduler     /* 157 */
	.long __asm32_int80_sched_yield            /* 158 */
	.long __asm32_int80_sched_get_priority_max /* 159 */
	.long __asm32_int80_sched_get_priority_min /* 160 */
	.long __asm32_int80_sched_rr_get_interval  /* 161 */
	.long __asm32_int80_nanosleep              /* 162 */
	.long __asm32_int80_mremap                 /* 163 */
	.long __asm32_int80_setresuid              /* 164 */
	.long __asm32_int80_getresuid              /* 165 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_poll                   /* 168 */
	.long __asm32_int80_invalid
	.long __asm32_int80_setresgid              /* 170 */
	.long __asm32_int80_getresgid              /* 171 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_rt_sigaction           /* 174 */
	.long __asm32_int80_rt_sigprocmask         /* 175 */
	.long __asm32_int80_rt_sigpending          /* 176 */
	.long __asm32_int80_rt_sigtimedwait        /* 177 */
	.long __asm32_int80_rt_sigqueueinfo        /* 178 */
	.long __asm32_int80_rt_sigsuspend          /* 179 */
	.long __asm32_int80_pread64                /* 180 */
	.long __asm32_int80_pwrite64               /* 181 */
	.long __asm32_int80_chown                  /* 182 */
	.long __asm32_int80_getcwd                 /* 183 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_sigaltstack            /* 186 */
	.long __asm32_int80_sendfile               /* 187 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_vfork                  /* 190 */
	.long __asm32_int80_invalid
	.long __asm32_int80_mmap2                  /* 192 */
	.long __asm32_int80_truncate64             /* 193 */
	.long __asm32_int80_ftruncate64            /* 194 */
	.long __asm32_int80_linux_stat64           /* 195 */
	.long __asm32_int80_linux_lstat64          /* 196 */
	.long __asm32_int80_linux_fstat64          /* 197 */
	.long __asm32_int80_lchown32               /* 198 */
	.long __asm32_int80_getuid32               /* 199 */
	.long __asm32_int80_getgid32               /* 200 */
	.long __asm32_int80_geteuid32              /* 201 */
	.long __asm32_int80_getegid32              /* 202 */
	.long __asm32_int80_setreuid32             /* 203 */
	.long __asm32_int80_setregid32             /* 204 */
	.long __asm32_int80_getgroups32            /* 205 */
	.long __asm32_int80_setgroups32            /* 206 */
	.long __asm32_int80_fchown32               /* 207 */
	.long __asm32_int80_setresuid32            /* 208 */
	.long __asm32_int80_getresuid32            /* 209 */
	.long __asm32_int80_setresgid32            /* 210 */
	.long __asm32_int80_getresgid32            /* 211 */
	.long __asm32_int80_chown32                /* 212 */
	.long __asm32_int80_setuid32               /* 213 */
	.long __asm32_int80_setgid32               /* 214 */
	.long __asm32_int80_setfsuid32             /* 215 */
	.long __asm32_int80_setfsgid32             /* 216 */
	.long __asm32_int80_invalid
	.long __asm32_int80_mincore                /* 218 */
	.long __asm32_int80_madvise                /* 219 */
	.long __asm32_int80_getdents64             /* 220 */
	.long __asm32_int80_fcntl64                /* 221 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_gettid                 /* 224 */
	.long __asm32_int80_readahead              /* 225 */
	.long __asm32_int80_setxattr               /* 226 */
	.long __asm32_int80_lsetxattr              /* 227 */
	.long __asm32_int80_fsetxattr              /* 228 */
	.long __asm32_int80_getxattr               /* 229 */
	.long __asm32_int80_lgetxattr              /* 230 */
	.long __asm32_int80_fgetxattr              /* 231 */
	.long __asm32_int80_listxattr              /* 232 */
	.long __asm32_int80_llistxattr             /* 233 */
	.long __asm32_int80_flistxattr             /* 234 */
	.long __asm32_int80_removexattr            /* 235 */
	.long __asm32_int80_lremovexattr           /* 236 */
	.long __asm32_int80_fremovexattr           /* 237 */
	.long __asm32_int80_tkill                  /* 238 */
	.long __asm32_int80_sendfile64             /* 239 */
	.long __asm32_int80_futex                  /* 240 */
	.long __asm32_int80_sched_setaffinity      /* 241 */
	.long __asm32_int80_sched_getaffinity      /* 242 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_exit_group             /* 252 */
	.long __asm32_int80_invalid
	.long __asm32_int80_epoll_create           /* 254 */
	.long __asm32_int80_epoll_ctl              /* 255 */
	.long __asm32_int80_epoll_wait             /* 256 */
	.long __asm32_int80_remap_file_pages       /* 257 */
	.long __asm32_int80_set_tid_address        /* 258 */
	.long __asm32_int80_timer_create           /* 259 */
	.long __asm32_int80_timer_settime          /* 260 */
	.long __asm32_int80_timer_gettime          /* 261 */
	.long __asm32_int80_timer_getoverrun       /* 262 */
	.long __asm32_int80_timer_delete           /* 263 */
	.long __asm32_int80_clock_settime          /* 264 */
	.long __asm32_int80_clock_gettime          /* 265 */
	.long __asm32_int80_clock_getres           /* 266 */
	.long __asm32_int80_clock_nanosleep        /* 267 */
	.long __asm32_int80_statfs64               /* 268 */
	.long __asm32_int80_fstatfs64              /* 269 */
	.long __asm32_int80_tgkill                 /* 270 */
	.long __asm32_int80_utimes                 /* 271 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_waitid                 /* 284 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_ioprio_set             /* 289 */
	.long __asm32_int80_ioprio_get             /* 290 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_openat                 /* 295 */
	.long __asm32_int80_mkdirat                /* 296 */
	.long __asm32_int80_mknodat                /* 297 */
	.long __asm32_int80_fchownat               /* 298 */
	.long __asm32_int80_futimesat              /* 299 */
	.long __asm32_int80_linux_fstatat64        /* 300 */
	.long __asm32_int80_unlinkat               /* 301 */
	.long __asm32_int80_renameat               /* 302 */
	.long __asm32_int80_linkat                 /* 303 */
	.long __asm32_int80_symlinkat              /* 304 */
	.long __asm32_int80_readlinkat             /* 305 */
	.long __asm32_int80_fchmodat               /* 306 */
	.long __asm32_int80_faccessat              /* 307 */
	.long __asm32_int80_pselect6               /* 308 */
	.long __asm32_int80_ppoll                  /* 309 */
	.long __asm32_int80_unshare                /* 310 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_splice                 /* 313 */
	.long __asm32_int80_sync_file_range        /* 314 */
	.long __asm32_int80_tee                    /* 315 */
	.long __asm32_int80_vmsplice               /* 316 */
	.long __asm32_int80_invalid
	.long __asm32_int80_getcpu                 /* 318 */
	.long __asm32_int80_epoll_pwait            /* 319 */
	.long __asm32_int80_utimensat              /* 320 */
	.long __asm32_int80_signalfd               /* 321 */
	.long __asm32_int80_timerfd_create         /* 322 */
	.long __asm32_int80_eventfd                /* 323 */
	.long __asm32_int80_fallocate              /* 324 */
	.long __asm32_int80_timerfd_settime        /* 325 */
	.long __asm32_int80_timerfd_gettime        /* 326 */
	.long __asm32_int80_signalfd4              /* 327 */
	.long __asm32_int80_eventfd2               /* 328 */
	.long __asm32_int80_epoll_create1          /* 329 */
	.long __asm32_int80_dup3                   /* 330 */
	.long __asm32_int80_pipe2                  /* 331 */
	.long __asm32_int80_invalid
	.long __asm32_int80_preadv                 /* 333 */
	.long __asm32_int80_pwritev                /* 334 */
	.long __asm32_int80_rt_tgsigqueueinfo      /* 335 */
	.long __asm32_int80_invalid
	.long __asm32_int80_recvmmsg               /* 337 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_prlimit64              /* 340 */
	.long __asm32_int80_name_to_handle_at      /* 341 */
	.long __asm32_int80_open_by_handle_at      /* 342 */
	.long __asm32_int80_invalid
	.long __asm32_int80_syncfs                 /* 344 */
	.long __asm32_int80_sendmmsg               /* 345 */
	.long __asm32_int80_setns                  /* 346 */
	.long __asm32_int80_process_vm_readv       /* 347 */
	.long __asm32_int80_process_vm_writev      /* 348 */
	.long __asm32_int80_kcmp                   /* 349 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_renameat2              /* 353 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_execveat               /* 358 */
	.long __asm32_int80_socket                 /* 359 */
	.long __asm32_int80_socketpair             /* 360 */
	.long __asm32_int80_bind                   /* 361 */
	.long __asm32_int80_connect                /* 362 */
	.long __asm32_int80_listen                 /* 363 */
	.long __asm32_int80_accept4                /* 364 */
	.long __asm32_int80_getsockopt             /* 365 */
	.long __asm32_int80_setsockopt             /* 366 */
	.long __asm32_int80_getsockname            /* 367 */
	.long __asm32_int80_getpeername            /* 368 */
	.long __asm32_int80_sendto                 /* 369 */
	.long __asm32_int80_sendmsg                /* 370 */
	.long __asm32_int80_recvfrom               /* 371 */
	.long __asm32_int80_recvmsg                /* 372 */
	.long __asm32_int80_shutdown               /* 373 */
END(__asm32_syscallrouter_int80)


PUBLIC_OBJECT(__asm32_exsyscallrouter_int80)
	.long __asm32_int80_hop                     /* 0x80000001 */
	.long __asm32_int80_hopf                    /* 0x80000002 */
	.long __asm32_int80_readf                   /* 0x80000003 */
	.long __asm32_int80_writef                  /* 0x80000004 */
	.long __asm32_int80_detach                  /* 0x80000005 */
	.long __asm32_int80_getdrives               /* 0x80000006 */
	.long __asm32_int80_frealpath4              /* 0x80000007 */
	.long __asm32_int80_frealpathat             /* 0x80000008 */
	.long __asm32_int80_rpc_schedule            /* 0x80000009 */
	.long __asm32_int80_sysctl                  /* 0x8000000a */
	.long __asm32_int80_openpty                 /* 0x8000000b */
	.long __asm32_int80_fchdirat                /* 0x8000000c */
	.long __asm32_int80_time64                  /* 0x8000000d */
	.long __asm32_int80_set_exception_handler   /* 0x8000000e */
	.long __asm32_int80_get_exception_handler   /* 0x8000000f */
	.long __asm32_int80_set_library_listdef     /* 0x80000010 */
	.long __asm32_int80_debugtrap               /* 0x80000011 */
	.long __asm32_int80_lfutex                  /* 0x80000012 */
	.long __asm32_int80_lseek64                 /* 0x80000013 */
	.long __asm32_int80_lfutexexpr              /* 0x80000014 */
	.long __asm32_int80_lfutexlockexpr          /* 0x80000015 */
	.long __asm32_int80_mktty                   /* 0x80000016 */
	.long __asm32_int80_raiseat                 /* 0x80000017 */
	.long __asm32_int80_coredump                /* 0x80000018 */
	.long __asm32_int80_stime64                 /* 0x80000019 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_utime64                 /* 0x8000001e */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_ioctlf                  /* 0x80000036 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_fsmode                  /* 0x8000003c */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_gettimeofday64          /* 0x8000004e */
	.long __asm32_int80_settimeofday64          /* 0x8000004f */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_select64                /* 0x80000052 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_maplibrary              /* 0x80000056 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_setitimer64             /* 0x80000068 */
	.long __asm32_int80_getitimer64             /* 0x80000069 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_kreaddir                /* 0x8000008d */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_readvf                  /* 0x80000091 */
	.long __asm32_int80_writevf                 /* 0x80000092 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_rpc_service             /* 0x8000009e */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_sched_rr_get_interval64 /* 0x800000a1 */
	.long __asm32_int80_nanosleep64             /* 0x800000a2 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_rt_sigtimedwait64       /* 0x800000b1 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_pread64f                /* 0x800000b4 */
	.long __asm32_int80_pwrite64f               /* 0x800000b5 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_kstat                   /* 0x800000c3 */
	.long __asm32_int80_klstat                  /* 0x800000c4 */
	.long __asm32_int80_kfstat                  /* 0x800000c5 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_kreaddirf               /* 0x800000dc */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_timer_settime64         /* 0x80000104 */
	.long __asm32_int80_timer_gettime64         /* 0x80000105 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_clock_settime64         /* 0x80000108 */
	.long __asm32_int80_clock_gettime64         /* 0x80000109 */
	.long __asm32_int80_clock_getres64          /* 0x8000010a */
	.long __asm32_int80_clock_nanosleep64       /* 0x8000010b */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_utimes64                /* 0x8000010f */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_fmkdirat                /* 0x80000128 */
	.long __asm32_int80_fmknodat                /* 0x80000129 */
	.long __asm32_int80_invalid
	.long __asm32_int80_futimesat64             /* 0x8000012b */
	.long __asm32_int80_kfstatat                /* 0x8000012c */
	.long __asm32_int80_invalid
	.long __asm32_int80_frenameat               /* 0x8000012e */
	.long __asm32_int80_invalid
	.long __asm32_int80_fsymlinkat              /* 0x80000130 */
	.long __asm32_int80_freadlinkat             /* 0x80000131 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_pselect6_64             /* 0x80000134 */
	.long __asm32_int80_ppoll64                 /* 0x80000135 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_utimensat64             /* 0x80000140 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_fallocate64             /* 0x80000144 */
	.long __asm32_int80_timerfd_settime64       /* 0x80000145 */
	.long __asm32_int80_timerfd_gettime64       /* 0x80000146 */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_preadvf                 /* 0x8000014d */
	.long __asm32_int80_pwritevf                /* 0x8000014e */
	.long __asm32_int80_invalid
	.long __asm32_int80_invalid
	.long __asm32_int80_recvmmsg64              /* 0x80000151 */
END(__asm32_exsyscallrouter_int80)


/****************************************************************************/
/* 32-bit System call router for <sysenter>                                 */
/****************************************************************************/
.section .rodata.x86.syscall32.router_sysenter
PUBLIC_OBJECT(__asm32_syscallrouter_sysenter)
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_exit                   /* 1 */
	.long __asm32_sysenter_fork                   /* 2 */
	.long __asm32_sysenter_read                   /* 3 */
	.long __asm32_sysenter_write                  /* 4 */
	.long __asm32_sysenter_open                   /* 5 */
	.long __asm32_sysenter_close                  /* 6 */
	.long __asm32_sysenter_waitpid                /* 7 */
	.long __asm32_sysenter_creat                  /* 8 */
	.long __asm32_sysenter_link                   /* 9 */
	.long __asm32_sysenter_unlink                 /* 10 */
	.long __asm32_sysenter_execve                 /* 11 */
	.long __asm32_sysenter_chdir                  /* 12 */
	.long __asm32_sysenter_time                   /* 13 */
	.long __asm32_sysenter_mknod                  /* 14 */
	.long __asm32_sysenter_chmod                  /* 15 */
	.long __asm32_sysenter_lchown                 /* 16 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_linux_oldstat          /* 18 */
	.long __asm32_sysenter_lseek                  /* 19 */
	.long __asm32_sysenter_getpid                 /* 20 */
	.long __asm32_sysenter_mount                  /* 21 */
	.long __asm32_sysenter_umount                 /* 22 */
	.long __asm32_sysenter_setuid                 /* 23 */
	.long __asm32_sysenter_getuid                 /* 24 */
	.long __asm32_sysenter_stime                  /* 25 */
	.long __asm32_sysenter_ptrace                 /* 26 */
	.long __asm32_sysenter_alarm                  /* 27 */
	.long __asm32_sysenter_linux_oldfstat         /* 28 */
	.long __asm32_sysenter_pause                  /* 29 */
	.long __asm32_sysenter_utime                  /* 30 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_access                 /* 33 */
	.long __asm32_sysenter_nice                   /* 34 */
	.long __asm32_sysenter_ftime                  /* 35 */
	.long __asm32_sysenter_sync                   /* 36 */
	.long __asm32_sysenter_kill                   /* 37 */
	.long __asm32_sysenter_rename                 /* 38 */
	.long __asm32_sysenter_mkdir                  /* 39 */
	.long __asm32_sysenter_rmdir                  /* 40 */
	.long __asm32_sysenter_dup                    /* 41 */
	.long __asm32_sysenter_pipe                   /* 42 */
	.long __asm32_sysenter_times                  /* 43 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_brk                    /* 45 */
	.long __asm32_sysenter_setgid                 /* 46 */
	.long __asm32_sysenter_getgid                 /* 47 */
	.long __asm32_sysenter_signal                 /* 48 */
	.long __asm32_sysenter_geteuid                /* 49 */
	.long __asm32_sysenter_getegid                /* 50 */
	.long __asm32_sysenter_acct                   /* 51 */
	.long __asm32_sysenter_umount2                /* 52 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_ioctl                  /* 54 */
	.long __asm32_sysenter_fcntl                  /* 55 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_setpgid                /* 57 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_oldolduname            /* 59 */
	.long __asm32_sysenter_umask                  /* 60 */
	.long __asm32_sysenter_chroot                 /* 61 */
	.long __asm32_sysenter_ustat                  /* 62 */
	.long __asm32_sysenter_dup2                   /* 63 */
	.long __asm32_sysenter_getppid                /* 64 */
	.long __asm32_sysenter_getpgrp                /* 65 */
	.long __asm32_sysenter_setsid                 /* 66 */
	.long __asm32_sysenter_sigaction              /* 67 */
	.long __asm32_sysenter_sgetmask               /* 68 */
	.long __asm32_sysenter_ssetmask               /* 69 */
	.long __asm32_sysenter_setreuid               /* 70 */
	.long __asm32_sysenter_setregid               /* 71 */
	.long __asm32_sysenter_sigsuspend             /* 72 */
	.long __asm32_sysenter_sigpending             /* 73 */
	.long __asm32_sysenter_sethostname            /* 74 */
	.long __asm32_sysenter_setrlimit              /* 75 */
	.long __asm32_sysenter_getrlimit              /* 76 */
	.long __asm32_sysenter_getrusage              /* 77 */
	.long __asm32_sysenter_gettimeofday           /* 78 */
	.long __asm32_sysenter_settimeofday           /* 79 */
	.long __asm32_sysenter_getgroups              /* 80 */
	.long __asm32_sysenter_setgroups              /* 81 */
	.long __asm32_sysenter_select                 /* 82 */
	.long __asm32_sysenter_symlink                /* 83 */
	.long __asm32_sysenter_linux_oldlstat         /* 84 */
	.long __asm32_sysenter_readlink               /* 85 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_swapon                 /* 87 */
	.long __asm32_sysenter_reboot                 /* 88 */
	.long __asm32_sysenter_readdir                /* 89 */
	.long __asm32_sysenter_mmap                   /* 90 */
	.long __asm32_sysenter_munmap                 /* 91 */
	.long __asm32_sysenter_truncate               /* 92 */
	.long __asm32_sysenter_ftruncate              /* 93 */
	.long __asm32_sysenter_fchmod                 /* 94 */
	.long __asm32_sysenter_fchown                 /* 95 */
	.long __asm32_sysenter_getpriority            /* 96 */
	.long __asm32_sysenter_setpriority            /* 97 */
	.long __asm32_sysenter_profil                 /* 98 */
	.long __asm32_sysenter_statfs                 /* 99 */
	.long __asm32_sysenter_fstatfs                /* 100 */
	.long __asm32_sysenter_ioperm                 /* 101 */
	.long __asm32_sysenter_socketcall             /* 102 */
	.long __asm32_sysenter_syslog                 /* 103 */
	.long __asm32_sysenter_setitimer              /* 104 */
	.long __asm32_sysenter_getitimer              /* 105 */
	.long __asm32_sysenter_linux_stat32           /* 106 */
	.long __asm32_sysenter_linux_lstat32          /* 107 */
	.long __asm32_sysenter_linux_fstat32          /* 108 */
	.long __asm32_sysenter_olduname               /* 109 */
	.long __asm32_sysenter_iopl                   /* 110 */
	.long __asm32_sysenter_vhangup                /* 111 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_wait4                  /* 114 */
	.long __asm32_sysenter_swapoff                /* 115 */
	.long __asm32_sysenter_sysinfo                /* 116 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_fsync                  /* 118 */
	.long __asm32_sysenter_sigreturn              /* 119 */
	.long __asm32_sysenter_clone                  /* 120 */
	.long __asm32_sysenter_setdomainname          /* 121 */
	.long __asm32_sysenter_uname                  /* 122 */
	.long __asm32_sysenter_modify_ldt             /* 123 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_mprotect               /* 125 */
	.long __asm32_sysenter_sigprocmask            /* 126 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_getpgid                /* 132 */
	.long __asm32_sysenter_fchdir                 /* 133 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_setfsuid               /* 138 */
	.long __asm32_sysenter_setfsgid               /* 139 */
	.long __asm32_sysenter__llseek                /* 140 */
	.long __asm32_sysenter_getdents               /* 141 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_flock                  /* 143 */
	.long __asm32_sysenter_msync                  /* 144 */
	.long __asm32_sysenter_readv                  /* 145 */
	.long __asm32_sysenter_writev                 /* 146 */
	.long __asm32_sysenter_getsid                 /* 147 */
	.long __asm32_sysenter_fdatasync              /* 148 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_mlock                  /* 150 */
	.long __asm32_sysenter_munlock                /* 151 */
	.long __asm32_sysenter_mlockall               /* 152 */
	.long __asm32_sysenter_munlockall             /* 153 */
	.long __asm32_sysenter_sched_setparam         /* 154 */
	.long __asm32_sysenter_sched_getparam         /* 155 */
	.long __asm32_sysenter_sched_setscheduler     /* 156 */
	.long __asm32_sysenter_sched_getscheduler     /* 157 */
	.long __asm32_sysenter_sched_yield            /* 158 */
	.long __asm32_sysenter_sched_get_priority_max /* 159 */
	.long __asm32_sysenter_sched_get_priority_min /* 160 */
	.long __asm32_sysenter_sched_rr_get_interval  /* 161 */
	.long __asm32_sysenter_nanosleep              /* 162 */
	.long __asm32_sysenter_mremap                 /* 163 */
	.long __asm32_sysenter_setresuid              /* 164 */
	.long __asm32_sysenter_getresuid              /* 165 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_poll                   /* 168 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_setresgid              /* 170 */
	.long __asm32_sysenter_getresgid              /* 171 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_rt_sigaction           /* 174 */
	.long __asm32_sysenter_rt_sigprocmask         /* 175 */
	.long __asm32_sysenter_rt_sigpending          /* 176 */
	.long __asm32_sysenter_rt_sigtimedwait        /* 177 */
	.long __asm32_sysenter_rt_sigqueueinfo        /* 178 */
	.long __asm32_sysenter_rt_sigsuspend          /* 179 */
	.long __asm32_sysenter_pread64                /* 180 */
	.long __asm32_sysenter_pwrite64               /* 181 */
	.long __asm32_sysenter_chown                  /* 182 */
	.long __asm32_sysenter_getcwd                 /* 183 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_sigaltstack            /* 186 */
	.long __asm32_sysenter_sendfile               /* 187 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_vfork                  /* 190 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_mmap2                  /* 192 */
	.long __asm32_sysenter_truncate64             /* 193 */
	.long __asm32_sysenter_ftruncate64            /* 194 */
	.long __asm32_sysenter_linux_stat64           /* 195 */
	.long __asm32_sysenter_linux_lstat64          /* 196 */
	.long __asm32_sysenter_linux_fstat64          /* 197 */
	.long __asm32_sysenter_lchown32               /* 198 */
	.long __asm32_sysenter_getuid32               /* 199 */
	.long __asm32_sysenter_getgid32               /* 200 */
	.long __asm32_sysenter_geteuid32              /* 201 */
	.long __asm32_sysenter_getegid32              /* 202 */
	.long __asm32_sysenter_setreuid32             /* 203 */
	.long __asm32_sysenter_setregid32             /* 204 */
	.long __asm32_sysenter_getgroups32            /* 205 */
	.long __asm32_sysenter_setgroups32            /* 206 */
	.long __asm32_sysenter_fchown32               /* 207 */
	.long __asm32_sysenter_setresuid32            /* 208 */
	.long __asm32_sysenter_getresuid32            /* 209 */
	.long __asm32_sysenter_setresgid32            /* 210 */
	.long __asm32_sysenter_getresgid32            /* 211 */
	.long __asm32_sysenter_chown32                /* 212 */
	.long __asm32_sysenter_setuid32               /* 213 */
	.long __asm32_sysenter_setgid32               /* 214 */
	.long __asm32_sysenter_setfsuid32             /* 215 */
	.long __asm32_sysenter_setfsgid32             /* 216 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_mincore                /* 218 */
	.long __asm32_sysenter_madvise                /* 219 */
	.long __asm32_sysenter_getdents64             /* 220 */
	.long __asm32_sysenter_fcntl64                /* 221 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_gettid                 /* 224 */
	.long __asm32_sysenter_readahead              /* 225 */
	.long __asm32_sysenter_setxattr               /* 226 */
	.long __asm32_sysenter_lsetxattr              /* 227 */
	.long __asm32_sysenter_fsetxattr              /* 228 */
	.long __asm32_sysenter_getxattr               /* 229 */
	.long __asm32_sysenter_lgetxattr              /* 230 */
	.long __asm32_sysenter_fgetxattr              /* 231 */
	.long __asm32_sysenter_listxattr              /* 232 */
	.long __asm32_sysenter_llistxattr             /* 233 */
	.long __asm32_sysenter_flistxattr             /* 234 */
	.long __asm32_sysenter_removexattr            /* 235 */
	.long __asm32_sysenter_lremovexattr           /* 236 */
	.long __asm32_sysenter_fremovexattr           /* 237 */
	.long __asm32_sysenter_tkill                  /* 238 */
	.long __asm32_sysenter_sendfile64             /* 239 */
	.long __asm32_sysenter_futex                  /* 240 */
	.long __asm32_sysenter_sched_setaffinity      /* 241 */
	.long __asm32_sysenter_sched_getaffinity      /* 242 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_exit_group             /* 252 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_epoll_create           /* 254 */
	.long __asm32_sysenter_epoll_ctl              /* 255 */
	.long __asm32_sysenter_epoll_wait             /* 256 */
	.long __asm32_sysenter_remap_file_pages       /* 257 */
	.long __asm32_sysenter_set_tid_address        /* 258 */
	.long __asm32_sysenter_timer_create           /* 259 */
	.long __asm32_sysenter_timer_settime          /* 260 */
	.long __asm32_sysenter_timer_gettime          /* 261 */
	.long __asm32_sysenter_timer_getoverrun       /* 262 */
	.long __asm32_sysenter_timer_delete           /* 263 */
	.long __asm32_sysenter_clock_settime          /* 264 */
	.long __asm32_sysenter_clock_gettime          /* 265 */
	.long __asm32_sysenter_clock_getres           /* 266 */
	.long __asm32_sysenter_clock_nanosleep        /* 267 */
	.long __asm32_sysenter_statfs64               /* 268 */
	.long __asm32_sysenter_fstatfs64              /* 269 */
	.long __asm32_sysenter_tgkill                 /* 270 */
	.long __asm32_sysenter_utimes                 /* 271 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_waitid                 /* 284 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_ioprio_set             /* 289 */
	.long __asm32_sysenter_ioprio_get             /* 290 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_openat                 /* 295 */
	.long __asm32_sysenter_mkdirat                /* 296 */
	.long __asm32_sysenter_mknodat                /* 297 */
	.long __asm32_sysenter_fchownat               /* 298 */
	.long __asm32_sysenter_futimesat              /* 299 */
	.long __asm32_sysenter_linux_fstatat64        /* 300 */
	.long __asm32_sysenter_unlinkat               /* 301 */
	.long __asm32_sysenter_renameat               /* 302 */
	.long __asm32_sysenter_linkat                 /* 303 */
	.long __asm32_sysenter_symlinkat              /* 304 */
	.long __asm32_sysenter_readlinkat             /* 305 */
	.long __asm32_sysenter_fchmodat               /* 306 */
	.long __asm32_sysenter_faccessat              /* 307 */
	.long __asm32_sysenter_pselect6               /* 308 */
	.long __asm32_sysenter_ppoll                  /* 309 */
	.long __asm32_sysenter_unshare                /* 310 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_splice                 /* 313 */
	.long __asm32_sysenter_sync_file_range        /* 314 */
	.long __asm32_sysenter_tee                    /* 315 */
	.long __asm32_sysenter_vmsplice               /* 316 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_getcpu                 /* 318 */
	.long __asm32_sysenter_epoll_pwait            /* 319 */
	.long __asm32_sysenter_utimensat              /* 320 */
	.long __asm32_sysenter_signalfd               /* 321 */
	.long __asm32_sysenter_timerfd_create         /* 322 */
	.long __asm32_sysenter_eventfd                /* 323 */
	.long __asm32_sysenter_fallocate              /* 324 */
	.long __asm32_sysenter_timerfd_settime        /* 325 */
	.long __asm32_sysenter_timerfd_gettime        /* 326 */
	.long __asm32_sysenter_signalfd4              /* 327 */
	.long __asm32_sysenter_eventfd2               /* 328 */
	.long __asm32_sysenter_epoll_create1          /* 329 */
	.long __asm32_sysenter_dup3                   /* 330 */
	.long __asm32_sysenter_pipe2                  /* 331 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_preadv                 /* 333 */
	.long __asm32_sysenter_pwritev                /* 334 */
	.long __asm32_sysenter_rt_tgsigqueueinfo      /* 335 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_recvmmsg               /* 337 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_prlimit64              /* 340 */
	.long __asm32_sysenter_name_to_handle_at      /* 341 */
	.long __asm32_sysenter_open_by_handle_at      /* 342 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_syncfs                 /* 344 */
	.long __asm32_sysenter_sendmmsg               /* 345 */
	.long __asm32_sysenter_setns                  /* 346 */
	.long __asm32_sysenter_process_vm_readv       /* 347 */
	.long __asm32_sysenter_process_vm_writev      /* 348 */
	.long __asm32_sysenter_kcmp                   /* 349 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_renameat2              /* 353 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_execveat               /* 358 */
	.long __asm32_sysenter_socket                 /* 359 */
	.long __asm32_sysenter_socketpair             /* 360 */
	.long __asm32_sysenter_bind                   /* 361 */
	.long __asm32_sysenter_connect                /* 362 */
	.long __asm32_sysenter_listen                 /* 363 */
	.long __asm32_sysenter_accept4                /* 364 */
	.long __asm32_sysenter_getsockopt             /* 365 */
	.long __asm32_sysenter_setsockopt             /* 366 */
	.long __asm32_sysenter_getsockname            /* 367 */
	.long __asm32_sysenter_getpeername            /* 368 */
	.long __asm32_sysenter_sendto                 /* 369 */
	.long __asm32_sysenter_sendmsg                /* 370 */
	.long __asm32_sysenter_recvfrom               /* 371 */
	.long __asm32_sysenter_recvmsg                /* 372 */
	.long __asm32_sysenter_shutdown               /* 373 */
END(__asm32_syscallrouter_sysenter)


PUBLIC_OBJECT(__asm32_exsyscallrouter_sysenter)
	.long __asm32_sysenter_hop                     /* 0x80000001 */
	.long __asm32_sysenter_hopf                    /* 0x80000002 */
	.long __asm32_sysenter_readf                   /* 0x80000003 */
	.long __asm32_sysenter_writef                  /* 0x80000004 */
	.long __asm32_sysenter_detach                  /* 0x80000005 */
	.long __asm32_sysenter_getdrives               /* 0x80000006 */
	.long __asm32_sysenter_frealpath4              /* 0x80000007 */
	.long __asm32_sysenter_frealpathat             /* 0x80000008 */
	.long __asm32_sysenter_rpc_schedule            /* 0x80000009 */
	.long __asm32_sysenter_sysctl                  /* 0x8000000a */
	.long __asm32_sysenter_openpty                 /* 0x8000000b */
	.long __asm32_sysenter_fchdirat                /* 0x8000000c */
	.long __asm32_sysenter_time64                  /* 0x8000000d */
	.long __asm32_sysenter_set_exception_handler   /* 0x8000000e */
	.long __asm32_sysenter_get_exception_handler   /* 0x8000000f */
	.long __asm32_sysenter_set_library_listdef     /* 0x80000010 */
	.long __asm32_sysenter_debugtrap               /* 0x80000011 */
	.long __asm32_sysenter_lfutex                  /* 0x80000012 */
	.long __asm32_sysenter_lseek64                 /* 0x80000013 */
	.long __asm32_sysenter_lfutexexpr              /* 0x80000014 */
	.long __asm32_sysenter_lfutexlockexpr          /* 0x80000015 */
	.long __asm32_sysenter_mktty                   /* 0x80000016 */
	.long __asm32_sysenter_raiseat                 /* 0x80000017 */
	.long __asm32_sysenter_coredump                /* 0x80000018 */
	.long __asm32_sysenter_stime64                 /* 0x80000019 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_utime64                 /* 0x8000001e */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_ioctlf                  /* 0x80000036 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_fsmode                  /* 0x8000003c */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_gettimeofday64          /* 0x8000004e */
	.long __asm32_sysenter_settimeofday64          /* 0x8000004f */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_select64                /* 0x80000052 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_maplibrary              /* 0x80000056 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_setitimer64             /* 0x80000068 */
	.long __asm32_sysenter_getitimer64             /* 0x80000069 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_kreaddir                /* 0x8000008d */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_readvf                  /* 0x80000091 */
	.long __asm32_sysenter_writevf                 /* 0x80000092 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_rpc_service             /* 0x8000009e */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_sched_rr_get_interval64 /* 0x800000a1 */
	.long __asm32_sysenter_nanosleep64             /* 0x800000a2 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_rt_sigtimedwait64       /* 0x800000b1 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_pread64f                /* 0x800000b4 */
	.long __asm32_sysenter_pwrite64f               /* 0x800000b5 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_kstat                   /* 0x800000c3 */
	.long __asm32_sysenter_klstat                  /* 0x800000c4 */
	.long __asm32_sysenter_kfstat                  /* 0x800000c5 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_kreaddirf               /* 0x800000dc */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_timer_settime64         /* 0x80000104 */
	.long __asm32_sysenter_timer_gettime64         /* 0x80000105 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_clock_settime64         /* 0x80000108 */
	.long __asm32_sysenter_clock_gettime64         /* 0x80000109 */
	.long __asm32_sysenter_clock_getres64          /* 0x8000010a */
	.long __asm32_sysenter_clock_nanosleep64       /* 0x8000010b */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_utimes64                /* 0x8000010f */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_fmkdirat                /* 0x80000128 */
	.long __asm32_sysenter_fmknodat                /* 0x80000129 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_futimesat64             /* 0x8000012b */
	.long __asm32_sysenter_kfstatat                /* 0x8000012c */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_frenameat               /* 0x8000012e */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_fsymlinkat              /* 0x80000130 */
	.long __asm32_sysenter_freadlinkat             /* 0x80000131 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_pselect6_64             /* 0x80000134 */
	.long __asm32_sysenter_ppoll64                 /* 0x80000135 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_utimensat64             /* 0x80000140 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_fallocate64             /* 0x80000144 */
	.long __asm32_sysenter_timerfd_settime64       /* 0x80000145 */
	.long __asm32_sysenter_timerfd_gettime64       /* 0x80000146 */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_preadvf                 /* 0x8000014d */
	.long __asm32_sysenter_pwritevf                /* 0x8000014e */
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_invalid
	.long __asm32_sysenter_recvmmsg64              /* 0x80000151 */
END(__asm32_exsyscallrouter_sysenter)


/****************************************************************************/
/* 32-bit System call router for high-level C-implementations               */
/****************************************************************************/
.section .rodata.x86.syscall32.c_router
PUBLIC_OBJECT(__c32_syscallrouter)
	.long sys_invalid0
	.long sys_exit                   /* 1 */
	.long sys_fork                   /* 2 */
	.long sys_read                   /* 3 */
	.long sys_write                  /* 4 */
	.long sys_open                   /* 5 */
	.long sys_close                  /* 6 */
	.long sys_waitpid                /* 7 */
	.long sys_creat                  /* 8 */
	.long sys_link                   /* 9 */
	.long sys_unlink                 /* 10 */
	.long sys_execve                 /* 11 */
	.long sys_chdir                  /* 12 */
	.long sys_time                   /* 13 */
	.long sys_mknod                  /* 14 */
	.long sys_chmod                  /* 15 */
	.long sys_lchown                 /* 16 */
	.long sys_invalid0
	.long sys_linux_oldstat          /* 18 */
	.long sys_lseek                  /* 19 */
	.long sys_getpid                 /* 20 */
	.long sys_mount                  /* 21 */
	.long sys_umount                 /* 22 */
	.long sys_setuid                 /* 23 */
	.long sys_getuid                 /* 24 */
	.long sys_stime                  /* 25 */
	.long sys_ptrace                 /* 26 */
	.long sys_alarm                  /* 27 */
	.long sys_linux_oldfstat         /* 28 */
	.long sys_pause                  /* 29 */
	.long sys_utime                  /* 30 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_access                 /* 33 */
	.long sys_nice                   /* 34 */
	.long sys_ftime                  /* 35 */
	.long sys_sync                   /* 36 */
	.long sys_kill                   /* 37 */
	.long sys_rename                 /* 38 */
	.long sys_mkdir                  /* 39 */
	.long sys_rmdir                  /* 40 */
	.long sys_dup                    /* 41 */
	.long sys_pipe                   /* 42 */
	.long sys_times                  /* 43 */
	.long sys_invalid0
	.long sys_brk                    /* 45 */
	.long sys_setgid                 /* 46 */
	.long sys_getgid                 /* 47 */
	.long sys_signal                 /* 48 */
	.long sys_geteuid                /* 49 */
	.long sys_getegid                /* 50 */
	.long sys_acct                   /* 51 */
	.long sys_umount2                /* 52 */
	.long sys_invalid0
	.long sys_ioctl                  /* 54 */
	.long sys_fcntl                  /* 55 */
	.long sys_invalid0
	.long sys_setpgid                /* 57 */
	.long sys_invalid0
	.long sys_oldolduname            /* 59 */
	.long sys_umask                  /* 60 */
	.long sys_chroot                 /* 61 */
	.long sys_ustat                  /* 62 */
	.long sys_dup2                   /* 63 */
	.long sys_getppid                /* 64 */
	.long sys_getpgrp                /* 65 */
	.long sys_setsid                 /* 66 */
	.long sys_sigaction              /* 67 */
	.long sys_sgetmask               /* 68 */
	.long sys_ssetmask               /* 69 */
	.long sys_setreuid               /* 70 */
	.long sys_setregid               /* 71 */
	.long sys_sigsuspend             /* 72 */
	.long sys_sigpending             /* 73 */
	.long sys_sethostname            /* 74 */
	.long sys_setrlimit              /* 75 */
	.long sys_getrlimit              /* 76 */
	.long sys_getrusage              /* 77 */
	.long sys_gettimeofday           /* 78 */
	.long sys_settimeofday           /* 79 */
	.long sys_getgroups              /* 80 */
	.long sys_setgroups              /* 81 */
	.long sys_select                 /* 82 */
	.long sys_symlink                /* 83 */
	.long sys_linux_oldlstat         /* 84 */
	.long sys_readlink               /* 85 */
	.long sys_invalid0
	.long sys_swapon                 /* 87 */
	.long sys_reboot                 /* 88 */
	.long sys_readdir                /* 89 */
	.long sys_mmap                   /* 90 */
	.long sys_munmap                 /* 91 */
	.long sys_truncate               /* 92 */
	.long sys_ftruncate              /* 93 */
	.long sys_fchmod                 /* 94 */
	.long sys_fchown                 /* 95 */
	.long sys_getpriority            /* 96 */
	.long sys_setpriority            /* 97 */
	.long sys_profil                 /* 98 */
	.long sys_statfs                 /* 99 */
	.long sys_fstatfs                /* 100 */
	.long sys_ioperm                 /* 101 */
	.long sys_socketcall             /* 102 */
	.long sys_syslog                 /* 103 */
	.long sys_setitimer              /* 104 */
	.long sys_getitimer              /* 105 */
	.long sys_linux_stat32           /* 106 */
	.long sys_linux_lstat32          /* 107 */
	.long sys_linux_fstat32          /* 108 */
	.long sys_olduname               /* 109 */
	.long sys_iopl                   /* 110 */
	.long sys_vhangup                /* 111 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_wait4                  /* 114 */
	.long sys_swapoff                /* 115 */
	.long sys_sysinfo                /* 116 */
	.long sys_invalid0
	.long sys_fsync                  /* 118 */
	.long sys_sigreturn              /* 119 */
	.long sys_clone                  /* 120 */
	.long sys_setdomainname          /* 121 */
	.long sys_uname                  /* 122 */
	.long sys_modify_ldt             /* 123 */
	.long sys_invalid0
	.long sys_mprotect               /* 125 */
	.long sys_sigprocmask            /* 126 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_getpgid                /* 132 */
	.long sys_fchdir                 /* 133 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_setfsuid               /* 138 */
	.long sys_setfsgid               /* 139 */
	.long sys__llseek                /* 140 */
	.long sys_getdents               /* 141 */
	.long sys_invalid0
	.long sys_flock                  /* 143 */
	.long sys_msync                  /* 144 */
	.long sys_readv                  /* 145 */
	.long sys_writev                 /* 146 */
	.long sys_getsid                 /* 147 */
	.long sys_fdatasync              /* 148 */
	.long sys_invalid0
	.long sys_mlock                  /* 150 */
	.long sys_munlock                /* 151 */
	.long sys_mlockall               /* 152 */
	.long sys_munlockall             /* 153 */
	.long sys_sched_setparam         /* 154 */
	.long sys_sched_getparam         /* 155 */
	.long sys_sched_setscheduler     /* 156 */
	.long sys_sched_getscheduler     /* 157 */
	.long sys_sched_yield            /* 158 */
	.long sys_sched_get_priority_max /* 159 */
	.long sys_sched_get_priority_min /* 160 */
	.long sys_sched_rr_get_interval  /* 161 */
	.long sys_nanosleep              /* 162 */
	.long sys_mremap                 /* 163 */
	.long sys_setresuid              /* 164 */
	.long sys_getresuid              /* 165 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_poll                   /* 168 */
	.long sys_invalid0
	.long sys_setresgid              /* 170 */
	.long sys_getresgid              /* 171 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_rt_sigaction           /* 174 */
	.long sys_rt_sigprocmask         /* 175 */
	.long sys_rt_sigpending          /* 176 */
	.long sys_rt_sigtimedwait        /* 177 */
	.long sys_rt_sigqueueinfo        /* 178 */
	.long sys_rt_sigsuspend          /* 179 */
	.long sys_pread64                /* 180 */
	.long sys_pwrite64               /* 181 */
	.long sys_chown                  /* 182 */
	.long sys_getcwd                 /* 183 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_sigaltstack            /* 186 */
	.long sys_sendfile               /* 187 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_vfork                  /* 190 */
	.long sys_invalid0
	.long sys_mmap2                  /* 192 */
	.long sys_truncate64             /* 193 */
	.long sys_ftruncate64            /* 194 */
	.long sys_linux_stat64           /* 195 */
	.long sys_linux_lstat64          /* 196 */
	.long sys_linux_fstat64          /* 197 */
	.long sys_lchown32               /* 198 */
	.long sys_getuid32               /* 199 */
	.long sys_getgid32               /* 200 */
	.long sys_geteuid32              /* 201 */
	.long sys_getegid32              /* 202 */
	.long sys_setreuid32             /* 203 */
	.long sys_setregid32             /* 204 */
	.long sys_getgroups32            /* 205 */
	.long sys_setgroups32            /* 206 */
	.long sys_fchown32               /* 207 */
	.long sys_setresuid32            /* 208 */
	.long sys_getresuid32            /* 209 */
	.long sys_setresgid32            /* 210 */
	.long sys_getresgid32            /* 211 */
	.long sys_chown32                /* 212 */
	.long sys_setuid32               /* 213 */
	.long sys_setgid32               /* 214 */
	.long sys_setfsuid32             /* 215 */
	.long sys_setfsgid32             /* 216 */
	.long sys_invalid0
	.long sys_mincore                /* 218 */
	.long sys_madvise                /* 219 */
	.long sys_getdents64             /* 220 */
	.long sys_fcntl64                /* 221 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_gettid                 /* 224 */
	.long sys_readahead              /* 225 */
	.long sys_setxattr               /* 226 */
	.long sys_lsetxattr              /* 227 */
	.long sys_fsetxattr              /* 228 */
	.long sys_getxattr               /* 229 */
	.long sys_lgetxattr              /* 230 */
	.long sys_fgetxattr              /* 231 */
	.long sys_listxattr              /* 232 */
	.long sys_llistxattr             /* 233 */
	.long sys_flistxattr             /* 234 */
	.long sys_removexattr            /* 235 */
	.long sys_lremovexattr           /* 236 */
	.long sys_fremovexattr           /* 237 */
	.long sys_tkill                  /* 238 */
	.long sys_sendfile64             /* 239 */
	.long sys_futex                  /* 240 */
	.long sys_sched_setaffinity      /* 241 */
	.long sys_sched_getaffinity      /* 242 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_exit_group             /* 252 */
	.long sys_invalid0
	.long sys_epoll_create           /* 254 */
	.long sys_epoll_ctl              /* 255 */
	.long sys_epoll_wait             /* 256 */
	.long sys_remap_file_pages       /* 257 */
	.long sys_set_tid_address        /* 258 */
	.long sys_timer_create           /* 259 */
	.long sys_timer_settime          /* 260 */
	.long sys_timer_gettime          /* 261 */
	.long sys_timer_getoverrun       /* 262 */
	.long sys_timer_delete           /* 263 */
	.long sys_clock_settime          /* 264 */
	.long sys_clock_gettime          /* 265 */
	.long sys_clock_getres           /* 266 */
	.long sys_clock_nanosleep        /* 267 */
	.long sys_statfs64               /* 268 */
	.long sys_fstatfs64              /* 269 */
	.long sys_tgkill                 /* 270 */
	.long sys_utimes                 /* 271 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_waitid                 /* 284 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_ioprio_set             /* 289 */
	.long sys_ioprio_get             /* 290 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_openat                 /* 295 */
	.long sys_mkdirat                /* 296 */
	.long sys_mknodat                /* 297 */
	.long sys_fchownat               /* 298 */
	.long sys_futimesat              /* 299 */
	.long sys_linux_fstatat64        /* 300 */
	.long sys_unlinkat               /* 301 */
	.long sys_renameat               /* 302 */
	.long sys_linkat                 /* 303 */
	.long sys_symlinkat              /* 304 */
	.long sys_readlinkat             /* 305 */
	.long sys_fchmodat               /* 306 */
	.long sys_faccessat              /* 307 */
	.long sys_pselect6               /* 308 */
	.long sys_ppoll                  /* 309 */
	.long sys_unshare                /* 310 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_splice                 /* 313 */
	.long sys_sync_file_range        /* 314 */
	.long sys_tee                    /* 315 */
	.long sys_vmsplice               /* 316 */
	.long sys_invalid0
	.long sys_getcpu                 /* 318 */
	.long sys_epoll_pwait            /* 319 */
	.long sys_utimensat              /* 320 */
	.long sys_signalfd               /* 321 */
	.long sys_timerfd_create         /* 322 */
	.long sys_eventfd                /* 323 */
	.long sys_fallocate              /* 324 */
	.long sys_timerfd_settime        /* 325 */
	.long sys_timerfd_gettime        /* 326 */
	.long sys_signalfd4              /* 327 */
	.long sys_eventfd2               /* 328 */
	.long sys_epoll_create1          /* 329 */
	.long sys_dup3                   /* 330 */
	.long sys_pipe2                  /* 331 */
	.long sys_invalid0
	.long sys_preadv                 /* 333 */
	.long sys_pwritev                /* 334 */
	.long sys_rt_tgsigqueueinfo      /* 335 */
	.long sys_invalid0
	.long sys_recvmmsg               /* 337 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_prlimit64              /* 340 */
	.long sys_name_to_handle_at      /* 341 */
	.long sys_open_by_handle_at      /* 342 */
	.long sys_invalid0
	.long sys_syncfs                 /* 344 */
	.long sys_sendmmsg               /* 345 */
	.long sys_setns                  /* 346 */
	.long sys_process_vm_readv       /* 347 */
	.long sys_process_vm_writev      /* 348 */
	.long sys_kcmp                   /* 349 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_renameat2              /* 353 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_execveat               /* 358 */
	.long sys_socket                 /* 359 */
	.long sys_socketpair             /* 360 */
	.long sys_bind                   /* 361 */
	.long sys_connect                /* 362 */
	.long sys_listen                 /* 363 */
	.long sys_accept4                /* 364 */
	.long sys_getsockopt             /* 365 */
	.long sys_setsockopt             /* 366 */
	.long sys_getsockname            /* 367 */
	.long sys_getpeername            /* 368 */
	.long sys_sendto                 /* 369 */
	.long sys_sendmsg                /* 370 */
	.long sys_recvfrom               /* 371 */
	.long sys_recvmsg                /* 372 */
	.long sys_shutdown               /* 373 */
END(__c32_syscallrouter)


PUBLIC_OBJECT(__c32_exsyscallrouter)
	.long sys_hop                     /* 0x80000001 */
	.long sys_hopf                    /* 0x80000002 */
	.long sys_readf                   /* 0x80000003 */
	.long sys_writef                  /* 0x80000004 */
	.long sys_detach                  /* 0x80000005 */
	.long sys_getdrives               /* 0x80000006 */
	.long sys_frealpath4              /* 0x80000007 */
	.long sys_frealpathat             /* 0x80000008 */
	.long sys_rpc_schedule            /* 0x80000009 */
	.long sys_sysctl                  /* 0x8000000a */
	.long sys_openpty                 /* 0x8000000b */
	.long sys_fchdirat                /* 0x8000000c */
	.long sys_time64                  /* 0x8000000d */
	.long sys_set_exception_handler   /* 0x8000000e */
	.long sys_get_exception_handler   /* 0x8000000f */
	.long sys_set_library_listdef     /* 0x80000010 */
	.long sys_debugtrap               /* 0x80000011 */
	.long sys_lfutex                  /* 0x80000012 */
	.long sys_lseek64                 /* 0x80000013 */
	.long sys_lfutexexpr              /* 0x80000014 */
	.long sys_lfutexlockexpr          /* 0x80000015 */
	.long sys_mktty                   /* 0x80000016 */
	.long sys_raiseat                 /* 0x80000017 */
	.long sys_coredump                /* 0x80000018 */
	.long sys_stime64                 /* 0x80000019 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_utime64                 /* 0x8000001e */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_ioctlf                  /* 0x80000036 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_fsmode                  /* 0x8000003c */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_gettimeofday64          /* 0x8000004e */
	.long sys_settimeofday64          /* 0x8000004f */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_select64                /* 0x80000052 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_maplibrary              /* 0x80000056 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_setitimer64             /* 0x80000068 */
	.long sys_getitimer64             /* 0x80000069 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_kreaddir                /* 0x8000008d */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_readvf                  /* 0x80000091 */
	.long sys_writevf                 /* 0x80000092 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_rpc_service             /* 0x8000009e */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_sched_rr_get_interval64 /* 0x800000a1 */
	.long sys_nanosleep64             /* 0x800000a2 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_rt_sigtimedwait64       /* 0x800000b1 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_pread64f                /* 0x800000b4 */
	.long sys_pwrite64f               /* 0x800000b5 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_kstat                   /* 0x800000c3 */
	.long sys_klstat                  /* 0x800000c4 */
	.long sys_kfstat                  /* 0x800000c5 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_kreaddirf               /* 0x800000dc */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_timer_settime64         /* 0x80000104 */
	.long sys_timer_gettime64         /* 0x80000105 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_clock_settime64         /* 0x80000108 */
	.long sys_clock_gettime64         /* 0x80000109 */
	.long sys_clock_getres64          /* 0x8000010a */
	.long sys_clock_nanosleep64       /* 0x8000010b */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_utimes64                /* 0x8000010f */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_fmkdirat                /* 0x80000128 */
	.long sys_fmknodat                /* 0x80000129 */
	.long sys_invalid0
	.long sys_futimesat64             /* 0x8000012b */
	.long sys_kfstatat                /* 0x8000012c */
	.long sys_invalid0
	.long sys_frenameat               /* 0x8000012e */
	.long sys_invalid0
	.long sys_fsymlinkat              /* 0x80000130 */
	.long sys_freadlinkat             /* 0x80000131 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_pselect6_64             /* 0x80000134 */
	.long sys_ppoll64                 /* 0x80000135 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_utimensat64             /* 0x80000140 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_fallocate64             /* 0x80000144 */
	.long sys_timerfd_settime64       /* 0x80000145 */
	.long sys_timerfd_gettime64       /* 0x80000146 */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_invalid0
	.long sys_preadvf                 /* 0x8000014d */
	.long sys_pwritevf                /* 0x8000014e */
	.long sys_invalid0
	.long sys_invalid0
	.long sys_recvmmsg64              /* 0x80000151 */
END(__c32_exsyscallrouter)


